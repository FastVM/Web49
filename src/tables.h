
#if !defined(WEB49_HEADER_TABLES)
#define WEB49_HEADER_TABLES

#include "./ast.h"

typedef struct web49_table_stack_effect_t web49_table_stack_effect_t;

enum {
    WEB49_TABLE_STACK_EFFECT_END,
    WEB49_TABLE_STACK_EFFECT_ANY,
    WEB49_TABLE_STACK_EFFECT_ARGS,
    WEB49_TABLE_STACK_EFFECT_ARGS_INDIRECT,
    WEB49_TABLE_STACK_EFFECT_BLOCK,
    WEB49_TABLE_STACK_EFFECT_RET,
    WEB49_TABLE_STACK_EFFECT_RET_INDIRECT,
    WEB49_TABLE_STACK_EFFECT_I32,
    WEB49_TABLE_STACK_EFFECT_I64,
    WEB49_TABLE_STACK_EFFECT_F32,
    WEB49_TABLE_STACK_EFFECT_F64,
    WEB49_TABLE_STACK_EFFECT_V128,
};

struct web49_table_stack_effect_t {
    uint8_t in[8];
    uint8_t out[8];
    bool branch : 1;
    bool fail : 1;
};

bool web49_opcode_is_simd(web49_opcode_t);
size_t web49_opcode_byte_count(uint8_t first_byte);
web49_opcode_t web49_bytes_to_opcode(uint8_t *bytes);
void web49_opcode_to_bytes(web49_opcode_t opcode, size_t *out_len, uint8_t *out_bytes);
uint8_t web49_opcode_skip(web49_opcode_t opcode);
extern const web49_table_stack_effect_t web49_stack_effects[WEB49_MAX_OPCODE_NUM];
extern const size_t web49_opcode_memsize[WEB49_MAX_OPCODE_NUM];
extern const web49_immediate_id_t web49_opcode_immediate[WEB49_MAX_OPCODE_NUM];
web49_opcode_t web49_name_to_opcode(const char *name);
const char *web49_opcode_to_name(web49_opcode_t opcode);

#endif
