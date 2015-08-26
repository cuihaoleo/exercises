#include <stdio.h>

int main ()
{
    long long n, i, max;

    scanf("%lld", &n);

    i = 2;
    while (n > 1)
    {
        if (n % i == 0)
            max = i;

        while (n % i == 0)
            n /= i;

        i++;
    }

    printf("%lld\n", max);

    return 0;
}
    
