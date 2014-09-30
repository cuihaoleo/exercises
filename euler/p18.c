#include <stdio.h>

int main ()
{
    int map[200][200] = {{0}}, dyn[200][200] = {{0}}, i, j, n, max;

    i = 0;
    while (1)
    {
        i++;

        for (j=1; j<=i; j++)
            if (!scanf("%d", &map[i][j]))
                goto outside;
    }

    if (0)
        outside: n = i - 1;

    for (i=1; i<=n; i++)
        for (j=1; j<=i; j++)
            dyn[i][j] = map[i][j] + \
                (dyn[i-1][j] > dyn[i-1][j-1] ? dyn[i-1][j] : dyn[i-1][j-1]);

    max = 0;
    for (i=1; i<=n; i++)
        if (max < dyn[n][i])
            max = dyn[n][i];

    printf("%d\n", max);

    return 0;
}
