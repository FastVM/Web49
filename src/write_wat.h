
#if !defined(WEB49_HEADER_WRITEWAT)
#define WEB49_HEADER_WRITEWAT

#include "./ast.h"

void web49_wat_print_lang_type(FILE *out, web49_lang_type_t ltype);
void web49_wat_print_instr(FILE *out, web49_instr_t instr);
void web49_wat_print_instr_depth(FILE *out, web49_instr_t instr, uint64_t indent);
void web49_wat_print_section_custom(FILE *out, web49_module_t mod, web49_section_custom_t scustom);
void web49_wat_print_section_type(FILE *out, web49_module_t mod, web49_section_type_t stype);
void web49_wat_print_section_import(FILE *out, web49_module_t mod, web49_section_import_t simport);
void web49_wat_print_section_function(FILE *out, web49_module_t mod, web49_section_function_t sfunction);
void web49_wat_print_section_table(FILE *out, web49_module_t mod, web49_section_table_t stable);
void web49_wat_print_section_memory(FILE *out, web49_module_t mod, web49_section_memory_t smemory);
void web49_wat_print_section_global(FILE *out, web49_module_t mod, web49_section_global_t sglobal);
void web49_wat_print_section_export(FILE *out, web49_module_t mod, web49_section_export_t sexport);
void web49_wat_print_section_start(FILE *out, web49_module_t mod, web49_section_start_t sstart);
void web49_wat_print_section_element(FILE *out, web49_module_t mod, web49_section_element_t selement);
void web49_wat_print_section_code(FILE *out, web49_module_t mod, web49_section_code_t scode);
void web49_wat_print_section_data(FILE *out, web49_module_t mod, web49_section_data_t sdata);
void web49_wat_print_section(FILE *out, web49_module_t mod, web49_section_t section);
void web49_wat_print_module(FILE *out, web49_module_t mod);

#endif
