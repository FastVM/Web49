#include "./write_wat.h"

#include "./tables.h"

void web49_wat_print_lang_type(web49_io_output_t *out, web49_tag_t ltype) {
    switch (ltype) {
        case WEB49_TYPE_I32: {
            web49_io_output_write_str(out, "i32");
            break;
        }
        case WEB49_TYPE_I64: {
            web49_io_output_write_str(out, "i64");
            break;
        }
        case WEB49_TYPE_F32: {
            web49_io_output_write_str(out, "f32");
            break;
        }
        case WEB49_TYPE_F64: {
            web49_io_output_write_str(out, "f64");
            break;
        }
        case WEB49_TYPE_FUNC: {
            web49_io_output_write_str(out, "func");
            break;
        }
        case WEB49_TYPE_FUNCREF: {
            web49_io_output_write_str(out, "funcref");
            break;
        }
        case WEB49_TYPE_EXTERNREF: {
            web49_io_output_write_str(out, "externref");
            break;
        }
        case WEB49_TYPE_BLOCK_TYPE: {
            web49_io_output_write_str(out, "block_type");
            break;
        }
        case WEB49_TYPE_V128: {
            web49_io_output_write_str(out, "v128");
            break;
        }
        default: {
            web49_error("unsupported: type tag 0x%02zX\n", (size_t)ltype);
        }
    }
}

void web49_wat_print_instr(web49_io_output_t *out, web49_instr_t instr) {
    web49_wat_print_instr_depth(out, instr, 0);
}

void web49_wat_print_instr_depth(web49_io_output_t *out, web49_instr_t instr, uint64_t indent) {
    for (uint64_t i = 0; i < indent; i++) {
        web49_io_output_write_str(out, "  ");
    }
    const char *name = web49_opcode_to_name(instr.opcode);
    web49_io_output_write_str(out, name);
    switch (instr.immediate.id) {
        case WEB49_IMMEDIATE_NONE:
            break;
        case WEB49_IMMEDIATE_BLOCK_TYPE:
            if (instr.immediate.block_type.is_type_index) {
                web49_io_output_fprintf(out, " (type %" PRIu32 ")", instr.immediate.block_type.type_index);
            } else {
                if (instr.immediate.block_type.type_value != WEB49_TYPE_BLOCK_TYPE) {
                    web49_io_output_write_str(out, " (result ");
                    web49_wat_print_lang_type(out, instr.immediate.block_type.type_value);
                    web49_io_output_write_str(out, ")");
                }
            }
            break;
        case WEB49_IMMEDIATE_VARUINT1:
            if (instr.opcode != WEB49_OPCODE_MEMORY_GROW && instr.opcode != WEB49_OPCODE_MEMORY_SIZE) {
                web49_io_output_fprintf(out, " %zu", (size_t)(instr.immediate.varuint1 ? 1 : 0));
            }
            break;
        case WEB49_IMMEDIATE_VARUINT32:
            web49_io_output_fprintf(out, " %" PRIu32, instr.immediate.varuint32);
            if (instr.opcode == WEB49_OPCODE_BR_IF || instr.opcode == WEB49_OPCODE_BR) {
                web49_io_output_fprintf(out, " (;@%zu;)", (size_t)(indent - instr.immediate.varuint32));
            }
            break;
        case WEB49_IMMEDIATE_VARUINT64:
            web49_io_output_fprintf(out, " %" PRIu64, instr.immediate.varuint64);
            break;
        case WEB49_IMMEDIATE_VARINT32:
            web49_io_output_fprintf(out, " %" PRIi32, instr.immediate.varint32);
            break;
        case WEB49_IMMEDIATE_VARINT64:
            web49_io_output_fprintf(out, " %" PRIi64, instr.immediate.varint64);
            break;
        case WEB49_IMMEDIATE_UINT32:
            web49_io_output_fprintf(out, " %a (;=%g;)", *(float *)&instr.immediate.uint32, *(float *)&instr.immediate.uint32);
            break;
        case WEB49_IMMEDIATE_UINT64:
            web49_io_output_fprintf(out, " %la (;=%lg;)", *(double *)&instr.immediate.uint64, *(double *)&instr.immediate.uint64);
            break;
        case WEB49_IMMEDIATE_BR_TABLE:
            for (uint64_t i = 0; i < instr.immediate.br_table.num_targets; i++) {
                web49_io_output_fprintf(out, " %" PRIu64 " (;@%zu;)", instr.immediate.br_table.targets[i], (size_t)(indent - instr.immediate.br_table.targets[i]));
            }
            web49_io_output_fprintf(out, " %" PRIu64 " (;@%zu;)", instr.immediate.br_table.default_target, (size_t)(indent - instr.immediate.br_table.default_target));
            break;
        case WEB49_IMMEDIATE_CALL_INDIRECT:
            web49_io_output_fprintf(out, " (type %" PRIu64 ")", instr.immediate.call_indirect.index);
            break;
        case WEB49_IMMEDIATE_MEMORY_IMMEDIATE:
            if (instr.immediate.memory_immediate.offset != 0) {
                web49_io_output_fprintf(out, " offset=%" PRIu32, instr.immediate.memory_immediate.offset);
            }
            size_t nat_size = web49_opcode_memsize[instr.opcode];
            size_t size = (size_t)1 << instr.immediate.memory_immediate.align;
            if (size != nat_size) {
                web49_io_output_fprintf(out, " align=%zu", size);
            }
            break;
        case WEB49_IMMEDIATE_TABLE_INDEX:
            break;
        case WEB49_IMMEDIATE_LANE:
            web49_io_output_fprintf(out, " %zu", instr.immediate.lane);
            break;
        case WEB49_IMMEDIATE_V128:
            web49_io_output_fprintf(out, " i32x4", instr.immediate.memory_immediate.offset);
            for (size_t i = 0; i < 4; i++) {
                web49_io_output_fprintf(out, " 0x%08" PRIx32, instr.immediate.u32s[i]);
            }
            break;
    }
}

void web49_wat_print_section_type(web49_io_output_t *out, web49_module_t mod, web49_section_type_t stype) {
    (void)mod;
    for (uint64_t i = 0; i < stype.num_entries; i++) {
        web49_io_output_write_str(out, "\n  (type");
        web49_io_output_write_str(out, " ");
        web49_section_type_entry_t entry = stype.entries[i];
        web49_io_output_fprintf(out, "(;%" PRIi64 ";) ", i);
        if (entry.type == WEB49_TYPE_FUNCREF || entry.type == WEB49_TYPE_FUNC) {
            web49_io_output_write_str(out, "(func");
            if (entry.num_params != 0) {
                web49_io_output_write_str(out, " (param");
                for (uint64_t j = 0; j < entry.num_params; j++) {
                    web49_io_output_write_str(out, " ");
                    web49_wat_print_lang_type(out, entry.params[j]);
                }
                web49_io_output_write_str(out, ")");
            }
            if (entry.num_returns != 0) {
                web49_io_output_write_str(out, " (result");
                for (uint64_t j = 0; j < entry.num_returns; j++) {
                    web49_io_output_write_str(out, " ");
                    web49_wat_print_lang_type(out, entry.return_types[j]);
                }
                web49_io_output_write_str(out, ")");
            }
            web49_io_output_write_str(out, ")");
        } else {
            web49_wat_print_lang_type(out, entry.type);
        }
        web49_io_output_write_str(out, ")");
    }
}

void web49_wat_print_section_import(web49_io_output_t *out, web49_module_t mod, web49_section_import_t simport) {
    (void)mod;
    size_t num_funcs = 0;
    for (uint64_t i = 0; i < simport.num_entries; i++) {
        web49_section_import_entry_t import = simport.entries[i];
        web49_io_output_fprintf(out, "\n  (import \"%s\" \"%s\" ", import.module_str, import.field_str);
        switch (import.kind) {
            case WEB49_EXTERNAL_KIND_FUNCTION:
                web49_io_output_fprintf(out, "(func (;%zu;) (type %zu))", (size_t)num_funcs++, (size_t)import.func_type.data);
                break;
            case WEB49_EXTERNAL_KIND_TABLE:
                web49_io_output_write_str(out, "(table ");
                web49_wat_print_lang_type(out, import.table_type.element_type);
                web49_io_output_write_str(out, ")");
                break;
            case WEB49_EXTERNAL_KIND_MEMORY:
                web49_io_output_fprintf(out, "(memory %" PRIu64 ")", import.memory_type.initial);
                break;
            case WEB49_EXTERNAL_KIND_GLOBAL:
                web49_io_output_write_str(out, "(global ");
                if (import.global_type.is_mutable) {
                    web49_io_output_write_str(out, "(mut ");
                    web49_wat_print_lang_type(out, import.global_type.content_type);
                    web49_io_output_write_str(out, ")");
                } else {
                    web49_wat_print_lang_type(out, import.global_type.content_type);
                }
                web49_io_output_write_str(out, ")");
                break;
        }
        web49_io_output_write_str(out, ")");
    }
}

void web49_wat_print_section_function(web49_io_output_t *out, web49_module_t mod, web49_section_function_t sfunction) {
    (void)mod;
    size_t num_funcs = 0;
    web49_section_code_t code_section;
    web49_section_type_t type_section;
    for (uint64_t i = 0; i < mod.num_sections; i++) {
        if (mod.sections[i].header.id == WEB49_SECTION_ID_CODE) {
            code_section = mod.sections[i].section.code;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_TYPE) {
            type_section = mod.sections[i].section.type;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_IMPORT) {
            for (uint64_t j = 0; j < mod.sections[i].section.import.num_entries; j++) {
                if (mod.sections[i].section.import.entries[j].kind == WEB49_EXTERNAL_KIND_FUNCTION) {
                    num_funcs++;
                }
            }
        }
    }
    for (uint64_t i = 0; i < code_section.num_entries; i++) {
        web49_section_type_entry_t type = type_section.entries[sfunction.entries[i]];
        web49_section_code_entry_t code = code_section.entries[i];
        web49_io_output_fprintf(out, "\n  (func (;%zu;) (type %zu)", (size_t)num_funcs++, (size_t)sfunction.entries[i]);
        if (type.num_params != 0) {
            web49_io_output_write_str(out, " (param");
            for (uint64_t j = 0; j < type.num_params; j++) {
                web49_io_output_write_str(out, " ");
                web49_wat_print_lang_type(out, type.params[j]);
            }
            web49_io_output_write_str(out, ")");
        }
        if (type.num_returns != 0) {
            web49_io_output_write_str(out, " (result");
            for (uint64_t j = 0; j < type.num_returns; j++) {
                web49_io_output_write_str(out, " ");
                web49_wat_print_lang_type(out, type.return_types[j]);
            }
            web49_io_output_write_str(out, ")");
        }
        if (code.num_locals != 0) {
            web49_io_output_write_str(out, "\n    (local");
            for (uint64_t j = 0; j < code.num_locals; j++) {
                for (uint64_t k = 0; k < code.locals[j].count; k++) {
                    web49_io_output_write_str(out, " ");
                    web49_wat_print_lang_type(out, code.locals[j].type);
                }
            }
            web49_io_output_write_str(out, ")");
        }
        uint64_t depth = 0;
        for (uint64_t j = 0; j < code.num_instrs; j++) {
            web49_opcode_t op = code.instrs[j].opcode;
            if (j + 1 == code.num_instrs && op == WEB49_OPCODE_END) {
                break;
            }
            if (depth != 0 && (op == WEB49_OPCODE_END || op == WEB49_OPCODE_ELSE)) {
                depth -= 1;
            }
            web49_io_output_write_str(out, "\n    ");
            web49_wat_print_instr_depth(out, code.instrs[j], depth);
            if (op == WEB49_OPCODE_ELSE || op == WEB49_OPCODE_BLOCK || op == WEB49_OPCODE_IF || op == WEB49_OPCODE_LOOP) {
                depth += 1;
            }
            if (op == WEB49_OPCODE_BLOCK || op == WEB49_OPCODE_LOOP || op == WEB49_OPCODE_IF) {
                web49_io_output_fprintf(out, "  ;; label = @%zu", (size_t)depth);
            }
        }
        web49_io_output_write_str(out, ")");
    }
}

void web49_wat_print_section_table(web49_io_output_t *out, web49_module_t mod, web49_section_table_t stable) {
    (void)mod;
    for (uint64_t i = 0; i < stable.num_entries; i++) {
        web49_type_table_t table = stable.entries[i];
        web49_io_output_fprintf(out, "\n  (table (;%zu;) %" PRIu32, (size_t)i, table.limits.initial);
        if (table.limits.maximum != UINT32_MAX) {
            web49_io_output_fprintf(out, " %" PRIu32, table.limits.maximum);
        }
        web49_io_output_write_str(out, " ");
        web49_wat_print_lang_type(out, table.element_type);
        web49_io_output_write_str(out, ")");
    }
}

void web49_wat_print_section_memory(web49_io_output_t *out, web49_module_t mod, web49_section_memory_t smemory) {
    (void)mod;
    for (uint64_t i = 0; i < smemory.num_entries; i++) {
        web49_limits_t mem = smemory.entries[i];
        if (mem.maximum != UINT32_MAX) {
            web49_io_output_fprintf(out, "\n  (memory (;%zu;) %zu %zu)", (size_t)i, (size_t)mem.initial, (size_t)mem.maximum);
        } else {
            web49_io_output_fprintf(out, "\n  (memory (;%zu;) %zu)", (size_t)i, (size_t)mem.initial);
        }
    }
}

void web49_wat_print_section_global(web49_io_output_t *out, web49_module_t mod, web49_section_global_t sglobal) {
    (void)mod;
    for (uint64_t i = 0; i < sglobal.num_entries; i++) {
        web49_section_global_entry_t global = sglobal.entries[i];
        web49_io_output_fprintf(out, "\n  (global (;%zu;) ", (size_t)i);
        if (global.global.is_mutable) {
            web49_io_output_write_str(out, "(mut ");
            web49_wat_print_lang_type(out, global.global.content_type);
            web49_io_output_write_str(out, ")");
        } else {
            web49_wat_print_lang_type(out, global.global.content_type);
        }
        web49_io_output_write_str(out, " (");
        web49_wat_print_instr(out, global.init_expr);
        web49_io_output_write_str(out, ")");
        web49_io_output_write_str(out, ")");
    }
}

void web49_wat_print_section_export(web49_io_output_t *out, web49_module_t mod, web49_section_export_t sexport) {
    (void)mod;
    for (uint64_t i = 0; i < sexport.num_entries; i++) {
        web49_section_export_entry_t export = sexport.entries[i];
        web49_io_output_fprintf(out, "\n  (export \"%s\" ", export.field_str);
        switch (export.kind) {
            case WEB49_EXTERNAL_KIND_FUNCTION:
                web49_io_output_fprintf(out, "(func %zu)", (size_t)export.index);
                break;
            case WEB49_EXTERNAL_KIND_TABLE:
                web49_io_output_fprintf(out, "(table %zu)", (size_t)export.index);
                break;
            case WEB49_EXTERNAL_KIND_MEMORY:
                web49_io_output_fprintf(out, "(memory %zu)", (size_t)export.index);
                break;
            case WEB49_EXTERNAL_KIND_GLOBAL:
                web49_io_output_fprintf(out, "(global %zu)", (size_t)export.index);
                break;
        }
        web49_io_output_write_str(out, ")");
    }
}

void web49_wat_print_section_start(web49_io_output_t *out, web49_module_t mod, web49_section_start_t sstart) {
    (void)out;
    (void)mod;
    (void)sstart;
}

void web49_wat_print_section_element(web49_io_output_t *out, web49_module_t mod, web49_section_element_t selement) {
    (void)mod;
    for (uint64_t i = 0; i < selement.num_entries; i++) {
        web49_section_element_entry_t element = selement.entries[i];
        web49_io_output_fprintf(out, "\n  (elem (;%" PRIu64 ";) (", i);
        web49_wat_print_instr(out, element.offset);
        web49_io_output_write_str(out, ") func");
        for (uint64_t j = 0; j < element.num_elems; j++) {
            web49_io_output_fprintf(out, " %zu", (size_t)element.elems[j]);
        }
        web49_io_output_write_str(out, ")");
    }
}

void web49_wat_print_section_code(web49_io_output_t *out, web49_module_t mod, web49_section_code_t scode) {
    (void)out;
    (void)mod;
    (void)scode;
}

void web49_wat_print_section_data(web49_io_output_t *out, web49_module_t mod, web49_section_data_t sdata) {
    (void)mod;
    for (uint64_t i = 0; i < sdata.num_entries; i++) {
        web49_section_data_entry_t data = sdata.entries[i];
        web49_io_output_fprintf(out, "\n  (data (;%" PRIu64 ";) (", i);
        web49_wat_print_instr(out, data.offset);
        web49_io_output_write_str(out, ") \"");
        for (uint64_t j = 0; j < data.size; j++) {
            uint8_t arg = data.data[j];
            if (arg == '\\') {
                web49_io_output_fprintf(out, "\\%02zx", (size_t)'\\');
            } else if (arg == '\t') {
                web49_io_output_fprintf(out, "\\%02zx", (size_t)'\t');
            } else if (arg == '\r') {
                web49_io_output_fprintf(out, "\\%02zx", (size_t)'\r');
            } else if (arg == '\n') {
                web49_io_output_fprintf(out, "\\%02zx", (size_t)'\n');
            } else if (arg == '\'') {
                web49_io_output_fprintf(out, "\\%02zx", (size_t)'\'');
            } else if (arg == '\"') {
                web49_io_output_fprintf(out, "\\%02zx", (size_t)'\"');
            } else if (isprint(arg)) {
                web49_io_output_fprintf(out, "%c", (char)arg);
            } else {
                web49_io_output_fprintf(out, "\\%02zx", (size_t)arg);
            }
        }
        web49_io_output_write_str(out, "\")");
    }
}

void web49_wat_print_section(web49_io_output_t *out, web49_module_t mod, web49_section_t section) {
    switch (section.header.id) {
        case WEB49_SECTION_ID_CUSTOM: {
            break;
        }
        case WEB49_SECTION_ID_TYPE: {
            web49_wat_print_section_type(out, mod, section.section.type);
            break;
        }
        case WEB49_SECTION_ID_IMPORT: {
            web49_wat_print_section_import(out, mod, section.section.import);
            break;
        }
        case WEB49_SECTION_ID_FUNCTION: {
            web49_wat_print_section_function(out, mod, section.section.function);
            break;
        }
        case WEB49_SECTION_ID_TABLE: {
            web49_wat_print_section_table(out, mod, section.section.table);
            break;
        }
        case WEB49_SECTION_ID_MEMORY: {
            web49_wat_print_section_memory(out, mod, section.section.memory);
            break;
        }
        case WEB49_SECTION_ID_GLOBAL: {
            web49_wat_print_section_global(out, mod, section.section.global);
            break;
        }
        case WEB49_SECTION_ID_EXPORT: {
            web49_wat_print_section_export(out, mod, section.section.export);
            break;
        }
        case WEB49_SECTION_ID_START: {
            web49_wat_print_section_start(out, mod, section.section.start);
            break;
        }
        case WEB49_SECTION_ID_ELEMENT: {
            web49_wat_print_section_element(out, mod, section.section.element);
            break;
        }
        case WEB49_SECTION_ID_CODE: {
            web49_wat_print_section_code(out, mod, section.section.code);
            break;
        }
        case WEB49_SECTION_ID_DATA: {
            web49_wat_print_section_data(out, mod, section.section.data);
            break;
        }
    }
}

void web49_wat_print_module(web49_io_output_t *out, web49_module_t mod) {
    web49_io_output_write_str(out, "(module");
    for (uint64_t i = 0; i < mod.num_sections; i++) {
        web49_wat_print_section(out, mod, mod.sections[i]);
    }
    web49_io_output_write_str(out, ")\n");
}
