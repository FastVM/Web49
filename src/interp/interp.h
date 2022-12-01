#if !defined(WEB49_HEADER_INTERP_INTERP)
#define WEB49_HEADER_INTERP_INTERP

#include "../ast.h"

typedef uint64_t web49_interp_instr_t;

enum web49_interp_instr_enum_t {
    WEB49_MIN_OPCODE_INTERP = WEB49_MAX_OPCODE_NUM,
    WEB49_OPCODE_FFI_CALL,
    WEB49_OPCODE_IF_I32_EQZ,
    WEB49_OPCODE_IF_I32_EQ,
    WEB49_OPCODE_IF_I32_NE,
    WEB49_OPCODE_IF_I32_LT_S,
    WEB49_OPCODE_IF_I32_LT_U,
    WEB49_OPCODE_IF_I32_GT_S,
    WEB49_OPCODE_IF_I32_GT_U,
    WEB49_OPCODE_IF_I32_LE_S,
    WEB49_OPCODE_IF_I32_LE_U,
    WEB49_OPCODE_IF_I32_GE_S,
    WEB49_OPCODE_IF_I32_GE_U,
    WEB49_OPCODE_IF_I64_EQZ,
    WEB49_OPCODE_IF_I64_EQ,
    WEB49_OPCODE_IF_I64_NE,
    WEB49_OPCODE_IF_I64_LT_S,
    WEB49_OPCODE_IF_I64_LT_U,
    WEB49_OPCODE_IF_I64_GT_S,
    WEB49_OPCODE_IF_I64_GT_U,
    WEB49_OPCODE_IF_I64_LE_S,
    WEB49_OPCODE_IF_I64_LE_U,
    WEB49_OPCODE_IF_I64_GE_S,
    WEB49_OPCODE_IF_I64_GE_U,
    WEB49_OPCODE_IF_F32_EQ,
    WEB49_OPCODE_IF_F32_NE,
    WEB49_OPCODE_IF_F32_LT,
    WEB49_OPCODE_IF_F32_GT,
    WEB49_OPCODE_IF_F32_LE,
    WEB49_OPCODE_IF_F32_GE,
    WEB49_OPCODE_IF_F64_EQ,
    WEB49_OPCODE_IF_F64_NE,
    WEB49_OPCODE_IF_F64_LT,
    WEB49_OPCODE_IF_F64_GT,
    WEB49_OPCODE_IF_F64_LE,
    WEB49_OPCODE_IF_F64_GE,
    WEB49_OPCODE_IF_I32_AND,
    WEB49_OPCODE_IF_I32_OR,
    WEB49_OPCODE_IF_I32_XOR,
    WEB49_OPCODE_WITH_CONST_LAST,
    WEB49_OPCODE_WITH_TMP = WEB49_OPCODE_WITH_CONST_LAST * 2,
    WEB49_MAX_OPCODE_INTERP_NUM,
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

struct web49_read_block_state_t;
typedef struct web49_read_block_state_t web49_read_block_state_t;

struct web49_interp_build_t;
typedef struct web49_interp_build_t web49_interp_build_t;

struct web49_interp_link_t;
typedef struct web49_interp_link_t web49_interp_link_t;

struct web49_interp_link_t {
    uint32_t *box;
    uint32_t out;
};

struct web49_interp_build_t {
    uint64_t alloc;
    web49_interp_opcode_t *code;
    uint64_t ncode;
};

union web49_interp_data_t {
    int64_t i64_s;
    int32_t i32_s;

    uint64_t i64_u;
    uint32_t i32_u;

    float f32;
    double f64;
};

typedef web49_interp_data_t (*web49_env_func_t)(web49_interp_t interp);
typedef web49_env_func_t (*web49_env_table_t)(void *state, const char *mod, const char *sym);

struct web49_interp_t {
    web49_interp_data_t *restrict locals;
    uint8_t *restrict memory;
    web49_interp_data_t *restrict globals;
    web49_interp_block_t **table;
    web49_interp_block_t *funcs;
    const char **args;
    void *import_state;
    uint32_t memsize;
    web49_env_table_t import_func;
    void *locals_base;
    web49_interp_data_t **restrict stacks;
    web49_interp_opcode_t **restrict returns;
};

union web49_interp_opcode_t {
    void *opcode;
    void *ptr;
    web49_interp_data_t data;
    web49_interp_block_t *block;
    size_t link;
};

struct web49_interp_block_t {
    web49_interp_opcode_t *code;
    uint32_t nlocals;
    uint16_t nparams;
    uint16_t nreturns;
    union {
        struct {
            uint32_t num_instrs;
            web49_instr_t *instrs;
        };
        struct {
            const char *module_str;
            const char *field_str;
        };
    };
    bool is_code;
};

struct web49_read_block_state_t {
    void *ptrs;
    web49_interp_t *interp;
    web49_interp_build_t build;
    web49_interp_link_t *links;
    uint32_t **bufs_base;
    uint32_t bufs_alloc;
    uint32_t bufs_head;
    uint32_t depth;
    uint32_t nlocals;
    uint32_t alloc_links;
    uint32_t nlinks;
};

uint32_t *web49_interp_link_box(void);
void web49_interp_link_get(web49_read_block_state_t *state, uint32_t out, uint32_t *from);
web49_interp_t web49_interp_module(web49_module_t mod, const char **args);
web49_interp_data_t web49_interp_block_run(web49_interp_t interp, web49_interp_block_t *block);

void web49_free_interp(web49_interp_t interp);

#endif
