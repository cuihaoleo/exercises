#include "common.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sra(int x, int k) {
    int xsrl = (unsigned) x >> k;
    int mask = (xsrl & (1 << (INT_WIDTH - k - 1)));
    mask <<= 1;
    mask -= 1;
    mask ^= -1;

    return mask | xsrl;
}

unsigned srl(unsigned x, int k) {
    unsigned xsra = (int) x >> k;
    int mask = 1 << (INT_WIDTH - k - 1) << 1;
    mask -= 1;
    return xsra & mask;
}

#define TEST_N 1000000

int main() {
    for (int i=0; i<TEST_N; i++) {
        int r = randint();
        int k = rand() % (sizeof(int) * 8);

        if (sra(r, k) != r >> k)
            printf("sra(0x%0*X, %d) fail!\n",
                    (int)sizeof(int) * 2,
                    (unsigned)r,
                    k);

        if (srl(r, k) != (unsigned)r >> k)
            printf("srl(0x%0*X, %d) fail!\n",
                    (int)sizeof(int) * 2,
                    (unsigned)r,
                    k);
    }

    return 0;
}
