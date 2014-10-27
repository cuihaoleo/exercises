#include <stdio.h>

int factor_sum (int n)
{
    int ans = 1, i;

    for (i=2; i*i<=n; i++)
        if (n%i == 0)
        {
            ans += i + n/i;
            if (i == n/i)
                ans -= i;
        }

    return ans;
}

int main (int argc, char *argv[])
{
    int a, sum = 0;

    for (a=1; a<=10000; a++)
    {
        int b = factor_sum(a);
        int aa = factor_sum(b);

        if (aa == a && a > b)
        {
            sum += a + b;
            printf("%d %d\n", a, b);
        }
    }

    printf("%d\n", sum);

    return 0;
}

