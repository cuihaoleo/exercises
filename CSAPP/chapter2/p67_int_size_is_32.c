#include <stdio.h>
#include <assert.h>

int bad_int_size_is_32() {
    int set_msb = 1 << 31;
    int beyond_msb = 1 << 32;  // warning: undefined behavior!
    return set_msb && !beyond_msb;
}

int int_size_is_32a() {
    unsigned set_msb = 1U << 31;
    unsigned beyond_msb = 1U << 31 << 1;
    return set_msb && !beyond_msb;
}

int int_size_is_32b() {
    unsigned set_msb = 1U << 15 << 15 << 1;
    unsigned beyond_msb = 1U << 15 << 15 << 2;
    return set_msb && !beyond_msb;
}


int main() {
    assert(sizeof(int) == 4);
    assert(int_size_is_32a());
    assert(int_size_is_32b());
    return 0;
}
