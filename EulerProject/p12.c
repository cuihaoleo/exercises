#include <stdio.h>

int howmanyfactors (int n)
{
    int p=2, ans = 1;

    while (n > 1)
    {
        int ct = 0;
        while (n % p == 0)
            n /= p, ct++;
        ans *= ct + 1;
        p++;
    }

    return ans;
}

int main ()
{
    int i=1, n;
    while (howmanyfactors((n = i*(i+1)/2)) <= 500)
        i++;
    printf("%d\n", n);

    return 0;
}
