#include <stdio.h>

/* x = (0.yyyy ...)
 * x * 2^k = (y.yyyy ...)
 * x * (2^k - 1) = (y.0000) = Y
 * so, x = Y / (2^k - 1)
 */
double recurring_float(unsigned yy, size_t k) {
    return yy / ((1<<k) - 1.0);
}

int main() {
    printf("y = 01, x = %lg\n", recurring_float(1, 2));
    printf("y = 0011, x = %lg\n", recurring_float(3, 4));
    printf("y = 001, x = %lg\n", recurring_float(1, 3));
    printf("y = 1001, x = %lg\n", recurring_float(9, 4));
    printf("y = 000111, x = %lg\n", recurring_float(7, 6));

    return 0;
}
