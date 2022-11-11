#if !defined(WEB49_HEADER_INTERP_TABLE)
#define WEB49_HEADER_INTERP_TABLE

#include "interp.h"

struct web49_interp_table_t;
typedef struct web49_interp_table_t web49_interp_table_t;

enum {
    WEB49_INTERP_TABLE_END,
    WEB49_INTERP_TABLE_ANY,
    WEB49_INTERP_TABLE_ARGS,
    WEB49_INTERP_TABLE_ARGS_INDIRECT,
    WEB49_INTERP_TABLE_BLOCK,
    WEB49_INTERP_TABLE_RET,
    WEB49_INTERP_TABLE_RET_INDIRECT,
    WEB49_INTERP_TABLE_I32,
    WEB49_INTERP_TABLE_I64,
    WEB49_INTERP_TABLE_F32,
    WEB49_INTERP_TABLE_F64,
};

struct web49_interp_table_t {
    uint8_t in[8];
    uint8_t out[8];
    bool branch: 1;
    bool fail: 1;
};

extern const web49_interp_table_t web49_interp_opcode_stack_effect[WEB49_MAX_OPCODE_INTERP_NUM];

#endif