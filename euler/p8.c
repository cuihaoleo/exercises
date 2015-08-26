#include <stdio.h>
#include <ctype.h>

int main ()
{
    char rec[1000], c;
    int i=0, j;
    long long max=0;

    while ((c = getchar()) != EOF)
        if (isdigit(c))
        {
            rec[i++] = c;

            if (i>12)
            {
                long long mul=1;
                for (j=i-13; j<i; j++)
                    mul *= rec[j]-'0';

                if (mul>max)
                    max = mul;
            }
        }

    printf("%lld\n", max);

    return 0;
}

