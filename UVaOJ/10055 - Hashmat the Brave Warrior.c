#include <stdio.h>

int main()
{
    long long wo, di;
    while (scanf("%lld%lld", &wo, &di) == 2)
        printf("%lld\n", di>wo ? di-wo : wo-di);
    return 0;
}
