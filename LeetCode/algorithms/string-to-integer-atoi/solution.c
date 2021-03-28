#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

int myAtoi (char* str) {
    uint32_t ans = 0;
    signed char positive = 1;

    while (isspace(*str))
        str++;

    if (*str == '-')
        positive = 0, str++;
    else if (*str == '+')
        str++;
    
    while (isdigit(*str)) {
        if (ans > INT32_MAX / 10)
            return positive ? INT32_MAX : INT32_MIN;
        int ne = ans * 10 + *str - '0';
        if (ne > (uint32_t)INT32_MAX)
            return positive ? INT32_MAX : INT32_MIN;
        ans = ne;
        str++;
    }

    return positive ? ans : -ans;
}

int main () {
    printf("%d\n", myAtoi("    10522545459"));
    printf("%d\n", myAtoi("2147483648"));
    return 0;
}
