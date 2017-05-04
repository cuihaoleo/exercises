#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool isPrime(unsigned long long n) {
    if (n % 2 == 0)
        return true;

    for (unsigned long long i=3; i*i<=n; i+=2)
        if (n % i == 0)
            return false;

    return true;
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
    unsigned long long number;
    bool result;

    printf("Number to test: ");
    scanf("%llu", &number);

    measure_time_ms(true);
    result = isPrime(number);
    printf("%lu ms taken.\n\n", measure_time_ms(false));

    if (result)
        printf("%llu is prime\n", number);
    else
        printf("%llu is not prime\n", number);

    return 0;
}
