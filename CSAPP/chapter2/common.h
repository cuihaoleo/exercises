#ifndef _INCLUDE_COMMON_H_
#define _INCLUDE_COMMON_H_
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define INT_WIDTH (sizeof(int)<<3)

void fill_random_bytes(void *p, size_t len);
int randint();

typedef uint32_t float_bits;
#define FLOAT_SIGN(x) ((x)>>31)
#define FLOAT_FRAC(x) ((x) & 0x7FFFFF)
#define FLOAT_EXP(x) (((x)>>23) & 0xFF)

float float_bits_to_float(float_bits b);
float_bits float_to_float_bits(float f);

#endif
