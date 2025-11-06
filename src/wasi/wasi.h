#if !defined(WEB49_HEADER_API_API)
#define WEB49_HEADER_API_API

#include "../interp/interp.h"

typedef struct web49_wasi_t web49_wasi_t;

struct web49_wasi_t {
    const char **argv;
    const char **envp;
};

web49_wasi_t *web49_wasi_new(const char **argv, const char **envp);
web49_env_t *web49_api_wasi(void *state, const char *module, const char *func);

#endif
