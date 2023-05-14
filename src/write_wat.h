
#if !defined(WEB49_HEADER_WRITEWAT)
#define WEB49_HEADER_WRITEWAT

#include "./ast.h"
#include "./io.h"

void web49_wat_print_lang_type(web49_io_output_t *out, web49_tag_t ltype);
void web49_wat_print_instr(web49_io_output_t *out, web49_instr_t instr);
void web49_wat_print_instr_depth(web49_io_output_t *out, web49_instr_t instr, uint64_t indent);
void web49_wat_print_section_custom(web49_io_output_t *out, web49_module_t mod, web49_section_custom_t scustom);
void web49_wat_print_section_type(web49_io_output_t *out, web49_module_t mod, web49_section_type_t stype);
void web49_wat_print_section_import(web49_io_output_t *out, web49_module_t mod, web49_section_import_t simport);
void web49_wat_print_section_function(web49_io_output_t *out, web49_module_t mod, web49_section_function_t sfunction);
void web49_wat_print_section_table(web49_io_output_t *out, web49_module_t mod, web49_section_table_t stable);
void web49_wat_print_section_memory(web49_io_output_t *out, web49_module_t mod, web49_section_memory_t smemory);
void web49_wat_print_section_global(web49_io_output_t *out, web49_module_t mod, web49_section_global_t sglobal);
void web49_wat_print_section_export(web49_io_output_t *out, web49_module_t mod, web49_section_export_t sexport);
void web49_wat_print_section_start(web49_io_output_t *out, web49_module_t mod, web49_section_start_t sstart);
void web49_wat_print_section_element(web49_io_output_t *out, web49_module_t mod, web49_section_element_t selement);
void web49_wat_print_section_code(web49_io_output_t *out, web49_module_t mod, web49_section_code_t scode);
void web49_wat_print_section_data(web49_io_output_t *out, web49_module_t mod, web49_section_data_t sdata);
void web49_wat_print_section(web49_io_output_t *out, web49_module_t mod, web49_section_t section);
void web49_wat_print_module(web49_io_output_t *out, web49_module_t mod);

#endif
