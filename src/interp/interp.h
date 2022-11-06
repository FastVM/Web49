#if !defined(WEB49_HEADER_INTERP)
#define WEB49_HEADER_INTERP

#include "../ast.h"

typedef uint64_t web49_interp_instr_t;

enum web49_interp_instr_enum_t {
    WEB49_INTERP_INSTR_DROP,
    WEB49_INTERP_INSTR_RETURN,

    WEB49_INTERP_INSTR_SET_GLOBAL,
    WEB49_INTERP_INSTR_GET_GLOBAL,
    WEB49_INTERP_INSTR_TEE_LOCAL,
    WEB49_INTERP_INSTR_GET_LOCAL,
    WEB49_INTERP_INSTR_SET_LOCAL,

    WEB49_INTERP_INSTR_I32_ADD,
    WEB49_INTERP_INSTR_I32_SUB,
    WEB49_INTERP_INSTR_I32_MUL,
    WEB49_INTERP_INSTR_I32_DIV_S,
    WEB49_INTERP_INSTR_I32_DIV_U,
    WEB49_INTERP_INSTR_I32_EQ,
    WEB49_INTERP_INSTR_I32_NE,
    WEB49_INTERP_INSTR_I32_LT_S,
    WEB49_INTERP_INSTR_I32_GT_S,
    WEB49_INTERP_INSTR_I32_LE_S,
    WEB49_INTERP_INSTR_I32_GE_S,
    WEB49_INTERP_INSTR_I32_LT_U,
    WEB49_INTERP_INSTR_I32_GT_U,
    WEB49_INTERP_INSTR_I32_LE_U,
    WEB49_INTERP_INSTR_I32_GE_U,
    WEB49_INTERP_INSTR_I32_SHL,
    WEB49_INTERP_INSTR_I32_SHR_U,
    WEB49_INTERP_INSTR_I32_SHR_S,
    WEB49_INTERP_INSTR_I32_EQZ,
    WEB49_INTERP_INSTR_I32_AND,
    WEB49_INTERP_INSTR_I32_OR,
    WEB49_INTERP_INSTR_I32_XOR,
    WEB49_INTERP_INSTR_I32_STORE8,
    WEB49_INTERP_INSTR_I32_LOAD8_S,
    WEB49_INTERP_INSTR_I32_LOAD8_U,
    WEB49_INTERP_INSTR_I32_STORE16,
    WEB49_INTERP_INSTR_I32_LOAD16_S,
    WEB49_INTERP_INSTR_I32_LOAD16_U,
    WEB49_INTERP_INSTR_I32_STORE,
    WEB49_INTERP_INSTR_I32_LOAD,

    WEB49_INTERP_INSTR_I64_EXTEND_I32_U,
    WEB49_INTERP_INSTR_I64_EXTEND_I32_S,
    WEB49_INTERP_INSTR_I32_WRAP_I64,

    WEB49_INTERP_INSTR_I64_ADD,
    WEB49_INTERP_INSTR_I64_SUB,
    WEB49_INTERP_INSTR_I64_MUL,
    WEB49_INTERP_INSTR_I64_DIV_S,
    WEB49_INTERP_INSTR_I64_DIV_U,
    WEB49_INTERP_INSTR_I64_EQ,
    WEB49_INTERP_INSTR_I64_NE,
    WEB49_INTERP_INSTR_I64_LT_S,
    WEB49_INTERP_INSTR_I64_GT_S,
    WEB49_INTERP_INSTR_I64_LE_S,
    WEB49_INTERP_INSTR_I64_GE_S,
    WEB49_INTERP_INSTR_I64_LT_U,
    WEB49_INTERP_INSTR_I64_GT_U,
    WEB49_INTERP_INSTR_I64_LE_U,
    WEB49_INTERP_INSTR_I64_GE_U,
    WEB49_INTERP_INSTR_I64_SHL,
    WEB49_INTERP_INSTR_I64_SHR_U,
    WEB49_INTERP_INSTR_I64_SHR_S,
    WEB49_INTERP_INSTR_I64_EQZ,
    WEB49_INTERP_INSTR_I64_AND,
    WEB49_INTERP_INSTR_I64_OR,
    WEB49_INTERP_INSTR_I64_XOR,
    WEB49_INTERP_INSTR_I64_STORE8,
    WEB49_INTERP_INSTR_I64_LOAD8_S,
    WEB49_INTERP_INSTR_I64_LOAD8_U,
    WEB49_INTERP_INSTR_I64_STORE16,
    WEB49_INTERP_INSTR_I64_LOAD16_S,
    WEB49_INTERP_INSTR_I64_LOAD16_U,
    WEB49_INTERP_INSTR_I64_STORE32,
    WEB49_INTERP_INSTR_I64_LOAD32_S,
    WEB49_INTERP_INSTR_I64_LOAD32_U,
    WEB49_INTERP_INSTR_I64_STORE,
    WEB49_INTERP_INSTR_I64_LOAD,

    WEB49_INTERP_INSTR_F64_LOAD,

    WEB49_INTERP_INSTR_DATA_CONST,

    WEB49_INTERP_INSTR_CALL,
    WEB49_INTERP_INSTR_CALL_INDIRECT,

    WEB49_INTERP_INSTR_BLOCK,
    WEB49_INTERP_INSTR_END,

    WEB49_INTERP_INSTR_LOOP,
    WEB49_INTERP_INSTR_SELECT,
    WEB49_INTERP_INSTR_IF,
    WEB49_INTERP_INSTR_BR_IF,
    WEB49_INTERP_INSTR_BR,
    WEB49_INTERP_INSTR_BR_TABLE,

    WEB49_INTERP_INSTR_WASI_PROC_EXIT,
    WEB49_INTERP_INSTR_WASI_FD_WRITE,
    WEB49_INTERP_INSTR_WASI_FD_CLOSE,
    WEB49_INTERP_INSTR_WASI_FD_SEEK,

    WEB49_INTERP_MAX_INSTR,
};

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
    web49_interp_data_t *locals;
    web49_interp_block_t **funcs;
    web49_interp_block_t **table;
    web49_section_type_entry_t *ftypes;
    uint64_t global_alloc;
    web49_interp_data_t *globals;
    uint8_t *memory;
    uint64_t nreturns;
};

union web49_interp_opcode_t {
    uint64_t opcode;
    web49_interp_data_t *ptr;
    web49_interp_data_t data;
    web49_interp_block_t *block;
};

struct web49_interp_block_t {
    uint64_t nlocals;
    uint64_t nparams;
    uint64_t nreturns;
    uint64_t ncode;
    web49_interp_opcode_t *code;
};

struct web49_interp_instr_buf_t {
    uint64_t head;
    uint64_t len;
    web49_instr_t *instrs;
};

web49_interp_block_t *web49_interp_import(web49_interp_t *interp, const char *mod, const char *sym);
web49_interp_block_t *web49_interp_read_block(web49_interp_t *interp, web49_interp_instr_buf_t *instrs);
void web49_interp_module(web49_module_t mod);

#endif
