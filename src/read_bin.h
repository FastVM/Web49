
#if !defined(WEB49_HEADER_READBIN)
#define WEB49_HEADER_READBIN

#include "ast.h"

uint64_t web49_readbin_uleb(FILE *in);
int64_t web49_readbin_sleb(FILE *in);
uint8_t web49_readbin_byte(FILE *in);
web49_preamble_t web49_readbin_preamble(FILE *in);
web49_section_header_t web49_readbin_section_header(FILE *in);
uint8_t web49_readbin_varuint1(FILE *in);
int32_t web49_readbin_varuint32(FILE *in);
int64_t web49_readbin_varuint64(FILE *in);
uint32_t web49_readbin_uint32(FILE *in);
uint64_t web49_readbin_uint64(FILE *in);
web49_lang_type_t web49_readbin_block_type(FILE *in);
web49_br_table_t web49_readbin_br_table(FILE *in);
web49_call_indirect_t web49_readbin_call_indirect(FILE *in);
web49_memory_immediate_t web49_readbin_memory_immediate(FILE *in);
web49_type_function_t web49_readbin_type_function(FILE *in);
web49_type_table_t web49_readbin_type_table(FILE *in);
web49_type_global_t web49_readbin_type_global(FILE *in);
web49_type_memory_t web49_readbin_type_memory(FILE *in);
web49_type_t web49_readbin_type(FILE *in, web49_lang_type_t tag);
web49_section_custom_t web49_readbin_section_custom(FILE *in, web49_section_header_t header);
web49_section_type_t web49_readbin_section_type(FILE *in);
web49_section_import_t web49_readbin_section_import(FILE *in);
web49_section_function_t web49_readbin_section_function(FILE *in);
web49_section_table_t web49_readbin_section_table(FILE *in);
web49_section_memory_t web49_readbin_section_memory(FILE *in);
web49_section_global_t web49_readbin_section_global(FILE *in);
web49_section_export_t web49_readbin_section_export(FILE *in);
web49_section_start_t web49_readbin_section_start(FILE *in);
web49_section_element_t web49_readbin_section_element(FILE *in);
web49_section_code_t web49_readbin_section_code(FILE *in);
web49_section_data_t web49_readbin_section_data(FILE *in);
web49_instr_immediate_t web49_readbin_instr_immediate(FILE *in, web49_immediate_id_t id);
web49_instr_t web49_readbin_init_expr(FILE *in);
web49_instr_t web49_readbin_instr(FILE *in);
web49_section_t web49_readbin_section(FILE *in, web49_section_header_t id);
web49_module_t web49_readbin_module(FILE *in);

#endif
