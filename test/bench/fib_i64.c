
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t fib(uint64_t n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int main(int argc, char **argv) {
    uint64_t n = 0;
    for (char *head = argv[1]; *head != '\0'; head += 1) {
        n *= 10;
        n += *head - '0';
    }
    uint64_t fibn = fib(n);
    printf("fib(%"PRIu64") = %"PRIu64"\n", n, fibn);
    return 0;
}
