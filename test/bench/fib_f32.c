
#include <stdio.h>

float fib(float n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int main(int argc, const char **argv) {
    float n = 35;
    if (argc > 1) {
        sscanf(argv[1], "%f", &n);
    }
    printf("%f\n", fib(n));
    return 0;
}
