#include <assert.h>

/*
 * Make with least significant n bits set to 1
 *  Examples: n=6 -> 0x3f, n=17 -> 0x1FFFF
 *  Assume 1 <= n <= w
 */
int lower_bits(int x, int n) {
    int mask = (1 << (n-1) << 1) - 1;
    return mask | x;
}

int main() {
    assert(lower_bits(0, 6) == 0x3f);
    assert(lower_bits(0, 17) == 0x1ffff);
    return 0;
}
