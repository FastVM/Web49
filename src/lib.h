
#if !defined(WEB49_HEADER_LIB)
#define WEB49_HEADER_LIB

#include <assert.h>
#include <ctype.h>
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

#define web49_bump(size) (malloc(size))
#define web49_malloc(size) (malloc(size))
#define web49_alloc0(size) (calloc(size, 1))
#define web49_realloc(ptr, size) (realloc(ptr, size))
#define web49_free(ptr) (free((void *)ptr))

#endif
