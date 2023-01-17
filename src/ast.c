#include "ast.h"

#include "tables.h"

void web49_free_instr(web49_instr_t instr) {
    for (size_t i = 0; i < instr.nargs; i++) {
        web49_free_instr(instr.args[i]);
    }
    web49_free(instr.args);
    if (instr.immediate.id == WEB49_IMMEDIATE_BR_TABLE) {
        web49_free(instr.immediate.br_table.targets);
    }
}

void web49_free_module(web49_module_t mod) {
    for (size_t i = 0; i < mod.num_sections; i++) {
        web49_section_t section = mod.sections[i];
        switch (section.header.id) {
            case WEB49_SECTION_ID_CUSTOM: {
                web49_section_custom_t cur = section.custom_section;
                web49_free(cur.name);
                web49_free(cur.payload);
                break;
            }
            case WEB49_SECTION_ID_TYPE: {
                web49_section_type_t cur = section.type_section;
                for (size_t j = 0; j < cur.num_entries; j++) {
                    web49_section_type_entry_t ent = cur.entries[j];
                    web49_free(ent.params);
                }
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_IMPORT: {
                web49_section_import_t cur = section.import_section;
                for (size_t j = 0; j < cur.num_entries; j++) {
                    web49_section_import_entry_t ent = cur.entries[j];
                    web49_free(ent.module_str);
                    web49_free(ent.field_str);
                }
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_FUNCTION: {
                web49_section_function_t cur = section.function_section;
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_TABLE: {
                web49_section_table_t cur = section.table_section;
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_MEMORY: {
                web49_section_memory_t cur = section.memory_section;
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_GLOBAL: {
                web49_section_global_t cur = section.global_section;
                for (size_t j = 0; j < cur.num_entries; j++) {
                    web49_section_global_entry_t ent = cur.entries[j];
                    web49_free_instr(ent.init_expr);
                }
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_EXPORT: {
                web49_section_export_t cur = section.export_section;
                for (size_t j = 0; j < cur.num_entries; j++) {
                    web49_section_export_entry_t ent = cur.entries[j];
                    web49_free(ent.field_str);
                }
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_START: {
                break;
            }
            case WEB49_SECTION_ID_ELEMENT: {
                web49_section_element_t cur = section.element_section;
                for (size_t j = 0; j < cur.num_entries; j++) {
                    web49_section_element_entry_t ent = cur.entries[j];
                    web49_free(ent.elems);
                }
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_CODE: {
                web49_section_code_t cur = section.code_section;
                for (size_t j = 0; j < cur.num_entries; j++) {
                    web49_section_code_entry_t ent = cur.entries[j];
                    for (size_t k = 0; k < ent.num_instrs; k++) {
                        web49_free_instr(ent.instrs[k]);
                    }
                    web49_free(ent.instrs);
                    web49_free(ent.locals);
                }
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_DATA: {
                web49_section_data_t cur = section.data_section;
                for (size_t j = 0; j < cur.num_entries; j++) {
                    web49_free(cur.entries[j].data);
                }
                web49_free(cur.entries);
                break;
            }
            case WEB49_SECTION_ID_DATA_COUNT: {
                __builtin_trap();
            }
        }
    }
    web49_free(mod.sections);
}

static void web49_debug_print_instr_depth(FILE *file, web49_instr_t instr, size_t depth) {
    fprintf(file, "(%s", web49_opcode_to_name(instr.opcode));
    switch (instr.immediate.id) {
        case WEB49_IMMEDIATE_NONE:
            break;
        case WEB49_IMMEDIATE_BLOCK_TYPE:
            if (instr.immediate.block_type.is_type_index) {
                fprintf(file, " (type %"PRIu32")", instr.immediate.block_type.type_index);
            } else {
                switch (instr.immediate.block_type.type_value) {
                    case WEB49_TYPE_I32:
                        fprintf(file, " (result i32)");
                        break;
                    case WEB49_TYPE_I64:
                        fprintf(file, " (result i64)");
                        break;
                    case WEB49_TYPE_F32:
                        fprintf(file, " (result f32)");
                        break;
                    case WEB49_TYPE_F64:
                        fprintf(file, " (result f64)");
                        break;
                    default:
                        break;
                }
            }
            break;
        case WEB49_IMMEDIATE_VARUINT1:
            break;
        case WEB49_IMMEDIATE_VARUINT32:
            fprintf(file, " %" PRIu32, instr.immediate.varuint32);
            break;
        case WEB49_IMMEDIATE_VARUINT64:
            fprintf(file, " %" PRIu64, instr.immediate.varuint64);
            break;
        case WEB49_IMMEDIATE_VARINT32:
            fprintf(file, " %" PRIi32, instr.immediate.varint32);
            break;
        case WEB49_IMMEDIATE_VARINT64:
            fprintf(file, " %" PRIi64, instr.immediate.varint64);
            break;
        case WEB49_IMMEDIATE_UINT32:
            fprintf(file, " %" PRIi32, instr.immediate.uint32);
            break;
        case WEB49_IMMEDIATE_UINT64:
            fprintf(file, " %" PRIi64, instr.immediate.uint64);
            break;
        case WEB49_IMMEDIATE_BR_TABLE:
            for (size_t i = 0; i < instr.immediate.br_table.num_targets; i++) {
                fprintf(file, " %" PRIu32, instr.immediate.br_table.targets[i]);
            }
            fprintf(file, " %" PRIu32, instr.immediate.br_table.default_target);
            break;
        case WEB49_IMMEDIATE_CALL_INDIRECT:
            break;
        case WEB49_IMMEDIATE_MEMORY_IMMEDIATE:
            if (instr.immediate.memory_immediate.offset != 0) {
                fprintf(file, " offset=%"PRIu32, instr.immediate.memory_immediate.offset);
            }
            break;
        default:
            fprintf(file, " ...");
            break;
    }
    for (size_t i = 0; i < instr.nargs; i++) {
        fprintf(file, "\n%*c", (int)(depth * 2), ' ');
        web49_debug_print_instr_depth(file, instr.args[i], depth + 1);
    }
    fprintf(file, ")");
}

void web49_debug_print_instr(FILE *file, web49_instr_t instr) {
    web49_debug_print_instr_depth(file, instr, 0);
    fprintf(file, "\n");
}

web49_section_t web49_module_get_section(web49_module_t mod, web49_section_id_t id) {
    for (size_t i = 0; i < mod.num_sections; i++) {
        if (mod.sections[i].header.id == id) {
            return mod.sections[i];
        }
    }
    return (web49_section_t){};
}

uint32_t web49_module_num_func_imports(web49_module_t mod) {
    for (size_t i = 0; i < mod.num_sections; i++) {
        if (mod.sections[i].header.id == WEB49_SECTION_ID_IMPORT) {
            web49_section_import_t *pimport = &mod.sections[i].import_section;
            if (pimport->num_func_imports == 0) {
                pimport->num_func_imports = 1;
                for (size_t j = 0; j < pimport->num_entries; j++) {
                    if (pimport->entries[j].kind == WEB49_EXTERNAL_KIND_FUNCTION) {
                        pimport->num_func_imports += 1;
                    }
                }
            }
            return pimport->num_func_imports - 1;
        }
    }
    return 0;
}
