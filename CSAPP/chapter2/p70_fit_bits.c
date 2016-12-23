#include <stdio.h>
#include "common.h"

/*
 * Return 1 when x can be represented as an n-bit, 2's complement
 * number; 0 otherwise
 * Assume 1 <= n <= w
 */
int fit_bits(int x, int n) {
    unsigned exceed = (unsigned)x >> (n-1);
    unsigned comp_n = (1 << (INT_WIDTH-n+1)) - 1;
    return comp_n == exceed || exceed == 0;
}

int fit_bits_correct(int x, int n) {
    int upper = (1 << (n-1)) - 1;
    int lower = -upper - 1;
    return x <= upper && x >= lower;
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int r = randint();
        int n = randint() % INT_WIDTH + 1;
        if (fit_bits(r, n) != fit_bits_correct(r, n))
            printf("fit_bits(%d, %d) is wrong!\n", r, n);
    }

    return 0;
}
