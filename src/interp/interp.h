#if !defined(WEB49_HEADER_INTERP)
#define WEB49_HEADER_INTERP

#include "../ast.h"

union web49_interp_data_t;
typedef union web49_interp_data_t web49_interp_data_t;

struct web49_interp_t;
typedef struct web49_interp_t web49_interp_t;

union web49_interp_opcode_t;
typedef union web49_interp_opcode_t web49_interp_opcode_t;

struct web49_interp_block_t;
typedef struct web49_interp_block_t web49_interp_block_t;

struct web49_interp_instr_buf_t;
typedef struct web49_interp_instr_buf_t web49_interp_instr_buf_t;

union web49_interp_data_t {
    int64_t i64_s;
    int32_t i32_s;

    uint64_t i64_u;
    uint32_t i32_u;
};

struct web49_interp_t {
    web49_interp_data_t *stack;
};

union web49_interp_opcode_t {
    size_t opcode;
    web49_interp_data_t data;
    web49_interp_block_t *block;
};

struct web49_interp_block_t {
    web49_interp_opcode_t opcode;
};

struct web49_interp_instr_buf_t {
    uint64_t len;
    web49_instr_t *instrs;
    uint64_t head;
};

web49_interp_block_t *web49_instrs_read_block(web49_interp_t *interp, web49_interp_instr_buf_t *instrs);
void web49_interp_module(web49_module_t mod);

#endif
