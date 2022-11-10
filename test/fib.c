
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
    size_t n = 0;
    for (char *head = argv[1]; *head != '\0'; head += 1) {
        n *= 10;
        n += *head - '0';
    }
    size_t fibn = fib(n);
    printf("fib(%zu) = %zu\n", n, fibn);
    return 0;
}
