#include <stdio.h>

int int_shifts_are_logical() {
    return -1 >> 8 != -1;
}

int main() {
    if (int_shifts_are_logical())
        puts("int shifts are logical!");
    else
        puts("int shifts are arithmetic!");

    return 0;
}
