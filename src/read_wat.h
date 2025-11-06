
#if !defined(WEB49_HEADER_READWAT)
#define WEB49_HEADER_READWAT

#include "./ast.h"
#include "./io.h"
enum {
    WEB49_READWAT_EXPR_TAG_INIT,
    WEB49_READWAT_EXPR_TAG_FUN,
    WEB49_READWAT_EXPR_TAG_SYM,
    WEB49_READWAT_EXPR_TAG_STR,
};

typedef struct web49_readwat_table_t web49_readwat_table_t;
typedef struct web49_readwat_state_t web49_readwat_state_t;
typedef struct web49_readwat_expr_t web49_readwat_expr_t;

void web49_readwat_skip(web49_io_input_t *in);
const char *web49_readwat_sym_to_str(web49_readwat_expr_t expr);
web49_instr_t web49_readwat_instr(web49_readwat_state_t *out, web49_readwat_expr_t code);
uint64_t web49_readwat_expr_to_u64f(web49_readwat_expr_t expr);
uint32_t web49_readwat_expr_to_u32f(web49_readwat_expr_t expr);
uint64_t web49_readwat_expr_to_u64(web49_readwat_table_t *table, web49_readwat_expr_t expr);
int64_t web49_readwat_expr_to_i64(web49_readwat_expr_t expr);
web49_readwat_expr_t web49_readwat_expr_base(web49_io_input_t *in);
web49_readwat_expr_t web49_readwat_expr(web49_io_input_t *in);
void web49_readwat_state_type_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
void web49_readwat_state_import_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
void web49_readwat_state_func_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
void web49_readwat_state_table_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
void web49_readwat_state_global_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
void web49_readwat_state_export_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
void web49_readwat_state_elem_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
void web49_readwat_state_data_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
void web49_readwat_state_memory_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);

struct web49_readwat_table_t {
    uint64_t len;
    const char **key;
    uint64_t *value;
    uint64_t alloc;
};

struct web49_readwat_state_t {
    uint64_t num_func_imports;
    uint64_t block_depth;

    web49_readwat_table_t func_table;
    web49_readwat_table_t type_table;
    web49_readwat_table_t local_table;
    web49_readwat_table_t branch_table;
    web49_readwat_table_t global_table;
    web49_readwat_table_t table_table;
    web49_readwat_table_t memory_table;

    uint64_t alloc_type;
    uint64_t alloc_import;
    uint64_t alloc_function;
    uint64_t alloc_table;
    uint64_t alloc_global;
    uint64_t alloc_memory;
    uint64_t alloc_export;
    uint64_t alloc_element;
    uint64_t alloc_code;
    uint64_t alloc_data;

    web49_section_type_t stype;
    web49_section_import_t simport;
    web49_section_function_t sfunction;
    web49_section_table_t stable;
    web49_section_global_t sglobal;
    web49_section_memory_t smemory;
    web49_section_export_t sexport;
    web49_section_element_t selement;
    web49_section_code_t scode;
    web49_section_data_t sdata;
};

struct web49_readwat_expr_t {
    uint64_t start;
    uint64_t end;
    union {
        struct {
            const char *fun_fun;
            uint64_t fun_nargs;
            web49_readwat_expr_t *fun_args;
        };
        struct {
            uint64_t len_str;
            uint8_t *str;
        };
        const char *sym;
    };
    uint8_t tag;
};

const char *web49_readwat_name(web49_io_input_t *in);
web49_module_t web49_readwat_module(web49_io_input_t *in);
web49_module_t web49_readwat_to_module(web49_readwat_expr_t expr);

#endif
