#include <stdio.h>
#include <limits.h>
#include "common.h"

int saturating_add(int x, int y) {
    unsigned s = (unsigned)x + y;

    unsigned of_flag = (~(x^y) & (x^s) & (y^s)) >> (INT_WIDTH - 1);
    unsigned mask = -of_flag;

    unsigned s_sign = s >> (INT_WIDTH - 1);
    unsigned limit = (unsigned)INT_MIN - s_sign;

    return (mask & limit) + (~mask & s);
}

int saturating_add_correct(int x, int y) {
    unsigned raw = (unsigned)x + y;
    int raw_int = (int)raw;

    if (x >= 0 && y >= 0 && raw_int < 0)
        return INT_MAX;
    else if (x < 0 && y < 0 && raw_int >= 0)
        return INT_MIN;
    else
        return raw_int;
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int a = randint();
        int b = randint();
        if (saturating_add(a, b) != saturating_add_correct(a, b))
            printf("saturating_add(%d, %d) is wrong!\n", a, b);
    }

    return 0;
}
