#include <stdio.h>
#include "common.h"

/* Return 1 when x contains an even number of 1s; 0 otherwise.
 * Assume w=32 */
int even_ones(unsigned x) {
    x = x ^ x >> 1;
    x = x ^ x >> 2;
    x = x ^ x >> 4;
    x = x ^ x >> 8;
    x = x ^ x >> 16;
    return (x & 1) == 0;
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int x = randint();
        if (even_ones(x) != (__builtin_popcount(x) % 2 == 0))
            printf("even_ones(%d) is wrong!\n", x);
    }

}
