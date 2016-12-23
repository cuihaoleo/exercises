#include <assert.h>
#include <stdio.h>

int get_lsb(int x) {
    return x & 0xFF;
}

int get_msb(int x) {
    int shift_val = (sizeof(int)-1) << 3;
    int xright = x >> shift_val;
    return xright & 0xFF;
}

int bit_all_1(int n) {
    return !(n + 1);
}

int bit_all_0(int n) {
    return !n;
}

int msb_all_0(int n) {
    return !get_msb(n);
}

int lsb_all_0(int n) {
    return !get_lsb(n);
}

int main() {
    int a = -1;  // 0xFFFFFFFF
    int b = 0;  // 0x00000000
    int c = (a >> 8) << 8;  // 0xFFFFFF00
    int d = (unsigned)a >> 8;  // 0x00FFFFFF

    printf("a = 0x%0*X\n", (int)sizeof(int) * 2, a);
    printf("b = 0x%0*X\n", (int)sizeof(int) * 2, b);
    printf("c = 0x%0*X\n", (int)sizeof(int) * 2, c);
    printf("d = 0x%0*X\n", (int)sizeof(int) * 2, d);

    assert(bit_all_1(a));
    assert(!bit_all_1(b));
    assert(!bit_all_1(c));
    assert(!bit_all_1(d));

    assert(!bit_all_0(a));
    assert(bit_all_0(b));
    assert(!bit_all_0(c));
    assert(!bit_all_0(d));

    assert(!msb_all_0(a));
    assert(msb_all_0(b));
    assert(!msb_all_0(c));
    assert(msb_all_0(d));

    assert(!lsb_all_0(a));
    assert(lsb_all_0(b));
    assert(lsb_all_0(c));
    assert(!lsb_all_0(d));

    return 0;
}
