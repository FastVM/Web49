
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    printf("argc = %i\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("strlen(argv[%i]) = %i\n", i, (int) strlen(argv[i]));
    }
    printf("argv[%i] = %p\n", argc, argv[argc]);
}
