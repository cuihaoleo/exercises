#include <stdio.h>

void eatline ()
{
    while (getchar() != '\n');
}

int main()
{
    while (1)
    {
        int round, wd[26] = {0}, stroke = 7, chct = 0;
        char c;

        scanf("%d", &round);
        if (round == -1)
            break;
        else
            printf("Round %d\n", round);

        eatline();
        while ((c = getchar()) != '\n')
            if (! wd[c-'a'])
                chct++, wd[c-'a'] = 1;

        while ((c = getchar()) != '\n')
            if (wd[c-'a'] == 1)
            {
                wd[c-'a'] = 2;
                if (--chct == 0)
                {
                    eatline();
                    puts("You win.");
                    goto con;
                }
            }
            else if (wd[c-'a'] == 0)
            {
                if (--stroke == 0)
                {
                    eatline();
                    puts("You lose.");
                    goto con;
                }
            }

        puts("You chickened out.");
con:
        ;
    }
    return 0;
}
