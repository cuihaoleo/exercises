#include "common.h"
#include <math.h>
#include <stdio.h>

/* Compute 0.5*f.  If f is NaN, then return f */
float_bits float_half(float_bits f) {
    uint32_t sign_part = FLOAT_SIGN(f);
    uint32_t frac_part = FLOAT_FRAC(f);
    uint32_t exp_part = FLOAT_EXP(f);

    if (exp_part == 0xFF && frac_part)  // nan
        return f;

    if (exp_part == 0) {
        // denormalized
        frac_part = (frac_part >> 1) + ((frac_part & 3) == 3); // round to even
    } else if (exp_part == 1) {
        // normalized, but will be denormalized after division
        exp_part -= 1;
        frac_part = ((frac_part >> 1) | 0x400000) + ((frac_part & 3) == 3);
    } else  // normalized
        exp_part -= 1;

    return (sign_part << 31) + (exp_part << 23) + frac_part;
}

#define TEST_N 10000000

int main() {
    float_bits f;

    for (int i=0; i<TEST_N; i++) {
        int test;

        fill_random_bytes(&f, sizeof(f));
        float_bits nf = float_half(f);

        if (isnan(*(float*)&f))
            test = f == nf;
        else {
            float cmp = 0.5 * *(float*)&f;
            test = cmp == *(float*)&nf;
        }

        if (!test)
            printf("float_half(%g) is wrong!\n", *(float*)&f);
    }

    return 0;
}
