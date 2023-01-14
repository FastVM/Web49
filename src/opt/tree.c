#include "tree.h"

#include <stdio.h>

#include "../tables.h"

struct web49_opt_list_t;
typedef struct web49_opt_list_t web49_opt_list_t;

struct web49_opt_list_t {
    size_t nreturns;
    web49_opt_list_t *last;
};

static void web49_check(web49_instr_t cur) {
    if (cur.opcode == WEB49_OPCODE_BEGIN0 && cur.nargs == 0) {
        __builtin_trap();
    }
    for (size_t i = 0; i < cur.nargs; i++) {
        web49_check(cur.args[i]);
    }
}

web49_instr_t web49_opt_tree_read_block(web49_module_t *mod, web49_instr_t **head) {
    web49_section_type_t type_section;
    web49_section_function_t function_section;
    web49_section_import_t import_section;
    int32_t num_funcs = 0;
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
    ret.opcode = WEB49_OPCODE_BEGIN0;
    while (true) {
        web49_instr_t cur = **head;
        *head += 1;
        if (cur.opcode == WEB49_OPCODE_END || cur.opcode == WEB49_OPCODE_ELSE) {
            web49_free_instr(cur);
            break;
        }
        if (cur.opcode == WEB49_OPCODE_NOP) {
            web49_free_instr(cur);
            continue;
        }
        if (ret.nargs + 16 >= nalloc) {
            nalloc = (ret.nargs + 16) * 2;
            ret.args = web49_realloc(ret.args, sizeof(web49_instr_t) * nalloc);
        }
        if (cur.opcode == WEB49_OPCODE_BLOCK || cur.opcode == WEB49_OPCODE_LOOP) {
            web49_instr_t body = web49_opt_tree_read_block(mod, head);
            cur.nargs = 1;
            cur.args = web49_malloc(sizeof(web49_instr_t));
            cur.args[0] = body;
            if (cur.immediate.block_type.type_value != WEB49_TYPE_BLOCK_TYPE || ret.nargs == 0) {
                ret.args[ret.nargs++] = cur;
            } else {
                web49_instr_t begin0;
                begin0.opcode = WEB49_OPCODE_BEGIN0;
                begin0.immediate.id = WEB49_IMMEDIATE_NONE;
                begin0.nargs = 2;
                begin0.args = web49_malloc(sizeof(web49_instr_t) * 2);
                begin0.args[0] = ret.args[--ret.nargs];
                begin0.args[1] = cur;
                ret.args[ret.nargs++] = begin0;
            }
            continue;
        }
        if (cur.opcode == WEB49_OPCODE_IF) {
            web49_instr_t ifthen = web49_opt_tree_read_block(mod, head);
            if ((*head)[-1].opcode == WEB49_OPCODE_ELSE) {
                cur.nargs = 3;
                cur.args = web49_malloc(sizeof(web49_instr_t) * 3);
                cur.args[0] = ret.args[--ret.nargs];
                cur.args[1] = ifthen;
                cur.args[2] = web49_opt_tree_read_block(mod, head);
            } else {
                cur.nargs = 2;
                cur.args = web49_malloc(sizeof(web49_instr_t) * 2);
                cur.args[0] = ret.args[--ret.nargs];
                cur.args[1] = ifthen;
            }
            // web49_debug_print_instr(stderr, cur);
            if (cur.immediate.block_type.type_value != WEB49_TYPE_BLOCK_TYPE || ret.nargs == 0) {
                ret.args[ret.nargs++] = cur;
            } else {
                web49_instr_t begin0;
                begin0.opcode = WEB49_OPCODE_BEGIN0;
                begin0.immediate.id = WEB49_IMMEDIATE_NONE;
                begin0.nargs = 2;
                begin0.args = web49_malloc(sizeof(web49_instr_t) * 2);
                begin0.args[0] = ret.args[--ret.nargs];
                begin0.args[1] = cur;
                ret.args[ret.nargs++] = begin0;
            }
            continue;
        }
        web49_table_stack_effect_t effect = web49_stack_effects[cur.opcode];
        size_t nargs = 0;
        for (size_t i = 0; effect.in[i] != WEB49_TABLE_STACK_EFFECT_END; i++) {
            if (effect.in[i] == WEB49_TABLE_STACK_EFFECT_ARGS) {
                if (cur.immediate.varint32 >= num_funcs) {
                    int32_t entry = function_section.entries[cur.immediate.varint32 - num_funcs];
                    nargs += type_section.entries[entry].num_params;
                } else {
                    int32_t index = 0;
                    for (uint64_t j = 0; j < import_section.num_entries; j++) {
                        if (import_section.entries[j].kind == WEB49_EXTERNAL_KIND_FUNCTION) {
                            if (index == cur.immediate.varint32) {
                                nargs += type_section.entries[import_section.entries[j].func_type.data].num_params;
                                break;
                            }
                            index += 1;
                        }
                    }
                }
            } else if (effect.in[i] == WEB49_TABLE_STACK_EFFECT_ARGS_INDIRECT) {
                nargs += type_section.entries[cur.immediate.call_indirect.index].num_params;
            } else {
                nargs += 1;
            }
        }
        bool use_begin0 = false;
        if (effect.out[0] == WEB49_TABLE_STACK_EFFECT_END) {
            use_begin0 = true;
        } else if (effect.out[0] == WEB49_TABLE_STACK_EFFECT_RET) {
            if (cur.immediate.varint32 >= num_funcs) {
                int32_t entry = function_section.entries[cur.immediate.varint32 - num_funcs];
                use_begin0 = !type_section.entries[entry].num_returns;
            } else {
                int32_t index = 0;
                for (uint64_t j = 0; j < import_section.num_entries; j++) {
                    if (import_section.entries[j].kind == WEB49_EXTERNAL_KIND_FUNCTION) {
                        if (index == cur.immediate.varint32) {
                            use_begin0 = !type_section.entries[import_section.entries[j].func_type.data].num_returns;
                            break;
                        }
                        index += 1;
                    }
                }
            }
        } else if (effect.out[0] == WEB49_TABLE_STACK_EFFECT_RET_INDIRECT) {
            use_begin0 = !type_section.entries[cur.immediate.call_indirect.index].num_returns;
        }
        cur.nargs = 0;
        cur.args = web49_malloc(sizeof(web49_instr_t) * (nargs));
        while (ret.nargs < nargs) {
            if (nargs + 2 >= nalloc) {
                nalloc = (nargs + 2) * 2;
                ret.args = web49_realloc(ret.args, sizeof(web49_instr_t) * nalloc);
            }
            ret.args[ret.nargs++] = (web49_instr_t){
                .opcode = WEB49_OPCODE_NOP,
                .immediate = (web49_instr_immediate_t){
                    .id = WEB49_IMMEDIATE_NONE,
                },
                .nargs = 0,
                .args = NULL,
            };
        }
        ret.nargs -= nargs;
        for (size_t i = 0; i < nargs; i++) {
            cur.args[cur.nargs++] = ret.args[ret.nargs + i];
        }
        if (use_begin0 && ret.nargs != 0) {
            web49_instr_t begin0;
            begin0.opcode = WEB49_OPCODE_BEGIN0;
            begin0.immediate.id = WEB49_IMMEDIATE_NONE;
            begin0.nargs = 2;
            begin0.args = web49_malloc(sizeof(web49_instr_t) * 2);
            begin0.args[0] = ret.args[--ret.nargs];
            begin0.args[1] = cur;
            ret.args[ret.nargs++] = begin0;
        } else {
            ret.args[ret.nargs++] = cur;
        }
    }
    return ret;
}

struct web49_block_list_t;
typedef struct web49_block_list_t web49_block_list_t;

struct web49_block_list_t {
    uint32_t nparams;
    uint32_t nreturns;
};

void web49_opt_untree_emit_push(web49_instr_t cur, size_t *len, web49_instr_t **out, size_t *alloc) {
    if (*len + 2 >= *alloc) {
        *alloc = (*len + 2) * 2;
        *out = web49_realloc(*out, sizeof(web49_instr_t) * *alloc);
    }
    (*out)[(*len)++] = (web49_instr_t) {
        .opcode = cur.opcode,
        .immediate = cur.immediate,
    };
}

void web49_opt_untree_emit_counting(web49_opcode_t op, uint32_t num, size_t *len, web49_instr_t **out, size_t *alloc) {
    for (size_t i = 0; i < num; i++) {
        web49_instr_t instr = (web49_instr_t){
            .opcode = op,
            .immediate = (web49_instr_immediate_t){
                .id = WEB49_IMMEDIATE_VARUINT32,
                .varuint32 = i + 1024,
            },
        };
        web49_opt_untree_emit_push(instr, len, out, alloc);
    }
}

void web49_opt_untree(web49_module_t *mod, uint32_t func_nreturns, web49_block_list_t **pblocks, web49_instr_t cur, size_t *len, web49_instr_t **out, size_t *alloc) {
    size_t nargs = cur.nargs;
    cur.nargs = 0;
    if (cur.opcode == WEB49_OPCODE_IF) {
        web49_block_list_t list;
        web49_block_type_t type = cur.immediate.block_type;
        cur.immediate.block_type = (web49_block_type_t) {
            .type_value = WEB49_TYPE_BLOCK_TYPE,
            .is_type_index = false,
        };
        if (type.is_type_index) {
            web49_section_type_t types = web49_module_get_section(*mod, WEB49_SECTION_ID_TYPE).type_section;
            web49_section_type_entry_t te = types.entries[type.type_index];
            list.nreturns = te.num_returns;
            list.nparams = te.num_params;
        } else if (type.type_value != WEB49_TYPE_BLOCK_TYPE) {
            list.nparams = 0;
            list.nreturns = 1;
        } else {
            list.nparams = 0;
            list.nreturns = 0;
        }
        for (size_t i = 0; i < nargs; i++) {
            if (cur.args[i].opcode != WEB49_OPCODE_THEN && cur.args[i].opcode != WEB49_OPCODE_ELSE && cur.args[i].opcode != WEB49_OPCODE_END) {
                web49_opt_untree(mod, func_nreturns, pblocks, cur.args[i], len, out, alloc);
            }
        }
        (*pblocks)[1] = list;
        *pblocks += 1;
        if (list.nparams == 0) {
            web49_opt_untree_emit_push(cur, len, out, alloc);
        } else {
            web49_opt_untree_emit_push((web49_instr_t){.opcode = WEB49_OPCODE_SET_LOCAL, .immediate.id = WEB49_IMMEDIATE_VARUINT32, .immediate.varuint32 = list.nparams}, len, out, alloc);
            web49_opt_untree_emit_counting(WEB49_OPCODE_SET_LOCAL, list.nparams, len, out, alloc);
            web49_opt_untree_emit_push((web49_instr_t){.opcode = WEB49_OPCODE_GET_LOCAL, .immediate.id = WEB49_IMMEDIATE_VARUINT32, .immediate.varuint32 = list.nparams}, len, out, alloc);
            web49_opt_untree_emit_push(cur, len, out, alloc);
        }
        for (size_t i = 0; i < nargs; i++) {
            if (cur.args[i].opcode == WEB49_OPCODE_THEN || cur.args[i].opcode == WEB49_OPCODE_ELSE || cur.args[i].opcode == WEB49_OPCODE_END) {
                web49_opt_untree(mod, func_nreturns, pblocks, cur.args[i], len, out, alloc);
            }
        }
    } else if (cur.opcode == WEB49_OPCODE_BR || cur.opcode == WEB49_OPCODE_BR_IF || cur.opcode == WEB49_OPCODE_BR_TABLE) {
        web49_block_list_t *head = *pblocks;
        if (cur.opcode == WEB49_OPCODE_BR_TABLE) {
            head -= cur.immediate.br_table.default_target;
        } else {
            head -= cur.immediate.varuint32;
        }
        if (cur.opcode == WEB49_OPCODE_BR_IF && head->nreturns != 0) {
            web49_opt_untree_emit_push((web49_instr_t){.opcode = WEB49_OPCODE_SET_LOCAL, .immediate.id = WEB49_IMMEDIATE_VARUINT32, .immediate.varuint32 = head->nreturns}, len, out, alloc);
            web49_opt_untree_emit_counting(WEB49_OPCODE_SET_LOCAL, head->nreturns, len, out, alloc);
            web49_opt_untree_emit_push((web49_instr_t){.opcode = WEB49_OPCODE_GET_LOCAL, .immediate.id = WEB49_IMMEDIATE_VARUINT32, .immediate.varuint32 = head->nreturns}, len, out, alloc);
            web49_opt_untree_emit_push(cur, len, out, alloc);
            web49_opt_untree_emit_counting(WEB49_OPCODE_GET_LOCAL, head->nreturns, len, out, alloc);
        } else {
            web49_opt_untree_emit_counting(WEB49_OPCODE_SET_LOCAL, head->nreturns, len, out, alloc);
            web49_opt_untree_emit_push(cur, len, out, alloc);
        }
    } else if (cur.opcode == WEB49_OPCODE_BLOCK || cur.opcode == WEB49_OPCODE_LOOP) {
        web49_block_list_t list;
        web49_block_type_t type = cur.immediate.block_type;
        cur.immediate.block_type = (web49_block_type_t) {
            .type_value = WEB49_TYPE_BLOCK_TYPE,
            .is_type_index = false,
        };
        if (type.is_type_index) {
            web49_section_type_t types = web49_module_get_section(*mod, WEB49_SECTION_ID_TYPE).type_section;
            web49_section_type_entry_t te = types.entries[type.type_index];
            list.nreturns = te.num_returns;
            list.nparams = te.num_params;
        } else if (type.type_value != WEB49_TYPE_BLOCK_TYPE) {
            list.nparams = 0;
            list.nreturns = 1;
        } else {
            list.nparams = 0;
            list.nreturns = 0;
        }
        web49_opt_untree_emit_counting(WEB49_OPCODE_SET_LOCAL, list.nparams, len, out, alloc);
        web49_opt_untree_emit_push(cur, len, out, alloc);
        web49_opt_untree_emit_counting(WEB49_OPCODE_GET_LOCAL, list.nparams, len, out, alloc);
        (*pblocks)[1] = list;
        *pblocks += 1;
        for (size_t i = 0; i < nargs; i++) {
            web49_opt_untree(mod, func_nreturns, pblocks, cur.args[i], len, out, alloc);
        }
    } else if (cur.opcode == WEB49_OPCODE_THEN || cur.opcode == WEB49_OPCODE_ELSE) {
        if (cur.opcode == WEB49_OPCODE_ELSE) {
            web49_opt_untree_emit_counting(WEB49_OPCODE_SET_LOCAL, (**pblocks).nreturns, len, out, alloc);
            web49_opt_untree_emit_push((web49_instr_t){.opcode = WEB49_OPCODE_ELSE}, len, out, alloc);
        }
        web49_opt_untree_emit_counting(WEB49_OPCODE_GET_LOCAL, (**pblocks).nparams, len, out, alloc);
        for (size_t i = 0; i < nargs; i++) {
            web49_opt_untree(mod, func_nreturns, pblocks, cur.args[i], len, out, alloc);
        }
    } else if (cur.opcode == WEB49_OPCODE_END) {
        web49_opt_untree_emit_counting(WEB49_OPCODE_SET_LOCAL, (**pblocks).nreturns, len, out, alloc);
        web49_opt_untree_emit_push((web49_instr_t){.opcode = WEB49_OPCODE_END}, len, out, alloc);
        web49_opt_untree_emit_counting(WEB49_OPCODE_GET_LOCAL, (**pblocks).nreturns, len, out, alloc);
        *pblocks -= 1;
    } else if (cur.opcode == WEB49_OPCODE_RETURN) {
        for (size_t i = 0; i < nargs; i++) {
            web49_opt_untree(mod, func_nreturns, pblocks, cur.args[i], len, out, alloc);
        }
        if (func_nreturns > 1) {
            web49_opt_untree_emit_counting(WEB49_OPCODE_SET_LOCAL, func_nreturns, len, out, alloc);
            web49_opt_untree_emit_counting(WEB49_OPCODE_GET_LOCAL, func_nreturns, len, out, alloc);
        }
        for (size_t i = 0; i < func_nreturns; i++) {
            web49_instr_t instr = (web49_instr_t){
                .opcode = WEB49_OPCODE_SET_LOCAL,
                .immediate = (web49_instr_immediate_t){
                    .id = WEB49_IMMEDIATE_VARUINT32,
                    .varuint32 = func_nreturns - i - 1,
                },
            };
            web49_opt_untree_emit_push(instr, len, out, alloc);
        }
        web49_opt_untree_emit_push((web49_instr_t){.opcode = WEB49_OPCODE_RETURN}, len, out, alloc);
    } else {
        for (size_t i = 0; i < nargs; i++) {
            web49_opt_untree(mod, func_nreturns, pblocks, cur.args[i], len, out, alloc);
        }
        web49_opt_untree_emit_push(cur, len, out, alloc);
    }
}

void web49_opt_tree_code(web49_module_t *mod, web49_section_code_entry_t *entry, web49_section_type_entry_t type) {
    web49_instr_t *head = NULL;
    size_t alloc = 0;
    size_t len = 0;
    web49_block_list_t stack_blocks[256];
    web49_block_list_t *blocks = &stack_blocks[0];
    blocks[0] = (web49_block_list_t) {
        // .nparams = type.num_params,
        .nparams = 0,
        .nreturns = 0,
    };
    // fprintf(stderr, " ---0---\n");
    for (size_t i = 0; i < entry->num_instrs; i++) {
        // web49_debug_print_instr(stderr, entry->instrs[i]);
        web49_opt_untree(mod, type.num_returns, &blocks, entry->instrs[i], &len, &head, &alloc);
    }
    // fprintf(stderr, " ---1---\n");
    // for (size_t i = 0; i < len; i++) {
    //     web49_debug_print_instr(stderr, head[i]);
    // }
    web49_instr_t bump = head[--len];
    web49_opt_untree(mod, type.num_returns, &blocks, (web49_instr_t) {.opcode = WEB49_OPCODE_RETURN}, &len, &head, &alloc);
    web49_opt_untree_emit_push(bump, &len, &head, &alloc);
    // fprintf(stderr, " ---2---\n");
    // for (size_t i = 0; i < len; i++) {
    //     web49_debug_print_instr(stderr, head[i]);
    // }
    // fprintf(stderr, " ---3---\n");
    web49_instr_t instr = web49_opt_tree_read_block(mod, &head);
    // web49_debug_print_instr(stderr, instr);
    // fprintf(stderr, " ---4---\n\n\n");
    entry->instrs = web49_realloc(entry->instrs, sizeof(web49_instr_t) * 1);
    entry->num_instrs = 1;
    entry->instrs[0] = instr;
}

void web49_opt_tree_module(web49_module_t *mod) {
    web49_section_code_t code_section = web49_module_get_section(*mod, WEB49_SECTION_ID_CODE).code_section;
    web49_section_function_t function_section = web49_module_get_section(*mod, WEB49_SECTION_ID_FUNCTION).function_section;
    web49_section_type_t type_section = web49_module_get_section(*mod, WEB49_SECTION_ID_TYPE).type_section;
    for (uint64_t i = 0; i < code_section.num_entries; i++) {
        web49_opt_tree_code(mod, &code_section.entries[i], type_section.entries[function_section.entries[i]]);
    }
}