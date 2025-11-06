#if !defined(WEB49_HEADER_INTERP_INTERP)
#define WEB49_HEADER_INTERP_INTERP

#include "../ast.h"

typedef uint64_t web49_interp_instr_t;

enum web49_interp_instr_enum_t {
    WEB49_MIN_OPCODE_INTERP = WEB49_MAX_OPCODE_NUM,
    WEB49_OPCODE_EXIT,
    WEB49_OPCODE_FFI_CALL0,
    WEB49_OPCODE_FFI_CALL1,
    WEB49_OPCODE_IF_I32_EQ,
    WEB49_OPCODE_IF_I32_LT_S,
    WEB49_OPCODE_IF_I32_LT_U,
    WEB49_OPCODE_IF_I32_GT_S,
    WEB49_OPCODE_IF_I32_GT_U,
    WEB49_OPCODE_IF_I64_EQ,
    WEB49_OPCODE_IF_I64_LT_S,
    WEB49_OPCODE_IF_I64_LT_U,
    WEB49_OPCODE_IF_I64_GT_S,
    WEB49_OPCODE_IF_I64_GT_U,
    WEB49_OPCODE_CALL_DONE0,
    WEB49_OPCODE_CALL_DONE1,
    WEB49_OPCODE_CALL_DONE2,
    WEB49_OPCODE_CALL_DONE4,
    WEB49_OPCODE_CALL_DONE8,
    WEB49_OPCODE_CALL_DONE16,
    WEB49_OPCODE_CALL_DONE32,
    WEB49_OPCODE_CALL_DONE64,
    WEB49_OPCODE_CALL_DONE128,
    WEB49_OPCODE_CALL_DONE256,
    WEB49_OPCODE_CALL_DONE512,
    WEB49_OPCODE_CALL_DONE1024,
    WEB49_MAX_OPCODE_INTERP,
#if WEB49_OPT_CONST
    WEB49_OPCODE_WITH_CONST0 = WEB49_MAX_OPCODE_INTERP * 1,
    WEB49_OPCODE_WITH_CONST1 = WEB49_MAX_OPCODE_INTERP * 2,
    WEB49_MAX_OPCODE_INTERP_NUM = WEB49_MAX_OPCODE_INTERP * 4,
#else
    WEB49_OPCODE_WITH_CONST1 = WEB49_MAX_OPCODE_INTERP * 1,
    WEB49_MAX_OPCODE_INTERP_NUM = WEB49_MAX_OPCODE_INTERP * 2,
#endif
};

typedef union web49_interp_data_t web49_interp_data_t;
typedef struct web49_interp_t web49_interp_t;
typedef union web49_interp_opcode_t web49_interp_opcode_t;
typedef struct web49_interp_block_t web49_interp_block_t;
typedef struct web49_read_block_state_t web49_read_block_state_t;
typedef struct web49_interp_build_t web49_interp_build_t;
typedef struct web49_interp_link_t web49_interp_link_t;
typedef struct web49_env_t web49_env_t;
typedef struct web49_interp_table_t web49_interp_table_t;

typedef web49_interp_data_t (*web49_env_func_t)(void *state, web49_interp_t interp);
typedef web49_env_t *(*web49_env_table_t)(void *state, const char *mod, const char *sym);

struct web49_env_t {
    void *state;
    web49_env_func_t func;
};

struct web49_interp_link_t {
    uint32_t *box;
    uint32_t out;
};

struct web49_interp_build_t {
    web49_interp_opcode_t *code;
    uint32_t alloc;
    uint32_t ncode;
};

union web49_interp_data_t {
    int64_t i64_s;
    int32_t i32_s;

    uint64_t i64_u;
    uint32_t i32_u;

    float f32;
    double f64;
};

struct web49_interp_table_t {
    void **restrict elems;
    size_t size;
};

struct web49_interp_t {
    web49_interp_data_t *restrict locals;
    uint8_t *restrict memory;
    web49_interp_data_t *restrict globals;
    web49_interp_table_t *restrict tables;
    size_t num_tables;
    web49_interp_block_t *funcs;
    void *import_state;
    size_t num_env;
    void **env_states;
    web49_env_table_t *env_funcs;
    size_t env_alloc;
    void *locals_base;
    web49_interp_data_t **restrict stacks;
    web49_interp_opcode_t **restrict returns;
    web49_interp_data_t *yield_base;
    uint32_t memsize;
    uint32_t num_funcs;
};

union web49_interp_opcode_t {
#if WEB49_USE_SWITCH
    size_t opcode;
#else
    void *opcode;
#endif
    web49_interp_opcode_t *opcodes;
    web49_env_t *func;
    web49_interp_data_t data;
    web49_interp_block_t *block;
    size_t link;
};

struct web49_interp_block_t {
    web49_interp_opcode_t *code;
    // uint32_t nlocals : 32;
    // uint32_t nparams : 16;
    // uint32_t nreturns : 15;
    // bool is_code : 1;
    uint32_t nlocals;
    uint8_t nparams;
    uint8_t nreturns;
    bool is_code;
    union {
        struct {
            web49_instr_t *instrs;
            uint32_t num_instrs;
        };
        struct {
            const char *module_str;
            const char *field_str;
        };
    };
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

web49_env_t *web49_env_new(void *state, web49_env_func_t func);
uint32_t *web49_interp_link_box(void);
void web49_interp_link_get(web49_read_block_state_t *state, uint32_t out, uint32_t *from);
web49_interp_t web49_interp_module(web49_module_t mod);
void web49_interp_add_import_func(web49_interp_t *ptr_interp, void *env_state, web49_env_table_t env_func);
web49_interp_data_t *web49_interp_block_run(web49_interp_t *ptr_interp, web49_interp_block_t *block);
uint32_t web49_interp_read_instr(web49_read_block_state_t *state, web49_instr_t cur, uint32_t local);

void web49_free_interp(web49_interp_t interp);

static inline void web49_interp_bounds(uint32_t dest, uint32_t add) {
#if WEB49_CHECK_BOUNDS
    web49_error(stderr, "memory access 0x%zx of size 0x%zx out of bounds\n", (size_t)(low), (size_t)(add));
#else
    __builtin_trap();
#endif
}

static inline uint8_t *web49_interp_addr(web49_interp_t interp, uint32_t addr, uint32_t size) {
    if (interp.memsize < addr + size) {
        web49_interp_bounds(addr, size);
    };
    return &interp.memory[addr];
}

// unsigned read
static inline uint8_t web49_interp_read_u8(web49_interp_t interp, uint32_t addr) {
    return *web49_interp_addr(interp, addr, sizeof(uint8_t));
}

static inline uint16_t web49_interp_read_u16(web49_interp_t interp, uint32_t addr) {
    uint8_t *ptr = web49_interp_addr(interp, addr, sizeof(uint16_t));
    return (uint16_t)ptr[0] | (uint16_t)ptr[1] << 8;
}

static inline uint32_t web49_interp_read_u32(web49_interp_t interp, uint32_t addr) {
    uint8_t *ptr = web49_interp_addr(interp, addr, sizeof(uint32_t));
    return ((uint32_t)ptr[0]) | ((uint32_t)ptr[1] << 8) | ((uint32_t)ptr[2] << 16) | ((uint32_t)ptr[3] << 24);
}

static inline uint64_t web49_interp_read_u64(web49_interp_t interp, uint32_t addr) {
    uint8_t *ptr = web49_interp_addr(interp, addr, sizeof(uint64_t));
    return ((uint64_t)ptr[0]) | ((uint64_t)ptr[1] << 8) | ((uint64_t)ptr[2] << 16) | ((uint64_t)ptr[3] << 24) | ((uint64_t)ptr[4] << 32) | ((uint64_t)ptr[5] << 40) | ((uint64_t)ptr[6] << 48) | ((uint64_t)ptr[7] << 56);
}

// signed read
static inline int8_t web49_interp_read_i8(web49_interp_t interp, uint32_t addr) {
    return (int8_t)web49_interp_read_u8(interp, addr);
}

static inline int16_t web49_interp_read_i16(web49_interp_t interp, uint32_t addr) {
    return (int16_t)web49_interp_read_u16(interp, addr);
}

static inline int32_t web49_interp_read_i32(web49_interp_t interp, uint32_t addr) {
    return (int32_t)web49_interp_read_u32(interp, addr);
}

static inline int64_t web49_interp_read_i64(web49_interp_t interp, uint32_t addr) {
    return (int64_t)web49_interp_read_u64(interp, addr);
}

// float read
static inline float web49_interp_read_f32(web49_interp_t interp, uint32_t addr) {
    uint32_t x = web49_interp_read_u32(interp, addr);
    return *(float *) &x;
}

static inline double web49_interp_read_f64(web49_interp_t interp, uint32_t addr) {
    uint64_t x = web49_interp_read_u64(interp, addr);
    return *(double *) &x;
}

// unsigned write
static inline void web49_interp_write_u8(web49_interp_t interp, uint32_t addr, uint8_t value) {
    *web49_interp_addr(interp, addr, sizeof(uint8_t)) = value;
}

static inline void web49_interp_write_u16(web49_interp_t interp, uint32_t addr, uint16_t value) {
    uint8_t *ptr = web49_interp_addr(interp, addr, sizeof(uint16_t));
    ptr[0] = (uint8_t) value;
    ptr[1] = (uint8_t) (value >> 8);
}

static inline void web49_interp_write_u32(web49_interp_t interp, uint32_t addr, uint32_t value) {
    uint8_t *ptr = web49_interp_addr(interp, addr, sizeof(uint32_t));
    ptr[0] = (uint8_t) value;
    ptr[1] = (uint8_t) (value >> 8);
    ptr[2] = (uint8_t) (value >> 16);
    ptr[3] = (uint8_t) (value >> 24);
}

static inline void web49_interp_write_u64(web49_interp_t interp, uint32_t addr, uint64_t value) {
    uint8_t *ptr = web49_interp_addr(interp, addr, sizeof(uint64_t));
    ptr[0] = (uint8_t) value;
    ptr[1] = (uint8_t) (value >> 8);
    ptr[2] = (uint8_t) (value >> 16);
    ptr[3] = (uint8_t) (value >> 24);
    ptr[4] = (uint8_t) (value >> 32);
    ptr[5] = (uint8_t) (value >> 40);
    ptr[6] = (uint8_t) (value >> 48);
    ptr[7] = (uint8_t) (value >> 56);
}

// signed write
static inline void web49_interp_write_i8(web49_interp_t interp, uint32_t addr, int8_t value) {
    web49_interp_write_u8(interp, addr, (uint8_t) value);
}

static inline void web49_interp_write_i16(web49_interp_t interp, uint32_t addr, uint16_t value) {
    web49_interp_write_u16(interp, addr, (uint16_t) value);
}

static inline void web49_interp_write_i32(web49_interp_t interp, uint32_t addr, uint16_t value) {
    web49_interp_write_u32(interp, addr, (uint32_t) value);
}

static inline void web49_interp_write_i64(web49_interp_t interp, uint32_t addr, uint16_t value) {
    web49_interp_write_u64(interp, addr, (uint64_t) value);
}

// write read
static inline void web49_interp_write_f32(web49_interp_t interp, uint32_t addr, float value) {
    web49_interp_write_u32(interp, addr, *(uint32_t *)&value);
}

static inline void web49_interp_write_f64(web49_interp_t interp, uint32_t addr, double value) {
    web49_interp_write_u64(interp, addr, *(uint64_t *)&value);
}

#endif
