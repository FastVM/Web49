
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

int getentropy(void *buffer, size_t length);

#if defined(WEB49_COUNT_ALLOC)
extern size_t web49_total_alloc;
#define web49_req_mem(size) (web49_total_alloc += (size))
#else
#define web49_req_mem(size) ((void)(size))
#endif

#define web49_malloc(size) (malloc(size))
#define web49_alloc0(size) (calloc(size, 1))
#define web49_realloc(ptr, size) (realloc(ptr, size))
#define web49_free(ptr) (free((void *)ptr))

#endif
