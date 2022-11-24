#if !defined(WEB49_HEADER_INTERP_INTERP)
#define WEB49_HEADER_INTERP_INTERP

#include "../ast.h"

typedef uint64_t web49_interp_instr_t;

enum web49_interp_instr_enum_t {
    WEB49_INTERP_OPCODE_WASI = WEB49_MAX_OPCODE_NUM,
    WEB49_OPCODE_CALL0,
    WEB49_OPCODE_CALL1,
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
    WEB49_OPCODE_WITH_CONST0,
    WEB49_OPCODE_WITH_CONST1 = WEB49_OPCODE_WITH_CONST0 * 2,
    WEB49_OPCODE_WITH_CONST01 = WEB49_OPCODE_WITH_CONST0 * 3,
    WEB49_OPCODE_WITH_TMP = WEB49_OPCODE_WITH_CONST0 * 4,
    WEB49_OPCODE_REST_WASI = WEB49_OPCODE_WITH_CONST0 * 5,
    WEB49_OPCODE_WASI_FD_SEEK,
    WEB49_OPCODE_WASI_FD_FILESTAT_GET,
    WEB49_OPCODE_WASI_PATH_FILESTAT_GET,
    WEB49_OPCODE_WASI_ARGS_GET,
    WEB49_OPCODE_WASI_ARGS_SIZES_GET,
    WEB49_OPCODE_WASI_CLOCK_RES_GET,
    WEB49_OPCODE_WASI_CLOCK_TIME_GET,
    WEB49_OPCODE_WASI_ENVIRON_GET,
    WEB49_OPCODE_WASI_ENVIRON_SIZES_GET,
    WEB49_OPCODE_WASI_FD_ADVISE,
    WEB49_OPCODE_WASI_FD_ALLOCATE,
    WEB49_OPCODE_WASI_FD_CLOSE,
    WEB49_OPCODE_WASI_FD_DATASYNC,
    WEB49_OPCODE_WASI_FD_FDSTAT_GET,
    WEB49_OPCODE_WASI_FD_FDSTAT_SET_FLAGS,
    WEB49_OPCODE_WASI_FD_FDSTAT_SET_RIGHTS,
    WEB49_OPCODE_WASI_FD_FILESTAT_SET_SIZE,
    WEB49_OPCODE_WASI_FD_FILESTAT_SET_TIMES,
    WEB49_OPCODE_WASI_FD_PREAD,
    WEB49_OPCODE_WASI_FD_PRESTAT_GET,
    WEB49_OPCODE_WASI_FD_PRESTAT_DIR_NAME,
    WEB49_OPCODE_WASI_FD_PWRITE,
    WEB49_OPCODE_WASI_FD_READ,
    WEB49_OPCODE_WASI_FD_READDIR,
    WEB49_OPCODE_WASI_FD_RENUMBER,
    WEB49_OPCODE_WASI_FD_SYNC,
    WEB49_OPCODE_WASI_FD_TELL,
    WEB49_OPCODE_WASI_FD_WRITE,
    WEB49_OPCODE_WASI_PATH_CREATE_DIRECTORY,
    WEB49_OPCODE_WASI_PATH_FILESTAT_SET_TIMES,
    WEB49_OPCODE_WASI_PATH_LINK,
    WEB49_OPCODE_WASI_PATH_OPEN,
    WEB49_OPCODE_WASI_PATH_READLINK,
    WEB49_OPCODE_WASI_PATH_REMOVE_DIRECTORY,
    WEB49_OPCODE_WASI_PATH_RENAME,
    WEB49_OPCODE_WASI_PATH_SYMLINK,
    WEB49_OPCODE_WASI_PATH_UNLINK_FILE,
    WEB49_OPCODE_WASI_POLL_ONEOFF,
    WEB49_OPCODE_WASI_PROC_EXIT,
    WEB49_OPCODE_WASI_PROC_RAISE,
    WEB49_OPCODE_WASI_RANDOM_GET,
    WEB49_OPCODE_WASI_SCHED_YIELD,
    WEB49_OPCODE_WASI_SOCK_RECV,
    WEB49_OPCODE_WASI_SOCK_SEND,
    WEB49_OPCODE_WASI_SOCK_SHUTDOWN,
    WEB49_MAX_OPCODE_INTERP_NUM,
};

union web49_interp_data_t;
typedef union web49_interp_data_t web49_interp_data_t;

struct web49_interp_t;
typedef struct web49_interp_t web49_interp_t;

struct web49_interp_extra_t;
typedef struct web49_interp_extra_t web49_interp_extra_t;

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
    uint64_t out;
    uint64_t *box;
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

struct web49_interp_extra_t {
    web49_interp_data_t *restrict globals;
    web49_interp_block_t **table;
    web49_interp_block_t *funcs;
    const char **args;
    uint64_t memsize;
    web49_section_type_t type_section;
    web49_section_import_t import_section;
    web49_section_code_t code_section;
    web49_section_function_t function_section;
    web49_section_global_t global_section;
    web49_section_data_t data_section;
    web49_section_table_t table_section;
    web49_section_element_t element_section;
    uint8_t memory[0];
};

struct web49_interp_t {
    web49_interp_data_t *restrict locals;
    web49_interp_extra_t *restrict extra;
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
        web49_section_code_entry_t *code_entry;
        web49_section_import_entry_t *import_entry;
    };
    bool is_code;
};

struct web49_read_block_state_t {
    void *ptrs;
    uint64_t **bufs;
    web49_interp_t *interp;
    web49_interp_build_t build;
    web49_interp_link_t *links;
    uint32_t depth;
    uint32_t nlocals;
    uint64_t alloc_links;
    uint64_t nlinks;
};

typedef web49_interp_data_t (*web49_env_func_t)(void *mem, web49_interp_data_t *locals);

web49_env_func_t web49_env_func(const char *name);

uint64_t *web49_interp_link_box(void);
void web49_interp_link_get(web49_read_block_state_t *state, uint64_t out, uint64_t *from);
void web49_interp_import(void **ptrs, const char *mod, const char *sym, web49_interp_block_t *block);
web49_interp_t web49_interp_module(web49_module_t mod, const char **args);
web49_interp_data_t web49_interp_block_run(web49_interp_t interp, web49_interp_block_t *block);

// opt.c

web49_instr_t web49_interp_opt(web49_instr_t cur);

#endif
