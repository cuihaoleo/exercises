#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ct = 0;
    while (1)
    {
        long long a;
        int l, step = 1;

        scanf("%lld%d", &a, &l);
        if (a < 0)
            break;

        printf("Case %d: A = %lld, limit = %d, ", ++ct, a, l);
        while (a!=1)
        {
            a = a%2 ? a*3+1 : a/2;
            if (a <= l)
                step++;
            else
                break;
        }

        printf("number of terms = %d\n", step);
    }

    return 0;
}
