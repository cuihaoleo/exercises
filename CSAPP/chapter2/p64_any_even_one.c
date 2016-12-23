#include <stdio.h>
#include <assert.h>

/* Return 1 when any even bit of x equals 1; 0 otherwise.
 * Assume w=32 */

int any_even_one(unsigned x) {
    // 0b1010 = 0xA
    return (x & 0xAAAAAAAA) != 0;
}

int main() {
    assert(sizeof(int) * 8 == 32);
    assert(any_even_one(8));
    assert(any_even_one(9));
    return 0;
}
