#include <stdio.h>
#include "common.h"

int mul_5(int x) {
    return (x << 2) + x;
}

int mul_9(int x) {
    return (x << 3) + x;
}

int mul_30(int x) {
    return (x << 5) - (x << 1);
}

int mul_m56(int x) {
    return (x << 3) - (x << 6);
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int x = randint();

        if (mul_5(x) != x * 5)
            printf("mul_5(%d) is wrong!\n", x);

        if (mul_9(x) != x * 9)
            printf("mul_5(%d) is wrong!\n", x);

        if (mul_30(x) != x * 30)
            printf("mul_5(%d) is wrong!\n", x);

        if (mul_m56(x) != x * -56)
            printf("mul_5(%d) is wrong!\n", x);
    }

    return 0;
}
