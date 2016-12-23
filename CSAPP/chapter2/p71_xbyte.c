#include <assert.h>
#include <stdint.h>

typedef uint32_t packed_t;

int xbyte(packed_t word, int byte_num) {
    return word << (((3-byte_num) << 3)) >> 24;
}

int main() {
    uint32_t a = 0x12345678;
    assert(xbyte(a, 0) == 0x78);
    assert(xbyte(a, 1) == 0x56);
    assert(xbyte(a, 2) == 0x34);
    assert(xbyte(a, 3) == 0x12);
    return 0;
}
