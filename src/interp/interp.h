#if !defined(WEB49_HEADER_INTERP)
#define WEB49_HEADER_INTERP

#include "../ast.h"

typedef uint64_t web49_interp_instr_t;

enum web49_interp_instr_enum_t {
    WEB49_INTERP_OPCODE_WASI = WEB49_MAX_OPCODE_NUM,
    WEB49_OPCODE_END_WITH,
    WEB49_OPCODE_BLOCK_RETURNS,
    WEB49_OPCODE_IF_RETURNS,
    WEB49_OPCODE_WASI_PROC_EXIT,
    WEB49_OPCODE_WASI_FD_WRITE,
    WEB49_OPCODE_WASI_FD_CLOSE,
    WEB49_OPCODE_WASI_FD_SEEK,
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
    web49_interp_data_t *returns;
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
web49_interp_block_t *web49_interp_read_block(web49_interp_t *interp, web49_interp_instr_buf_t *instrs, size_t nreturns);
void web49_interp_module(web49_module_t mod);

#endif
