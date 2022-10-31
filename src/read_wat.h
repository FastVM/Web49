
#if !defined(WEB49_HEADER_READWAT)
#define WEB49_HEADER_READWAT

#include "ast.h"

web49_opcode_t web49_readwat_name_to_opcode(const char *name);
const char *web49_readwat_name(FILE *in);
web49_module_t web49_readwat_module(FILE *in);

#endif
