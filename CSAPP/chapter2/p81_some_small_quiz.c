#include "common.h"
#include <assert.h>
#include <limits.h>

int test_a(int x, int y) {
    return (x>y) == (-x<-y);
}

int test_b(int x, int y) {
    return ((x+y)<<5) + x-y == 31*y+33*x;
}

int test_c(int x, int y) {
    return ~x+~y == ~(x+y);
}


int test_d(int x, int y) {
    unsigned ux = (unsigned)x;
    unsigned uy = (unsigned)y;
    return (int)(ux-uy) == -(y-x);
}

int test_e(int x, int y) {
    (void)y;
    return ((x >> 1) << 1) <= x;
}

int test_random(int n, int (*f)(int, int)) {
    int a, b;

    for (int i=0; i<n; i++) {
        fill_random_bytes(&a, sizeof(a));
        fill_random_bytes(&b, sizeof(b));
        if (!f(a, b))
            return 0;
    }

    return 1;
}

int main() {
    assert(!test_a(INT_MIN+1, INT_MIN));  // A is false
    assert(test_random(1000000, test_b));  // B is true
    assert(!test_c(INT_MAX, 0));  // C is false
    assert(test_random(1000000, test_d));  // D is true
    assert(test_random(1000000, test_e));  // E is true

    return 0;
}
