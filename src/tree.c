#include "tree.h"
#include "tables.h"

static void debug_print(web49_instr_t instr) {
    fprintf(stderr, "(%s", web49_opcode_to_name(instr.opcode));
    switch (instr.immediate.id) {
    case WEB49_IMMEDIATE_NONE: {
        fprintf(stderr, " ");
        break;
    }
    case WEB49_IMMEDIATE_VARUINT1: {
        break;
    }
    case WEB49_IMMEDIATE_VARUINT32: {
        fprintf(stderr, " %"PRIu32, instr.immediate.varuint32);
        break;
    }
    case WEB49_IMMEDIATE_VARUINT64: {
        fprintf(stderr, " %"PRIu64, instr.immediate.varuint64);
        break;
    }
    case WEB49_IMMEDIATE_VARINT32: {
        fprintf(stderr, " %"PRIi32, instr.immediate.varint32);
        break;
    }
    case WEB49_IMMEDIATE_VARINT64: {
        fprintf(stderr, " %"PRIi64, instr.immediate.varint64);
        break;
    }
    case WEB49_IMMEDIATE_UINT32: {
        fprintf(stderr, " %"PRIu32, instr.immediate.uint32);
        break;
    }
    case WEB49_IMMEDIATE_UINT64: {
        fprintf(stderr, " %"PRIu64, instr.immediate.uint64);
        break;
    }
    case WEB49_IMMEDIATE_BR_TABLE: {
        break;
    }
    case WEB49_IMMEDIATE_CALL_INDIRECT: {
        break;
    }
    case WEB49_IMMEDIATE_MEMORY_IMMEDIATE: {
        break;
    }
    case WEB49_IMMEDIATE_DATA_INDEX: {
        break;
    }
    }
    for (uint64_t i = 0; i < instr.nargs; i++) {
        fprintf(stderr, " ");
        debug_print(instr.args[i]);
    }
    fprintf(stderr, ")");
}

web49_instr_t web49_tree_opt_read_block(web49_module_t *mod, web49_instr_t **head) {
    web49_section_type_t type_section;
    web49_section_function_t function_section;
    web49_section_import_t import_section;
    size_t num_funcs = 0;
    for (uint64_t s = 0; s < mod->num_sections; s++) {
        web49_section_t cur = mod->sections[s];
        if (cur.header.id == WEB49_SECTION_ID_TYPE) {
            type_section = cur.type_section;
        }
        if (cur.header.id == WEB49_SECTION_ID_FUNCTION) {
            function_section = cur.function_section;
        }
        if (cur.header.id == WEB49_SECTION_ID_IMPORT) {
            import_section = cur.import_section;
            for (uint64_t j = 0; j < import_section.num_entries; j++) {
                if (import_section.entries[j].kind == WEB49_EXTERNAL_KIND_FUNCTION) {
                    num_funcs++;
                }
            }
        }
    }
    web49_instr_t ret;
    uint64_t nalloc = 8;
    ret.nargs = 0;
    ret.args = web49_malloc(sizeof(web49_instr_t) * nalloc);
    ret.immediate.id = WEB49_IMMEDIATE_NONE;
    ret.opcode = WEB49_OPCODE_BLOCK;
    ret.args[ret.nargs++] = (web49_instr_t) {
        .opcode = WEB49_OPCODE_NOP,
    };
    while (true) {
        web49_instr_t cur = **head;
        *head += 1;
        if (cur.opcode == WEB49_OPCODE_END || cur.opcode == WEB49_OPCODE_ELSE) {
            break;
        }
        if (cur.opcode == WEB49_OPCODE_NOP) {
            continue;
        }
        if (ret.nargs + 4 >= nalloc) {
            nalloc = (ret.nargs + 4) * 2;
            ret.args = web49_realloc(ret.args, sizeof(web49_instr_t) * nalloc);
        }
        if (cur.opcode == WEB49_OPCODE_BLOCK || cur.opcode == WEB49_OPCODE_LOOP) {
            web49_instr_t body = web49_tree_opt_read_block(mod, head);
            cur.nargs = 1;
            cur.args = web49_malloc(sizeof(web49_instr_t));
            cur.args[0] = body;
            ret.args[ret.nargs++] = cur;
            continue;
        }
        if (cur.opcode == WEB49_OPCODE_IF) {
            web49_instr_t ifthen = web49_tree_opt_read_block(mod, head);
            if ((*head)[-1].opcode == WEB49_OPCODE_ELSE) {
                *head += 1;
                cur.nargs = 2;
                cur.args = web49_malloc(sizeof(web49_instr_t) * 2);
                cur.args[0] = ifthen;
                cur.args[1] = web49_tree_opt_read_block(mod, head);
            } else {
                cur.nargs = 1;
                cur.args = web49_malloc(sizeof(web49_instr_t));
                cur.args[0] = ifthen;
            }
            ret.args[ret.nargs++] = cur;
            continue;
        }
        web49_table_stack_effect_t effect = web49_stack_effects[cur.opcode];
        size_t nargs = 0;
        for (size_t i = 0; effect.in[i] != WEB49_TABLE_STACK_EFFECT_END; i++) {
            if (effect.in[i] == WEB49_TABLE_STACK_EFFECT_ARGS) {
                int32_t entry = function_section.entries[cur.immediate.varint32];
                if (entry >= num_funcs) {
                    nargs += type_section.entries[entry-num_funcs].num_params;
                } else {
                    uint32_t cur = 0;
                    for (uint64_t j = 0; j < import_section.num_entries; j++) {
                        if (import_section.entries[j].kind == WEB49_EXTERNAL_KIND_FUNCTION) {
                            if (cur == entry) {
                                nargs += type_section.entries[import_section.entries[entry].func_type.data].num_params;
                                break;
                            }
                            cur += 1;
                        }
                    }
                }
            } else if (effect.in[i] == WEB49_TABLE_STACK_EFFECT_ARGS_INDIRECT) {
                nargs += type_section.entries[cur.immediate.call_indirect.index].num_params;
            } else {
                nargs += 1;
            }
        }
        if (effect.out[0] == WEB49_TABLE_STACK_EFFECT_END) {
            nargs += 1;
        }
        cur.nargs = 0;
        cur.args = web49_malloc(sizeof(web49_instr_t) * (nargs));
        // fprintf(stderr, "%s [%zu] -= %zu\n", web49_opcode_to_name(cur.opcode), (size_t) ret.nargs, nargs);
        for (size_t i = 0; i < nargs; i++) {
            cur.args[cur.nargs++] = ret.args[--ret.nargs];
        }
        ret.args[ret.nargs++] = cur;
    }
    return ret;
}

void web49_tree_opt_code(web49_module_t *mod, web49_section_code_entry_t *entry) {
    web49_instr_t *head = entry->instrs;
    web49_instr_t instr = web49_tree_opt_read_block(mod, &head);
    debug_print(instr);
    fprintf(stderr, "\n");
    // entry->num_instrs = 1;
    // entry->instrs = instr;
}

void web49_tree_opt_module(web49_module_t *mod) {
    for (uint64_t s = 0; s < mod->num_sections; s++) {
        web49_section_t cur = mod->sections[s];
        if (cur.header.id == WEB49_SECTION_ID_CODE) {
            for (uint64_t i = 0; i < cur.code_section.num_entries; i++) {
                web49_tree_opt_code(mod, &cur.code_section.entries[i]);
            }
        }
    }
}