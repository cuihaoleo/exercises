#include <stdio.h>
#include "common.h"

int fiveeighths(int x) {
    // assume that int shr is arithmetic
    int sign = (unsigned)x >> (INT_WIDTH - 1);
    int bias = (8 - sign) & 0x07;

    int lowest_3bits = x & 0x07;
    int lowest_3bits_of_4x = (x << 2) & 0x07;

    int sum_3bits = lowest_3bits + lowest_3bits_of_4x + bias;

    return (x >> 3) + (x >> 1) + (sum_3bits >> 3);
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int x = randint();
        if (fiveeighths(x) != (int)(x * 5.0 / 8))
            printf("mul5div8(%d) is wrong!\n", x);
    }

    return 0;
}
