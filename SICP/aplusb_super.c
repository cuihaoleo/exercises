#include <stdio.h>

int plus (const int sum, const int left)
{
    if (left == 0)
        return sum;
    else
        return plus(sum + 1, left - 1);
}

int main ()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", plus(a, b));
    return 0;
}
