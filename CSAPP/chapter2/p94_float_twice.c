#include "common.h"
#include <math.h>
#include <stdio.h>

/* Compute 2*f.  If f is NaN, then return f */
float_bits float_twice(float_bits f) {
    uint32_t sign_part = FLOAT_SIGN(f);
    uint32_t frac_part = FLOAT_FRAC(f);
    uint32_t exp_part = FLOAT_EXP(f);

    if (exp_part == 0xFF && frac_part)  // nan
        return f;

    if (exp_part >= 0xFE) {
        // result will be inf
        exp_part = 0xFF;
        frac_part = 0;
    } else if (exp_part == 0) {
        // overflowed bits happened to be at exp_part
        frac_part <<= 1;
    } else
        exp_part += 1;

    return (sign_part << 31) + (exp_part << 23) + frac_part;
}

#define TEST_N 10000000

int main() {
    float_bits f;

    for (int i=0; i<TEST_N; i++) {
        int test;

        fill_random_bytes(&f, sizeof(f));
        float_bits nf = float_twice(f);

        if (isnan(*(float*)&f))
            test = f == nf;
        else {
            float cmp = 2 * *(float*)&f;
            test = cmp == *(float*)&nf;
        }

        if (!test)
            printf("float_twice(%g) is wrong!\n", *(float*)&f);
    }

    return 0;
}
