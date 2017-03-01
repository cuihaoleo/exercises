#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <complex.h>
#include <float.h>
#include <math.h>

#include <fftw3.h>

/* Precison setting of float numbers
 *     0: float
 *     1: double
 *     2: long double
 *     3: __float128 gcc extension */
#ifndef FLOAT_PRECISION
    #define FLOAT_PRECISION 1
#endif

#if FLOAT_PRECISION == 0
    #define FLOAT_TYPE float
    #define COMPLEX_TYPE complex FLOAT_TYPE
    #define FFTW_ID(X) fftwf_ ## X
    #define MFUNC(X) X ## f
    #define FMT_CHAR "f"
    #define FLOAT_DIG FLT_DIG
#elif FLOAT_PRECISION == 1
    #define FLOAT_TYPE double
    #define COMPLEX_TYPE complex FLOAT_TYPE
    #define FFTW_ID(X) fftw_ ## X
    #define MFUNC(X) X
    #define FMT_CHAR "l"
    #define FLOAT_DIG DBL_DIG
#elif FLOAT_PRECISION == 2
    #define FLOAT_TYPE long double
    #define COMPLEX_TYPE complex FLOAT_TYPE
    #define FFTW_ID(X) fftwl_ ## X
    #define MFUNC(X) X ## l
    #define FMT_CHAR "L"
    #define FLOAT_DIG LDBL_DIG
#elif FLOAT_PRECISION == 3
    #include <quadmath.h>
    #define FLOAT_TYPE __float128
    #define COMPLEX_TYPE __complex128
    #define FFTW_ID(X) fftwq_ ## X
    #define MFUNC(X) X ## q
    #define FMT_CHAR "Q"
    #define FLOAT_DIG FLT128_DIG
#else
    #error Invalid precision profile!
#endif

#define CONST_PI MFUNC(3.1415926535897932384626433832795029)
#define CONST_2PI (2*CONST_PI)

// Computing parameters
#define TOTAL_POINT 10000
#define GFUNC_STEEP 2.0
//#define MIN_GRAD 1e-24
#define MIN_GRAD 0.0
//#define MAX_STUCK 100
#define MAX_STUCK 10000
#define DELTA_1 1e-8
#define DELTA_2 1e-8
#define ZERO_THRESHOLD 1e-12

#define SQUARE(x) ((x)*(x))
#define CEIL(x) (MFUNC(ceil)((x)-(ZERO_THRESHOLD)))
#define FLOOR(x) (MFUNC(floor)((x)+(ZERO_THRESHOLD)))
#define SYM_MAT_SIZE(x) ((x)*((x)+1)/2)
#define SYM_IDX(i,j) ((j)<=(i) ? (SYM_MAT_SIZE(i)+(j)) : (SYM_MAT_SIZE(j)+(i)))

typedef struct {
    FLOAT_TYPE *restrict impres;
    COMPLEX_TYPE *restrict frqres;
} system_response;

FLOAT_TYPE weigh_g(FLOAT_TYPE x, FLOAT_TYPE x0) {
    FLOAT_TYPE xn = MFUNC(pow)(x, GFUNC_STEEP);
    FLOAT_TYPE x0n = MFUNC(pow)(x0, GFUNC_STEEP);
    return xn / (x0n + xn);
}

FLOAT_TYPE weigh_g_d(FLOAT_TYPE x, FLOAT_TYPE x0) {
    FLOAT_TYPE xn_1 = MFUNC(pow)(x, GFUNC_STEEP-1);
    FLOAT_TYPE xn = xn_1 * x;
    FLOAT_TYPE x0n = MFUNC(pow)(x0, GFUNC_STEEP);
    return (GFUNC_STEEP * x0n * xn_1) / ((x0n + xn) * (x0n + xn));
}

FLOAT_TYPE weigh_g_d2(FLOAT_TYPE x, FLOAT_TYPE x0) {
    FLOAT_TYPE xn_2 = MFUNC(pow)(x, GFUNC_STEEP-2);
    FLOAT_TYPE xn_1 = xn_2 * x;
    FLOAT_TYPE xn = xn_1 * x;
    FLOAT_TYPE x0n = MFUNC(pow)(x0, GFUNC_STEEP);

    return GFUNC_STEEP * x0n * xn_2 * 
           ((GFUNC_STEEP - 1)*x0n - (GFUNC_STEEP + 1)*xn)
           / MFUNC(pow)(x0n + xn, 3);
}

void z_fill(
        const int passband,
        const int transband,
        const int rejectband,
        const int cpassband,
        const int ctransband,
        const int crejectband,
        const FLOAT_TYPE *restrict phi,
        const FLOAT_TYPE *restrict m,
        FLOAT_TYPE *restrict value,
        FLOAT_TYPE *restrict jacobian,
        FLOAT_TYPE *restrict hessian) {

    size_t transband_length = transband - passband;
    FLOAT_TYPE cm[crejectband];

    *value = 0.0;
    memset(jacobian, 0, transband_length * sizeof(FLOAT_TYPE));
    memset(hessian, 0, SYM_MAT_SIZE(transband_length) * sizeof(FLOAT_TYPE));
    memset(cm, 0, crejectband * sizeof(FLOAT_TYPE));

    for (int k=0; k<rejectband; k++)
        for (int l=0; l<crejectband; l++)
            cm[l] += m[k] * phi[k*crejectband + l];

    for (int k=0; k<cpassband; k++) {
        FLOAT_TYPE x = cm[k] - 1;
        FLOAT_TYPE x2 = SQUARE(x);
        FLOAT_TYPE x4 = SQUARE(x2);
        FLOAT_TYPE g = weigh_g(x2, DELTA_1);
        FLOAT_TYPE gd = weigh_g_d(x2, DELTA_1);
        FLOAT_TYPE gd2 = weigh_g_d2(x2, DELTA_1);
        FLOAT_TYPE tmp1 = (g + x2*gd) * 2*x;

        FLOAT_TYPE *restrict jacobian_ptr = jacobian;
        FLOAT_TYPE *restrict hessian_ptr = hessian;

        *value += g * x2;
        for (int i=passband; i<transband; i++) {
            FLOAT_TYPE phi_ik = phi[i*crejectband + k];
            FLOAT_TYPE tmp2 = g + 5*x2*gd + 2*x4*gd2;

            *(jacobian_ptr++) += tmp1 * phi_ik;

            for (int j=passband; j<=i; j++) {
                FLOAT_TYPE phi_jk = phi[j*crejectband + k];
                *(hessian_ptr++) += tmp2 * 2 * phi_ik * phi_jk;
            }
        }
    }

    for (int k=ctransband; k<crejectband; k++) {
        FLOAT_TYPE x = cm[k];
        FLOAT_TYPE x2 = SQUARE(x);
        FLOAT_TYPE x4 = SQUARE(x2);
        FLOAT_TYPE g = weigh_g(x2, DELTA_2);
        FLOAT_TYPE gd = weigh_g_d(x2, DELTA_2);
        FLOAT_TYPE gd2 = weigh_g_d2(x2, DELTA_2);
        FLOAT_TYPE tmp1 = (g + x2*gd) * 2*x;

        FLOAT_TYPE *restrict jacobian_ptr = jacobian;
        FLOAT_TYPE *restrict hessian_ptr = hessian;

        *value += g * x2;
        for (int i=passband; i<transband; i++) {
            FLOAT_TYPE phi_ik = phi[i*crejectband + k];
            FLOAT_TYPE tmp2 = g + 5*x2*gd + 2*x4*gd2;

            *(jacobian_ptr++) += tmp1 * phi_ik;

            for (int j=passband; j<=i; j++) {
                FLOAT_TYPE phi_jk = phi[j*crejectband + k];
                *(hessian_ptr++) += tmp2 * 2 * phi_ik * phi_jk;
            }
        }
    }

    FLOAT_TYPE factor = CONST_PI / crejectband;

    *value *= factor;
    for (size_t i=0; i<transband_length; i++)
        jacobian[i] *= factor;
    for (size_t i=0; i<SYM_MAT_SIZE(transband_length); i++)
        hessian[i] *= factor;
}

system_response IFrSmp(
        int n,
        FLOAT_TYPE w_cutoff,
        FLOAT_TYPE w_stop) {

    // upper bound (not include) of each band (discrete)
    int passband, transband, rejectband;
    // upper bound (not include) of each band (continuous)
    int cpassband, ctransband, crejectband;

    if (w_cutoff >= w_stop || w_cutoff <= 0.0 || w_stop >= 1.0) {
        fprintf(stderr, "invalid w_cutoff / w_stop");
        exit(-1);
    }

    passband = CEIL(w_cutoff * n / 2.0) + 1;
    transband = FLOOR(w_stop * n / 2.0);
    rejectband = (n + 1) / 2;

    cpassband = CEIL(w_cutoff * TOTAL_POINT / 2.0) + 1;
    ctransband = FLOOR(w_stop * TOTAL_POINT / 2.0);
    crejectband = (TOTAL_POINT + 1) / 2;

    if (transband - passband <= 0) {
        fprintf(stderr, "n too small");
        exit(-1);
    }

    FLOAT_TYPE phi[rejectband * crejectband];
    for (int k=0; k<rejectband; k++)
        for (int l=0; l<crejectband; l++) {
            FLOAT_TYPE w = l * CONST_2PI / TOTAL_POINT;

            FLOAT_TYPE a = MFUNC(sin)(n*(w/2-CONST_PI*k/n));
            FLOAT_TYPE b = MFUNC(sin)(w/2-CONST_PI*k/n);
            FLOAT_TYPE c = MFUNC(sin)(n*(w/2+CONST_PI*k/n));
            FLOAT_TYPE d = MFUNC(sin)(w/2+CONST_PI*k/n);

            FLOAT_TYPE p1 = (MFUNC(fabs)(b) > ZERO_THRESHOLD) ? a / b : n;
            FLOAT_TYPE p2 = (MFUNC(fabs)(d) > ZERO_THRESHOLD) ? c / d : n;

            phi[k*crejectband + l] = (p1 + p2) / n;
        }
   
    for (int l=0; l<crejectband; l++)
        phi[l] /= 2.0;

    FLOAT_TYPE m[rejectband];
    for (int i=0; i<passband; i++)
        m[i] = 1.0;

    FLOAT_TYPE delta_m = 1 / (1 + transband - passband);
    for (int i=passband; i<transband; i++)
        m[i] = m[i-1] - delta_m;

    memset(m + transband, 0, (rejectband - transband) * sizeof(FLOAT_TYPE));

    FLOAT_TYPE sqr_jacobian;
    size_t transband_length = transband - passband;
    FLOAT_TYPE old_value = 1.0, value;
    FLOAT_TYPE jacobian[transband_length]; 
    FLOAT_TYPE hessian[SYM_MAT_SIZE(transband_length)];
    unsigned iter_count = 0;
    unsigned stuck_count = 0;

    do {
        iter_count++;
        z_fill(passband, transband, rejectband,
               cpassband, ctransband, crejectband,
               phi, m, &value, jacobian, hessian);

        if (value >= old_value && ++stuck_count > MAX_STUCK)
            break;

        fprintf(stderr, "  Objective function #%u: %.*"FMT_CHAR"e\n",
                iter_count, FLOAT_DIG, old_value=value);

        // 2-norm of Jacobian vector
        sqr_jacobian = 0.0;
        for (size_t i=0; i<transband_length; i++)
            sqr_jacobian += jacobian[i] * jacobian[i];

        // Gradient method
        FLOAT_TYPE sum = 0.0;
        for (size_t i=0; i<transband_length; i++)
            for (size_t j=0; j<transband_length; j++)
                sum += jacobian[j] * hessian[SYM_IDX(j,i)] * jacobian[i];

        FLOAT_TYPE delta_x = -sqr_jacobian / sum;
        for (size_t i=0; i<transband_length; i++) {
            m[passband + i] += delta_x * jacobian[i];
        }
    } while (MFUNC(sqrt)(sqr_jacobian) > MIN_GRAD);

    if (stuck_count > MAX_STUCK)
        fputs("  (Seems no improvement, abort iteration)\n", stderr);

    COMPLEX_TYPE *fft = (COMPLEX_TYPE*)FFTW_ID(malloc)(sizeof(COMPLEX_TYPE) * n);
    FLOAT_TYPE *h = (FLOAT_TYPE*)FFTW_ID(malloc)(sizeof(FLOAT_TYPE) * n);
    FFTW_ID(plan) p = FFTW_ID(plan_dft_c2r_1d)(n, fft, h, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);

    for (int i=0; i<rejectband; i++) {
        FLOAT_TYPE theta = -CONST_PI / n * (n-1) * i;
        fft[i] = m[i] * MFUNC(cexp)(theta * 1I);
    }

    fft[rejectband] = 0;
    for (int i=n/2+1; i<n; i++)
        fft[i] = MFUNC(conj)(fft[n-i]);

    FFTW_ID(execute)(p);
    FFTW_ID(destroy_plan)(p);

    for (int i=0; i<n; i++)
        h[i] /= n;

    system_response response = { h, fft };
    return response;
}

FLOAT_TYPE input_signal() {
    static bool initialized = false;

    if (!initialized) {
        srand(time(NULL));
        initialized = true;
    }

    return rand() / (FLOAT_TYPE)RAND_MAX;
}

unsigned long measure_time_ms(bool reset) {
    static clock_t begin = 0;

    if (reset) {
        begin = clock();
        return 0;
    } else {
        clock_t end = clock();
        return 1000 * (end - begin) / CLOCKS_PER_SEC;
    }
}

int main() {
    int n = 80;
    FLOAT_TYPE w_cutoff = 0.2;
    FLOAT_TYPE w_stop = 0.3;

    // computing system response
    puts("Computing system response...");
    measure_time_ms(true);
    system_response response = IFrSmp(n, w_cutoff, w_stop);
    printf("%lu ms taken to design the filter.\n\n", measure_time_ms(false));

    FILE *f_impres = fopen("impres.txt", "w");
    FILE *f_frqres = fopen("frqres.txt", "w");

    if (f_impres == NULL || f_frqres == NULL) {
        fprintf(stderr, "Cannot open output files.");
        exit(-1);
    }

    for (int i=0; i<n; i++) {
        fprintf(f_impres, "%.*"FMT_CHAR"e\n",
                FLOAT_DIG, response.impres[i]);

        COMPLEX_TYPE frq = response.frqres[i];
        fprintf(f_frqres, "%+.*"FMT_CHAR"e%+.*"FMT_CHAR"ej\n",
                FLOAT_DIG, MFUNC(creal)(frq),
                FLOAT_DIG, MFUNC(cimag)(frq));
    }

    fclose(f_impres);
    fclose(f_frqres);

    // evaluate the filter
    FLOAT_TYPE *impres_ext = (FLOAT_TYPE*)FFTW_ID(malloc)(
                                sizeof(FLOAT_TYPE) * TOTAL_POINT);
    COMPLEX_TYPE *dtft = (COMPLEX_TYPE*)FFTW_ID(malloc)(
                                sizeof(COMPLEX_TYPE) * (TOTAL_POINT / 2 + 1));
    FFTW_ID(plan) p = FFTW_ID(plan_dft_r2c_1d)(
                                TOTAL_POINT, impres_ext, dtft, FFTW_ESTIMATE);

    memcpy(impres_ext, response.impres, n * sizeof(FLOAT_TYPE));
    memset(impres_ext + n, 0, (TOTAL_POINT - n) * sizeof(FLOAT_TYPE));

    FFTW_ID(execute)(p);
    FFTW_ID(destroy_plan)(p);

    float passband_max_gain = 1.0 / -0.0, passband_max_attn = 1.0 / +0.0;
    float rejectband_min_attn = 1.0 / -0.0;
    for (int i=0; i<TOTAL_POINT/2+1; i++) {
        FLOAT_TYPE w = i * 2.0 / TOTAL_POINT;
        FLOAT_TYPE amp = MFUNC(cabs)(dtft[i]);
        float db = 20 * MFUNC(log10)(amp);

        if (w <= w_cutoff) {
            if (db > passband_max_gain)
                passband_max_gain = db;
            else if (db < passband_max_attn)
                passband_max_attn = db;
        } else if (w >= w_stop) {
            if (db > rejectband_min_attn)
                rejectband_min_attn = db;
        }
    }

    FFTW_ID(free)(impres_ext);
    FFTW_ID(free)(dtft);

    printf("Max gain in passband: %.3fdB\n", passband_max_gain);
    printf("Max attenuation in passband: %.3fdB\n", passband_max_attn);
    printf("Min attenuation in rejectband: %.3fdB\n", rejectband_min_attn);
    puts("");

    // generate random signal and filter
    /*
    FILE *f_input = fopen("input.txt", "w");
    FILE *f_output = fopen("output.txt", "w");

    if (f_input == NULL || f_output == NULL) {
        fprintf(stderr, "Cannot open output files.");
        exit(-1);
    }

    unsigned input_length = 0;

    printf("Signal length: ");
    while (scanf("%u", &input_length) != 1)
        continue;

    FLOAT_TYPE buffer[n];
    int headptr = 0;
    memset(buffer, 0, n * sizeof(FLOAT_TYPE));

    for (unsigned i=0; i<input_length; i++) {
        FLOAT_TYPE x = input_signal();

        buffer[headptr++] = x;
        headptr %= n;

        FLOAT_TYPE y = 0.0;
        for (int j=headptr, k=n-1; k>=0; j=(j+1)%n, k--)
            y += buffer[j] * response.impres[k];

        fprintf(f_input, "%.*"FMT_CHAR"e\n", FLOAT_DIG, x);
        fprintf(f_output, "%.*"FMT_CHAR"e\n", FLOAT_DIG, y);
    }

    fclose(f_input);
    fclose(f_output);
    */

    puts("Everything done!");

    FFTW_ID(free)(response.impres);
    FFTW_ID(free)(response.frqres);
    FFTW_ID(cleanup)();


    return 0;
}
