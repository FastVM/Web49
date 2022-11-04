#include "interp.h"
#include "../tables.h"

web49_interp_block_t *web49_interp_import(web49_interp_t *interp, const char *mod, const char *sym) {
    if (!strcmp(mod, "wasi_snapshot_preview1")) {
        if (!strcmp(sym, "proc_exit")) {
            static web49_interp_opcode_t code[] = {
                (web49_interp_opcode_t) {
                    .opcode = WEB49_INTERP_INSTR_WASI_EXIT,
                },
            };
            static web49_interp_block_t ret = (web49_interp_block_t) {
                .code = code,
            };
            return &ret;
        }
        if (!strcmp(sym, "fd_write")) {
            static web49_interp_opcode_t code[] = {
                (web49_interp_opcode_t) {
                    .opcode = WEB49_INTERP_INSTR_WASI_FD_WRITE,
                },
            };
            static web49_interp_block_t ret = (web49_interp_block_t) {
                .code = code,
            };
            return &ret;
        }
        if (!strcmp(sym, "fd_close")) {
            static web49_interp_opcode_t code[] = {
                (web49_interp_opcode_t) {
                    .opcode = WEB49_INTERP_INSTR_WASI_FD_CLOSE,
                },
            };
            static web49_interp_block_t ret = (web49_interp_block_t) {
                .code = code,
            };
            return &ret;
        }
        if (!strcmp(sym, "fd_seek")) {
            static web49_interp_opcode_t code[] = {
                (web49_interp_opcode_t) {
                    .opcode = WEB49_INTERP_INSTR_WASI_FD_SEEK,
                },
            };
            static web49_interp_block_t ret = (web49_interp_block_t) {
                .code = code,
            };
            return &ret;
        }
        fprintf(stderr, "unknown wasi import symbol: %s\n", sym);
        exit(1);
    }
    fprintf(stderr, "unknown import module: %s\n", mod);
    exit(1);
}

web49_interp_block_t *web49_interp_read_block(web49_interp_t *interp, web49_interp_instr_buf_t *instrs) {
    uint64_t alloc = 64;
    web49_interp_opcode_t *code = web49_malloc(sizeof(web49_interp_opcode_t) * alloc);
    uint64_t ncode = 0;
    while (instrs->head < instrs->len) {
        web49_instr_t cur = instrs->instrs[instrs->head++];
        if (cur.opcode == WEB49_OPCODE_END || cur.opcode == WEB49_OPCODE_ELSE) {
            break;
        }
        switch (cur.opcode) {
        case WEB49_OPCODE_NOP:
            break;
        case WEB49_OPCODE_UNREACHABLE:
            break;
        case WEB49_OPCODE_RETURN:
            break;
        case WEB49_OPCODE_DROP:
            code[ncode++].opcode = WEB49_INTERP_INSTR_DROP;
            break;
        case WEB49_OPCODE_GET_GLOBAL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_GET_GLOBAL;
            code[ncode++].ptr = &interp->globals[cur.immediate.varuint32];
            break;
        case WEB49_OPCODE_SET_GLOBAL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_SET_GLOBAL;
            code[ncode++].ptr = &interp->globals[cur.immediate.varuint32];
            break;
        case WEB49_OPCODE_I64_CONST:
            code[ncode++].opcode = WEB49_INTERP_INSTR_DATA_CONST;
            code[ncode++].data.i64_s = cur.immediate.varint64;
            break;
        case WEB49_OPCODE_I32_CONST:
            code[ncode++].opcode = WEB49_INTERP_INSTR_DATA_CONST;
            code[ncode++].data.i32_s = cur.immediate.varint32;
            break;
        case WEB49_OPCODE_I32_ADD:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_ADD;
            break;
        case WEB49_OPCODE_I32_SUB:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_SUB;
            break;
        case WEB49_OPCODE_I32_MUL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_MUL;
            break;
        case WEB49_OPCODE_I32_DIV_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_DIV_S;
            break;
        case WEB49_OPCODE_I32_DIV_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_DIV_S;
            break;
        case WEB49_OPCODE_I32_EQ:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_EQ;
            break;
        case WEB49_OPCODE_I32_NE:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_NE;
            break;
        case WEB49_OPCODE_I32_LT_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LT_S;
            break;
        case WEB49_OPCODE_I32_GT_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_GT_S;
            break;
        case WEB49_OPCODE_I32_LE_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LE_S;
            break;
        case WEB49_OPCODE_I32_GE_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_GE_S;
            break;
        case WEB49_OPCODE_I32_LT_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LT_U;
            break;
        case WEB49_OPCODE_I32_GT_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_GT_U;
            break;
        case WEB49_OPCODE_I32_LE_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LE_U;
            break;
        case WEB49_OPCODE_I32_GE_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_GE_U;
            break;
        case WEB49_OPCODE_I32_SHL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_SHL;
            break;
        case WEB49_OPCODE_I32_SHR_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_SHR_S;
            break;
        case WEB49_OPCODE_I32_SHR_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_SHR_U;
            break;
        case WEB49_OPCODE_I32_EQZ:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_EQZ;
            break;
        case WEB49_OPCODE_I32_OR:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_OR;
            break;
        case WEB49_OPCODE_I32_XOR:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_XOR;
            break;
        case WEB49_OPCODE_I32_AND:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_AND;
            break;
        case WEB49_OPCODE_I32_STORE:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_STORE;
            break;
        case WEB49_OPCODE_I32_LOAD:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LOAD;
            break;
        case WEB49_OPCODE_I32_STORE8:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_STORE8;
            break;
        case WEB49_OPCODE_I32_LOAD8_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LOAD8_S;
            break;
        case WEB49_OPCODE_I32_LOAD8_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LOAD8_U;
            break;
        case WEB49_OPCODE_I32_STORE16:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_STORE16;
            break;
        case WEB49_OPCODE_I32_LOAD16_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LOAD16_S;
            break;
        case WEB49_OPCODE_I32_LOAD16_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I32_LOAD16_U;
            break;
        case WEB49_OPCODE_I64_ADD:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_ADD;
            break;
        case WEB49_OPCODE_I64_SUB:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_SUB;
            break;
        case WEB49_OPCODE_I64_MUL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_MUL;
            break;
        case WEB49_OPCODE_I64_DIV_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_DIV_S;
            break;
        case WEB49_OPCODE_I64_DIV_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_DIV_S;
            break;
        case WEB49_OPCODE_I64_EQ:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_EQ;
            break;
        case WEB49_OPCODE_I64_NE:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_NE;
            break;
        case WEB49_OPCODE_I64_LT_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LT_S;
            break;
        case WEB49_OPCODE_I64_GT_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_GT_S;
            break;
        case WEB49_OPCODE_I64_LE_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LE_S;
            break;
        case WEB49_OPCODE_I64_GE_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_GE_S;
            break;
        case WEB49_OPCODE_I64_LT_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LT_U;
            break;
        case WEB49_OPCODE_I64_GT_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_GT_U;
            break;
        case WEB49_OPCODE_I64_LE_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LE_U;
            break;
        case WEB49_OPCODE_I64_GE_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_GE_U;
            break;
        case WEB49_OPCODE_I64_EQZ:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_EQZ;
            break;
        case WEB49_OPCODE_I64_OR:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_OR;
            break;
        case WEB49_OPCODE_I64_AND:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_AND;
            break;
        case WEB49_OPCODE_I64_XOR:
            code[ncode++].opcode = WEB49_OPCODE_I64_XOR;
            break;
        case WEB49_OPCODE_I64_STORE:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_STORE;
            break;
        case WEB49_OPCODE_I64_LOAD:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LOAD;
            break;
        case WEB49_OPCODE_I64_STORE8:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_STORE8;
            break;
        case WEB49_OPCODE_I64_LOAD8_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LOAD8_S;
            break;
        case WEB49_OPCODE_I64_LOAD8_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LOAD8_U;
            break;
        case WEB49_OPCODE_I64_STORE16:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_STORE16;
            break;
        case WEB49_OPCODE_I64_LOAD16_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LOAD16_S;
            break;
        case WEB49_OPCODE_I64_LOAD16_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LOAD16_U;
            break;
        case WEB49_OPCODE_I64_STORE32:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_STORE32;
            break;
        case WEB49_OPCODE_I64_LOAD32_S:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LOAD32_S;
            break;
        case WEB49_OPCODE_I64_LOAD32_U:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_LOAD32_U;
            break;
        case WEB49_OPCODE_TEE_LOCAL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_TEE_LOCAL;
            code[ncode++].data.i32_u = cur.immediate.varuint32;
            break;
        case WEB49_OPCODE_GET_LOCAL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_GET_LOCAL;
            code[ncode++].data.i32_u = cur.immediate.varuint32;
            break;
        case WEB49_OPCODE_SET_LOCAL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_SET_LOCAL;
            code[ncode++].data.i32_u = cur.immediate.varuint32;
            break;
        case WEB49_OPCODE_CALL:
            code[ncode++].opcode = WEB49_INTERP_INSTR_CALL;
            code[ncode++].data.i32_u = cur.immediate.varuint32;
            break;
        case WEB49_OPCODE_CALL_INDIRECT:
            code[ncode++].opcode = WEB49_INTERP_INSTR_CALL_INDIRECT;
        case WEB49_OPCODE_BR:
            code[ncode++].opcode = WEB49_INTERP_INSTR_BR;
            code[ncode++].data.i32_u = cur.immediate.varuint32;
        case WEB49_OPCODE_BR_TABLE:
            code[ncode++].opcode = WEB49_INTERP_INSTR_BR_TABLE;
            code[ncode++].data.i32_u = cur.immediate.br_table.num_targets;
            for (uint64_t i = 0; i < cur.immediate.br_table.num_targets; i++) {
                code[ncode++].data.i32_u = cur.immediate.br_table.targets[i];
            }
            code[ncode++].data.i32_u = cur.immediate.br_table.default_target;
        case WEB49_OPCODE_BR_IF:
            code[ncode++].opcode = WEB49_INTERP_INSTR_BR_IF;
            code[ncode++].data.i32_u = cur.immediate.varuint32;
        case WEB49_OPCODE_SELECT:
            code[ncode++].opcode = WEB49_INTERP_INSTR_SELECT;
        case WEB49_OPCODE_IF:
            code[ncode++].opcode = WEB49_INTERP_INSTR_IF;
            code[ncode++].block = web49_interp_read_block(interp, instrs);
            if (instrs->instrs[instrs->head-1].opcode == WEB49_OPCODE_ELSE) {
                code[ncode++].block = web49_interp_read_block(interp, instrs);
            } else {
                static web49_interp_opcode_t next[] = {
                    (web49_interp_opcode_t) {
                        .opcode = WEB49_INTERP_INSTR_END,
                    },
                };
                static web49_interp_block_t noop = (web49_interp_block_t) {
                    .code = next,
                };
                code[ncode++].block = &noop;
            }
            break;
        case WEB49_OPCODE_LOOP:
            code[ncode++].opcode = WEB49_INTERP_INSTR_LOOP;
            code[ncode++].block = web49_interp_read_block(interp, instrs);
            break;
        case WEB49_OPCODE_BLOCK:
            code[ncode++].opcode = WEB49_INTERP_INSTR_BLOCK;
            code[ncode++].block = web49_interp_read_block(interp, instrs);
            break;
        case WEB49_OPCODE_I64_EXTEND_S_I32:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_EXTEND_I32_S;
            break;
        case WEB49_OPCODE_I64_EXTEND_U_I32:
            code[ncode++].opcode = WEB49_INTERP_INSTR_I64_EXTEND_I32_U;
            break;
        default:
            fprintf(stderr, "not implemented: %s\n", web49_opcode_to_name(cur.opcode));
            exit(1);
        }
        if (ncode + 64 >= alloc) {
            alloc = (ncode + 64) * 2;
            code = web49_realloc(code, sizeof(web49_interp_opcode_t) * alloc);
        }
    }
    web49_interp_block_t *block = web49_malloc(sizeof(web49_interp_block_t));
    block->code = code;
    return block;
}

void web49_interp_module(web49_module_t mod) {
    web49_section_type_t type_section = {0};
    web49_section_import_t import_section = {0};
    web49_section_code_t code_section = {0};
    web49_section_global_t global_section = {0};
    uint64_t start = 0;
    for (size_t i = 0; i < mod.num_sections; i++) {
        web49_section_t section = mod.sections[i];
        if (section.header.id == WEB49_SECTION_ID_EXPORT) {
            for (size_t j = 0; j < section.export_section.num_entries; j++) {
                web49_section_export_entry_t entry = section.export_section.entries[j];
                if (!strcmp(entry.field_str, "_start")) {
                    start = entry.index;
                }
            }
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_TYPE) {
            type_section = mod.sections[i].type_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_IMPORT) {
            import_section = mod.sections[i].import_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_CODE){
            code_section = mod.sections[i].code_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_GLOBAL) {
            global_section = mod.sections[i].global_section;
        }
    }
    uint64_t num_funcs = code_section.num_entries;
    for (size_t j = 0; j < import_section.num_entries; j++) {
        web49_section_import_entry_t entry = import_section.entries[j];
        if (entry.kind == WEB49_EXTERNAL_KIND_FUNCTION) {
            num_funcs += 1;
        }
    }
    uint64_t cur_func = 0;
    web49_interp_block_t **blocks = web49_malloc(sizeof(web49_interp_block_t *) * num_funcs);
    web49_section_type_entry_t *ftypes = web49_malloc(sizeof(web49_section_type_entry_t) * num_funcs);
    web49_interp_data_t *globals = web49_malloc(sizeof(web49_interp_data_t) * global_section.num_entries);
    web49_interp_t interp = (web49_interp_t) {
        .funcs = blocks,
        .ftypes = ftypes,
        .globals = globals,
    };
    for (size_t j = 0; j < import_section.num_entries; j++) {
        web49_section_import_entry_t entry = import_section.entries[j];
        if (entry.kind == WEB49_EXTERNAL_KIND_FUNCTION) {
            ftypes[cur_func] = type_section.entries[entry.func_type.data];
            blocks[cur_func] = web49_interp_import(&interp, entry.module_str, entry.field_str);
            cur_func += 1;
        }
    }
    for (size_t j = 0; j < code_section.num_entries; j++) {
        web49_section_code_entry_t entry = code_section.entries[j];
        web49_interp_instr_buf_t buf;
        buf.head = 0;
        buf.len = entry.num_instrs;
        buf.instrs = entry.instrs;
        blocks[cur_func++] = web49_interp_read_block(&interp, &buf);
    }
}
