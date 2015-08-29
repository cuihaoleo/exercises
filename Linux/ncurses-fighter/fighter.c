#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <time.h>
#include <glib.h>
#include <sys/time.h>

#define INFO_WIN_HEIGHT 3
#define REFRESH_MS 10

struct js_event {
	unsigned int time;
	short value;
	unsigned char type;
	unsigned char number;
};

typedef struct {
    double x, y;  // screen coordinate in float
    double vx, vy;  // line/ms
    double health;
    char c;
    int last_update;
} fighter;

typedef struct {
    int height, width;
    WINDOW *win;
} window;

window info_win, field_win;

GList* tekki, *bullets;
fighter jiki;

int timestamp = 0;
int kills = 0;

#define display_info(format,args...) mvwprintw(info_win.win, 1, 1, format, ##args);

void generate_tekki() {
    static int last_ts = 0;
    // hardcoded!
    if (timestamp - last_ts > 400) {
        fighter tk = {
            .x = field_win.width,
            .y = (rand() / (double)RAND_MAX) * field_win.height,
            .vx = -0.02,
            .vy = 0.00,
            .health = 0.8,
            .c = 'x',
            .last_update = timestamp
        };
        fighter *ptk = malloc(sizeof(fighter));
        *ptk = tk;
        tekki = g_list_append(tekki, ptk);
        last_ts = timestamp;
    }
}

void shoot() {
    static int last_ts = 0;
    // hardcoded!
    if (timestamp - last_ts > 100) {
        fighter tk = {
            .x = jiki.x,
            .y = jiki.y,
            .vx = 0.02,
            .vy = 0.00,
            .health = 0.5,
            .c = '.',
            .last_update = timestamp
        };
        fighter *ptk = malloc(sizeof(fighter));
        *ptk = tk;
        bullets = g_list_append(bullets, ptk);
        last_ts = timestamp;
    }
}

void move_fighter(fighter *ptk) {
    int dt = timestamp - ptk->last_update;
    ptk->x += dt * ptk->vx;
    ptk->y += dt * ptk->vy;
    ptk->last_update = timestamp;
}

void moveback_fighter(fighter *ptk) {
    if (ptk->x < 0)
        ptk->x = 0;
    else if (ptk->x >= field_win.width)
        ptk->x = field_win.width - 1;

    if (ptk->y < 0)
        ptk->y = 0;
    else if (ptk->y >= field_win.height)
        ptk->y = field_win.height - 1;
}

void hide_fighter(fighter *ptk) {
    mvwprintw(field_win.win, ptk->y, ptk->x, " ");
}

void show_fighter(fighter *ptk) {
    mvwprintw(field_win.win, ptk->y, ptk->x, "%c", ptk->c);
}

void free_fighter(fighter *ptk) {
    free(ptk);
}

void apply_action_to_fighters(GList *li, void (*action)(fighter *)) {
    GList *it = NULL;
    for (it = li; it; it = it->next) {
        fighter *ptk = it->data;
        action(ptk);
    }
}

void jiki_colision_check(fighter *ptk) {
    if ((int)ptk->x == (int)jiki.x && (int)ptk->y == (int)jiki.y) {
        double jh = jiki.health;
        jiki.health -= ptk->health;
        ptk->health -= jh;
    }
}

void bullets_colision_check(fighter *bu) {
    GList *it = NULL;
    for (it = tekki; it; it = it->next) {
        fighter *ptk = it->data;
        if ((int)ptk->x == (int)bu->x && \
            (int)ptk->y == (int)bu->y && bu->health > 0.0) {
            ptk->health -= bu->health;
            if ((bu->health = 0.0) <= 0.0) {
                kills += 1;
            }
        }
    }
}

void clean_fighters(GList **li) {
    GList *it = *li;
    while (it) {
        fighter *ptk = it->data;
        GList *nit = it->next;
        if (ptk->x < 0 || ptk->y < 0 || ptk->health <= 0.0) {
            hide_fighter(ptk);
            *li = g_list_delete_link(*li, it);
            free(ptk);
        }
        it = nit;
    }
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;


    int jsfd;
	jsfd = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
    if (jsfd <= 0) {
        exit(-1);
    }

    initscr();
    start_color();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(REFRESH_MS);
    refresh();

    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);

    // initialize window
    info_win.width = max_x,
    info_win.height = INFO_WIN_HEIGHT,
    info_win.win = newwin(INFO_WIN_HEIGHT, max_x, 0, 0);
    field_win.width = max_x,
    field_win.height = max_y-INFO_WIN_HEIGHT,
    field_win.win = newwin(max_y-INFO_WIN_HEIGHT, max_x, INFO_WIN_HEIGHT, 0);
    wrefresh(info_win.win);
    wrefresh(field_win.win);

    // draw border
    box(info_win.win, 0, 0);
    refresh();
    wrefresh(info_win.win);
    wrefresh(field_win.win);

    jiki.health = 1.0;
    jiki.c = 'o';

    bool shooting;
    while (getch() != 'q') {

        // read joystick event
	    struct js_event jse;
        if (read(jsfd, &jse, sizeof(jse)) == sizeof(jse)) {
            if (jse.type == 2 && jse.number == 1) {
                jiki.vy = jse.value / 3276000.0;
            }
            else if (jse.type == 2 && jse.number == 0) {
                jiki.vx = jse.value / 3276000.0;
            }
            else if (jse.type == 1 && jse.number == 0) {
                shooting = jse.value;
            }
        }

        if (shooting) { shoot(); }

        hide_fighter(&jiki);
        move_fighter(&jiki);
        moveback_fighter(&jiki);

        generate_tekki();
        apply_action_to_fighters(tekki, hide_fighter);
        apply_action_to_fighters(tekki, move_fighter);
        apply_action_to_fighters(tekki, show_fighter);
        apply_action_to_fighters(tekki, jiki_colision_check);
        clean_fighters(&tekki);

        apply_action_to_fighters(bullets, hide_fighter);
        apply_action_to_fighters(bullets, move_fighter);
        apply_action_to_fighters(bullets, show_fighter);
        apply_action_to_fighters(bullets, bullets_colision_check);
        clean_fighters(&bullets);
 
        show_fighter(&jiki);
        display_info("Health: %.2lf, Kills: %d", jiki.health, kills);

        wrefresh(info_win.win);
        wrefresh(field_win.win);
        timestamp += REFRESH_MS;

        if (jiki.health <= 0.0) {
            break;
        }
    }

    mvwprintw(field_win.win, 1, 1, "GAME OVER!");
    wrefresh(field_win.win);

    apply_action_to_fighters(bullets, free_fighter);
    g_list_free(bullets);
    apply_action_to_fighters(tekki, free_fighter);
    g_list_free(tekki);

    close(jsfd);
    
    while (getch() != 'q') { 
        ;
    }

    endwin();

    return 0;
}
