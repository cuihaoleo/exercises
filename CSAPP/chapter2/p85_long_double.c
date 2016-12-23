#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <float.h>

union x86_long_double_parser {
    long double val;
    struct {
        uint64_t mantisa: 63;
        uint8_t integer: 1;
        uint16_t exponent: 15;
        uint8_t sign: 1;
        uint64_t padding: 48;
    } parts;
};

int main() {
    union x86_long_double_parser min_unnorm, min_norm, max_norm;

    assert(sizeof(union x86_long_double_parser) == 16);

    min_unnorm.parts.sign = 0;
    min_unnorm.parts.exponent = 0;
    min_unnorm.parts.integer = 0;
    min_unnorm.parts.mantisa = 1;
    printf("min_unnorm = %Lg\n", min_unnorm.val);

    min_norm.parts.sign = 0;
    min_norm.parts.exponent = 1;
    min_norm.parts.integer = 1;
    min_norm.parts.mantisa = 0;
    assert(min_norm.val == LDBL_MIN);
    printf("min_norm = %Lg\n", min_norm.val);

    max_norm.val = 0.0;
    max_norm.parts.exponent = ~max_norm.parts.exponent - 1;
    max_norm.parts.integer = 1;
    max_norm.parts.mantisa = ~max_norm.parts.mantisa;
    assert(max_norm.val == LDBL_MAX);
    printf("max = %Lg\n", max_norm.val);
 
    return 0;
}
