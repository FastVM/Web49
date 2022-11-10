
#include <stdio.h>
#include <stdlib.h>

size_t fib(size_t n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int main(int argc, char **argv) {
    size_t n = 1;
    sscanf(argv[1], "%zu", &n);
    size_t fibn = fib(n);
    printf("fib(%zu) = %zu\n", n, fibn);
    return 0;
}
