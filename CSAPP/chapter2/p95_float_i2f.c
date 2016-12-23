#include "common.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

/* Compute (float) i */
float_bits float_i2f(int i) {
    int sign_part = (unsigned)i >> 31;
    unsigned ui = i >= 0 ? i : -i;
    int count;

    if (i == 0)
        return 0;
    else if (i == INT_MIN)
        return 0xcf000000;

    for (i=ui, count=0; i>0; i>>=1)
        count++;

    if (count <= 24) {
        ui <<= 24 - count;
    } else {
        unsigned shift = count - 24;
        unsigned discard = ui << (32 - shift) >> (32 - shift);
        unsigned frac = ui >> shift;
        unsigned rounding_threshold = (1 << (shift - 1)) - (frac & 1);

        if (discard > rounding_threshold)
            frac++;

        if (frac >> 24) {
            frac >>= 1;
            count++;
        }

        ui = frac;
    }

    return (sign_part << 31) + ((count + 126) << 23) + (ui & 0x7FFFFF);
}

int main() {
    unsigned loop = 0;

    do {
        int i = (int)loop;
        float_bits nf = float_i2f(i);
        float i2f = (float)i;

        if (nf != float_to_float_bits(i2f))
            printf("float_i2f(%d) is wrong!\n", i);
    } while (++loop);

    return 0;
}
