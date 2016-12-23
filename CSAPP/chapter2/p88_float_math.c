#include <assert.h>
#include <limits.h>

int x, y, z;
double dx, dy, dz;

void fill_in(int xx, int yy, int zz) {
    x = xx;
    y = yy;
    z = zz;
    dx = (double) xx;
    dy = (double) yy;
    dz = (double) zz;
}

int test1() {
    return (double)(float)x == dx;
}

int test2() {
    return dx + dy == (double)(x + y);
}

int test3() {
    return dx + dy + dz == dz + dy + dx;
}

int test4() {
    return dx * dy * dz == dz * dy * dx;
}

int test5() {
    return dx / dx == dy / dy;
}

int main() {
    fill_in(INT_MAX, 0, 0);
    assert(!test1());

    fill_in(INT_MAX, 1, 0);
    assert(!test2());

    // think that test3 and test4 is always true?

    fill_in(0, 1, 0);
    assert(!test5());

    return 0;
}
