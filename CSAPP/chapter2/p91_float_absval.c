#include "common.h"
#include <math.h>
#include <stdio.h>

float_bits float_absval(float_bits f) {
    f &= 0x7FFFFFFF;
    return f;
}

#define TEST_N 10000000

int main() {
    float_bits f;
    float the_float;

    for (int i=0; i<TEST_N; i++) {
        fill_random_bytes(&f, sizeof(f));

        float abs1 = fabsf(the_float = float_bits_to_float(f));
        float_bits abs2_bits = float_absval(f);
        float abs2 = float_bits_to_float(abs2_bits);

        if (abs1 != abs2 && !(isnan(abs1) && isnan(abs2)))
            printf("float_absval(%g) is wrong!\n", the_float);
    }

    return 0;
}
