#include <stdio.h>
#include <ctype.h>

char map[35] = {
    'A', 0x0, 0x0, 0x0, '3',
    0x0, 0x0, 'H', 'I', 'L',
    0x0, 'J', 'M', 0x0, 'O',
    0x0, 0x0, 0x0, '2', 'T',
    'U', 'V', 'W', 'X', 'Y',
    '5', '1', 'S', 'E', 0x0,
    'Z', 0x0, 0x0, '8', 0x0
};

int tra (int c)
{
    if (isalpha(c))
        return map[c - 'A'];
    else
        return map[c - '1' + 26];
}

int mipa_check (char *s)
{
    char *p;
    int pa = 1, mi = 2;

    for (p=s; *p; p++)
        ;
    p--;

    for (; s<=p; s++, p--)
    {
        if (*s != *p)
            pa = 0;
        if (tra(*s) != *p ||
            tra(*p) != *s)
            mi = 0;
    }

    return pa | mi;
}

int main ()
{
    char s[100];

    while (!feof(stdin) && gets(s)) 
    {
        if (!s[0])
            break;

        switch (mipa_check(s))
        {
            case 0:
                printf("%s -- is not a palindrome.\n\n", s);
                break;
            case 1:
                printf("%s -- is a regular palindrome.\n\n", s);
                break;
            case 2:
                printf("%s -- is a mirrored string.\n\n", s);
                break;
            case 3:
                printf("%s -- is a mirrored palindrome.\n\n", s);
                break;
        }
    }

    return 0;
}
        

