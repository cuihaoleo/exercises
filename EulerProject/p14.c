#include <stdio.h>

#define MAX 1000000

long long rec[MAX+1];

long long go (long long n)
{
    if (n<=MAX && rec[n])
        return rec[n];

    long long ans;
    if (n == 1)
        ans = 1;
    else if (n % 2)
        ans = go(n*3+1) + 1;
    else
        ans = go(n/2) + 1;

    if (n<=MAX)
        rec[n] = ans;

    return ans;
}

int main ()
{
    long long i, max=0, maxn;

    for (i=MAX; i>=1; i--)
    {
        go(i);
        if (rec[i] > max)
            max = rec[i], maxn = i;
    }

    printf("%lld\n", maxn);

    return 0;
}

