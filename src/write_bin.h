
#if !defined(WEB49_HEADER_WRITEBIN)
#define WEB49_HEADER_WRITEBIN

#include "./ast.h"

struct web49_writebin_buf_t;
typedef struct web49_writebin_buf_t web49_writebin_buf_t;

struct web49_writebin_buf_t {
    uint8_t *data;
    size_t len;
    size_t alloc;
};

void web49_writebin_uleb(web49_writebin_buf_t *out, uint64_t x);
void web49_writebin_sleb(web49_writebin_buf_t *out, int64_t x);

void web49_writebin_type_function(web49_writebin_buf_t *out, web49_type_function_t type);
void web49_writebin_type_table(web49_writebin_buf_t *out, web49_type_table_t type);
void web49_writebin_type_memory(web49_writebin_buf_t *out, web49_limits_t type);
void web49_writebin_type_global(web49_writebin_buf_t *out, web49_type_global_t type);
void web49_writebin_type(web49_writebin_buf_t *out, web49_type_t type);

void web49_writebin_instr(web49_writebin_buf_t *out, web49_instr_t instr);

void web49_writebin_section_custom(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_type(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_import(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_function(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_table(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_memory(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_global(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_export(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_start(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_element(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_code(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_section_data(web49_writebin_buf_t *out, web49_section_t mod);

void web49_writebin_section(web49_writebin_buf_t *out, web49_section_t mod);
void web49_writebin_module(web49_writebin_buf_t *out, web49_module_t mod);

#endif
