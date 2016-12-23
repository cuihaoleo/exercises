#include "common.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

#define INT_FLOAT_OVF 0x80000000

/* Compute (int) f.
 * If conversion causes overflow or f is NaN, return 0x80000000 */
int float_f2i(float_bits f) {
    /* 0x4f000000 (1.0 x 2^31) -> 0x80000000
     * 0xcf000000 (-1.0 x 2^31) -> 0x80000000
     */
    uint32_t sign_part = FLOAT_SIGN(f);
    uint32_t frac_part = FLOAT_FRAC(f);
    uint32_t exp_part = FLOAT_EXP(f);

    switch (sign_part) {
        case 0:
            if (f >= 0x4f000000)
                return  INT_FLOAT_OVF;
            break;
        default:
            if (f >= 0xcf000000)
                return  INT_FLOAT_OVF;
    }

    if (exp_part == 0xFF && frac_part)
        return  INT_FLOAT_OVF;

    unsigned raw_int = frac_part | 0x800000;
    int shift = ((int)exp_part - 127) - 23;
    if (shift >= 0)
        raw_int <<= shift;
    else if (shift > -24)
        raw_int >>= -shift;
    else
        raw_int = 0;

    return sign_part ? -raw_int : raw_int;
}

#define TEST_N 10000000

int main() {
    float_bits f;

    for (int i=0; i<TEST_N; i++) {
        fill_random_bytes(&f, sizeof(f));
        float the_float = float_bits_to_float(f);

        int n = float_f2i(f);
        int n_real = (int)the_float;

        if (n != n_real)
            printf("float_f2i(%g) is wrong!\n", the_float);
    }

    return 0;
}
