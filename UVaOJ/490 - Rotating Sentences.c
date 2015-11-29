#include <stdio.h>
#include <stdlib.h>

char li[200][200];

int main()
{
    int ct = 0, i = 0;
    while (!feof(stdin) && gets(li[ct]))
        if (li[ct++][0] == '\0')
        {
            ct--;
            break;
        }

    while (1)
    {
        int j, fl=0;

        for (j=ct-1; j>=0; j--)
            if (li[j][i])
            {
                fl = 1;
                break;
            }

        if (!fl)
            break;

        for (j=ct-1; j>=0; j--)
            if (li[j][i])
                putchar(li[j][i]);
            else
                putchar(' ');

        putchar('\n');
        i++;
    }

    return 0;
}
