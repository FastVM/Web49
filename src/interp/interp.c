#include "interp.h"

#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "../tables.h"

#define OPCODE(n) ({size_t x = (n); if (ptrs[x] == NULL) {__builtin_trap();} ptrs[x]; })

void web49_interp_import(void **ptrs, const char *mod, const char *sym, web49_interp_block_t *block) {
    if (!strcmp(mod, "env")) {
        if (ptrs != NULL) {
            web49_interp_opcode_t *instrs = web49_malloc(sizeof(web49_interp_opcode_t) * 2);
            instrs[0].opcode = OPCODE(WEB49_OPCODE_FFI_CALL);
            instrs[1].ptr = web49_env_func(sym);
            if (instrs[1].ptr == NULL) {
                fprintf(stderr, "not implemented: env.%s\n", sym);
            }
            block->code = instrs;
        } else {
            block->code = NULL;
        }
        // fprintf(stderr, "block->code = %p\n", block->code);
        block->nlocals = 0;
        block->nreturns = 1;
        block->nparams = 0;
        return;
    }
    if (!strcmp(mod, "wasi_snapshot_preview1")) {
        size_t iit;
        uint64_t nargs = UINT64_MAX;
        uint64_t nreturns = UINT64_MAX;
        if (!strcmp(sym, "proc_exit")) {
            iit = WEB49_OPCODE_WASI_PROC_EXIT;
            nargs = 1;
            nreturns = 0;
        } else if (!strcmp(sym, "fd_seek")) {
            iit = WEB49_OPCODE_WASI_FD_SEEK;
            nargs = 4;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_filestat_get")) {
            iit = WEB49_OPCODE_WASI_FD_FILESTAT_GET;
            nargs = 5;
            nreturns = 1;
        } else if (!strcmp(sym, "path_filestat_get")) {
            iit = WEB49_OPCODE_WASI_PATH_FILESTAT_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "args_get")) {
            iit = WEB49_OPCODE_WASI_ARGS_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "args_sizes_get")) {
            iit = WEB49_OPCODE_WASI_ARGS_SIZES_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "clock_res_get")) {
            iit = WEB49_OPCODE_WASI_CLOCK_RES_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "clock_time_get")) {
            iit = WEB49_OPCODE_WASI_CLOCK_TIME_GET;
            nargs = 3;
            nreturns = 1;
        } else if (!strcmp(sym, "environ_get")) {
            iit = WEB49_OPCODE_WASI_ENVIRON_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "environ_sizes_get")) {
            iit = WEB49_OPCODE_WASI_ENVIRON_SIZES_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_advise")) {
            iit = WEB49_OPCODE_WASI_FD_ADVISE;
            nargs = 4;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_allocate")) {
            iit = WEB49_OPCODE_WASI_FD_ALLOCATE;
            nargs = 3;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_close")) {
            iit = WEB49_OPCODE_WASI_FD_CLOSE;
            nargs = 1;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_datasync")) {
            iit = WEB49_OPCODE_WASI_FD_DATASYNC;
            nargs = 1;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_fdstat_get")) {
            iit = WEB49_OPCODE_WASI_FD_FDSTAT_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_fdstat_set_flags")) {
            iit = WEB49_OPCODE_WASI_FD_FDSTAT_SET_FLAGS;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_fdstat_set_rights")) {
            iit = WEB49_OPCODE_WASI_FD_FDSTAT_SET_RIGHTS;
            nargs = 3;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_filestat_set_size")) {
            iit = WEB49_OPCODE_WASI_FD_FILESTAT_SET_SIZE;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_filestat_set_times")) {
            iit = WEB49_OPCODE_WASI_FD_FILESTAT_SET_TIMES;
            nargs = 4;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_pread")) {
            iit = WEB49_OPCODE_WASI_FD_PREAD;
            nargs = 5;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_prestat_get")) {
            iit = WEB49_OPCODE_WASI_FD_PRESTAT_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_prestat_dir_name")) {
            iit = WEB49_OPCODE_WASI_FD_PRESTAT_DIR_NAME;
            nargs = 3;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_pwrite")) {
            iit = WEB49_OPCODE_WASI_FD_PWRITE;
            nargs = 5;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_read")) {
            iit = WEB49_OPCODE_WASI_FD_READ;
            nargs = 4;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_readdir")) {
            iit = WEB49_OPCODE_WASI_FD_READDIR;
            nargs = 5;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_renumber")) {
            iit = WEB49_OPCODE_WASI_FD_RENUMBER;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_sync")) {
            iit = WEB49_OPCODE_WASI_FD_SYNC;
            nargs = 1;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_tell")) {
            iit = WEB49_OPCODE_WASI_FD_TELL;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "fd_write")) {
            iit = WEB49_OPCODE_WASI_FD_WRITE;
            nargs = 4;
            nreturns = 1;
        } else if (!strcmp(sym, "path_create_directory")) {
            iit = WEB49_OPCODE_WASI_PATH_CREATE_DIRECTORY;
            nargs = 3;
            nreturns = 1;
        } else if (!strcmp(sym, "path_filestat_set_times")) {
            iit = WEB49_OPCODE_WASI_PATH_FILESTAT_SET_TIMES;
            nargs = 7;
            nreturns = 1;
        } else if (!strcmp(sym, "path_link")) {
            iit = WEB49_OPCODE_WASI_PATH_LINK;
            nargs = 7;
            nreturns = 1;
        } else if (!strcmp(sym, "path_open")) {
            iit = WEB49_OPCODE_WASI_PATH_OPEN;
            nargs = 9;
            nreturns = 1;
        } else if (!strcmp(sym, "path_readlink")) {
            iit = WEB49_OPCODE_WASI_PATH_READLINK;
            nargs = 6;
            nreturns = 1;
        } else if (!strcmp(sym, "path_remove_directory")) {
            iit = WEB49_OPCODE_WASI_PATH_REMOVE_DIRECTORY;
            nargs = 3;
            nreturns = 1;
        } else if (!strcmp(sym, "path_rename")) {
            iit = WEB49_OPCODE_WASI_PATH_RENAME;
            nargs = 6;
            nreturns = 1;
        } else if (!strcmp(sym, "path_symlink")) {
            iit = WEB49_OPCODE_WASI_PATH_SYMLINK;
            nargs = 6;
            nreturns = 1;
        } else if (!strcmp(sym, "path_unlink_file")) {
            iit = WEB49_OPCODE_WASI_PATH_UNLINK_FILE;
            nargs = 3;
            nreturns = 1;
        } else if (!strcmp(sym, "poll_oneoff")) {
            iit = WEB49_OPCODE_WASI_POLL_ONEOFF;
            nargs = 4;
            nreturns = 1;
        } else if (!strcmp(sym, "proc_raise")) {
            iit = WEB49_OPCODE_WASI_PROC_RAISE;
            nargs = 1;
            nreturns = 1;
        } else if (!strcmp(sym, "random_get")) {
            iit = WEB49_OPCODE_WASI_RANDOM_GET;
            nargs = 2;
            nreturns = 1;
        } else if (!strcmp(sym, "sched_yield")) {
            iit = WEB49_OPCODE_WASI_SCHED_YIELD;
            nargs = 0;
            nreturns = 1;
        } else if (!strcmp(sym, "sock_recv")) {
            iit = WEB49_OPCODE_WASI_SOCK_RECV;
            nargs = 6;
            nreturns = 1;
        } else if (!strcmp(sym, "sock_send")) {
            iit = WEB49_OPCODE_WASI_SOCK_SEND;
            nargs = 5;
            nreturns = 1;
        } else if (!strcmp(sym, "sock_shutdown")) {
            iit = WEB49_OPCODE_WASI_SOCK_SHUTDOWN;
            nargs = 2;
            nreturns = 1;
        } else {
            fprintf(stderr, "unknown wasi import symbol: %s\n", sym);
            exit(1);
        }
        if (ptrs != NULL) {
            web49_interp_opcode_t *instrs = web49_malloc(sizeof(web49_interp_opcode_t));
            instrs[0].opcode = OPCODE(iit);
            block->code = instrs;
        } else {
            block->code = NULL;
        }
        // fprintf(stderr, "block->code = %p\n", block->code);
        block->nlocals = 0;
        block->nreturns = nreturns;
        block->nparams = nargs;
        return;
    }
    fprintf(stderr, "unknown import module: %s\n", mod);
    exit(1);
}

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

uint64_t *web49_interp_link_box(void) {
    return malloc(sizeof(uint64_t));
}

void web49_interp_link_get(web49_read_block_state_t *state, uint64_t out, uint64_t *from) {
    if (state->nlinks + 1 >= state->alloc_links) {
        state->alloc_links = (state->nlinks + 1) * 2;
        state->links = web49_realloc(state->links, sizeof(web49_interp_link_t) * state->alloc_links);
    }
    state->links[state->nlinks++] = (web49_interp_link_t){
        .box = from,
        .out = out,
    };
}

static void debug_print(FILE *out, web49_instr_t instr, size_t depth, size_t maxdepth) {
    fprintf(out, "(%s", web49_opcode_to_name(instr.opcode));
    switch (instr.immediate.id) {
        case WEB49_IMMEDIATE_NONE: {
            break;
        }
        case WEB49_IMMEDIATE_VARUINT1: {
            break;
        }
        case WEB49_IMMEDIATE_VARUINT32: {
            fprintf(out, " %" PRIu32, instr.immediate.varuint32);
            break;
        }
        case WEB49_IMMEDIATE_VARUINT64: {
            fprintf(out, " %" PRIu64, instr.immediate.varuint64);
            break;
        }
        case WEB49_IMMEDIATE_VARINT32: {
            fprintf(out, " %" PRIi32, instr.immediate.varint32);
            break;
        }
        case WEB49_IMMEDIATE_VARINT64: {
            fprintf(out, " %" PRIi64, instr.immediate.varint64);
            break;
        }
        case WEB49_IMMEDIATE_UINT32: {
            fprintf(out, " %" PRIu32, instr.immediate.uint32);
            break;
        }
        case WEB49_IMMEDIATE_UINT64: {
            fprintf(out, " %" PRIu64, instr.immediate.uint64);
            break;
        }
        case WEB49_IMMEDIATE_BR_TABLE: {
            break;
        }
        case WEB49_IMMEDIATE_CALL_INDIRECT: {
            break;
        }
        case WEB49_IMMEDIATE_MEMORY_IMMEDIATE: {
            fprintf(out, " offset=%" PRIu64, instr.immediate.memory_immediate.offset);
            break;
        }
        case WEB49_IMMEDIATE_DATA_INDEX: {
            break;
        }
    }
    for (uint64_t i = 0; i < instr.nargs; i++) {
        fprintf(out, "\n");
        for (size_t j = 0; j < depth + 1; j++) {
            fprintf(out, "  ");
        }
        if (depth >= maxdepth) {
            fprintf(out, "...");
        } else {
            debug_print(out, instr.args[i], depth + 1, maxdepth);
        }
    }
    fprintf(out, ")");
    if (depth == 0) {
        fprintf(out, "\n");
    }
}

uint32_t web49_interp_read_instr(web49_read_block_state_t *state, web49_instr_t cur, uint32_t local) {
    web49_interp_build_t *build = &state->build;
    void **ptrs = state->ptrs;
    if (build->ncode + 16 >= build->alloc) {
        fprintf(stderr, "error: outran preallocated code memory\n");
        __builtin_trap();
    }
    if (cur.opcode == WEB49_OPCODE_BLOCK) {
        uint64_t *box = web49_interp_link_box();
        uint32_t save = state->depth;
        *++state->bufs = box;
        for (size_t i = 0; i < cur.nargs; i++) {
            web49_interp_read_instr(state, cur.args[i], UINT32_MAX);
        }
        state->bufs--;
        state->depth = save;
        *box = build->ncode;
        if (cur.immediate.block_type != WEB49_TYPE_BLOCK_TYPE) {
            uint32_t ret = state->depth + state->nlocals;
            state->depth += 1;
            return ret;
        } else {
            return UINT32_MAX;
        }
    }
    if (cur.opcode == WEB49_OPCODE_LOOP) {
        uint64_t *box = web49_interp_link_box();
        *box = build->ncode;
        uint32_t save = state->depth;
        *++state->bufs = box;
        for (size_t i = 0; i < cur.nargs; i++) {
            web49_interp_read_instr(state, cur.args[i], UINT32_MAX);
        }
        state->bufs--;
        state->depth = save;
        if (cur.immediate.block_type != WEB49_TYPE_BLOCK_TYPE) {
            uint32_t ret = state->depth + state->nlocals;
            state->depth += 1;
            return ret;
        } else {
            return UINT32_MAX;
        }
    }
    if (cur.opcode == WEB49_OPCODE_IF) {
        if (cur.nargs == 3) {
            uint64_t *ift = web49_interp_link_box();
            uint64_t *iff = web49_interp_link_box();
            uint64_t *end = web49_interp_link_box();
            uint32_t cpos = web49_interp_read_instr(state, cur.args[0], UINT32_MAX);
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_IF);
            build->code[build->ncode++].data.i32_u = cpos;
            web49_interp_link_get(state, build->ncode++, ift);
            web49_interp_link_get(state, build->ncode++, iff);
            state->depth -= 1;
            uint32_t save = state->depth;
            *++state->bufs = end;
            *ift = build->ncode;
            for (size_t i = 0; i < cur.args[1].nargs; i++) {
                web49_interp_read_instr(state, cur.args[1].args[i], UINT32_MAX);
            }
            state->depth = save;
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_BR);
            web49_interp_link_get(state, build->ncode++, end);
            // build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_UNREACHABLE);
            *iff = build->ncode;
            for (size_t i = 0; i < cur.args[2].nargs; i++) {
                web49_interp_read_instr(state, cur.args[2].args[i], UINT32_MAX);
            }
            state->bufs--;
            *end = build->ncode;
            state->depth = save;
        } else {
            uint64_t *then = web49_interp_link_box();
            uint64_t *end = web49_interp_link_box();
            uint32_t cpos = web49_interp_read_instr(state, cur.args[0], UINT32_MAX);
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_IF);
            build->code[build->ncode++].data.i32_u = cpos;
            web49_interp_link_get(state, build->ncode++, then);
            web49_interp_link_get(state, build->ncode++, end);
            state->depth -= 1;
            uint32_t save = state->depth;
            *++state->bufs = end;
            *then = build->ncode;
            for (size_t i = 0; i < cur.args[1].nargs; i++) {
                web49_interp_read_instr(state, cur.args[1].args[i], UINT32_MAX);
            }
            state->bufs--;
            *end = build->ncode;
            state->depth = save;
        }
        if (cur.immediate.block_type != WEB49_TYPE_BLOCK_TYPE) {
            uint32_t ret = state->depth + state->nlocals;
            state->depth += 1;
            return ret;
        } else {
            return UINT32_MAX;
        }
    }
    if (cur.opcode == WEB49_OPCODE_F64_REINTERPRET_I64 || cur.opcode == WEB49_OPCODE_I64_REINTERPRET_F64 || cur.opcode == WEB49_OPCODE_F32_REINTERPRET_I32 || cur.opcode == WEB49_OPCODE_I32_REINTERPRET_F32) {
        return web49_interp_read_instr(state, cur.args[0], local);
    }
    if (cur.opcode == WEB49_OPCODE_BEGIN0) {
        uint32_t ret = UINT32_MAX;
        for (uint64_t i = 0; i < cur.nargs; i++) {
            uint32_t tmp = web49_interp_read_instr(state, cur.args[i], local);
            if (tmp != UINT32_MAX) {
                local = UINT32_MAX;
                ret = tmp;
            }
        }
        return ret;
    }
#if !defined(WEB49_NO_OPT)
    if (cur.opcode == WEB49_OPCODE_SET_LOCAL && cur.args[0].opcode != WEB49_OPCODE_BEGIN0 && cur.args[0].opcode != WEB49_OPCODE_BLOCK && cur.args[0].opcode != WEB49_OPCODE_LOOP && cur.args[0].opcode != WEB49_OPCODE_IF) {
        uint32_t ret = web49_interp_read_instr(state, cur.args[0], cur.immediate.varuint32);
        if (state->depth < 1) {
            return UINT32_MAX;
            // __builtin_trap();
        }
        state->depth -= 1;
        if (ret != cur.immediate.varuint32) {
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_GET_LOCAL);
            build->code[build->ncode++].data.i32_u = ret;
            build->code[build->ncode++].data.i32_u = cur.immediate.varuint32;
        }
        return UINT32_MAX;
    }
#endif
    bool const0 = false;
    bool const1 = false;
    uint16_t add = 0;
    uint32_t args[64];
    for (uint64_t i = 0; i < cur.nargs; i++) {
#if !defined(WEB49_NO_OPT)
        if (cur.opcode != WEB49_OPCODE_CALL && cur.opcode != WEB49_OPCODE_CALL_INDIRECT && cur.opcode != WEB49_OPCODE_BR_IF) {
            if (cur.args[i].opcode == WEB49_OPCODE_I32_CONST || cur.args[i].opcode == WEB49_OPCODE_I64_CONST || cur.args[i].opcode == WEB49_OPCODE_F32_CONST || cur.args[i].opcode == WEB49_OPCODE_F64_CONST) {
                if (i == 0) {
                    state->depth += 1;
                    const0 = true;
                    add += WEB49_OPCODE_WITH_CONST0;
                    continue;
                }
                if (i == 1) {
                    state->depth += 1;
                    const1 = true;
                    add += WEB49_OPCODE_WITH_CONST1;
                    continue;
                }
            }
            if (cur.args[i].opcode == WEB49_OPCODE_GET_LOCAL) {
                for (uint64_t j = i + 1; j < cur.nargs; j++) {
                    if (cur.args[j].opcode == WEB49_OPCODE_BEGIN0 || cur.args[j].opcode == WEB49_OPCODE_TEE_LOCAL) {
                        goto next;
                    }
                }
                state->depth += 1;
                args[i] = cur.args[i].immediate.varint32;
                continue;
            }
        next:;
        }
#endif
        args[i] = web49_interp_read_instr(state, cur.args[i], UINT32_MAX);
        // fprintf(stderr, "%s.args[%zu] = stack[%zu](r%zu)\n", web49_opcode_to_name(cur.opcode), (size_t) i, (size_t) args[i] - state->nlocals, (size_t) args[i]);
    }
    if (cur.opcode == WEB49_OPCODE_RETURN && state->depth == 0) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN + WEB49_OPCODE_WITH_CONST0);
        build->code[build->ncode++].data.i64_u = 0;
        return UINT32_MAX;
    }
    if (state->depth < cur.nargs) {
        __builtin_trap();
    }
    state->depth -= cur.nargs;
    if (cur.opcode == WEB49_OPCODE_NOP || cur.opcode == WEB49_OPCODE_UNREACHABLE) {
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_DROP) {
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_CALL_INDIRECT) {
        web49_section_type_entry_t ent = state->interp->extra->type_section.entries[cur.immediate.call_indirect.index];
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL_INDIRECT);
        build->code[build->ncode++].data.i32_u = args[cur.nargs - 1];
        build->code[build->ncode++].data.i32_u = state->depth + state->nlocals;
        if (ent.num_returns == 1) {
            if (local == UINT32_MAX) {
                uint32_t out = state->depth + state->nlocals;
                // fprintf(stderr, "DYNCALL -> %zu\n", (size_t) out);
                build->code[build->ncode++].data.i32_u = out;
                state->depth += 1;
                return out;
            } else {
                // fprintf(stderr, "DYNCALL -> locals[%zu]\n", (size_t) local);
                build->code[build->ncode++].data.i32_u = local;
                state->depth += 1;
                return local;
            }
        } else {
            // fprintf(stderr, "DYNCALL -> (none %zu)\n", (size_t) (state->nlocals + 256));
            build->code[build->ncode++].data.i32_u = state->nlocals + 256;
            return UINT32_MAX;
        }
    }
    if (cur.opcode == WEB49_OPCODE_CALL) {
        switch (state->interp->extra->funcs[cur.immediate.varint32].nreturns) {
            case 0:
                build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL0);
                build->code[build->ncode++].ptr = &state->interp->extra->funcs[cur.immediate.varint32];
                build->code[build->ncode++].data.i32_u = state->depth + state->nlocals;
                // fprintf(stderr, "CALL0 %zu -> (none)\n", (size_t) cur.immediate.varint32);
                return UINT32_MAX;
            case 1:
                build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL1);
                build->code[build->ncode++].ptr = &state->interp->extra->funcs[cur.immediate.varint32];
                build->code[build->ncode++].data.i32_u = state->depth + state->nlocals;
                if (local == UINT32_MAX) {
                    uint32_t out = state->depth + state->nlocals;
                    // fprintf(stderr, "CALL1 %zu -> %zu\n", (size_t) cur.immediate.varint32, (size_t) out);
                    build->code[build->ncode++].data.i32_u = out;
                    state->depth += 1;
                    return out;
                } else {
                    // fprintf(stderr, "CALL1 %zu -> locals[%zu]\n", (size_t) cur.immediate.varint32, (size_t) local);
                    build->code[build->ncode++].data.i32_u = local;
                    state->depth += 1;
                    return local;
                }
                break;
            default:
                fprintf(stderr, "cannot compile multiple returns yet\n");
                __builtin_trap();
        }
    }
    if (cur.opcode == WEB49_OPCODE_BR) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_BR);
        web49_interp_link_get(state, build->ncode++, state->bufs[-(ptrdiff_t)cur.immediate.varuint32]);
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_BR_IF) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_BR_IF);
        build->code[build->ncode++].data.i32_u = args[0];
        web49_interp_link_get(state, build->ncode++, state->bufs[-(ptrdiff_t)cur.immediate.varuint32]);
        return UINT32_MAX;
    }
    if (cur.opcode == WEB49_OPCODE_RETURN) {
        if (cur.nargs == 0) {
            __builtin_trap();
        } else if (const0) {
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN + WEB49_OPCODE_WITH_CONST0);
            build->code[build->ncode++].data.i64_u = cur.args[0].immediate.uint64;
            return UINT32_MAX;
        } else if (args[0] == UINT32_MAX) {
            debug_print(stderr, cur, 0, SIZE_MAX);
            __builtin_trap();
            // build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN + WEB49_OPCODE_WITH_CONST0);
            // build->code[build->ncode++].data.i64_u = 0;
            // return UINT32_MAX;
        } else {
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN);
            build->code[build->ncode++].data.i32_u = args[0];
            return UINT32_MAX;
        }
    }
    build->code[build->ncode++].opcode = OPCODE(cur.opcode + add);
    for (uint64_t i = 0; i < cur.nargs; i++) {
        if (i == 0 && const0) {
            build->code[build->ncode++].data.i64_u = cur.args[0].immediate.uint64;
            continue;
        }
        if (i == 1 && const1) {
            build->code[build->ncode++].data.i64_u = cur.args[1].immediate.uint64;
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
                web49_interp_link_get(state, build->ncode++, state->bufs[-(ptrdiff_t)cur.immediate.br_table.targets[i]]);
            }
            web49_interp_link_get(state, build->ncode++, state->bufs[-(ptrdiff_t)cur.immediate.br_table.default_target]);
            break;
        case WEB49_IMMEDIATE_CALL_INDIRECT:
            break;
        case WEB49_IMMEDIATE_MEMORY_IMMEDIATE:
            build->code[build->ncode++].data.i32_u = cur.immediate.memory_immediate.offset;
            break;
        default:
            fprintf(stderr, "bad immediate: %zu\n", (size_t)cur.immediate.id);
            __builtin_trap();
    }
    return ret;
}

#if defined(WEB49_PRINT_INSTR)
#define DPRINT(name) fprintf(stderr, name "\n")
#else
#define DPRINT(name)
#endif

#if 1
#define LABEL(name)   \
    __builtin_trap(); \
    DO_##name:;       \
    DPRINT(#name);    \
    head += 1;
#define NEXT() goto * head->opcode
#else
#define LABEL(name)   \
    __builtin_trap(); \
    DO_##name:;       \
    DPRINT(#name);
#define NEXT() goto *head++->opcode
#endif

web49_interp_data_t web49_interp_block_run(web49_interp_t interp, web49_interp_block_t *block) {
    static void *ptrs[WEB49_MAX_OPCODE_INTERP_NUM] = {
#define TABLE_PUT1(n, v) [n] = &&DO_##v
#define TABLE_PUT(x) TABLE_PUT1(x, x##_RR), TABLE_PUT1(x + WEB49_OPCODE_WITH_CONST0, x##_CR), TABLE_PUT1(x + WEB49_OPCODE_WITH_CONST1, x##_RC), TABLE_PUT1(x + WEB49_OPCODE_WITH_CONST01, x##_CC)
        TABLE_PUT(WEB49_OPCODE_IF),
        TABLE_PUT(WEB49_OPCODE_BR),
        TABLE_PUT(WEB49_OPCODE_BR_IF),
        TABLE_PUT(WEB49_OPCODE_BR_TABLE),
        TABLE_PUT(WEB49_OPCODE_RETURN),
        TABLE_PUT(WEB49_OPCODE_CALL0),
        TABLE_PUT(WEB49_OPCODE_CALL1),
        TABLE_PUT(WEB49_OPCODE_CALL_INDIRECT),
        TABLE_PUT(WEB49_OPCODE_SELECT),
        TABLE_PUT(WEB49_OPCODE_GET_LOCAL),
        TABLE_PUT(WEB49_OPCODE_SET_LOCAL),
        TABLE_PUT(WEB49_OPCODE_TEE_LOCAL),
        TABLE_PUT(WEB49_OPCODE_GET_GLOBAL),
        TABLE_PUT(WEB49_OPCODE_SET_GLOBAL),
        TABLE_PUT(WEB49_OPCODE_I32_LOAD),
        TABLE_PUT(WEB49_OPCODE_I64_LOAD),
        TABLE_PUT(WEB49_OPCODE_F32_LOAD),
        TABLE_PUT(WEB49_OPCODE_F64_LOAD),
        TABLE_PUT(WEB49_OPCODE_I32_LOAD8_S),
        TABLE_PUT(WEB49_OPCODE_I32_LOAD8_U),
        TABLE_PUT(WEB49_OPCODE_I32_LOAD16_S),
        TABLE_PUT(WEB49_OPCODE_I32_LOAD16_U),
        TABLE_PUT(WEB49_OPCODE_I64_LOAD8_S),
        TABLE_PUT(WEB49_OPCODE_I64_LOAD8_U),
        TABLE_PUT(WEB49_OPCODE_I64_LOAD16_S),
        TABLE_PUT(WEB49_OPCODE_I64_LOAD16_U),
        TABLE_PUT(WEB49_OPCODE_I64_LOAD32_S),
        TABLE_PUT(WEB49_OPCODE_I64_LOAD32_U),
        TABLE_PUT(WEB49_OPCODE_I32_STORE),
        TABLE_PUT(WEB49_OPCODE_I64_STORE),
        TABLE_PUT(WEB49_OPCODE_F32_STORE),
        TABLE_PUT(WEB49_OPCODE_F64_STORE),
        TABLE_PUT(WEB49_OPCODE_I32_STORE8),
        TABLE_PUT(WEB49_OPCODE_I32_STORE16),
        TABLE_PUT(WEB49_OPCODE_I64_STORE8),
        TABLE_PUT(WEB49_OPCODE_I64_STORE16),
        TABLE_PUT(WEB49_OPCODE_I64_STORE32),
        TABLE_PUT(WEB49_OPCODE_MEMORY_SIZE),
        TABLE_PUT(WEB49_OPCODE_MEMORY_GROW),
        TABLE_PUT(WEB49_OPCODE_I32_CONST),
        TABLE_PUT(WEB49_OPCODE_I64_CONST),
        TABLE_PUT(WEB49_OPCODE_F32_CONST),
        TABLE_PUT(WEB49_OPCODE_F64_CONST),
        TABLE_PUT(WEB49_OPCODE_I32_EQZ),
        TABLE_PUT(WEB49_OPCODE_I32_EQ),
        TABLE_PUT(WEB49_OPCODE_I32_NE),
        TABLE_PUT(WEB49_OPCODE_I32_LT_S),
        TABLE_PUT(WEB49_OPCODE_I32_LT_U),
        TABLE_PUT(WEB49_OPCODE_I32_GT_S),
        TABLE_PUT(WEB49_OPCODE_I32_GT_U),
        TABLE_PUT(WEB49_OPCODE_I32_LE_S),
        TABLE_PUT(WEB49_OPCODE_I32_LE_U),
        TABLE_PUT(WEB49_OPCODE_I32_GE_S),
        TABLE_PUT(WEB49_OPCODE_I32_GE_U),
        TABLE_PUT(WEB49_OPCODE_I64_EQZ),
        TABLE_PUT(WEB49_OPCODE_I64_EQ),
        TABLE_PUT(WEB49_OPCODE_I64_NE),
        TABLE_PUT(WEB49_OPCODE_I64_LT_S),
        TABLE_PUT(WEB49_OPCODE_I64_LT_U),
        TABLE_PUT(WEB49_OPCODE_I64_GT_S),
        TABLE_PUT(WEB49_OPCODE_I64_GT_U),
        TABLE_PUT(WEB49_OPCODE_I64_LE_S),
        TABLE_PUT(WEB49_OPCODE_I64_LE_U),
        TABLE_PUT(WEB49_OPCODE_I64_GE_S),
        TABLE_PUT(WEB49_OPCODE_I64_GE_U),
        TABLE_PUT(WEB49_OPCODE_F32_EQ),
        TABLE_PUT(WEB49_OPCODE_F32_NE),
        TABLE_PUT(WEB49_OPCODE_F32_LT),
        TABLE_PUT(WEB49_OPCODE_F32_GT),
        TABLE_PUT(WEB49_OPCODE_F32_LE),
        TABLE_PUT(WEB49_OPCODE_F32_GE),
        TABLE_PUT(WEB49_OPCODE_F64_EQ),
        TABLE_PUT(WEB49_OPCODE_F64_NE),
        TABLE_PUT(WEB49_OPCODE_F64_LT),
        TABLE_PUT(WEB49_OPCODE_F64_GT),
        TABLE_PUT(WEB49_OPCODE_F64_LE),
        TABLE_PUT(WEB49_OPCODE_F64_GE),
        TABLE_PUT(WEB49_OPCODE_I32_CLZ),
        TABLE_PUT(WEB49_OPCODE_I32_CTZ),
        TABLE_PUT(WEB49_OPCODE_I32_POPCNT),
        TABLE_PUT(WEB49_OPCODE_I32_ADD),
        TABLE_PUT(WEB49_OPCODE_I32_SUB),
        TABLE_PUT(WEB49_OPCODE_I32_MUL),
        TABLE_PUT(WEB49_OPCODE_I32_DIV_S),
        TABLE_PUT(WEB49_OPCODE_I32_DIV_U),
        TABLE_PUT(WEB49_OPCODE_I32_REM_S),
        TABLE_PUT(WEB49_OPCODE_I32_REM_U),
        TABLE_PUT(WEB49_OPCODE_I32_AND),
        TABLE_PUT(WEB49_OPCODE_I32_OR),
        TABLE_PUT(WEB49_OPCODE_I32_XOR),
        TABLE_PUT(WEB49_OPCODE_I32_SHL),
        TABLE_PUT(WEB49_OPCODE_I32_SHR_S),
        TABLE_PUT(WEB49_OPCODE_I32_SHR_U),
        TABLE_PUT(WEB49_OPCODE_I32_ROTL),
        TABLE_PUT(WEB49_OPCODE_I32_ROTR),
        TABLE_PUT(WEB49_OPCODE_I64_CLZ),
        TABLE_PUT(WEB49_OPCODE_I64_CTZ),
        TABLE_PUT(WEB49_OPCODE_I64_POPCNT),
        TABLE_PUT(WEB49_OPCODE_I64_ADD),
        TABLE_PUT(WEB49_OPCODE_I64_SUB),
        TABLE_PUT(WEB49_OPCODE_I64_MUL),
        TABLE_PUT(WEB49_OPCODE_I64_DIV_S),
        TABLE_PUT(WEB49_OPCODE_I64_DIV_U),
        TABLE_PUT(WEB49_OPCODE_I64_REM_S),
        TABLE_PUT(WEB49_OPCODE_I64_REM_U),
        TABLE_PUT(WEB49_OPCODE_I64_AND),
        TABLE_PUT(WEB49_OPCODE_I64_OR),
        TABLE_PUT(WEB49_OPCODE_I64_XOR),
        TABLE_PUT(WEB49_OPCODE_I64_SHL),
        TABLE_PUT(WEB49_OPCODE_I64_SHR_S),
        TABLE_PUT(WEB49_OPCODE_I64_SHR_U),
        TABLE_PUT(WEB49_OPCODE_I64_ROTL),
        TABLE_PUT(WEB49_OPCODE_I64_ROTR),
        TABLE_PUT(WEB49_OPCODE_F32_ABS),
        TABLE_PUT(WEB49_OPCODE_F32_NEG),
        TABLE_PUT(WEB49_OPCODE_F32_CEIL),
        TABLE_PUT(WEB49_OPCODE_F32_FLOOR),
        TABLE_PUT(WEB49_OPCODE_F32_TRUNC),
        TABLE_PUT(WEB49_OPCODE_F32_NEAREST),
        TABLE_PUT(WEB49_OPCODE_F32_SQRT),
        TABLE_PUT(WEB49_OPCODE_F32_ADD),
        TABLE_PUT(WEB49_OPCODE_F32_SUB),
        TABLE_PUT(WEB49_OPCODE_F32_MUL),
        TABLE_PUT(WEB49_OPCODE_F32_DIV),
        TABLE_PUT(WEB49_OPCODE_F32_MIN),
        TABLE_PUT(WEB49_OPCODE_F32_MAX),
        TABLE_PUT(WEB49_OPCODE_F32_COPYSIGN),
        TABLE_PUT(WEB49_OPCODE_F64_ABS),
        TABLE_PUT(WEB49_OPCODE_F64_NEG),
        TABLE_PUT(WEB49_OPCODE_F64_CEIL),
        TABLE_PUT(WEB49_OPCODE_F64_FLOOR),
        TABLE_PUT(WEB49_OPCODE_F64_TRUNC),
        TABLE_PUT(WEB49_OPCODE_F64_NEAREST),
        TABLE_PUT(WEB49_OPCODE_F64_SQRT),
        TABLE_PUT(WEB49_OPCODE_F64_ADD),
        TABLE_PUT(WEB49_OPCODE_F64_SUB),
        TABLE_PUT(WEB49_OPCODE_F64_MUL),
        TABLE_PUT(WEB49_OPCODE_F64_DIV),
        TABLE_PUT(WEB49_OPCODE_F64_MIN),
        TABLE_PUT(WEB49_OPCODE_F64_MAX),
        TABLE_PUT(WEB49_OPCODE_F64_COPYSIGN),
        TABLE_PUT(WEB49_OPCODE_I32_WRAP_I64),
        TABLE_PUT(WEB49_OPCODE_I32_TRUNC_S_F32),
        TABLE_PUT(WEB49_OPCODE_I32_TRUNC_U_F32),
        TABLE_PUT(WEB49_OPCODE_I32_TRUNC_S_F64),
        TABLE_PUT(WEB49_OPCODE_I32_TRUNC_U_F64),
        TABLE_PUT(WEB49_OPCODE_I64_EXTEND_S_I32),
        TABLE_PUT(WEB49_OPCODE_I64_EXTEND_U_I32),
        TABLE_PUT(WEB49_OPCODE_I64_TRUNC_S_F32),
        TABLE_PUT(WEB49_OPCODE_I64_TRUNC_U_F32),
        TABLE_PUT(WEB49_OPCODE_I64_TRUNC_S_F64),
        TABLE_PUT(WEB49_OPCODE_I64_TRUNC_U_F64),
        TABLE_PUT(WEB49_OPCODE_F32_CONVERT_S_I32),
        TABLE_PUT(WEB49_OPCODE_F32_CONVERT_U_I32),
        TABLE_PUT(WEB49_OPCODE_F32_CONVERT_S_I64),
        TABLE_PUT(WEB49_OPCODE_F32_CONVERT_U_I64),
        TABLE_PUT(WEB49_OPCODE_F32_DEMOTE_F64),
        TABLE_PUT(WEB49_OPCODE_F64_CONVERT_S_I32),
        TABLE_PUT(WEB49_OPCODE_F64_CONVERT_U_I32),
        TABLE_PUT(WEB49_OPCODE_F64_CONVERT_S_I64),
        TABLE_PUT(WEB49_OPCODE_F64_CONVERT_U_I64),
        TABLE_PUT(WEB49_OPCODE_F64_PROMOTE_F32),
#undef TABLE_PUT1
#undef TABLE_PUT
        [WEB49_OPCODE_MEMORY_INIT] = &&DO_WEB49_OPCODE_MEMORY_INIT,
        [WEB49_OPCODE_MEMORY_COPY] = &&DO_WEB49_OPCODE_MEMORY_COPY,
        [WEB49_OPCODE_MEMORY_FILL] = &&DO_WEB49_OPCODE_MEMORY_FILL,
        [WEB49_OPCODE_DATA_DROP] = &&DO_WEB49_OPCODE_DATA_DROP,
        [WEB49_OPCODE_TABLE_INIT] = &&DO_WEB49_OPCODE_TABLE_INIT,
        [WEB49_OPCODE_ELEM_DROP] = &&DO_WEB49_OPCODE_ELEM_DROP,
        [WEB49_OPCODE_TABLE_COPY] = &&DO_WEB49_OPCODE_TABLE_COPY,
        [WEB49_OPCODE_FFI_CALL] = &&DO_WEB49_OPCODE_FFI_CALL,
        [WEB49_OPCODE_WASI_FD_SEEK] = &&DO_WEB49_OPCODE_WASI_FD_SEEK,
        [WEB49_OPCODE_WASI_FD_FILESTAT_GET] = &&DO_WEB49_OPCODE_WASI_FD_FILESTAT_GET,
        [WEB49_OPCODE_WASI_PATH_FILESTAT_GET] = &&DO_WEB49_OPCODE_WASI_PATH_FILESTAT_GET,
        [WEB49_OPCODE_WASI_ARGS_GET] = &&DO_WEB49_OPCODE_WASI_ARGS_GET,
        [WEB49_OPCODE_WASI_ARGS_SIZES_GET] = &&DO_WEB49_OPCODE_WASI_ARGS_SIZES_GET,
        [WEB49_OPCODE_WASI_CLOCK_RES_GET] = &&DO_WEB49_OPCODE_WASI_CLOCK_RES_GET,
        [WEB49_OPCODE_WASI_CLOCK_TIME_GET] = &&DO_WEB49_OPCODE_WASI_CLOCK_TIME_GET,
        [WEB49_OPCODE_WASI_ENVIRON_GET] = &&DO_WEB49_OPCODE_WASI_ENVIRON_GET,
        [WEB49_OPCODE_WASI_ENVIRON_SIZES_GET] = &&DO_WEB49_OPCODE_WASI_ENVIRON_SIZES_GET,
        [WEB49_OPCODE_WASI_FD_ADVISE] = &&DO_WEB49_OPCODE_WASI_FD_ADVISE,
        [WEB49_OPCODE_WASI_FD_ALLOCATE] = &&DO_WEB49_OPCODE_WASI_FD_ALLOCATE,
        [WEB49_OPCODE_WASI_FD_CLOSE] = &&DO_WEB49_OPCODE_WASI_FD_CLOSE,
        [WEB49_OPCODE_WASI_FD_DATASYNC] = &&DO_WEB49_OPCODE_WASI_FD_DATASYNC,
        [WEB49_OPCODE_WASI_FD_FDSTAT_GET] = &&DO_WEB49_OPCODE_WASI_FD_FDSTAT_GET,
        [WEB49_OPCODE_WASI_FD_FDSTAT_SET_FLAGS] = &&DO_WEB49_OPCODE_WASI_FD_FDSTAT_SET_FLAGS,
        [WEB49_OPCODE_WASI_FD_FDSTAT_SET_RIGHTS] = &&DO_WEB49_OPCODE_WASI_FD_FDSTAT_SET_RIGHTS,
        [WEB49_OPCODE_WASI_FD_FILESTAT_SET_SIZE] = &&DO_WEB49_OPCODE_WASI_FD_FILESTAT_SET_SIZE,
        [WEB49_OPCODE_WASI_FD_FILESTAT_SET_TIMES] = &&DO_WEB49_OPCODE_WASI_FD_FILESTAT_SET_TIMES,
        [WEB49_OPCODE_WASI_FD_PREAD] = &&DO_WEB49_OPCODE_WASI_FD_PREAD,
        [WEB49_OPCODE_WASI_FD_PRESTAT_GET] = &&DO_WEB49_OPCODE_WASI_FD_PRESTAT_GET,
        [WEB49_OPCODE_WASI_FD_PRESTAT_DIR_NAME] = &&DO_WEB49_OPCODE_WASI_FD_PRESTAT_DIR_NAME,
        [WEB49_OPCODE_WASI_FD_PWRITE] = &&DO_WEB49_OPCODE_WASI_FD_PWRITE,
        [WEB49_OPCODE_WASI_FD_READ] = &&DO_WEB49_OPCODE_WASI_FD_READ,
        [WEB49_OPCODE_WASI_FD_READDIR] = &&DO_WEB49_OPCODE_WASI_FD_READDIR,
        [WEB49_OPCODE_WASI_FD_RENUMBER] = &&DO_WEB49_OPCODE_WASI_FD_RENUMBER,
        [WEB49_OPCODE_WASI_FD_SYNC] = &&DO_WEB49_OPCODE_WASI_FD_SYNC,
        [WEB49_OPCODE_WASI_FD_TELL] = &&DO_WEB49_OPCODE_WASI_FD_TELL,
        [WEB49_OPCODE_WASI_FD_WRITE] = &&DO_WEB49_OPCODE_WASI_FD_WRITE,
        [WEB49_OPCODE_WASI_PATH_CREATE_DIRECTORY] = &&DO_WEB49_OPCODE_WASI_PATH_CREATE_DIRECTORY,
        [WEB49_OPCODE_WASI_PATH_FILESTAT_SET_TIMES] = &&DO_WEB49_OPCODE_WASI_PATH_FILESTAT_SET_TIMES,
        [WEB49_OPCODE_WASI_PATH_LINK] = &&DO_WEB49_OPCODE_WASI_PATH_LINK,
        [WEB49_OPCODE_WASI_PATH_OPEN] = &&DO_WEB49_OPCODE_WASI_PATH_OPEN,
        [WEB49_OPCODE_WASI_PATH_READLINK] = &&DO_WEB49_OPCODE_WASI_PATH_READLINK,
        [WEB49_OPCODE_WASI_PATH_REMOVE_DIRECTORY] = &&DO_WEB49_OPCODE_WASI_PATH_REMOVE_DIRECTORY,
        [WEB49_OPCODE_WASI_PATH_RENAME] = &&DO_WEB49_OPCODE_WASI_PATH_RENAME,
        [WEB49_OPCODE_WASI_PATH_SYMLINK] = &&DO_WEB49_OPCODE_WASI_PATH_SYMLINK,
        [WEB49_OPCODE_WASI_PATH_UNLINK_FILE] = &&DO_WEB49_OPCODE_WASI_PATH_UNLINK_FILE,
        [WEB49_OPCODE_WASI_POLL_ONEOFF] = &&DO_WEB49_OPCODE_WASI_POLL_ONEOFF,
        [WEB49_OPCODE_WASI_PROC_EXIT] = &&DO_WEB49_OPCODE_WASI_PROC_EXIT,
        [WEB49_OPCODE_WASI_PROC_RAISE] = &&DO_WEB49_OPCODE_WASI_PROC_RAISE,
        [WEB49_OPCODE_WASI_RANDOM_GET] = &&DO_WEB49_OPCODE_WASI_RANDOM_GET,
        [WEB49_OPCODE_WASI_SCHED_YIELD] = &&DO_WEB49_OPCODE_WASI_SCHED_YIELD,
        [WEB49_OPCODE_WASI_SOCK_RECV] = &&DO_WEB49_OPCODE_WASI_SOCK_RECV,
        [WEB49_OPCODE_WASI_SOCK_SEND] = &&DO_WEB49_OPCODE_WASI_SOCK_SEND,
        [WEB49_OPCODE_WASI_SOCK_SHUTDOWN] = &&DO_WEB49_OPCODE_WASI_SOCK_SHUTDOWN,
    };
    // fprintf(stderr, "%p\n", block->code);
    if (block->code == NULL) {
        if (block->is_code) {
            web49_section_code_entry_t *entry = block->code_entry;
            // for (uint64_t i = 0; i < entry->num_instrs; i++) {
            //     entry->instrs[i] = web49_interp_opt(entry->instrs[i]);
            // }
            web49_read_block_state_t state;
            state.ptrs = ptrs;
            uint64_t **data = web49_malloc(sizeof(uint64_t *) * (128));
            state.bufs = &data[1];
            state.interp = &interp;
            state.build.alloc = 16;
            for (uint64_t i = 0; i < entry->num_instrs; i++) {
                state.build.alloc += web49_interp_count(entry->instrs[i]);
            }
            state.build.code = web49_malloc(sizeof(web49_interp_opcode_t) * state.build.alloc);
            state.build.ncode = 0;
            state.alloc_links = 0;
            state.nlinks = 0;
            state.links = NULL;
            state.depth = 0;
            state.nlocals = block->nparams + block->nlocals;
            uint32_t ret = UINT32_MAX;
            for (uint64_t i = 0; i < entry->num_instrs; i++) {
                // debug_print(stderr, entry->instrs[i], 0, SIZE_MAX);
            }
            for (uint64_t i = 0; i < entry->num_instrs; i++) {
                uint32_t tmp = web49_interp_read_instr(&state, entry->instrs[i], UINT32_MAX);
                if (tmp != UINT32_MAX) {
                    ret = tmp;
                } else {
                    // ret = tmp;
                }
            }
            if (ret == UINT32_MAX) {
                state.build.code[state.build.ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN + WEB49_OPCODE_WITH_CONST0);
                state.build.code[state.build.ncode++].data.i64_u = 0;
            } else {
                state.build.code[state.build.ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN);
                state.build.code[state.build.ncode++].data.i32_u = ret;
            }
            for (size_t i = 0; i < state.nlinks; i++) {
                web49_interp_link_t link = state.links[i];
                state.build.code[link.out].ptr = &state.build.code[*link.box];
            }
            block->code = state.build.code;
            web49_free(data);
        } else {
            web49_section_import_entry_t *entry = block->import_entry;
            web49_interp_import(ptrs, entry->module_str, entry->field_str, block);
        }
    }
    web49_interp_opcode_t *head = block->code;
    NEXT();
#define LOCAL0 interp.locals[head[0].data.i32_u]
#define LOCAL1 interp.locals[head[1].data.i32_u]
#define NAME(x) LABEL(x##_RR)
#include "interp.inc"
#undef LOCAL0
#undef LOCAL1
#undef NAME
#define LOCAL0 head[0].data
#define LOCAL1 interp.locals[head[1].data.i32_u]
#define NAME(x) LABEL(x##_CR)
#include "interp.inc"
#undef LOCAL0
#undef LOCAL1
#undef NAME
#define LOCAL0 interp.locals[head[0].data.i32_u]
#define LOCAL1 head[1].data
#define NAME(x) LABEL(x##_RC)
#include "interp.inc"
#undef LOCAL0
#undef LOCAL1
#undef NAME
#define LOCAL0 head[0].data
#define LOCAL1 head[1].data
#define NAME(x) LABEL(x##_CC)
#include "interp.inc"
#undef LOCAL0
#undef LOCAL1
#undef NAME
    LABEL(WEB49_OPCODE_MEMORY_INIT) {
        fprintf(stderr, "bulk memory? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_MEMORY_COPY) {
        fprintf(stderr, "bulk memory? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_MEMORY_FILL) {
        fprintf(stderr, "bulk memory? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_DATA_DROP) {
        fprintf(stderr, "bulk memory? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_TABLE_INIT) {
        fprintf(stderr, "bulk memory? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_ELEM_DROP) {
        fprintf(stderr, "bulk memory? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_TABLE_COPY) {
        fprintf(stderr, "bulk memory? you wish!\n");
        __builtin_trap();
        NEXT();
    }
    LABEL(WEB49_OPCODE_FFI_CALL) {
        web49_env_func_t func = head[0].ptr;
        return func(interp.extra->memory, interp.locals);
    }
    LABEL(WEB49_OPCODE_WASI_FD_SEEK) {
        uint32_t fd = interp.locals[0].i32_u;
        uint32_t offset = interp.locals[1].i32_u;
        uint32_t wasi_whence = interp.locals[2].i32_u;
        uint32_t result = interp.locals[3].i32_u;
        int whence = -1;
        switch (wasi_whence) {
            case 0:
                whence = SEEK_SET;
                break;
            case 1:
                whence = SEEK_CUR;
                break;
            case 2:
                whence = SEEK_END;
                break;
        }
        *(uint32_t *)&interp.extra->memory[result] = lseek(fd, offset, whence);
        return (web49_interp_data_t){.i32_u = 0};
    }
    LABEL(WEB49_OPCODE_WASI_FD_FILESTAT_GET) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_filestat_get");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_FILESTAT_GET) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_filestat_get");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_ARGS_GET) {
        uint32_t argv = interp.locals[0].i32_u;
        uint32_t buf = interp.locals[1].i32_u;
        uint32_t argc = 0;
        uint32_t head2 = buf;
        for (size_t i = 0; interp.extra->args[i] != NULL; i++) {
            *(uint32_t *)&interp.extra->memory[argv + argc * 4] = head2;
            size_t memlen = strlen(interp.extra->args[i]) + 1;
            memcpy(&interp.extra->memory[head2], interp.extra->args[i], memlen);
            head2 += memlen;
            argc += 1;
        }
        *(uint32_t *)&interp.extra->memory[argv + argc * 4] = 0;
        return (web49_interp_data_t){.i32_u = 0};
    }
    LABEL(WEB49_OPCODE_WASI_ARGS_SIZES_GET) {
        uint32_t argc = interp.locals[0].i32_u;
        uint32_t buf_size = interp.locals[1].i32_u;
        uint32_t buf_len = 0;
        uint32_t i = 0;
        while (interp.extra->args[i] != NULL) {
            buf_len += strlen(interp.extra->args[i]) + 1;
            i += 1;
        }
        *(uint32_t *)&interp.extra->memory[argc] = i;
        *(uint32_t *)&interp.extra->memory[buf_size] = buf_len;
        return (web49_interp_data_t){.i32_u = 0};
    }
    LABEL(WEB49_OPCODE_WASI_CLOCK_RES_GET) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_clock_res_get");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_CLOCK_TIME_GET) {
        uint32_t wasi_clock_id = interp.locals[0].i32_u;
        // uint64_t precision = interp.locals[1].i64_u;
        uint32_t time = interp.locals[2].i32_u;
        int clock_id = -1;
        switch (wasi_clock_id) {
            case 0:
                clock_id = CLOCK_REALTIME;
                break;
            case 1:
                clock_id = CLOCK_MONOTONIC;
                break;
            case 2:
                clock_id = CLOCK_PROCESS_CPUTIME_ID;
                break;
            case 3:
                clock_id = CLOCK_THREAD_CPUTIME_ID;
                break;
        }
        struct timespec ts;
        clock_gettime(clock_id, &ts);
        *(uint64_t *)&interp.extra->memory[time] = (uint64_t)ts.tv_sec * 1000000000 + (uint64_t)ts.tv_nsec;
        return (web49_interp_data_t){.i32_u = 0};
    }
    LABEL(WEB49_OPCODE_WASI_ENVIRON_GET) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_environ_get");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_ENVIRON_SIZES_GET) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_environ_sizes_get");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_ADVISE) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_advise");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_ALLOCATE) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_allocate");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_CLOSE) {
        uint32_t fd = interp.locals[0].i32_u;
        close(fd);
        return (web49_interp_data_t){.i32_u = 0};
    }
    LABEL(WEB49_OPCODE_WASI_FD_DATASYNC) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_datasync");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_FDSTAT_GET) {
        uint32_t fd = interp.locals[0].i32_u;
        uint32_t fdstat = interp.locals[1].i32_u;
        struct stat fd_stat;
        fstat(fd, &fd_stat);
        int mode = fd_stat.st_mode;
        uint16_t fs_filetype = (S_ISBLK(mode) ? 1 : 0) | (S_ISCHR(mode) ? 2 : 0) | (S_ISDIR(mode) ? 3 : 0) | (S_ISREG(mode) ? 4 : 0) | (S_ISLNK(mode) ? 7 : 0);
        uint16_t fs_flags = 0;
        uint64_t fs_rights_base = UINT64_MAX;
        uint64_t fs_rights_inheriting = UINT64_MAX;
        if (fd <= 2) {
            fs_rights_base &= ~(4 | 32);
        }
        *(uint16_t *)&interp.extra->memory[fdstat + 0] = fs_filetype;
        *(uint16_t *)&interp.extra->memory[fdstat + 2] = fs_flags;
        *(uint32_t *)&interp.extra->memory[fdstat + 4] = 0;
        *(uint64_t *)&interp.extra->memory[fdstat + 8] = fs_rights_base;
        *(uint64_t *)&interp.extra->memory[fdstat + 16] = fs_rights_inheriting;
        return (web49_interp_data_t){.i32_u = 0};
    }
    LABEL(WEB49_OPCODE_WASI_FD_FDSTAT_SET_FLAGS) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_fdstat_set_flags");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_FDSTAT_SET_RIGHTS) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_fdstat_set_rights");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_FILESTAT_SET_SIZE) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_filestat_set_size");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_FILESTAT_SET_TIMES) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_filestat_set_times");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_PREAD) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_pread");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_PRESTAT_GET) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_prestat_get");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_PRESTAT_DIR_NAME) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_prestat_dir_name");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_PWRITE) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_pwrite");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_READ) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_read");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_READDIR) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_readdir");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_RENUMBER) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_renumber");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_SYNC) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_sync");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_TELL) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_fd_tell");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_FD_WRITE) {
        uint32_t fd = interp.locals[0].i32_u;
        uint32_t iovs = interp.locals[1].i32_u;
        uint32_t iovs_len = interp.locals[2].i32_u;
        uint32_t nwritten = interp.locals[3].i32_u;
        *(uint32_t *)&interp.extra->memory[nwritten] = 0;
        for (size_t i = 0; i < iovs_len; i++) {
            uint32_t ptr = *(uint32_t *)&interp.extra->memory[iovs + i * 8];
            uint32_t len = *(uint32_t *)&interp.extra->memory[iovs + i * 8 + 4];
            *(uint32_t *)&interp.extra->memory[nwritten] += (uint32_t)write(fd, &interp.extra->memory[ptr], len);
        }
        return (web49_interp_data_t){.i32_u = 0};
    }
    LABEL(WEB49_OPCODE_WASI_PATH_CREATE_DIRECTORY) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_create_directory");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_FILESTAT_SET_TIMES) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_filestat_set_times");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_LINK) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_link");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_OPEN) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_open");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_READLINK) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_readlink");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_REMOVE_DIRECTORY) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_remove_directory");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_RENAME) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_rename");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_SYMLINK) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_symlink");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PATH_UNLINK_FILE) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_path_unlink_file");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_POLL_ONEOFF) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_poll_oneoff");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_PROC_EXIT) {
        exit(interp.locals[0].i32_u);
        NEXT();
    }
    LABEL(WEB49_OPCODE_WASI_PROC_RAISE) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_proc_raise");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_RANDOM_GET) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_random_get");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_SCHED_YIELD) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_sched_yield");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_SOCK_RECV) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_sock_recv");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_SOCK_SEND) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_sock_send");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_SOCK_SHUTDOWN) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_sock_shutdown");
        __builtin_trap();
    }
}

web49_interp_t web49_interp_module(web49_module_t mod, const char **args) {
    web49_section_type_t type_section = {0};
    web49_section_import_t import_section = {0};
    web49_section_code_t code_section = {0};
    web49_section_function_t function_section = {0};
    web49_section_global_t global_section = {0};
    web49_section_data_t data_section = {0};
    web49_section_table_t table_section = {0};
    web49_section_element_t element_section = {0};
    for (size_t i = 0; i < mod.num_sections; i++) {
        web49_section_t section = mod.sections[i];
        if (section.header.id == WEB49_SECTION_ID_EXPORT) {
            // for (size_t j = 0; j < section.export_section.num_entries; j++) {
            //     web49_section_export_entry_t entry = section.export_section.entries[j];
            //     if (!strcmp(entry.field_str, start)) {
            //         start = entry.index;
            //     }
            //     if (!strcmp(entry.field_str, update)) {
            //         update = entry.index;
            //     }
            // }
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_TYPE) {
            type_section = mod.sections[i].type_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_IMPORT) {
            import_section = mod.sections[i].import_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_FUNCTION) {
            function_section = mod.sections[i].function_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_CODE) {
            code_section = mod.sections[i].code_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_GLOBAL) {
            global_section = mod.sections[i].global_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_DATA) {
            data_section = mod.sections[i].data_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_TABLE) {
            table_section = mod.sections[i].table_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_ELEMENT) {
            element_section = mod.sections[i].element_section;
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
    web49_interp_data_t *locals = web49_alloc0(sizeof(web49_interp_data_t) * (1 << 16));
    uint64_t memsize = 65536 * 256;
    web49_interp_extra_t *extra = web49_alloc0(sizeof(web49_interp_extra_t) + memsize);
    *extra = (web49_interp_extra_t){
        .table = NULL,
        .funcs = web49_malloc(sizeof(web49_interp_block_t) * num_funcs),
        .globals = web49_alloc0(sizeof(web49_interp_data_t) * (global_section.num_entries)),
        .args = args,
        .memsize = memsize,
        .type_section = type_section,
        .import_section = import_section,
        .code_section = code_section,
        .function_section = function_section,
        .global_section = global_section,
        .data_section = data_section,
        .table_section = table_section,
        .element_section = element_section,
    };
    web49_interp_t interp = (web49_interp_t){
        .locals = locals,
        .extra = extra,
    };
    for (size_t j = 0; j < table_section.num_entries; j++) {
        web49_type_table_t entry = table_section.entries[j];
        if (entry.element_type == WEB49_TYPE_ANYFUNC) {
            interp.extra->table = web49_malloc(sizeof(web49_interp_block_t *) * entry.limits.maximum);
        }
    }
    for (size_t j = 0; j < import_section.num_entries; j++) {
        web49_section_import_entry_t *entry = &import_section.entries[j];
        if (entry->kind == WEB49_EXTERNAL_KIND_FUNCTION) {
            web49_interp_block_t *block = &interp.extra->funcs[cur_func++];
            block->is_code = false;
            block->import_entry = entry;
            web49_interp_import(NULL, entry->module_str, entry->field_str, block);
            block->code = NULL;
        }
    }
    for (size_t j = 0; j < global_section.num_entries; j++) {
        web49_section_global_entry_t global = global_section.entries[j];
        if (global.init_expr.opcode == WEB49_OPCODE_I32_CONST) {
            interp.extra->globals[j].i32_s = global.init_expr.immediate.varint32;
        } else if (global.init_expr.opcode == WEB49_OPCODE_I64_CONST) {
            interp.extra->globals[j].i64_s = global.init_expr.immediate.varint64;
        } else {
            interp.extra->globals[j].i64_u = 0;
        }
    }
    for (size_t j = 0; j < data_section.num_entries; j++) {
        web49_section_data_entry_t entry = data_section.entries[j];
        memcpy(&interp.extra->memory[entry.offset.immediate.varint32], entry.data, entry.size);
    }
    for (size_t j = 0; j < code_section.num_entries; j++) {
        web49_section_code_entry_t *entry = &code_section.entries[j];
        web49_interp_block_t *block = &interp.extra->funcs[cur_func++];
        block->code = NULL;
        block->nlocals = 0;
        for (uint64_t i = 0; i < entry->num_locals; i++) {
            block->nlocals += entry->locals[i].count;
        }
        block->nparams = type_section.entries[function_section.entries[j]].num_params;
        block->nreturns = type_section.entries[function_section.entries[j]].num_returns;
        block->is_code = true;
        block->code_entry = entry;
    }
    for (size_t j = 0; j < element_section.num_entries; j++) {
        web49_section_element_entry_t entry = element_section.entries[j];
        for (uint64_t i = 0; i < entry.num_elems; i++) {
            interp.extra->table[i + entry.offset.immediate.varint32] = &interp.extra->funcs[entry.elems[i]];
        }
    }
    return interp;
}
