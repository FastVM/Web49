
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
    uint32_t fibn = fib(40);
    printf("fib(40) = %"PRIu32"\n", fibn);
    return 0;
}
