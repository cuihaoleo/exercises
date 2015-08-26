#include <stdio.h>

int main ()
{
    int di[1000] = {1}, i, ans = 0;

    for (i=2; i<=100; i++)
    {
        int j, jw = 0;

        for (j=0; j<1000; j++)
        {
            di[j] *= i;
            di[j] += jw;
            jw = di[j] / 10;
            di[j] %= 10;
        }
    }

    for (i=0; i<1000; i++)
        ans += di[i];

    printf("%d\n", ans);

    return 0;
}
