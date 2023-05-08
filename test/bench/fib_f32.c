
#include <stdio.h>

float fib(float n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int main(int argc, const char **argv) {
    printf("%f\n", fib(40));
    return 0;
}
