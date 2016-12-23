#include <assert.h>
#include "common.h"

/*
 * Do rotating right shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32:
 *      n = 4 -> 0x81234567, n = 20 -> 0x45678123
 */
unsigned rotate_right(unsigned x, int n) {
    unsigned right = x >> (n-1) >> 1;
    unsigned left = x << (INT_WIDTH - n);
    return right + left;
}

int main() {
    assert(rotate_right(0x12345678, 4) == 0x81234567);
    assert(rotate_right(0x12345678, 20) == 0x45678123);
    return 0;
}
