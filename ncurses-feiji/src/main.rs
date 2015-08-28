extern crate ncurses;
use ncurses::*;

static INFO_WIN_HEIGHT: i32 = 3;

fn draw_borders(win: WINDOW) {
    box_(win, 0, 0);
    wrefresh(win);
}

struct Fighter {
    power: f32,
    life: f32,
    x: f32,
    y: f32,
}

impl Fighter {
    fn draw(&self, win: WINDOW) {
        let mut x = 0;
        let mut y = 0;
        getmaxyx(stdscr, &mut y, &mut x);

        x -= 2;
        y -= 2;

        let fx = (self.x * x as f32).floor() as i32;
        let fy = (self.y * y as f32).floor() as i32;
        mvwprintw(win, fx + 1, fy + 1, "o");
    }
    fn walk(&mut self, x: f32, y: f32) {
        self.x += x;
        self.y += y;
    }
}

fn main() {
    initscr();
    keypad(stdscr, true);
    raw();
    noecho();
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

    let mut max_x = 0;
    let mut max_y = 0;
    getmaxyx(stdscr, &mut max_y, &mut max_x);

    let info_win = newwin(INFO_WIN_HEIGHT, max_x, 0, 0);
    let field_win = newwin(max_y - INFO_WIN_HEIGHT, max_x, INFO_WIN_HEIGHT, 0);
    refresh();

    draw_borders(info_win);
    draw_borders(field_win);

    let mut jiki = Fighter{ power: 1.0, life: 1.0, x: 0.0, y: 0.0 };
    let EXIT = 'q' as i32;
    loop {
        jiki.draw(field_win);
        wrefresh(field_win);

        let mut ch = getch();
        if ch == EXIT {
            break;
        }

        let s = format!("KEY: {}", ch);
        mvwprintw(info_win, 1, 1, &s);
        wrefresh(info_win);

        match ch {
            KEY_UP => {
                jiki.walk(-0.01, 0.0);
            },
            KEY_DOWN => {
                jiki.walk(0.01, 0.0);
            },
            KEY_LEFT => {
                jiki.walk(0.0, -0.01);
            },
            KEY_RIGHT => {
                jiki.walk(0.0, 0.01);
            },
            _ => {
                ;
            }
        }
    }

    endwin();
}
