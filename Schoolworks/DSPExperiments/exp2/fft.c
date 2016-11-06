#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void _ditfft2(
        const complex double x[],
        complex double y[],
        unsigned n,
        unsigned step) {
    if (n == 1) {
        y[0] = x[0];
        return;
    }

    _ditfft2(x, y, n/2, 2*step);
    _ditfft2(x+step, y+n/2, n/2, 2*step);

    for (unsigned k=0; k<n/2; k++) {
        complex double t = y[k];
        y[k] = t + cexp(-2*M_PI*k/n * I) * y[k+n/2];
        y[k+n/2] = t - cexp(-2*M_PI*k/n * I) * y[k+n/2];
    }
}

void ditfft2(const complex double x[], complex double y[], unsigned n) {
    if ((n & (n-1)) != 0) {
        fprintf(stderr, "length of array must be power to 2");
        exit(-1);
    }

    _ditfft2(x, y, n, 1);
}
 
int main() {
    unsigned input_size = 0, n = 1;

    printf("Length of input array: ");
    scanf("%d", &input_size);

    while (n < input_size) n *= 2;

    complex double x[n];
    complex double y[n];
    memset(x, 0, n * sizeof(complex double));
    memset(y, 0, n * sizeof(complex double));

    printf("Input the array: ");
    for (unsigned i=0; i<input_size; i++) {
        double r;
        scanf("%lf", &r);
        x[i] = r;
    }

    ditfft2(x, y, n);

    printf("Padding zero to %d elements.\n", n);
    puts("FFT:");
    for (unsigned i=0; i<n; i++)
        printf("%+lf%+lfj, %lf\n", creal(y[i]), cimag(y[i]), cabs(y[i]));

    return 0;
}
