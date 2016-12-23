#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fill_random_bytes(void *p, size_t len) {
    static int first_call = 1;

    if (first_call) {
        srand(time(NULL));
        first_call = 0;
    }

    unsigned char *pa = p;
    for (unsigned i=0; i<len; i++)
        pa[i] = rand() % 256;
}

int randint() {
    int a;
    fill_random_bytes(&a, sizeof(int));
    return a;
}

float float_bits_to_float(float_bits b) {
    float f;
    memcpy(&f, &b, sizeof(float));
    return f;
}

float_bits float_to_float_bits(float f) {
    float_bits b;
    memcpy(&b, &f, sizeof(float));
    return b;
}
