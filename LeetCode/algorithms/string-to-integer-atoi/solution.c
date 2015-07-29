#include <stdio.h>
#include <ctype.h>

int myAtoi (char* str) {
    signed char positive = 1;

    while (isspace(*str)) {
        str++;
    }

    if (*str == '-')
        positive = 0, str++;
    else if (*str == '+')
        str++;
    
    int ans = 0;
    while (isdigit(*str)) {
        if (ans > 0x7fffffff / 10)
            return positive ? 0x7fffffff : 0x80000000;
        int ne = ans * 10 + *str - '0';
        if (ne < ans)
            return positive ? 0x7fffffff : 0x80000000;
        ans = ne;
        str++;
    }

    return positive ? ans : -ans;
}

int main () {
    printf("%d\n", myAtoi("    10522545459"));
    return 0;
}
