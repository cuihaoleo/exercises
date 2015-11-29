#include <stdio.h>

int main()
{
    char c;
    while ((c = getchar()) != EOF)
        putchar(c == '\n' ? '\n' : c-7);
    return 0;
}
