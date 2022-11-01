
#if !defined(WEB49_HEADER_READWAT)
#define WEB49_HEADER_READWAT

#include "ast.h"
#include "io.h"

web49_opcode_t web49_readwat_name_to_opcode(const char *name);
const char *web49_readwat_name(web49_io_input_t *in);
web49_module_t web49_readwat_module(web49_io_input_t *in);

#endif
