#include "common.h"
#include <math.h>
#include <stdio.h>

/* Compute -f.  If f is NaN, then return f */
float_bits float_negate(float_bits f) {
    uint32_t frac_part = FLOAT_FRAC(f);
    uint32_t exp_part = FLOAT_EXP(f);

    if (!(exp_part == 0xFF && frac_part))
        f ^= 1 << 31;

    return f;
}

#define TEST_N 1000000

int main() {
    float_bits f;

    for (int i=0; i<TEST_N; i++) {
        int test;

        fill_random_bytes(&f, sizeof(f));
        float_bits nf = float_negate(f);

        if (isnan(*(float*)&f))
            test = f == nf;
        else
            test = *(float*)&f == -*(float*)&nf;

        if (!test)
            printf("float_negate(%g) is wrong!\n", *(float*)&f);
    }

    return 0;
}
