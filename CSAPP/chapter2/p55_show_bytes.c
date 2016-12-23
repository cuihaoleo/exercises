#include <stdio.h>
#include "common.h"

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
    for (int i=0; i<len; i++)
        printf(" %.2x", start[i]);
    putchar('\n');
}

void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer)&x, sizeof(void*));
}

int main() {
    int a;
    float b;
    int *p;

    fill_random_bytes(p = &a, sizeof(int));
    fill_random_bytes(&b, sizeof(float));

    printf("Integer 0x%0*x: ", (int)sizeof(int)*2, a);
    show_int(a);
    printf("Float %g: ", b);
    show_float(b);
    printf("Pointer %p: ", p);
    show_pointer(p);

    return 0;
}
