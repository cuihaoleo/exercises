#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char homepage[] = "http://www.acm.org/";

int main ()
{
    char *li[1000], **p, **lastp;

    li[0] = strdup(homepage);
    lastp = p = li;
    while (1)
    {
        char cmd[8], boo=0;

        scanf("%7s", cmd);

        if (cmd[0] == 'V')
        {
            char url[101];
            scanf("%100s", url);
            //while (p < lastp)
            //    free(lastp--);
            *(++p) = strdup(url);
            lastp = p;
            boo = 1;
        }
        else if (cmd[0] == 'B')
            p>li && (boo=1) && p--;
        else if (cmd[0] == 'F')
            p<lastp && (boo=1) && p++;
        else
            break;

        if (boo)
            printf("%s\n", *p);
        else
            printf("Ignored\n");
    }

    return 0;
}
