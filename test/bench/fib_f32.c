
#include <stdio.h>

double fib(double n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int main(int argc, const char **argv) {
    double n = 35;
    if (argc > 1) {
        sscanf(argv[1], "%lf", &n);
    }
    printf("%lf\n", fib(n));
    return 0;
}
