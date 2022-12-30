#if !defined(WEB49_HEADER_API_API)
#define WEB49_HEADER_API_API

#include "../interp/interp.h"

web49_env_func_t web49_api_import_wasi(void *wasi, const char *func);
web49_env_func_t web49_api_import_raylib(const char *func);

#endif