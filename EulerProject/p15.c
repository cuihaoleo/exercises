#include <stdio.h>

int main ()
{
    long long grid[22][22] = {{0, 1}};
    int i, j;

    for (i=1; i<=21; i++)
        for (j=1; j<=21; j++)
            grid[i][j] = grid[i-1][j] + grid[i][j-1];

    printf("%lld\n", grid[21][21]);

    return 0;
}

