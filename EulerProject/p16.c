#include <stdio.h>

typedef char byte;

#define MAXLEN 500

int main ()
{
    byte num[MAXLEN+1] = {1};
    int i, j, ans;

    for (i=1; i<=1000; i++)
    {
        int jw = 0;
        for (j=0; j<MAXLEN; j++)
        {
            num[j] = num[j]*2 + jw;
            jw = num[j]/10;
            num[j] %= 10;
        }
    }

    ans = 0;
    for (i=0; i<MAXLEN; i++)
        ans += num[i];

    printf("%d\n", ans);

    return 0;
}
