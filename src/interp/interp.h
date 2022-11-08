#if !defined(WEB49_HEADER_INTERP)
#define WEB49_HEADER_INTERP

#include "../ast.h"

typedef uint64_t web49_interp_instr_t;

enum web49_interp_instr_enum_t {
    WEB49_INTERP_OPCODE_WASI = WEB49_MAX_OPCODE_NUM,
    WEB49_OPCODE_END_WITH,
    WEB49_OPCODE_BLOCK_RETURNS,
    WEB49_OPCODE_IF_RETURNS,
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
    uint64_t memsize;
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
const char *web49_interp_opcode_to_name(size_t opcode);

#endif
