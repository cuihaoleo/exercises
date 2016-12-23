#include <stdio.h>
#include "common.h"

int mul5div8(int x) {
    x += x << 2;

    int hbit = (unsigned)x >> (INT_WIDTH - 1);
    int bias = (8 - hbit) & 0x07;

    // assume that int shr is arithmetic
    return (x + bias) >> 3;
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int x = randint();
        if (mul5div8(x) != x * 5 / 8)
            printf("mul5div8(%d) is wrong!\n", x);
    }

    return 0;
}
