
#if !defined(WEB49_HEADER_LIB)
#define WEB49_HEADER_LIB

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./config.h"

#define web49_parse_float_to(str, ptr) (sscanf((str), "%f", (ptr)))
#define web49_parse_double_to(str, ptr) (sscanf((str), "%lf", (ptr)))

#if defined(_WIN32)
#define getentropy(buf, len) ((int)0)
#else
int getentropy(void *buffer, size_t length);
#endif

#if WEB49_COUNT_ALLOC
extern size_t web49_total_alloc;
#define web49_req_mem(size) (web49_total_alloc += (size))
#else
#define web49_req_mem(size) ((void)(size))
#endif

#define web49_malloc(size) (malloc(size))
#define web49_alloc0(size) (calloc(size, 1))
#define web49_realloc(ptr, size) (realloc(ptr, size))
#define web49_free(ptr) (free((void *)ptr))

#define web49_unreachable() __builtin_unreachable()

#if WEB49_DEBUG_DIE
#define web49_die() __builtin_trap()
#else
#define web49_die() exit(1)
#endif

#define web49_error(...)          \
    fprintf(stderr, __VA_ARGS__); \
    web49_die()

#endif
