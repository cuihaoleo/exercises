#include <stdio.h>
#include <stdint.h>
#include "common.h"

uint32_t signed_high_prod(int32_t a, int32_t b) {
    int64_t expanded_a = a;
    int64_t expanded_b = b;
    return (expanded_a * expanded_b) >> 32;
}

uint32_t unsigned_high_prod_correct(uint32_t a, uint32_t b) {
    uint64_t expanded_a = a;
    uint64_t expanded_b = b;
    return (expanded_a * expanded_b) >> 32;
}

uint32_t unsigned_high_prod(uint32_t x, uint32_t y) {
    uint32_t xhb = (x & 0x7FFFFFFFF) >> 31;
    uint32_t yhb = (y & 0x7FFFFFFFF) >> 31;
    return signed_high_prod(x, y) + x * yhb + y * xhb;
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int a = randint();
        int b = randint();
        if (unsigned_high_prod(a, b) != unsigned_high_prod_correct(a, b))
            printf("unsigned_high_prod(%d, %d) is wrong!\n", a, b);
    }

    return 0;
}
