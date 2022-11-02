
extern void print(int n);

int fib(int n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n-2) + fib(n-1);
    }
}

void _start() {
    print(10);
}
