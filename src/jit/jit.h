#if !defined(WEB49_HEADER_JIT_JIT)
#define WEB49_HEADER_JIT_JIT

#include "../ast.h"

struct web49_jit_t;
typedef struct web49_jit_t web49_jit_t;

struct web49_jit_t {
    void *Dst;
};

web49_jit_t web49_jit_module(web49_module_t mod, const char **args);

#endif
