
#if !defined(WEB49_HEADER_READBIN)
#define WEB49_HEADER_READBIN

#include "./ast.h"
#include "./io.h"

uint64_t web49_readbin_uleb(web49_io_input_t *in);
int64_t web49_readbin_sleb(web49_io_input_t *in);
uint8_t web49_readbin_byte(web49_io_input_t *in);
web49_preamble_t web49_readbin_preamble(web49_io_input_t *in);
web49_section_header_t web49_readbin_section_header(web49_io_input_t *in);
uint8_t web49_readbin_varuint1(web49_io_input_t *in);
int32_t web49_readbin_varuint32(web49_io_input_t *in);
int64_t web49_readbin_varuint64(web49_io_input_t *in);
uint32_t web49_readbin_uint32(web49_io_input_t *in);
uint64_t web49_readbin_uint64(web49_io_input_t *in);
web49_block_type_t web49_readbin_block_type(web49_io_input_t *in);
web49_br_table_t web49_readbin_br_table(web49_io_input_t *in);
web49_call_indirect_t web49_readbin_call_indirect(web49_io_input_t *in);
web49_memory_immediate_t web49_readbin_memory_immediate(web49_io_input_t *in);
web49_type_function_t web49_readbin_type_function(web49_io_input_t *in);
web49_type_table_t web49_readbin_type_table(web49_io_input_t *in);
web49_type_global_t web49_readbin_type_global(web49_io_input_t *in);
web49_limits_t web49_readbin_limits(web49_io_input_t *in);
web49_type_t web49_readbin_type(web49_io_input_t *in, web49_tag_t tag);
web49_section_custom_t web49_readbin_section_custom(web49_io_input_t *in, web49_section_header_t header);
web49_section_type_t web49_readbin_section_type(web49_io_input_t *in);
web49_section_import_t web49_readbin_section_import(web49_io_input_t *in);
web49_section_function_t web49_readbin_section_function(web49_io_input_t *in);
web49_section_table_t web49_readbin_section_table(web49_io_input_t *in);
web49_section_memory_t web49_readbin_section_memory(web49_io_input_t *in);
web49_section_global_t web49_readbin_section_global(web49_io_input_t *in);
web49_section_export_t web49_readbin_section_export(web49_io_input_t *in);
web49_section_start_t web49_readbin_section_start(web49_io_input_t *in);
web49_section_element_t web49_readbin_section_element(web49_io_input_t *in);
web49_section_code_t web49_readbin_section_code(web49_io_input_t *in);
web49_section_data_t web49_readbin_section_data(web49_io_input_t *in);
web49_instr_immediate_t web49_readbin_instr_immediate(web49_io_input_t *in, web49_immediate_id_t id);
web49_instr_t web49_readbin_init_expr(web49_io_input_t *in);
web49_instr_t web49_readbin_instr(web49_io_input_t *in);
web49_section_t web49_readbin_section(web49_io_input_t *in, web49_section_header_t id);
web49_module_t web49_readbin_module(web49_io_input_t *in);

#endif
