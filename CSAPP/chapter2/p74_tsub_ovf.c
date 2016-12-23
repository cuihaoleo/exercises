#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "common.h"

/* Determine whether subtracting arguments will cause overflow */
int tsub_ovf(int x, int y) {
    unsigned raw = (unsigned)x - y;
    return (x ^ y) >> (INT_WIDTH-1) && (x ^ raw) >> (INT_WIDTH-1);
}

int main() {
    assert(!tsub_ovf(0, 0));
    assert(!tsub_ovf(INT_MIN, -100));
    assert(!tsub_ovf(INT_MAX, 100));
    assert(tsub_ovf(INT_MIN, 1));
    assert(tsub_ovf(INT_MAX, -1));
    assert(tsub_ovf(INT_MIN, INT_MAX));
    assert(tsub_ovf(INT_MAX, INT_MIN));
    return 0;
}
