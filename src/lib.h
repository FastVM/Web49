
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
#include <errno.h>

int getentropy(void *buffer, size_t length);

#if defined(WEB49_COUNT_ALLOC)
extern size_t web49_total_alloc;
#define web49_req_mem(size) (web49_total_alloc += (size))
#else
#define web49_req_mem(size) ((void)(size))
#endif

#if 0
#define web49_malloc(size) (printf("%s@%s+%zu\n", __FILE__, __LINE__, (size_t)(size)), malloc(size))
#define web49_alloc0(size) (printf("%s@%s+%zu\n", __FILE__, __LINE__, (size_t)(size)), calloc(size, 1))
#define web49_realloc(ptr, size) (printf("%s@%s+%zu\n", __FILE__, __LINE__, (size_t)(size)), realloc(ptr, size))
#define web49_free(ptr) (free((void *)ptr))
#else
static void *web49_malloc(size_t size) {
	web49_req_mem(size);
	void *ret = malloc(size);
	if (size != 0 && ret == NULL) {
		fprintf(stderr, "malloc(%zu) => %s\n", size, strerror(errno));
		__builtin_unreachable();
	}
	return ret;
}
static void *web49_alloc0(size_t size) {
	web49_req_mem(size);
	void *ret = calloc(size, 1);
	if (size != 0 && ret == NULL) {
		fprintf(stderr, "calloc(%zu, 1) => %s\n", size, strerror(errno));
		__builtin_unreachable();
	}
	return ret;
}
static void *web49_realloc(void *ptr, size_t size) {
	web49_req_mem(size);
	void *ret = realloc(ptr, size);
	if (size != 0 && ret == NULL) {
		fprintf(stderr, "realloc(%p, %zu) => %s\n", ptr, size, strerror(errno));
		__builtin_unreachable();
	}
	return ret;
}
static void web49_free(const void *ptr) {
	free((void*) ptr);
}
static char *web49_strdup(const char *restrict str) {
	size_t len = strlen(str);
	char *ret = web49_malloc(len + 1);
	for (size_t i = 0; i < len; i++) {
		ret[i] = str[i];
	}
	ret[len] = '\0';
	return ret;
}
#endif

#endif
