
#include <stdio.h>

size_t fib(size_t n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int main() {
    printf("%zu\n", fib(35));
    return 0;
}
