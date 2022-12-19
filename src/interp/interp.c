#include "interp.h"

#include "../tables.h"

web49_interp_t web49_interp_module(web49_module_t mod, const char **args) {
    web49_section_code_t code_section = web49_module_get_section(mod, WEB49_SECTION_ID_CODE).code_section;
    web49_section_type_t type_section = web49_module_get_section(mod, WEB49_SECTION_ID_TYPE).type_section;
    web49_section_table_t table_section = web49_module_get_section(mod, WEB49_SECTION_ID_TABLE).table_section;
    web49_section_import_t import_section = web49_module_get_section(mod, WEB49_SECTION_ID_IMPORT).import_section;
    web49_section_global_t global_section = web49_module_get_section(mod, WEB49_SECTION_ID_GLOBAL).global_section;
    web49_section_data_t data_section = web49_module_get_section(mod, WEB49_SECTION_ID_DATA).data_section;
    web49_section_element_t element_section = web49_module_get_section(mod, WEB49_SECTION_ID_ELEMENT).element_section;
    web49_section_memory_t memory_section = web49_module_get_section(mod, WEB49_SECTION_ID_MEMORY).memory_section;
    web49_section_function_t function_section = web49_module_get_section(mod, WEB49_SECTION_ID_FUNCTION).function_section;
    uint64_t num_funcs = code_section.num_entries;
    for (size_t j = 0; j < import_section.num_entries; j++) {
        web49_section_import_entry_t entry = import_section.entries[j];
        if (entry.kind == WEB49_EXTERNAL_KIND_FUNCTION) {
            num_funcs += 1;
        }
    }
    uint64_t cur_func = 0;
    web49_interp_data_t *locals = web49_alloc0(sizeof(web49_interp_data_t) * (1 << 12));
    uint64_t memsize = 65536 * memory_section.entries[0].initial;
    web49_interp_t interp = (web49_interp_t){
        .locals = locals,
        .memory = web49_alloc0(memsize),
        .table = NULL,
        .funcs = web49_malloc(sizeof(web49_interp_block_t) * num_funcs),
        .globals = web49_alloc0(sizeof(web49_interp_data_t) * (global_section.num_entries)),
        .nglobals = global_section.num_entries,
        .args = args,
        .locals_base = locals,
        .memsize = memsize,
        .stacks = web49_malloc(sizeof(web49_interp_data_t *) * (1 << 10)),
        .returns = web49_malloc(sizeof(web49_opcode_t *) * (1 << 10)),
    };
    for (size_t j = 0; j < table_section.num_entries; j++) {
        web49_type_table_t entry = table_section.entries[j];
        if (entry.element_type == WEB49_TYPE_ANYFUNC) {
            interp.table = web49_malloc(sizeof(web49_interp_block_t *) * entry.limits.maximum);
        }
    }
    for (size_t j = 0; j < import_section.num_entries; j++) {
        web49_section_import_entry_t *entry = &import_section.entries[j];
        if (entry->kind == WEB49_EXTERNAL_KIND_FUNCTION) {
            web49_interp_block_t *block = &interp.funcs[cur_func++];
            block->is_code = false;
            block->module_str = entry->module_str;
            block->field_str = entry->field_str;
            block->code = NULL;
            block->nlocals = 0;
            block->nparams = 0;
            block->nreturns = 1;
            entry->module_str = NULL;
            entry->field_str = NULL;
        }
    }
    for (size_t j = 0; j < global_section.num_entries; j++) {
        web49_section_global_entry_t global = global_section.entries[j];
        if (global.init_expr.opcode == WEB49_OPCODE_I32_CONST) {
            interp.globals[j].i32_s = global.init_expr.immediate.varint32;
        } else if (global.init_expr.opcode == WEB49_OPCODE_I64_CONST) {
            interp.globals[j].i64_s = global.init_expr.immediate.varint64;
        } else {
            interp.globals[j].i64_u = 0;
        }
    }
    for (size_t j = 0; j < data_section.num_entries; j++) {
        web49_section_data_entry_t entry = data_section.entries[j];
        memcpy(&interp.memory[entry.offset.immediate.varint32], entry.data, entry.size);
    }
    for (size_t j = 0; j < code_section.num_entries; j++) {
        web49_section_code_entry_t *entry = &code_section.entries[j];
        web49_interp_block_t *block = &interp.funcs[cur_func++];
        block->code = NULL;
        block->nlocals = 0;
        for (uint64_t i = 0; i < entry->num_locals; i++) {
            block->nlocals += entry->locals[i].count;
        }
        block->nparams = type_section.entries[function_section.entries[j]].num_params;
        block->nreturns = type_section.entries[function_section.entries[j]].num_returns;
        block->is_code = true;
        block->instrs = entry->instrs;
        block->num_instrs = entry->num_instrs;
        entry->num_instrs = 0;
        entry->instrs = NULL;
    }
    for (size_t j = 0; j < element_section.num_entries; j++) {
        web49_section_element_entry_t entry = element_section.entries[j];
        for (uint64_t i = 0; i < entry.num_elems; i++) {
            interp.table[i + entry.offset.immediate.varint32] = &interp.funcs[entry.elems[i]];
        }
    }
    web49_free_module(mod);
    return interp;
}

void web49_free_interp(web49_interp_t interp) {
    web49_free(interp.memory);
    web49_free(interp.funcs);
    web49_free(interp.locals_base);
    web49_free(interp.globals);
    web49_free(interp.stacks);
    web49_free(interp.returns);
}
