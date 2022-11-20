
#include <stdio.h>
#include <stdlib.h>

double fib(double n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int main(int argc, char **argv) {
    double n = 0;
    for (char *head = argv[1]; *head != '\0'; head += 1) {
        n *= 10;
        n += *head - '0';
    }
    double fibn = fib(n);
    printf("fib(%lf) = %lf\n", n, fibn);
    return 0;
}
