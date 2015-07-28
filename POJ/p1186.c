#include <stdio.h>
#include <stdlib.h>

int pow_int (const int x, int p)
{
    int ans = 1;
    for (; p>0; p--)
        ans *= x;
    return ans;
}

int cmp (const void *pa, const void *pb)
{
    return *(int*)pa - *(int*)pb;
}

int left[4000000], right[4000000];

int main (void)
{
    int k[6]={0}, p[6]={0}, n, m, x[6]={0}, i,
        max[6]={1,1,1,1,1,1};

    scanf("%d%d", &n, &m);
    for (i=0; i<n; i++)
        scanf("%d%d", k+i, p+i);

    for (i=0; i<n; i++)
        max[i]=m;

    left[0] = 0;
    for (x[0]=1; x[0]<=max[0]; x[0]++)
        for (x[1]=1; x[1]<=max[1]; x[1]++)
            for (x[2]=1; x[2]<=max[2]; x[2]++)
            {
                int sum = 0;
                for (i=0; i<3; i++)
                    sum += k[i]*pow_int(x[i], p[i]);

                left[++left[0]] = sum;
            }

    right[0] = 0;
    for (x[3]=1; x[3]<=max[3]; x[3]++)
        for (x[4]=1; x[4]<=max[4]; x[4]++)
            for (x[5]=1; x[5]<=max[5]; x[5]++)
            {
                int sum = 0;
                for (i=3; i<6; i++)
                    sum += k[i]*pow_int(x[i], p[i]);

                right[++right[0]] = -sum;
            }

    qsort(left+1, left[0], sizeof(int), cmp);
    qsort(right+1, right[0], sizeof(int), cmp);

    int p1 = left[0], p2 = right[0], ans = 0;
    while (p1 && p2)
    {
        while (p1 && p2 && left[p1] != right[p2])
            if (left[p1] < right[p2])
                p2--;
            else if (left[p1] > right[p2])
                p1--;

        if (!p1 || !p2)
            break;
        
        int t = left[p1], ct1=0, ct2=0;
        while (left[p1]==t)
            p1--, ct1++;
        while (right[p2]==t)
            p2--, ct2++;
        ans += ct1*ct2;
    }

    printf("%d\n", ans);

    return 0;
}
