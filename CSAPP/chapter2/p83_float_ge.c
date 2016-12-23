#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include "common.h"

uint32_t f2u(float x) {
    return *(uint32_t*)&x;
}

int32_t map_float_to_int(float x) {
    uint32_t ux = f2u(x);
    uint32_t expanded_x_sign = (int32_t)ux >> 31;
    uint32_t stripped_x = ux & 0x7FFFFFFF; 
    return (~expanded_x_sign & stripped_x)+ \
           (expanded_x_sign & -stripped_x);
}

int float_ge(float x, float y) {
    return map_float_to_int(x) >= map_float_to_int(y);
}

#define TEST_N 1000000

int main() {
    float x, y;

    assert(sizeof(float) == sizeof(uint32_t));
    assert((-1 >> 1) == -1);  // need arithmetic shift

    assert(float_ge(0.0F, -0.0F));
    for (int i=0; i<TEST_N; i++) {
        fill_random_bytes(&x, sizeof(x));
        fill_random_bytes(&y, sizeof(y));

        if (isnan(x))
            x = y;
        else if (isnan(y))
            y = x;

        if (isnan(x))
            continue;

        if (float_ge(x, y) != (x >= y))
            printf("float_ge(%g, %g) is wrong!\n", x, y);
    }

    return 0;
}
