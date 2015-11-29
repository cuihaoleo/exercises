#include <stdio.h>
#include <ctype.h>

int main()
{
    char c, inword = 0, ct = 0;
    while ((c = getchar()) != EOF)
    {
        if (isalpha(c) && !inword)
            inword = 1;
        else if (!isalpha(c) && inword)
            ct++, inword = 0;
        if (c == '\n')
        {
            printf("%d\n", ct);
            ct = 0;
        }
    }
    return 0;
}
