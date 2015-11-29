#include <stdio.h>
#include <stdlib.h>

void print_wave (int amp)
{
    int i, j;
    for (i=1; i<=amp; i++)
    {
        for (j=0; j<i; j++)
            putchar('0'+i);
        putchar('\n');
    }

    for (i-=2; i>=1; i--)
    {
        for (j=0; j<i; j++)
            putchar('0'+i);
        putchar('\n');
    }
}

int main()
{
    int n, i;
    scanf("%d", &n);
    for (i=0; i<n; i++)
    {
        int amp, freq, j;
        scanf("%d%d", &amp, &freq);
        for (j=0; j<freq; j++)
        {
            print_wave(amp);
            if (i!=n-1 || j!=freq-1)
                putchar('\n');
        }
    }

    return 0;
}
