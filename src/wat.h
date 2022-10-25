
#if !defined(VM_HEADER_WAT)
#define VM_HEADER_WAT

#include "./parse.h"

void vm_wat_print_section_custom(FILE *out, vm_wasm_section_custom_t scustom);
void vm_wat_print_section_type(FILE *out, vm_wasm_section_type_t stype);
void vm_wat_print_section_import(FILE *out, vm_wasm_section_import_t simport);
void vm_wat_print_section_function(FILE *out, vm_wasm_module_t mod, vm_wasm_section_function_t sfunction);
void vm_wat_print_section_table(FILE *out, vm_wasm_section_table_t stable);
void vm_wat_print_section_memory(FILE *out, vm_wasm_section_memory_t smemory);
void vm_wat_print_section_global(FILE *out, vm_wasm_section_global_t sglobal);
void vm_wat_print_section_export(FILE *out, vm_wasm_section_export_t sexport);
void vm_wat_print_section_start(FILE *out, vm_wasm_section_start_t sstart);
void vm_wat_print_section_element(FILE *out, vm_wasm_section_element_t selement);
void vm_wat_print_section_code(FILE *out, vm_wasm_section_code_t scode);
void vm_wat_print_section_data(FILE *out, vm_wasm_section_data_t sdata);
void vm_wat_print_section(FILE *out, vm_wasm_module_t mod, vm_wasm_section_t section);
void vm_wat_print_module(FILE *out, vm_wasm_module_t mod);

#endif
