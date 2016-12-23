#include <stdio.h>
#include "common.h"

/* Divide by power of two. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
    int hbit = (unsigned)x >> (INT_WIDTH - 1);
    unsigned mask = ((1 << k) - hbit) << (INT_WIDTH - k - 1) << 1;
    unsigned bias = mask >> (INT_WIDTH - k);

    // I assume that int shr is arithmetic
    return ((int)(x + bias) >> k);
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int x = randint();
        int k = randint() % INT_WIDTH;

        if (divide_power2(x, k) != x / (1 << k))
            printf("divide_power2(%d, %d) is wrong!\n", x, k);
    }

    return 0;
}
