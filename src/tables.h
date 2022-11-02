
#if !defined(WEB49_HEADER_TABLES)
#define WEB49_HEADER_TABLES

#include "ast.h"

extern const size_t web49_opcode_memsize[WEB49_MAX_OPCODE_NUM];
extern const web49_immediate_id_t web49_opcode_immediate[WEB49_MAX_OPCODE_NUM];
web49_opcode_t web49_name_to_opcode(const char *name);
const char *web49_opcode_to_name(web49_opcode_t opcode);

#endif
