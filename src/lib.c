#include "./lib.h"

#if WEB49_COUNT_ALLOC
size_t web49_total_alloc = 0;
#endif

char *web49_format_float(float num) {
    size_t size = snprintf(NULL, 0, "%f", num);
    char *str = malloc(sizeof(char) * (size + 1));
    snprintf(str, size+1, "%f", num);
    return str;
}
char *web49_format_double(double num) {
    size_t size = snprintf(NULL, 0, "%lf", num);
    char *str = malloc(sizeof(char) * (size + 1));
    snprintf(str, size+1, "%lf", num);
    return str;
}