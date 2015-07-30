#include <stdlib.h>
int countPrimes(int n) {
    int i, ans = 0;
    char *a = malloc((n+1) * sizeof(char));

    for (i=0; i<=n; i++)
        a[n] = 0;

    for (i=2; i<=n; i++)
        if (a[i] == 0) {
            int m;
            ans++;
            for (m=i*2; m<n; m+=i)
                a[m] = 1;
        }

    free(a);
    return ans;    
}
