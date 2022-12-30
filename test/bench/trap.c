#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    int *x = (int*) (SIZE_MAX);
    return *x;
}