#include "interp.h"
#include <stdio.h>

#include "../tables.h"

#define OPCODE(n) ({size_t x = (n); if (ptrs[x] == NULL) {__builtin_trap();} ptrs[x]; })
#define MAX_DEPTH 256

uint64_t web49_interp_count(web49_instr_t cur) {
    uint64_t ret = 0;
    for (uint64_t i = 0; i < cur.nargs; i++) {
        ret += web49_interp_count(cur.args[i]);
    }
    ret += 4;
    switch (cur.immediate.id) {
        case WEB49_IMMEDIATE_BR_TABLE:
            ret += cur.immediate.br_table.num_targets + 1;
            break;
    }
    return ret;
}

uint32_t *web49_interp_link_box(void) {
    return web49_malloc(sizeof(uint32_t));
}

void web49_interp_link_get(web49_read_block_state_t *state, uint32_t out, uint32_t *from) {
    if (state->nlinks + 1 >= state->alloc_links) {
        state->alloc_links = (state->nlinks + 1) * 2;
        state->links = web49_realloc(state->links, sizeof(web49_interp_link_t) * state->alloc_links);
    }
    state->links[state->nlinks++] = (web49_interp_link_t){
        .box = from,
        .out = out,
    };
}

static bool web49_interp_cmp_to_ifcmp(web49_opcode_t opcode, web49_opcode_t *op_out, bool *swap_br_out) {
    switch (opcode) {
        case WEB49_OPCODE_I32_EQ:
            *op_out = WEB49_OPCODE_IF_I32_EQ;
            return true;
        case WEB49_OPCODE_I32_NE:
            *op_out = WEB49_OPCODE_IF_I32_EQ;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I32_LT_S:
            *op_out = WEB49_OPCODE_IF_I32_LT_S;
            return true;
        case WEB49_OPCODE_I32_LT_U:
            *op_out = WEB49_OPCODE_IF_I32_LT_U;
            return true;
        case WEB49_OPCODE_I32_GT_S:
            *op_out = WEB49_OPCODE_IF_I32_GT_S;
            return true;
        case WEB49_OPCODE_I32_GT_U:
            *op_out = WEB49_OPCODE_IF_I32_GT_U;
            return true;
        case WEB49_OPCODE_I32_LE_S:
            *op_out = WEB49_OPCODE_IF_I32_GT_S;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I32_LE_U:
            *op_out = WEB49_OPCODE_IF_I32_GT_U;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I32_GE_S:
            *op_out = WEB49_OPCODE_IF_I32_LT_S;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I32_GE_U:
            *op_out = WEB49_OPCODE_IF_I32_LT_U;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I64_EQ:
            *op_out = WEB49_OPCODE_IF_I64_EQ;
            return true;
        case WEB49_OPCODE_I64_NE:
            *op_out = WEB49_OPCODE_IF_I64_EQ;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I64_LT_S:
            *op_out = WEB49_OPCODE_IF_I64_LT_S;
            return true;
        case WEB49_OPCODE_I64_LT_U:
            *op_out = WEB49_OPCODE_IF_I64_LT_U;
            return true;
        case WEB49_OPCODE_I64_GT_S:
            *op_out = WEB49_OPCODE_IF_I64_GT_S;
            return true;
        case WEB49_OPCODE_I64_GT_U:
            *op_out = WEB49_OPCODE_IF_I64_GT_U;
            return true;
        case WEB49_OPCODE_I64_LE_S:
            *op_out = WEB49_OPCODE_IF_I64_GT_S;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I64_LE_U:
            *op_out = WEB49_OPCODE_IF_I64_GT_U;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I64_GE_S:
            *op_out = WEB49_OPCODE_IF_I64_LT_S;
            *swap_br_out = true;
            return true;
        case WEB49_OPCODE_I64_GE_U:
            *op_out = WEB49_OPCODE_IF_I64_LT_U;
            *swap_br_out = true;
            return true;
        default:
            return false;
    }
}

static void web49_interp_read_instr_branch(web49_read_block_state_t *state, web49_instr_t cond, uint32_t *ift, uint32_t *iff) {
    web49_interp_build_t *build = &state->build;
    void **ptrs = state->ptrs;
    uint32_t save = state->depth;
    web49_opcode_t op;
    bool swap_br = false;
    if (build->ncode + 16 >= build->alloc) {
        build->alloc = (build->ncode + 16) * 4;
        build->code = web49_realloc(build->code, sizeof(web49_interp_opcode_t) * build->alloc);
    }
    if (cond.opcode == WEB49_OPCODE_I32_EQZ) {
        web49_interp_read_instr_branch(state, cond.args[0], iff, ift);
    } else if (web49_interp_cmp_to_ifcmp(cond.opcode, &op, &swap_br)) {
        if (swap_br) {
            uint32_t *tt = ift;
            ift = iff;
            iff = tt;
        }
        uint32_t args[4];
#if defined(WEB49_OPT_CONST0)
        bool const0 = false;
#endif
        bool const1 = false;
        uint16_t add = 0;
        for (uint64_t i = 0; i < cond.nargs; i++) {
#if !defined(WEB49_NO_OPT)
            if (cond.args[i].opcode == WEB49_OPCODE_I32_CONST || cond.args[i].opcode == WEB49_OPCODE_I64_CONST || cond.args[i].opcode == WEB49_OPCODE_F32_CONST || cond.args[i].opcode == WEB49_OPCODE_F64_CONST) {
#if defined(WEB49_OPT_CONST0)
                if (i == 0) {
                    state->depth += 1;
                    const0 = true;
                    add += WEB49_OPCODE_WITH_CONST0;
                    continue;
                }
#endif
                if (i == 1) {
                    state->depth += 1;
                    const1 = true;
                    add += WEB49_OPCODE_WITH_CONST1;
                    continue;
                }
            }
            if (cond.args[i].opcode == WEB49_OPCODE_GET_LOCAL) {
                for (uint64_t j = i + 1; j < cond.nargs; j++) {
                    if (cond.args[j].opcode == WEB49_OPCODE_BEGIN0) {
                        goto next;
                    }
                }
                state->depth += 1;
                args[i] = cond.args[i].immediate.varint32;
                continue;
            }
        next:;
#endif
            args[i] = web49_interp_read_instr(state, cond.args[i], UINT32_MAX);
        }
        build->code[build->ncode++].opcode = OPCODE(op + add);
        for (uint64_t i = 0; i < cond.nargs; i++) {
#if defined(WEB49_OPT_CONST0)
            if (i == 0 && const0) {
                build->code[build->ncode++].data.i64_u = cond.args[i].immediate.uint64;
                continue;
            }
#endif
            if (i == 1 && const1) {
                build->code[build->ncode++].data.i64_u = cond.args[i].immediate.uint64;
                continue;
            }
            build->code[build->ncode++].data.i32_u = args[i];
        }
        web49_interp_link_get(state, build->ncode++, ift);
        web49_interp_link_get(state, build->ncode++, iff);
    } else if (cond.opcode == WEB49_OPCODE_GET_LOCAL) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_IF);
        build->code[build->ncode++].data.i32_u = cond.immediate.varint32;
        web49_interp_link_get(state, build->ncode++, ift);
        web49_interp_link_get(state, build->ncode++, iff);
    } else {
        uint32_t cpos = web49_interp_read_instr(state, cond, UINT32_MAX);
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_IF);
        build->code[build->ncode++].data.i32_u = cpos;
        web49_interp_link_get(state, build->ncode++, ift);
        web49_interp_link_get(state, build->ncode++, iff);
    }
    state->depth = save;
}

uint32_t web49_interp_read_instr(web49_read_block_state_t *state, web49_instr_t cur, uint32_t local) {
    // web49_debug_print_instr(stderr, cur);
    web49_interp_build_t *build = &state->build;
    void **ptrs = state->ptrs;
    uint32_t off = 16;
    if (cur.immediate.id == WEB49_IMMEDIATE_BR_TABLE) {
        off += cur.immediate.br_table.num_targets;
    }
    if (build->ncode + off >= build->alloc) {
        build->alloc = (build->ncode + off) * 4;
        build->code = web49_realloc(build->code, sizeof(web49_interp_opcode_t) * build->alloc);
    }
    if (state->bufs_head + 2 >= state->bufs_alloc) {
        state->bufs_alloc = (state->bufs_head + 2) * 2;
        state->bufs_base = web49_realloc(state->bufs_base, sizeof(uint32_t *) * (state->bufs_alloc));
    }
    if (cur.opcode == WEB49_OPCODE_BR) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_BR);
        web49_interp_link_get(state, build->ncode++, state->bufs_base[state->bufs_head - (ptrdiff_t)cur.immediate.varuint32]);
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_BR_IF) {
        uint32_t *next = web49_interp_link_box();
        web49_interp_read_instr_branch(state, cur.args[0], state->bufs_base[state->bufs_head - cur.immediate.varuint32], next);
        *next = build->ncode;
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_BLOCK) {
        uint32_t *box = web49_interp_link_box();
        uint32_t save = state->depth;
        state->bufs_base[++state->bufs_head] = box;
        for (size_t i = 0; i < cur.nargs; i++) {
            web49_interp_read_instr(state, cur.args[i], UINT32_MAX);
        }
        state->bufs_head -= 1;
        state->depth = save;
        *box = build->ncode;
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_LOOP) {
        uint32_t *box = web49_interp_link_box();
        *box = build->ncode;
        uint32_t save = state->depth;
        state->bufs_base[++state->bufs_head] = box;
        for (size_t i = 0; i < cur.nargs; i++) {
            web49_interp_read_instr(state, cur.args[i], UINT32_MAX);
        }
        state->bufs_head -= 1;
        state->depth = save;
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_IF) {
        uint32_t *ift = web49_interp_link_box();
        uint32_t *iff = web49_interp_link_box();
        uint32_t *end;
        if (cur.nargs == 3) {
            end = web49_interp_link_box();
        } else {
            end = iff;
        }
        uint32_t *over = end;
        web49_interp_read_instr_branch(state, cur.args[0], ift, iff);
        state->bufs_base[++state->bufs_head] = end;
        uint32_t save = state->depth;
        *ift = build->ncode;
        for (size_t i = 0; i < cur.args[1].nargs; i++) {
            web49_interp_read_instr(state, cur.args[1].args[i], UINT32_MAX);
        }
        if (cur.nargs == 3) {
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_BR);
            web49_interp_link_get(state, build->ncode++, over);
            state->depth = save;
            *iff = build->ncode;
            for (size_t i = 0; i < cur.args[2].nargs; i++) {
                web49_interp_read_instr(state, cur.args[2].args[i], UINT32_MAX);
            }
        }
        state->depth = save;
        state->bufs_head -= 1;
        *end = build->ncode;
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_F64_REINTERPRET_I64 || cur.opcode == WEB49_OPCODE_I64_REINTERPRET_F64 || cur.opcode == WEB49_OPCODE_F32_REINTERPRET_I32 || cur.opcode == WEB49_OPCODE_I32_REINTERPRET_F32) {
        return web49_interp_read_instr(state, cur.args[0], local);
    }
    if (cur.opcode == WEB49_OPCODE_BEGIN0) {
        uint32_t depth = state->depth;
        uint32_t ret = UINT32_MAX;
        for (uint64_t i = 0; i < cur.nargs; i++) {
            uint32_t tmp = web49_interp_read_instr(state, cur.args[i], local);
            if (tmp != UINT32_MAX) {
                local = UINT32_MAX;
                ret = tmp;
                depth = state->depth;
            } else {
                state->depth = depth;
            }
        }
        return ret;
    }
    // if (cur.opcode == WEB49_OPCODE_SET_LOCAL && cur.args[0].opcode != WEB49_OPCODE_BEGIN0 && cur.args[0].opcode != WEB49_OPCODE_BLOCK && cur.args[0].opcode != WEB49_OPCODE_LOOP && cur.args[0].opcode != WEB49_OPCODE_IF) {
    if (cur.opcode == WEB49_OPCODE_SET_LOCAL) {
        uint32_t ret = web49_interp_read_instr(state, cur.args[0], cur.immediate.varuint32);
        state->depth -= 1;
        if (ret != cur.immediate.varuint32 && ret != UINT32_MAX) {
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_GET_LOCAL);
            // fprintf(stderr, "%zu\n", (size_t) cur.immediate.varuint32);
            build->code[build->ncode++].data.i32_u = cur.immediate.varuint32;
            build->code[build->ncode++].data.i32_u = ret;
        }
        return UINT32_MAX;
    }
#if defined(WEB49_OPT_CONST0)
    bool const0 = false;
#endif
    bool const1 = false;
    uint16_t add = 0;
    uint32_t args[16];
    uint32_t outer_begin = state->depth;
    for (uint64_t i = 0; i < cur.nargs; i++) {
#if !defined(WEB49_NO_OPT)
        if (cur.opcode != WEB49_OPCODE_CALL && cur.opcode != WEB49_OPCODE_CALL_INDIRECT) {
            if (cur.args[i].opcode == WEB49_OPCODE_I32_CONST || cur.args[i].opcode == WEB49_OPCODE_I64_CONST || cur.args[i].opcode == WEB49_OPCODE_F32_CONST || cur.args[i].opcode == WEB49_OPCODE_F64_CONST) {
#if defined(WEB49_OPT_CONST0)
                if (i == 0) {
                    state->depth += 1;
                    const0 = true;
                    add += WEB49_OPCODE_WITH_CONST0;
                    continue;
                }
#endif
                if (i == 1) {
                    state->depth += 1;
                    const1 = true;
                    add += WEB49_OPCODE_WITH_CONST1;
                    continue;
                }
            }
            if (cur.args[i].opcode == WEB49_OPCODE_GET_LOCAL) {
                for (uint64_t j = i + 1; j < cur.nargs; j++) {
                    if (cur.args[j].opcode == WEB49_OPCODE_BEGIN0) {
                        goto next;
                    }
                }
                state->depth += 1;
                args[i] = cur.args[i].immediate.varint32;
                continue;
            }
        }
    next:;
#endif
        uint32_t begin = state->depth;
        args[i] = web49_interp_read_instr(state, cur.args[i], UINT32_MAX);
        uint32_t end = state->depth;
        if (begin + 1 != end) {
            fprintf(stderr, "error: the below instruction did not yield exactly 1 value (debug: %"PRIu32"+1 != %"PRIu32")\n", begin, end);
            web49_debug_print_instr(stderr, cur.args[i]);
            __builtin_trap();
            // state->depth = begin + 1;
        }
    }
    uint32_t outer_end = state->depth;
    if (outer_begin + cur.nargs != outer_end) {
        fprintf(stderr, "error: stack should have been at %zu, but was at %zu\n", (size_t) (outer_begin + cur.nargs), (size_t) outer_end);
        web49_debug_print_instr(stderr, cur);
        __builtin_trap();
    }
    if (state->depth < cur.nargs) {
        __builtin_trap();
    } 
    state->depth -= cur.nargs;
    if (cur.opcode == WEB49_OPCODE_NOP1) {
        state->depth += 1;
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_NOP || cur.opcode == WEB49_OPCODE_UNREACHABLE) {
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_DROP) {
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_CALL_INDIRECT) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL_INDIRECT);
        build->code[build->ncode++].data.i32_u = args[cur.nargs - 1];
        build->code[build->ncode++].data.i32_u = cur.nargs - 1;
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_CALL) {
        // uint32_t nreturns = (uint32_t) state->interp->funcs[cur.immediate.varint32].nreturns;
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL);
        build->code[build->ncode++].ptr = &state->interp->funcs[cur.immediate.varint32];
        build->code[build->ncode++].data.i32_u = state->depth + state->nlocals;
        build->code[build->ncode++].data.i32_u = cur.nargs;
        //     case 0:
        //         build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL);
        //         build->code[build->ncode++].ptr = &state->interp->funcs[cur.immediate.varint32];
        //         build->code[build->ncode++].data.i32_u = state->depth + state->nlocals;
        //         build->code[build->ncode++].data.i32_u = state->depth + state->nlocals;
        //         build->code[build->ncode++].data.i32_u = cur.nargs;
        //         return UINT32_MAX;
        //     case 1:
        //         build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL);
        //         build->code[build->ncode++].ptr = &state->interp->funcs[cur.immediate.varint32];
        //         build->code[build->ncode++].data.i32_u = state->depth + state->nlocals;
        //         if (local == UINT32_MAX) {
        //             uint32_t out = state->depth + state->nlocals;
        //             build->code[build->ncode++].data.i32_u = out;
        //             build->code[build->ncode++].data.i32_u = cur.nargs;
        //             state->depth += 1;
        //             return out;
        //         } else {
        //             build->code[build->ncode++].data.i32_u = local;
        //             build->code[build->ncode++].data.i32_u = cur.nargs;
        //             state->depth += 1;
        //             return local;
        //         }
        //         break;
        //     default:
        //         fprintf(stderr, "cannot compile %zu returns yet\n", (size_t)state->interp->funcs[cur.immediate.varint32].nreturns);
        //         __builtin_trap();
        // }
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_RETURN) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN0);
        return UINT32_MAX;
    }
    build->code[build->ncode++].opcode = OPCODE(cur.opcode + add);
    for (uint64_t i = 0; i < cur.nargs; i++) {
#if defined(WEB49_OPT_CONST0)
        if (const0 && i == 0) {
            build->code[build->ncode++].data.i64_u = cur.args[i].immediate.uint64;
            continue;
        }
#endif
        if (const1 && i == 1) {
            build->code[build->ncode++].data.i64_u = cur.args[i].immediate.uint64;
            continue;
        }
        build->code[build->ncode++].data.i32_u = args[i];
    }
    uint32_t ret = UINT32_MAX;
    if (web49_stack_effects[cur.opcode].out[0] != WEB49_TABLE_STACK_EFFECT_END) {
        if (local == UINT32_MAX) {
            ret = state->depth + state->nlocals;
        } else {
            ret = local;
        }
        build->code[build->ncode++].data.i32_u = ret;
        state->depth += 1;
    }
    switch (cur.immediate.id) {
        case WEB49_IMMEDIATE_NONE:
            break;
        case WEB49_IMMEDIATE_BLOCK_TYPE:
            break;
        case WEB49_IMMEDIATE_VARUINT1:
            break;
        case WEB49_IMMEDIATE_VARUINT32:
            build->code[build->ncode++].data.i32_u = cur.immediate.varuint32;
            break;
        case WEB49_IMMEDIATE_VARUINT64:
            build->code[build->ncode++].data.i64_u = cur.immediate.varuint64;
            break;
        case WEB49_IMMEDIATE_VARINT32:
            build->code[build->ncode++].data.i32_s = cur.immediate.varint32;
            break;
        case WEB49_IMMEDIATE_VARINT64:
            build->code[build->ncode++].data.i64_s = cur.immediate.varint64;
            break;
        case WEB49_IMMEDIATE_UINT32:
            build->code[build->ncode++].data.i32_u = cur.immediate.uint32;
            break;
        case WEB49_IMMEDIATE_UINT64:
            build->code[build->ncode++].data.i64_u = cur.immediate.uint64;
            break;
        case WEB49_IMMEDIATE_BR_TABLE:
            build->code[build->ncode++].data.i32_u = cur.immediate.br_table.num_targets;
            for (uint64_t i = 0; i < cur.immediate.br_table.num_targets; i++) {
                web49_interp_link_get(state, build->ncode++, state->bufs_base[state->bufs_head - cur.immediate.br_table.targets[i]]);
            }
            web49_interp_link_get(state, build->ncode++, state->bufs_base[state->bufs_head - cur.immediate.br_table.default_target]);
            break;
        case WEB49_IMMEDIATE_CALL_INDIRECT:
            break;
        case WEB49_IMMEDIATE_MEMORY_IMMEDIATE:
            build->code[build->ncode++].data.i32_u = cur.immediate.memory_immediate.offset;
            break;
        case WEB49_IMMEDIATE_DATA_INDEX:
            break;
        default:
            fprintf(stderr, "bad immediate: %zu\n", (size_t)cur.immediate.id);
            __builtin_trap();
    }
    return ret;
}

#if defined(WEB49_PRINT_INSTR)
// #define DPRINT(name) for (size_t p=0; p<depth; p++) { fprintf(stderr, "| "); } fprintf(stderr, name "\n")
#define DPRINT(name) fprintf(stderr, name "\n")
#else
#define DPRINT(name)
#endif

#if 0
#define LABEL(name)          \
    __builtin_unreachable(); \
    DO_##name:;              \
    DPRINT(#name);           \
    head += 1;
#define NEXT() goto * head->opcode
#else
#define LABEL(name)          \
    __builtin_unreachable(); \
    DO_##name:;              \
    DPRINT(#name);
#define NEXT() goto *head++->opcode
#endif

void web49_interp_block_run_comp(web49_interp_block_t *block, void **ptrs, web49_interp_t interp) {
    if (block->code == NULL) {
        if (block->is_code) {
            web49_read_block_state_t state;
            state.ptrs = ptrs;
            state.bufs_alloc = 4;
            state.bufs_base = web49_malloc(sizeof(uint32_t *) * (state.bufs_alloc));
            state.bufs_head = 0;
            state.interp = &interp;
            state.build.alloc = 32;
            state.build.code = web49_malloc(sizeof(web49_interp_opcode_t) * state.build.alloc);
            state.build.ncode = 0;
            state.alloc_links = 0;
            state.nlinks = 0;
            state.links = NULL;
            state.depth = 0;
            state.nlocals = block->nparams + block->nlocals;
            uint32_t ret = UINT32_MAX;
            for (uint64_t i = 0; i < block->num_instrs; i++) {
                web49_debug_print_instr(stderr, block->instrs[i]);
                uint32_t tmp = web49_interp_read_instr(&state, block->instrs[i], UINT32_MAX);
                if (tmp != UINT32_MAX) {
                    ret = tmp;
                }
            }
            // state.build.code[state.build.ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN0);
            for (size_t i = 0; i < state.nlinks; i++) {
                web49_interp_link_t link = state.links[i];
                state.build.code[link.out].ptr = &state.build.code[*link.box];
            }
            for (size_t i = 0; i < state.nlinks; i++) {
                state.links[i].box[0] = 0;
            }
            for (size_t i = 0; i < state.nlinks; i++) {
                state.links[i].box[0] += 1;
            }
            for (size_t i = 0; i < state.nlinks; i++) {
                if (--state.links[i].box[0] == 0) {
                    web49_free(state.links[i].box);
                }
            }
            web49_free(state.links);
            web49_free(state.bufs_base);
            web49_free(block->instrs);
            block->code = state.build.code;
        } else {
            web49_interp_opcode_t *instrs = web49_malloc(sizeof(web49_interp_opcode_t) * 2);
            instrs[0].opcode = OPCODE(WEB49_OPCODE_FFI_CALL);
            instrs[1].ptr = interp.import_func(interp.import_state, block->module_str, block->field_str);
            if (instrs[1].ptr == NULL) {
                fprintf(stderr, "not implemented: %s.%s\n", block->module_str, block->field_str);
                __builtin_trap();
            }
            web49_free(block->module_str);
            web49_free(block->field_str);
            block->code = instrs;
        }
    }
}

web49_interp_data_t *web49_interp_block_run(web49_interp_t *ptr_interp, web49_interp_block_t *block) {
    web49_interp_t interp = *ptr_interp;
    static void *ptrs[WEB49_MAX_OPCODE_INTERP_NUM] = {
#define TABLE_PUTV(n, v) [n] = &&DO_##v
#if defined(WEB49_OPT_CONST0)
#define TABLE_PUT0(x) TABLE_PUTV(x, x)
#define TABLE_PUT1(x) TABLE_PUTV(x, x##_R), TABLE_PUTV(x + WEB49_OPCODE_WITH_CONST0, x##_C0)
#define TABLE_PUT2(x) TABLE_PUTV(x, x##_R), TABLE_PUTV(x + WEB49_OPCODE_WITH_CONST0, x##_C0), TABLE_PUTV(x + WEB49_OPCODE_WITH_CONST1, x##_C1), TABLE_PUTV(x + WEB49_OPCODE_WITH_CONST0 + WEB49_OPCODE_WITH_CONST1, x##_C01)
#else
#define TABLE_PUT0(x) TABLE_PUTV(x, x)
#define TABLE_PUT1(x) TABLE_PUTV(x, x##_R)
#define TABLE_PUT2(x) TABLE_PUTV(x, x##_R), TABLE_PUTV(x + WEB49_OPCODE_WITH_CONST1, x##_C1)
#endif
        TABLE_PUT1(WEB49_OPCODE_IF),
        TABLE_PUT0(WEB49_OPCODE_BR),
        TABLE_PUT1(WEB49_OPCODE_BR_TABLE),
        TABLE_PUT0(WEB49_OPCODE_CALL),
        TABLE_PUT1(WEB49_OPCODE_CALL_INDIRECT),
        TABLE_PUT2(WEB49_OPCODE_SELECT),
        TABLE_PUT0(WEB49_OPCODE_GET_LOCAL),
        TABLE_PUT0(WEB49_OPCODE_GET_GLOBAL),
        TABLE_PUT1(WEB49_OPCODE_SET_GLOBAL),
        TABLE_PUT1(WEB49_OPCODE_I32_LOAD),
        TABLE_PUT1(WEB49_OPCODE_I64_LOAD),
        TABLE_PUT1(WEB49_OPCODE_F32_LOAD),
        TABLE_PUT1(WEB49_OPCODE_F64_LOAD),
        TABLE_PUT1(WEB49_OPCODE_I32_LOAD8_S),
        TABLE_PUT1(WEB49_OPCODE_I32_LOAD8_U),
        TABLE_PUT1(WEB49_OPCODE_I32_LOAD16_S),
        TABLE_PUT1(WEB49_OPCODE_I32_LOAD16_U),
        TABLE_PUT1(WEB49_OPCODE_I64_LOAD8_S),
        TABLE_PUT1(WEB49_OPCODE_I64_LOAD8_U),
        TABLE_PUT1(WEB49_OPCODE_I64_LOAD16_S),
        TABLE_PUT1(WEB49_OPCODE_I64_LOAD16_U),
        TABLE_PUT1(WEB49_OPCODE_I64_LOAD32_S),
        TABLE_PUT1(WEB49_OPCODE_I64_LOAD32_U),
        TABLE_PUT2(WEB49_OPCODE_I32_STORE),
        TABLE_PUT2(WEB49_OPCODE_I64_STORE),
        TABLE_PUT2(WEB49_OPCODE_F32_STORE),
        TABLE_PUT2(WEB49_OPCODE_F64_STORE),
        TABLE_PUT2(WEB49_OPCODE_I32_STORE8),
        TABLE_PUT2(WEB49_OPCODE_I32_STORE16),
        TABLE_PUT2(WEB49_OPCODE_I64_STORE8),
        TABLE_PUT2(WEB49_OPCODE_I64_STORE16),
        TABLE_PUT2(WEB49_OPCODE_I64_STORE32),
        TABLE_PUT0(WEB49_OPCODE_MEMORY_SIZE),
        TABLE_PUT1(WEB49_OPCODE_MEMORY_GROW),
        TABLE_PUT0(WEB49_OPCODE_I32_CONST),
        TABLE_PUT0(WEB49_OPCODE_I64_CONST),
        TABLE_PUT0(WEB49_OPCODE_F32_CONST),
        TABLE_PUT0(WEB49_OPCODE_F64_CONST),
        TABLE_PUT1(WEB49_OPCODE_I32_EQZ),
        TABLE_PUT2(WEB49_OPCODE_I32_EQ),
        TABLE_PUT2(WEB49_OPCODE_I32_NE),
        TABLE_PUT2(WEB49_OPCODE_I32_LT_S),
        TABLE_PUT2(WEB49_OPCODE_I32_LT_U),
        TABLE_PUT2(WEB49_OPCODE_I32_GT_S),
        TABLE_PUT2(WEB49_OPCODE_I32_GT_U),
        TABLE_PUT2(WEB49_OPCODE_I32_LE_S),
        TABLE_PUT2(WEB49_OPCODE_I32_LE_U),
        TABLE_PUT2(WEB49_OPCODE_I32_GE_S),
        TABLE_PUT2(WEB49_OPCODE_I32_GE_U),
        TABLE_PUT1(WEB49_OPCODE_I64_EQZ),
        TABLE_PUT2(WEB49_OPCODE_I64_EQ),
        TABLE_PUT2(WEB49_OPCODE_I64_NE),
        TABLE_PUT2(WEB49_OPCODE_I64_LT_S),
        TABLE_PUT2(WEB49_OPCODE_I64_LT_U),
        TABLE_PUT2(WEB49_OPCODE_I64_GT_S),
        TABLE_PUT2(WEB49_OPCODE_I64_GT_U),
        TABLE_PUT2(WEB49_OPCODE_I64_LE_S),
        TABLE_PUT2(WEB49_OPCODE_I64_LE_U),
        TABLE_PUT2(WEB49_OPCODE_I64_GE_S),
        TABLE_PUT2(WEB49_OPCODE_I64_GE_U),
        TABLE_PUT2(WEB49_OPCODE_F32_EQ),
        TABLE_PUT2(WEB49_OPCODE_F32_NE),
        TABLE_PUT2(WEB49_OPCODE_F32_LT),
        TABLE_PUT2(WEB49_OPCODE_F32_GT),
        TABLE_PUT2(WEB49_OPCODE_F32_LE),
        TABLE_PUT2(WEB49_OPCODE_F32_GE),
        TABLE_PUT2(WEB49_OPCODE_F64_EQ),
        TABLE_PUT2(WEB49_OPCODE_F64_NE),
        TABLE_PUT2(WEB49_OPCODE_F64_LT),
        TABLE_PUT2(WEB49_OPCODE_F64_GT),
        TABLE_PUT2(WEB49_OPCODE_F64_LE),
        TABLE_PUT2(WEB49_OPCODE_F64_GE),
        TABLE_PUT2(WEB49_OPCODE_IF_I32_EQ),
        TABLE_PUT2(WEB49_OPCODE_IF_I32_LT_S),
        TABLE_PUT2(WEB49_OPCODE_IF_I32_LT_U),
        TABLE_PUT2(WEB49_OPCODE_IF_I32_GT_S),
        TABLE_PUT2(WEB49_OPCODE_IF_I32_GT_U),
        TABLE_PUT2(WEB49_OPCODE_IF_I64_EQ),
        TABLE_PUT2(WEB49_OPCODE_IF_I64_LT_S),
        TABLE_PUT2(WEB49_OPCODE_IF_I64_LT_U),
        TABLE_PUT2(WEB49_OPCODE_IF_I64_GT_S),
        TABLE_PUT2(WEB49_OPCODE_IF_I64_GT_U),
        TABLE_PUT1(WEB49_OPCODE_I32_CLZ),
        TABLE_PUT1(WEB49_OPCODE_I32_CTZ),
        TABLE_PUT1(WEB49_OPCODE_I32_POPCNT),
        TABLE_PUT2(WEB49_OPCODE_I32_ADD),
        TABLE_PUT2(WEB49_OPCODE_I32_SUB),
        TABLE_PUT2(WEB49_OPCODE_I32_MUL),
        TABLE_PUT2(WEB49_OPCODE_I32_DIV_S),
        TABLE_PUT2(WEB49_OPCODE_I32_DIV_U),
        TABLE_PUT2(WEB49_OPCODE_I32_REM_S),
        TABLE_PUT2(WEB49_OPCODE_I32_REM_U),
        TABLE_PUT2(WEB49_OPCODE_I32_AND),
        TABLE_PUT2(WEB49_OPCODE_I32_OR),
        TABLE_PUT2(WEB49_OPCODE_I32_XOR),
        TABLE_PUT2(WEB49_OPCODE_I32_SHL),
        TABLE_PUT2(WEB49_OPCODE_I32_SHR_S),
        TABLE_PUT2(WEB49_OPCODE_I32_SHR_U),
        TABLE_PUT2(WEB49_OPCODE_I32_ROTL),
        TABLE_PUT2(WEB49_OPCODE_I32_ROTR),
        TABLE_PUT1(WEB49_OPCODE_I64_CLZ),
        TABLE_PUT1(WEB49_OPCODE_I64_CTZ),
        TABLE_PUT1(WEB49_OPCODE_I64_POPCNT),
        TABLE_PUT2(WEB49_OPCODE_I64_ADD),
        TABLE_PUT2(WEB49_OPCODE_I64_SUB),
        TABLE_PUT2(WEB49_OPCODE_I64_MUL),
        TABLE_PUT2(WEB49_OPCODE_I64_DIV_S),
        TABLE_PUT2(WEB49_OPCODE_I64_DIV_U),
        TABLE_PUT2(WEB49_OPCODE_I64_REM_S),
        TABLE_PUT2(WEB49_OPCODE_I64_REM_U),
        TABLE_PUT2(WEB49_OPCODE_I64_AND),
        TABLE_PUT2(WEB49_OPCODE_I64_OR),
        TABLE_PUT2(WEB49_OPCODE_I64_XOR),
        TABLE_PUT2(WEB49_OPCODE_I64_SHL),
        TABLE_PUT2(WEB49_OPCODE_I64_SHR_S),
        TABLE_PUT2(WEB49_OPCODE_I64_SHR_U),
        TABLE_PUT2(WEB49_OPCODE_I64_ROTL),
        TABLE_PUT2(WEB49_OPCODE_I64_ROTR),
        TABLE_PUT1(WEB49_OPCODE_F32_ABS),
        TABLE_PUT1(WEB49_OPCODE_F32_NEG),
        TABLE_PUT1(WEB49_OPCODE_F32_CEIL),
        TABLE_PUT1(WEB49_OPCODE_F32_FLOOR),
        TABLE_PUT1(WEB49_OPCODE_F32_TRUNC),
        TABLE_PUT1(WEB49_OPCODE_F32_NEAREST),
        TABLE_PUT1(WEB49_OPCODE_F32_SQRT),
        TABLE_PUT2(WEB49_OPCODE_F32_ADD),
        TABLE_PUT2(WEB49_OPCODE_F32_SUB),
        TABLE_PUT2(WEB49_OPCODE_F32_MUL),
        TABLE_PUT2(WEB49_OPCODE_F32_DIV),
        TABLE_PUT2(WEB49_OPCODE_F32_MIN),
        TABLE_PUT2(WEB49_OPCODE_F32_MAX),
        TABLE_PUT2(WEB49_OPCODE_F32_COPYSIGN),
        TABLE_PUT1(WEB49_OPCODE_F64_ABS),
        TABLE_PUT1(WEB49_OPCODE_F64_NEG),
        TABLE_PUT1(WEB49_OPCODE_F64_CEIL),
        TABLE_PUT1(WEB49_OPCODE_F64_FLOOR),
        TABLE_PUT1(WEB49_OPCODE_F64_TRUNC),
        TABLE_PUT1(WEB49_OPCODE_F64_NEAREST),
        TABLE_PUT1(WEB49_OPCODE_F64_SQRT),
        TABLE_PUT2(WEB49_OPCODE_F64_ADD),
        TABLE_PUT2(WEB49_OPCODE_F64_SUB),
        TABLE_PUT2(WEB49_OPCODE_F64_MUL),
        TABLE_PUT2(WEB49_OPCODE_F64_DIV),
        TABLE_PUT2(WEB49_OPCODE_F64_MIN),
        TABLE_PUT2(WEB49_OPCODE_F64_MAX),
        TABLE_PUT2(WEB49_OPCODE_F64_COPYSIGN),
        TABLE_PUT1(WEB49_OPCODE_I32_WRAP_I64),
        TABLE_PUT1(WEB49_OPCODE_I32_TRUNC_S_F32),
        TABLE_PUT1(WEB49_OPCODE_I32_TRUNC_U_F32),
        TABLE_PUT1(WEB49_OPCODE_I32_TRUNC_S_F64),
        TABLE_PUT1(WEB49_OPCODE_I32_TRUNC_U_F64),
        TABLE_PUT1(WEB49_OPCODE_I64_EXTEND_S_I32),
        TABLE_PUT1(WEB49_OPCODE_I64_EXTEND_U_I32),
        TABLE_PUT1(WEB49_OPCODE_I64_TRUNC_S_F32),
        TABLE_PUT1(WEB49_OPCODE_I64_TRUNC_U_F32),
        TABLE_PUT1(WEB49_OPCODE_I64_TRUNC_S_F64),
        TABLE_PUT1(WEB49_OPCODE_I64_TRUNC_U_F64),
        TABLE_PUT1(WEB49_OPCODE_F32_CONVERT_S_I32),
        TABLE_PUT1(WEB49_OPCODE_F32_CONVERT_U_I32),
        TABLE_PUT1(WEB49_OPCODE_F32_CONVERT_S_I64),
        TABLE_PUT1(WEB49_OPCODE_F32_CONVERT_U_I64),
        TABLE_PUT1(WEB49_OPCODE_F32_DEMOTE_F64),
        TABLE_PUT1(WEB49_OPCODE_F64_CONVERT_S_I32),
        TABLE_PUT1(WEB49_OPCODE_F64_CONVERT_U_I32),
        TABLE_PUT1(WEB49_OPCODE_F64_CONVERT_S_I64),
        TABLE_PUT1(WEB49_OPCODE_F64_CONVERT_U_I64),
        TABLE_PUT1(WEB49_OPCODE_F64_PROMOTE_F32),
        TABLE_PUT1(WEB49_OPCODE_I32_EXTEND8_S),
        TABLE_PUT1(WEB49_OPCODE_I32_EXTEND16_S),
        TABLE_PUT1(WEB49_OPCODE_I64_EXTEND8_S),
        TABLE_PUT1(WEB49_OPCODE_I64_EXTEND16_S),
        TABLE_PUT1(WEB49_OPCODE_I64_EXTEND32_S),
        TABLE_PUT2(WEB49_OPCODE_MEMORY_FILL),
        TABLE_PUT2(WEB49_OPCODE_MEMORY_COPY),
        TABLE_PUT0(WEB49_OPCODE_RETURN0),
        TABLE_PUT1(WEB49_OPCODE_YIELD_PUSH),
        TABLE_PUT0(WEB49_OPCODE_YIELD_POP),
#undef TABLE_PUTV
#undef TABLE_PUT1
#undef TABLE_PUT2
        [WEB49_OPCODE_MEMORY_INIT] = &&DO_WEB49_OPCODE_MEMORY_INIT,
        [WEB49_OPCODE_DATA_DROP] = &&DO_WEB49_OPCODE_DATA_DROP,
        [WEB49_OPCODE_TABLE_INIT] = &&DO_WEB49_OPCODE_TABLE_INIT,
        [WEB49_OPCODE_ELEM_DROP] = &&DO_WEB49_OPCODE_ELEM_DROP,
        [WEB49_OPCODE_TABLE_COPY] = &&DO_WEB49_OPCODE_TABLE_COPY,
        [WEB49_OPCODE_FFI_CALL] = &&DO_WEB49_OPCODE_FFI_CALL,
    };
    web49_interp_block_run_comp(block, ptrs, interp);
    web49_interp_data_t **restrict stacks = interp.stacks;
    web49_interp_opcode_t **restrict returns = interp.returns;
    web49_interp_opcode_t r0[] = {
        &&exitv,
        &&exitv,
    };
    *returns++ = r0;
    *stacks++ = &interp.locals[0];
    web49_interp_data_t *yield_ptr = interp.yield_base;
    web49_interp_opcode_t *restrict head = block->code;
    web49_interp_data_t *restrict locals = interp.locals;
#if defined(WEB49_PRINT_INSTR)
    size_t depth = 1;
#endif
    NEXT();
exitv:
    *ptr_interp = interp;
    return interp.yield_base;
#if defined(WEB49_OPT_CONST0)
#define LOCAL0 head[0].data
#define NAME(x) LABEL(x##_C0)
#include "interp1.inc"
#undef LOCAL0
#undef NAME
#define LOCAL0 head[0].data
#define LOCAL1 locals[head[1].data.i32_u]
#define NAME(x) LABEL(x##_C0)
#include "interp2.inc"
#undef LOCAL0
#undef LOCAL1
#undef NAME
#endif
#define NAME(x) LABEL(x)
#include "interp0.inc"
#undef NAME
#define LOCAL0 locals[head[0].data.i32_u]
#define NAME(x) LABEL(x##_R)
#include "interp1.inc"
#undef LOCAL0
#undef NAME
#define LOCAL0 locals[head[0].data.i32_u]
#define LOCAL1 head[1].data
#define NAME(x) LABEL(x##_C1)
#include "interp2.inc"
#undef LOCAL0
#undef LOCAL1
#undef NAME
#define LOCAL0 locals[head[0].data.i32_u]
#define LOCAL1 locals[head[1].data.i32_u]
#define NAME(x) LABEL(x##_R)
#include "interp2.inc"
#undef LOCAL0
#undef LOCAL1
#undef NAME
#if defined(WEB49_OPT_CONST0)
#define LOCAL0 head[0].data
#define LOCAL1 head[1].data
#define NAME(x) LABEL(x##_C01)
#include "interp2.inc"
#undef LOCAL0
#undef LOCAL1
#undef NAME
#endif
    LABEL(WEB49_OPCODE_MEMORY_INIT) {
        fprintf(stderr, "memory init? you wish\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_DATA_DROP) {
        NEXT();
    }
    LABEL(WEB49_OPCODE_TABLE_INIT) {
        fprintf(stderr, "table init? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_ELEM_DROP) {
        fprintf(stderr, "elem drop? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_TABLE_COPY) {
        fprintf(stderr, "table copy? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_FFI_CALL) {
        interp.locals = locals;
        web49_env_func_t func = head[0].ptr;
        *yield_ptr++ = func(interp);
        head = *--returns;
        locals = *--stacks;
        NEXT();
    }
}

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
    uint32_t num_funcs = code_section.num_entries + web49_module_num_func_imports(mod);
    uint32_t cur_func = 0;
    web49_interp_data_t *locals = web49_alloc0(sizeof(web49_interp_data_t) * (1 << 16));
    uint64_t memsize = 65536;
    if (memory_section.entries != 0) {
        memsize = 65536 * memory_section.entries[0].initial;
    }
    web49_interp_t interp = (web49_interp_t){
        .locals = locals,
        .memory = web49_alloc0(memsize),
        .table = NULL,
        .funcs = web49_malloc(sizeof(web49_interp_block_t) * num_funcs),
        .globals = web49_alloc0(sizeof(web49_interp_data_t) * (global_section.num_entries)),
        .args = args,
        .locals_base = locals,
        .memsize = memsize,
        .stacks = web49_malloc(sizeof(web49_interp_data_t *) * (1 << 12)),
        .returns = web49_malloc(sizeof(web49_opcode_t *) * (1 << 12)),
        .yield_base = web49_alloc0(sizeof(web49_interp_data_t) * (1 << 12)),
    };
    for (size_t j = 0; j < table_section.num_entries; j++) {
        web49_type_table_t entry = table_section.entries[j];
        if (entry.element_type == WEB49_TYPE_ANYFUNC) {
            interp.table = web49_alloc0(sizeof(web49_interp_block_t *) * entry.limits.initial);
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
    return interp;
}

void web49_free_interp(web49_interp_t interp) {
    web49_free(interp.memory);
    web49_free(interp.funcs);
    web49_free(interp.locals_base);
    web49_free(interp.globals);
    web49_free(interp.stacks);
    web49_free(interp.returns);
    web49_free(interp.yield_base);
}
