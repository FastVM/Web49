#include "./wat.h"
#include <stdio.h>

void vm_wat_print_lang_type(FILE *out, vm_wasm_lang_type_t ltype) {
    switch (ltype) {
    case VM_WASM_TYPE_I32: {
        fprintf(out, "i32");
        break;
    }
    case VM_WASM_TYPE_I64: {
        fprintf(out, "i64");
        break;
    }
    case VM_WASM_TYPE_F32: {
        fprintf(out, "f32");
        break;
    }
    case VM_WASM_TYPE_F64: {
        fprintf(out, "f64");
        break;
    }
    case VM_WASM_TYPE_ANYFUNC: {
        fprintf(out, "anyfunc");
        break;
    }
    case VM_WASM_TYPE_FUNC: {
        fprintf(out, "func");
        break;
    }
    case VM_WASM_TYPE_BLOCK_TYPE: {
        fprintf(out, "block_type");
        break;
    }
    default: {
        fprintf(stderr, "unsupported: type tag %x", (int) ltype);
    }
    }
}

void vm_wat_print_section_custom(FILE *out, vm_wasm_section_custom_t scustom) {
    fprintf(stderr, "unsupported: custom section type\n");
    __builtin_trap();
}

void vm_wat_print_section_type(FILE *out, vm_wasm_section_type_t stype) {
    fprintf(out, "(type");
    for (uint64_t i = 0; i < stype.num_entries; i++) {
        fprintf(out, " ");
        vm_wasm_section_type_entry_t entry = stype.entries[i];
        fprintf(out, "(;%zu;) ", (size_t) i);
        if (entry.type == VM_WASM_TYPE_FUNC) {
            fprintf(out, "(func");
            bool first = true;
            for (uint64_t j = 0; j < entry.num_params; j++) {
                fprintf(out, " ");
                vm_wat_print_lang_type(out, entry.params[j]);
            }
            if (entry.has_return_type) {
                fprintf(out, " ");
                fprintf(out, "(result ");
                vm_wat_print_lang_type(out, entry.return_type);
                fprintf(out, ")");
            }
            fprintf(out, ")");
        } else {
            vm_wat_print_lang_type(out, entry.type);
        }
    }
    fprintf(out, ")");
}

void vm_wat_print_section_import(FILE *out, vm_wasm_section_import_t simport) {
    fprintf(stderr, "unsupported: import section\n");
}

void vm_wat_print_section_function(FILE *out, vm_wasm_section_function_t sfunction) {
    fprintf(out, "(func");
    for (uint64_t i = 0; i < sfunction.num_entries; i++) {
        fprintf(out, " ");
    }
    fprintf(out, ")");
}

void vm_wat_print_section_table(FILE *out, vm_wasm_section_table_t stable) {
    fprintf(stderr, "unsupported: table section\n");
}

void vm_wat_print_section_memory(FILE *out, vm_wasm_section_memory_t smemory) {
    fprintf(stderr, "unsupported: memory section\n");
}

void vm_wat_print_section_global(FILE *out, vm_wasm_section_global_t sglobal) {
    fprintf(stderr, "unsupported: global section\n");
}

void vm_wat_print_section_export(FILE *out, vm_wasm_section_export_t sexport) {
    fprintf(stderr, "unsupported: export section\n");
}

void vm_wat_print_section_start(FILE *out, vm_wasm_section_start_t sstart) {
    fprintf(stderr, "unsupported: start section\n");
}

void vm_wat_print_section_element(FILE *out, vm_wasm_section_element_t selement) {
    fprintf(stderr, "unsupported: element section\n");
}

void vm_wat_print_section_code(FILE *out, vm_wasm_section_code_t scode) {
    fprintf(stderr, "unsupported: code section\n");
}

void vm_wat_print_section_data(FILE *out, vm_wasm_section_data_t sdata) {
    fprintf(stderr, "unsupported: data section\n");
}

void vm_wat_print_section(FILE *out, vm_wasm_section_t section) {
    switch(section.id) {
    case VM_WASM_SECTION_ID_CUSTOM: {
        vm_wat_print_section_custom(out, section.custom_section);
        break;
    }
    case VM_WASM_SECTION_ID_TYPE: {
        vm_wat_print_section_type(out, section.type_section);
        break;
    }
    case VM_WASM_SECTION_ID_IMPORT: {
        vm_wat_print_section_import(out, section.import_section);
        break;
    }
    case VM_WASM_SECTION_ID_FUNCTION: {
        vm_wat_print_section_function(out, section.function_section);
        break;
    }
    case VM_WASM_SECTION_ID_TABLE: {
        vm_wat_print_section_table(out, section.table_section);
        break;
    }
    case VM_WASM_SECTION_ID_MEMORY: {
        vm_wat_print_section_memory(out, section.memory_section);
        break;
    }
    case VM_WASM_SECTION_ID_GLOBAL: {
        vm_wat_print_section_global(out, section.global_section);
        break;
    }
    case VM_WASM_SECTION_ID_EXPORT: {
        vm_wat_print_section_export(out, section.export_section);
        break;
    }
    case VM_WASM_SECTION_ID_START: {
        vm_wat_print_section_start(out, section.start_section);
        break;
    }
    case VM_WASM_SECTION_ID_ELEMENT: {
        vm_wat_print_section_element(out, section.element_section);
        break;
    }
    case VM_WASM_SECTION_ID_CODE: {
        vm_wat_print_section_code(out, section.code_section);
        break;
    }
    case VM_WASM_SECTION_ID_DATA: {
        vm_wat_print_section_data(out, section.data_section);
        break;
    }
    }
}

void vm_wat_print_module(FILE *out, vm_wasm_module_t mod) {
    fprintf(out, "(module");
    for (uint64_t i = 0; i < mod.num_sections; i++) {
        fprintf(out, " ");
        vm_wat_print_section(out, mod.sections[i]);
    }
    fprintf(out, ")");
}
