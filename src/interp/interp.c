#include "interp.h"

#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "../tables.h"

#define OPCODE(n) ({size_t x = n; if (ptrs[x] == NULL) {fprintf(stderr, #n " = %zu\n", x); __builtin_trap();} ptrs[x]; })

void web49_interp_import(void **ptrs, const char *mod, const char *sym, web49_interp_block_t *block) {
    if (!strcmp(mod, "wasi_snapshot_preview1")) {
        size_t iit = 0;
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
            web49_interp_opcode_t *instrs = web49_malloc(sizeof(web49_interp_opcode_t) * 2);
            instrs[0].opcode = OPCODE(iit);
            instrs[1].opcode = OPCODE(WEB49_OPCODE_RETURN);
            block->code = instrs;
        }
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

void web49_interp_read_instr(web49_read_block_state_t *state, web49_instr_t cur) {
    web49_interp_build_t *build = &state->build;
    void **ptrs = state->ptrs;
    if (build->ncode + 8 >= build->alloc) {
        fprintf(stderr, "error: outran preallocated code memory\n");
        __builtin_trap();
    }
    if (cur.opcode == WEB49_OPCODE_BLOCK) {
        uint64_t *box = web49_interp_link_box();
        *++state->bufs = box;
        for (size_t i = 0; i < cur.nargs; i++) {
            web49_interp_read_instr(state, cur.args[i]);
        }
        state->bufs--;
        *box = build->ncode;
        return;
    }
    if (cur.opcode == WEB49_OPCODE_LOOP) {
        uint64_t *box = web49_interp_link_box();
        *box = build->ncode;
        *++state->bufs = box;
        for (size_t i = 0; i < cur.nargs; i++) {
            web49_interp_read_instr(state, cur.args[i]);
        }
        state->bufs--;
        return;
    }
    if (cur.opcode == WEB49_OPCODE_IF) {
        if (cur.nargs == 3) {
            uint64_t *ift = web49_interp_link_box();
            uint64_t *iff = web49_interp_link_box();
            uint64_t *end = web49_interp_link_box();
            web49_interp_read_instr(state, cur.args[0]);
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_IF);
            web49_interp_link_get(state, build->ncode++, ift);
            web49_interp_link_get(state, build->ncode++, iff);
            *++state->bufs = end;
            *ift = build->ncode;
            for (size_t i = 0; i < cur.args[1].nargs; i++) {
                web49_interp_read_instr(state, cur.args[1].args[i]);
            }
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_BR);
            web49_interp_link_get(state, build->ncode++, end);
            *iff = build->ncode;
            for (size_t i = 0; i < cur.args[2].nargs; i++) {
                web49_interp_read_instr(state, cur.args[2].args[i]);
            }
            state->bufs--;
            *end = build->ncode;
        } else {
            uint64_t *then = web49_interp_link_box();
            uint64_t *end = web49_interp_link_box();
            web49_interp_read_instr(state, cur.args[0]);
            build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_IF);
            web49_interp_link_get(state, build->ncode++, then);
            web49_interp_link_get(state, build->ncode++, end);
            *++state->bufs = end;
            *then = build->ncode;
            for (size_t i = 0; i < cur.args[1].nargs; i++) {
                web49_interp_read_instr(state, cur.args[1].args[i]);
            }
            state->bufs--;
            *end = build->ncode;
        }
        return;
    }
    for (uint64_t i = 0; i < cur.nargs; i++) {
        web49_interp_read_instr(state, cur.args[i]);
    }
    if (cur.opcode == WEB49_OPCODE_F64_REINTERPRET_I64 || cur.opcode == WEB49_OPCODE_I64_REINTERPRET_F64 || cur.opcode == WEB49_OPCODE_F32_REINTERPRET_I32 || cur.opcode == WEB49_OPCODE_I32_REINTERPRET_F32 || cur.opcode == WEB49_OPCODE_BEGIN0 || cur.opcode == WEB49_OPCODE_NOP) {
        return;
    }

#define NAME(n)                                                  \
    if (cur.opcode == n##_TO_STACK) {                            \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode); \
        return;                                                  \
    }
#include "name.inc"

#define NAME(n)                                                                          \
    if (cur.opcode == n##_TOP_CONST_TO_STACK) {                                          \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);                         \
        build->code[build->ncode++].data.i64_s = cur.args[cur.nargs].immediate.varint64; \
        return;                                                                          \
    }
#include "name.inc"

#define NAME(n)                                                                           \
    if (cur.opcode == n##_TOP_LOCAL_TO_STACK) {                                           \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);                          \
        build->code[build->ncode++].data.i32_u = cur.args[cur.nargs].immediate.varuint32; \
        return;                                                                           \
    }
#include "name.inc"

#define NAME(n)                                                                              \
    if (cur.opcode == n##_TOP_CONST_NEXT_LOCAL_TO_STACK) {                                   \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);                             \
        build->code[build->ncode++].data.i64_s = cur.args[cur.nargs + 1].immediate.varint64; \
        build->code[build->ncode++].data.i32_u = cur.args[cur.nargs].immediate.varuint32;    \
        return;                                                                              \
    }
#include "name.inc"

#define NAME(n)                                                                               \
    if (cur.opcode == n##_TOP_LOCAL_NEXT_LOCAL_TO_STACK) {                                    \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);                              \
        build->code[build->ncode++].data.i32_u = cur.args[cur.nargs + 1].immediate.varuint32; \
        build->code[build->ncode++].data.i32_u = cur.args[cur.nargs].immediate.varuint32;     \
        return;                                                                               \
    }
#include "name.inc"

#define NAME(n)                                                               \
    if (cur.opcode == n##_TO_LOCAL || cur.opcode == n##_TO_STACK_AND_LOCAL) { \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);              \
        build->code[build->ncode++].data.i32_u = cur.immediate.varuint32;     \
        return;                                                               \
    }
#include "name.inc"

#define NAME(n)                                                                                   \
    if (cur.opcode == n##_TOP_CONST_TO_LOCAL || cur.opcode == n##_TOP_CONST_TO_STACK_AND_LOCAL) { \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);                                  \
        build->code[build->ncode++].data.i64_s = cur.args[cur.nargs].immediate.varint64;          \
        build->code[build->ncode++].data.i32_u = cur.immediate.varuint32;                         \
        return;                                                                                   \
    }
#include "name.inc"

#define NAME(n)                                                                                   \
    if (cur.opcode == n##_TOP_LOCAL_TO_LOCAL || cur.opcode == n##_TOP_LOCAL_TO_STACK_AND_LOCAL) { \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);                                  \
        build->code[build->ncode++].data.i32_u = cur.args[cur.nargs].immediate.varuint32;         \
        build->code[build->ncode++].data.i32_u = cur.immediate.varuint32;                         \
        return;                                                                                   \
    }
#include "name.inc"

#define NAME(n)                                                                                                         \
    if (cur.opcode == n##_TOP_CONST_NEXT_LOCAL_TO_LOCAL || cur.opcode == n##_TOP_CONST_NEXT_LOCAL_TO_STACK_AND_LOCAL) { \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);                                                        \
        build->code[build->ncode++].data.i64_s = cur.args[cur.nargs + 1].immediate.varint64;                            \
        build->code[build->ncode++].data.i32_u = cur.args[cur.nargs].immediate.varuint32;                               \
        build->code[build->ncode++].data.i32_u = cur.immediate.varuint32;                                               \
        return;                                                                                                         \
    }
#include "name.inc"

#define NAME(n)                                                                                                         \
    if (cur.opcode == n##_TOP_LOCAL_NEXT_LOCAL_TO_LOCAL || cur.opcode == n##_TOP_LOCAL_NEXT_LOCAL_TO_STACK_AND_LOCAL) { \
        build->code[build->ncode++].opcode = OPCODE(cur.opcode);                                                        \
        build->code[build->ncode++].data.i32_u = cur.args[cur.nargs + 1].immediate.varuint32;                           \
        build->code[build->ncode++].data.i32_u = cur.args[cur.nargs].immediate.varuint32;                               \
        build->code[build->ncode++].data.i32_u = cur.immediate.varuint32;                                               \
        return;                                                                                                         \
    }
#include "name.inc"

    if (cur.opcode == WEB49_OPCODE_BR) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_BR);
        web49_interp_link_get(state, build->ncode++, state->bufs[-(ptrdiff_t)cur.immediate.varuint32]);
        return;
    }
    if (cur.opcode == WEB49_OPCODE_BR_IF) {
        build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_BR_IF);
        web49_interp_link_get(state, build->ncode++, state->bufs[-(ptrdiff_t)cur.immediate.varuint32]);
        return;
    }
    if (cur.opcode == WEB49_OPCODE_CALL) {
        switch (state->interp->extra->funcs[cur.immediate.varint32].nreturns) {
            case 0:
                build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL0);
                build->code[build->ncode++].ptr = &state->interp->extra->funcs[cur.immediate.varint32];
                break;
            case 1:
                build->code[build->ncode++].opcode = OPCODE(WEB49_OPCODE_CALL1);
                build->code[build->ncode++].ptr = &state->interp->extra->funcs[cur.immediate.varint32];
                break;
            default:
                fprintf(stderr, "cannot compile multiple returns yet\n");
                break;
        }
        return;
    }
    build->code[build->ncode++].opcode = OPCODE(cur.opcode);
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
}

#if defined(WEB49_PRINT_INSTR)
#define DPRINT(name) fprintf(stderr, name "\n")
#else
#define DPRINT(name)
#endif

#if defined(WEB49_COUNT_INSTR)
#define DCOUNT(n) interp.count[n] += 1; interp.names[n] = #n;
#else
#define DCOUNT(n)
#endif

#if 1
#define LABEL(name) \
    DO_##name:;     \
    DCOUNT(name);   \
    DPRINT(#name);  \
    head += 1;
#define NEXT() goto * head->opcode
#else
#define LABEL(name) \
    DO_##name:;     \
    DCOUNT(name);   \
    DPRINT(#name);
#define NEXT() goto *head++->opcode
#endif

web49_interp_data_t web49_interp_block_run(web49_interp_t interp, web49_interp_block_t *block) {
    static void *ptrs[WEB49_MAX_OPCODE_INTERP_NUM] = {
        [WEB49_OPCODE_UNREACHABLE] = &&DO_WEB49_OPCODE_UNREACHABLE,
        [WEB49_OPCODE_NOP] = &&DO_WEB49_OPCODE_NOP,
        [WEB49_OPCODE_BLOCK] = &&DO_WEB49_OPCODE_BLOCK,
        [WEB49_OPCODE_LOOP] = &&DO_WEB49_OPCODE_LOOP,
        [WEB49_OPCODE_IF] = &&DO_WEB49_OPCODE_IF,
        [WEB49_OPCODE_ELSE] = &&DO_WEB49_OPCODE_ELSE,
        [WEB49_OPCODE_END] = &&DO_WEB49_OPCODE_END,
        [WEB49_OPCODE_BR] = &&DO_WEB49_OPCODE_BR,
        [WEB49_OPCODE_BR_IF] = &&DO_WEB49_OPCODE_BR_IF,
        [WEB49_OPCODE_BR_TABLE] = &&DO_WEB49_OPCODE_BR_TABLE,
        [WEB49_OPCODE_RETURN] = &&DO_WEB49_OPCODE_RETURN,
        [WEB49_OPCODE_CALL0] = &&DO_WEB49_OPCODE_CALL0,
        [WEB49_OPCODE_CALL1] = &&DO_WEB49_OPCODE_CALL1,
        [WEB49_OPCODE_CALL_INDIRECT] = &&DO_WEB49_OPCODE_CALL_INDIRECT,
        [WEB49_OPCODE_DROP] = &&DO_WEB49_OPCODE_DROP,
        [WEB49_OPCODE_SELECT] = &&DO_WEB49_OPCODE_SELECT,
        [WEB49_OPCODE_GET_LOCAL] = &&DO_WEB49_OPCODE_GET_LOCAL,
        [WEB49_OPCODE_SET_LOCAL] = &&DO_WEB49_OPCODE_SET_LOCAL,
        [WEB49_OPCODE_TEE_LOCAL] = &&DO_WEB49_OPCODE_TEE_LOCAL,
        [WEB49_OPCODE_GET_GLOBAL] = &&DO_WEB49_OPCODE_GET_GLOBAL,
        [WEB49_OPCODE_SET_GLOBAL] = &&DO_WEB49_OPCODE_SET_GLOBAL,
        [WEB49_OPCODE_I32_LOAD] = &&DO_WEB49_OPCODE_I32_LOAD,
        [WEB49_OPCODE_I64_LOAD] = &&DO_WEB49_OPCODE_I64_LOAD,
        [WEB49_OPCODE_F32_LOAD] = &&DO_WEB49_OPCODE_F32_LOAD,
        [WEB49_OPCODE_F64_LOAD] = &&DO_WEB49_OPCODE_F64_LOAD,
        [WEB49_OPCODE_I32_LOAD8_S] = &&DO_WEB49_OPCODE_I32_LOAD8_S,
        [WEB49_OPCODE_I32_LOAD8_U] = &&DO_WEB49_OPCODE_I32_LOAD8_U,
        [WEB49_OPCODE_I32_LOAD16_S] = &&DO_WEB49_OPCODE_I32_LOAD16_S,
        [WEB49_OPCODE_I32_LOAD16_U] = &&DO_WEB49_OPCODE_I32_LOAD16_U,
        [WEB49_OPCODE_I64_LOAD8_S] = &&DO_WEB49_OPCODE_I64_LOAD8_S,
        [WEB49_OPCODE_I64_LOAD8_U] = &&DO_WEB49_OPCODE_I64_LOAD8_U,
        [WEB49_OPCODE_I64_LOAD16_S] = &&DO_WEB49_OPCODE_I64_LOAD16_S,
        [WEB49_OPCODE_I64_LOAD16_U] = &&DO_WEB49_OPCODE_I64_LOAD16_U,
        [WEB49_OPCODE_I64_LOAD32_S] = &&DO_WEB49_OPCODE_I64_LOAD32_S,
        [WEB49_OPCODE_I64_LOAD32_U] = &&DO_WEB49_OPCODE_I64_LOAD32_U,
        [WEB49_OPCODE_I32_STORE] = &&DO_WEB49_OPCODE_I32_STORE,
        [WEB49_OPCODE_I64_STORE] = &&DO_WEB49_OPCODE_I64_STORE,
        [WEB49_OPCODE_F32_STORE] = &&DO_WEB49_OPCODE_F32_STORE,
        [WEB49_OPCODE_F64_STORE] = &&DO_WEB49_OPCODE_F64_STORE,
        [WEB49_OPCODE_I32_STORE8] = &&DO_WEB49_OPCODE_I32_STORE8,
        [WEB49_OPCODE_I32_STORE16] = &&DO_WEB49_OPCODE_I32_STORE16,
        [WEB49_OPCODE_I64_STORE8] = &&DO_WEB49_OPCODE_I64_STORE8,
        [WEB49_OPCODE_I64_STORE16] = &&DO_WEB49_OPCODE_I64_STORE16,
        [WEB49_OPCODE_I64_STORE32] = &&DO_WEB49_OPCODE_I64_STORE32,
        [WEB49_OPCODE_MEMORY_SIZE] = &&DO_WEB49_OPCODE_MEMORY_SIZE,
        [WEB49_OPCODE_MEMORY_GROW] = &&DO_WEB49_OPCODE_MEMORY_GROW,
        [WEB49_OPCODE_I32_CONST] = &&DO_WEB49_OPCODE_I32_CONST,
        [WEB49_OPCODE_I64_CONST] = &&DO_WEB49_OPCODE_I64_CONST,
        [WEB49_OPCODE_F32_CONST] = &&DO_WEB49_OPCODE_F32_CONST,
        [WEB49_OPCODE_F64_CONST] = &&DO_WEB49_OPCODE_F64_CONST,
        [WEB49_OPCODE_I32_EQZ] = &&DO_WEB49_OPCODE_I32_EQZ,
        [WEB49_OPCODE_I64_EQZ] = &&DO_WEB49_OPCODE_I64_EQZ,
        [WEB49_OPCODE_I32_CLZ] = &&DO_WEB49_OPCODE_I32_CLZ,
        [WEB49_OPCODE_I32_CTZ] = &&DO_WEB49_OPCODE_I32_CTZ,
        [WEB49_OPCODE_I32_POPCNT] = &&DO_WEB49_OPCODE_I32_POPCNT,
        [WEB49_OPCODE_I64_CLZ] = &&DO_WEB49_OPCODE_I64_CLZ,
        [WEB49_OPCODE_I64_CTZ] = &&DO_WEB49_OPCODE_I64_CTZ,
        [WEB49_OPCODE_I64_POPCNT] = &&DO_WEB49_OPCODE_I64_POPCNT,
        [WEB49_OPCODE_F32_ABS] = &&DO_WEB49_OPCODE_F32_ABS,
        [WEB49_OPCODE_F32_NEG] = &&DO_WEB49_OPCODE_F32_NEG,
        [WEB49_OPCODE_F32_CEIL] = &&DO_WEB49_OPCODE_F32_CEIL,
        [WEB49_OPCODE_F32_FLOOR] = &&DO_WEB49_OPCODE_F32_FLOOR,
        [WEB49_OPCODE_F32_TRUNC] = &&DO_WEB49_OPCODE_F32_TRUNC,
        [WEB49_OPCODE_F32_NEAREST] = &&DO_WEB49_OPCODE_F32_NEAREST,
        [WEB49_OPCODE_F32_SQRT] = &&DO_WEB49_OPCODE_F32_SQRT,
        [WEB49_OPCODE_F64_ABS] = &&DO_WEB49_OPCODE_F64_ABS,
        [WEB49_OPCODE_F64_NEG] = &&DO_WEB49_OPCODE_F64_NEG,
        [WEB49_OPCODE_F64_CEIL] = &&DO_WEB49_OPCODE_F64_CEIL,
        [WEB49_OPCODE_F64_FLOOR] = &&DO_WEB49_OPCODE_F64_FLOOR,
        [WEB49_OPCODE_F64_TRUNC] = &&DO_WEB49_OPCODE_F64_TRUNC,
        [WEB49_OPCODE_F64_NEAREST] = &&DO_WEB49_OPCODE_F64_NEAREST,
        [WEB49_OPCODE_F64_SQRT] = &&DO_WEB49_OPCODE_F64_SQRT,
        [WEB49_OPCODE_I32_WRAP_I64] = &&DO_WEB49_OPCODE_I32_WRAP_I64,
        [WEB49_OPCODE_I32_TRUNC_S_F32] = &&DO_WEB49_OPCODE_I32_TRUNC_S_F32,
        [WEB49_OPCODE_I32_TRUNC_U_F32] = &&DO_WEB49_OPCODE_I32_TRUNC_U_F32,
        [WEB49_OPCODE_I32_TRUNC_S_F64] = &&DO_WEB49_OPCODE_I32_TRUNC_S_F64,
        [WEB49_OPCODE_I32_TRUNC_U_F64] = &&DO_WEB49_OPCODE_I32_TRUNC_U_F64,
        [WEB49_OPCODE_I64_EXTEND_S_I32] = &&DO_WEB49_OPCODE_I64_EXTEND_S_I32,
        [WEB49_OPCODE_I64_EXTEND_U_I32] = &&DO_WEB49_OPCODE_I64_EXTEND_U_I32,
        [WEB49_OPCODE_I64_TRUNC_S_F32] = &&DO_WEB49_OPCODE_I64_TRUNC_S_F32,
        [WEB49_OPCODE_I64_TRUNC_U_F32] = &&DO_WEB49_OPCODE_I64_TRUNC_U_F32,
        [WEB49_OPCODE_I64_TRUNC_S_F64] = &&DO_WEB49_OPCODE_I64_TRUNC_S_F64,
        [WEB49_OPCODE_I64_TRUNC_U_F64] = &&DO_WEB49_OPCODE_I64_TRUNC_U_F64,
        [WEB49_OPCODE_F32_CONVERT_S_I32] = &&DO_WEB49_OPCODE_F32_CONVERT_S_I32,
        [WEB49_OPCODE_F32_CONVERT_U_I32] = &&DO_WEB49_OPCODE_F32_CONVERT_U_I32,
        [WEB49_OPCODE_F32_CONVERT_S_I64] = &&DO_WEB49_OPCODE_F32_CONVERT_S_I64,
        [WEB49_OPCODE_F32_CONVERT_U_I64] = &&DO_WEB49_OPCODE_F32_CONVERT_U_I64,
        [WEB49_OPCODE_F32_DEMOTE_F64] = &&DO_WEB49_OPCODE_F32_DEMOTE_F64,
        [WEB49_OPCODE_F64_CONVERT_S_I32] = &&DO_WEB49_OPCODE_F64_CONVERT_S_I32,
        [WEB49_OPCODE_F64_CONVERT_U_I32] = &&DO_WEB49_OPCODE_F64_CONVERT_U_I32,
        [WEB49_OPCODE_F64_CONVERT_S_I64] = &&DO_WEB49_OPCODE_F64_CONVERT_S_I64,
        [WEB49_OPCODE_F64_CONVERT_U_I64] = &&DO_WEB49_OPCODE_F64_CONVERT_U_I64,
        [WEB49_OPCODE_F64_PROMOTE_F32] = &&DO_WEB49_OPCODE_F64_PROMOTE_F32,
        [WEB49_OPCODE_I32_REINTERPRET_F32] = &&DO_WEB49_OPCODE_I32_REINTERPRET_F32,
        [WEB49_OPCODE_I64_REINTERPRET_F64] = &&DO_WEB49_OPCODE_I64_REINTERPRET_F64,
        [WEB49_OPCODE_F32_REINTERPRET_I32] = &&DO_WEB49_OPCODE_F32_REINTERPRET_I32,
        [WEB49_OPCODE_F64_REINTERPRET_I64] = &&DO_WEB49_OPCODE_F64_REINTERPRET_I64,
        [WEB49_OPCODE_MEMORY_INIT] = &&DO_WEB49_OPCODE_MEMORY_INIT,
        [WEB49_OPCODE_MEMORY_COPY] = &&DO_WEB49_OPCODE_MEMORY_COPY,
        [WEB49_OPCODE_MEMORY_FILL] = &&DO_WEB49_OPCODE_MEMORY_FILL,
        [WEB49_OPCODE_DATA_DROP] = &&DO_WEB49_OPCODE_DATA_DROP,
        [WEB49_OPCODE_TABLE_INIT] = &&DO_WEB49_OPCODE_TABLE_INIT,
        [WEB49_OPCODE_ELEM_DROP] = &&DO_WEB49_OPCODE_ELEM_DROP,
        [WEB49_OPCODE_TABLE_COPY] = &&DO_WEB49_OPCODE_TABLE_COPY,
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
#define DO(a) [a] = &&DO_##a,
#define PERM1(c) DO(c##_TO_STACK) DO(c##_TO_LOCAL) DO(c##_TO_STACK_AND_LOCAL)
#define PERM2(b) [b] = &&DO_##b##_TO_STACK, PERM1(b) PERM1(b##_TOP_CONST) PERM1(b##_TOP_CONST_NEXT_LOCAL) PERM1(b##_TOP_LOCAL) PERM1(b##_TOP_LOCAL_NEXT_LOCAL)
#define NAME(d) PERM2(d)
#include "name.inc"
#undef PERM1
#undef PERM2
#undef DO
    };
    if (block->code == NULL) {
        if (block->is_code) {
            web49_section_code_entry_t *entry = block->code_entry;
            for (uint64_t i = 0; i < entry->num_instrs; i++) {
                entry->instrs[i] = web49_interp_opt(entry->instrs[i]);
            }
            web49_read_block_state_t state;
            state.ptrs = ptrs;
            state.bufs = &interp.extra->data[1];
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
            for (uint64_t i = 0; i < entry->num_instrs; i++) {
                web49_interp_read_instr(&state, entry->instrs[i]);
            }
            state.build.code[state.build.ncode++].opcode = OPCODE(WEB49_OPCODE_RETURN);
            for (size_t i = 0; i < state.nlinks; i++) {
                web49_interp_link_t link = state.links[i];
                state.build.code[link.out].ptr = &state.build.code[*link.box];
            }
            block->code = state.build.code;
        } else {
            web49_section_import_entry_t *entry = block->import_entry;
            web49_interp_import(ptrs, entry->module_str, entry->field_str, block);
        }
    }
    const web49_interp_opcode_t *restrict head = block->code;
    NEXT();
    LABEL(WEB49_OPCODE_UNREACHABLE) {
        fprintf(stderr, "unreachable was reached\n");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_NOP) {
        NEXT();
    }
    LABEL(WEB49_OPCODE_BLOCK) {
        head = head[0].ptr;
        NEXT();
    }
    LABEL(WEB49_OPCODE_LOOP) {
        head = head[0].ptr;
        NEXT();
    }
    LABEL(WEB49_OPCODE_IF) {
        if ((--interp.stack)->i32_u) {
            head = head[0].ptr;
            NEXT();
        } else {
            head = head[1].ptr;
            NEXT();
        }
    }
    LABEL(WEB49_OPCODE_ELSE) {
        fprintf(stderr, "no impl for: %s\n", "else");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_END) {
        head = head[0].ptr;
        NEXT();
    }
    LABEL(WEB49_OPCODE_BR) {
        head = head[0].ptr;
        NEXT();
    }
    LABEL(WEB49_OPCODE_BR_IF) {
        // fprintf(stderr, "(br_if ... %zu)\n", (size_t) interp.stack[-1].i32_u);
        if ((--interp.stack)->i32_u) {
            head = head[0].ptr;
            NEXT();
        } else {
            head += 1;
            NEXT();
        }
    }
    LABEL(WEB49_OPCODE_BR_TABLE) {
        web49_interp_data_t data = *--interp.stack;
        uint32_t max = head++->data.i32_u;
        if (data.i32_u >= max) {
            head = head[max].ptr;
            NEXT();
        } else {
            head = head[data.i32_u].ptr;
            NEXT();
        }
    }
    LABEL(WEB49_OPCODE_RETURN) {
        return interp.stack[-1];
    }
    LABEL(WEB49_OPCODE_CALL0) {
        web49_interp_block_t *func = head++->ptr;
        memset(interp.stack, 0, func->nlocals * sizeof(web49_interp_data_t));
        web49_interp_data_t *next = interp.stack - func->nparams;
        web49_interp_t interp2 = (web49_interp_t){
            .stack = interp.stack + func->nlocals,
            .locals = next,
            .memory = interp.memory,
            .extra = interp.extra,
#if defined(WEB49_COUNT_INSTR)
            .count = interp.count,
            .names = interp.names,
#endif
        };
        interp.stack = next;
        web49_interp_block_run(interp2, func);
        NEXT();
    }
    LABEL(WEB49_OPCODE_CALL1) {
        web49_interp_block_t *func = head++->ptr;
        memset(interp.stack, 0, func->nlocals * sizeof(web49_interp_data_t));
        web49_interp_data_t *next = interp.stack - func->nparams;
        web49_interp_t interp2 = (web49_interp_t){
            .stack = interp.stack + func->nlocals,
            .locals = next,
            .memory = interp.memory,
            .extra = interp.extra,
#if defined(WEB49_COUNT_INSTR)
            .count = interp.count,
            .names = interp.names,
#endif
        };
        interp.stack = next;
        web49_interp_data_t data = web49_interp_block_run(interp2, func);
        *interp.stack++ = data;
        NEXT();
    }
    LABEL(WEB49_OPCODE_CALL_INDIRECT) {
        uint32_t funcno = (--interp.stack)->i32_u;
        web49_interp_block_t *func = interp.extra->table[funcno];
        memset(interp.stack, 0, func->nlocals * sizeof(web49_interp_data_t));
        web49_interp_data_t *next = interp.stack - func->nparams;
        web49_interp_t interp2 = (web49_interp_t){
            .stack = interp.stack + func->nlocals,
            .locals = next,
            .memory = interp.memory,
            .extra = interp.extra,
#if defined(WEB49_COUNT_INSTR)
            .count = interp.count,
            .names = interp.names,
#endif
        };
        interp.stack = next;
        switch (func->nreturns) {
            case 0: {
                web49_interp_block_run(interp, func);
                break;
            }
            case 1: {
                *interp.stack++ = web49_interp_block_run(interp2, func);
                break;
            }
            default: {
                __builtin_unreachable();
            }
        }
        NEXT();
    }
    LABEL(WEB49_OPCODE_DROP) {
        interp.stack -= 1;
        NEXT();
    }
    LABEL(WEB49_OPCODE_SELECT) {
        web49_interp_data_t cond = *--interp.stack;
        web49_interp_data_t iff = *--interp.stack;
        web49_interp_data_t ift = *--interp.stack;
        if (cond.i32_u) {
            *interp.stack++ = ift;
        } else {
            *interp.stack++ = iff;
        }
        NEXT();
    }
    LABEL(WEB49_OPCODE_GET_LOCAL) {
        // fprintf(stderr, "LOCAL %zu\n", (size_t) head->data.i32_u);
        *interp.stack++ = interp.locals[head++->data.i32_u];
        NEXT();
    }
    LABEL(WEB49_OPCODE_SET_LOCAL) {
        interp.locals[head++->data.i32_u] = *--interp.stack;
        NEXT();
    }
    LABEL(WEB49_OPCODE_TEE_LOCAL) {
        interp.locals[head++->data.i32_u] = interp.stack[-1];
        NEXT();
    }
    LABEL(WEB49_OPCODE_GET_GLOBAL) {
        *interp.stack++ = interp.extra->globals[head++->data.i32_u];
        NEXT();
    }
    LABEL(WEB49_OPCODE_SET_GLOBAL) {
        interp.extra->globals[head++->data.i32_u] = *--interp.stack;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_LOAD) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i32_u = *(uint32_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_LOAD) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i64_u = *(uint64_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_LOAD) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->f32 = *(float *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_LOAD) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->f64 = *(double *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_LOAD8_S) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i32_s = (int32_t) * (int8_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_LOAD8_U) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i32_u = (uint32_t) * (uint8_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_LOAD16_S) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i32_s = (int32_t) * (int16_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_LOAD16_U) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i32_u = (uint32_t) * (uint16_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_LOAD8_S) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i64_s = (int64_t) * (int8_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_LOAD8_U) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i64_u = (uint64_t) * (uint8_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_LOAD16_S) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i64_s = (int64_t) * (int16_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_LOAD16_U) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i64_u = (uint64_t) * (uint16_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_LOAD32_S) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i64_s = (int64_t) * (int32_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_LOAD32_U) {
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        interp.stack++->i64_u = (uint64_t) * (uint32_t *)&interp.memory[ptr + off];
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_STORE) {
        uint32_t val = (--interp.stack)->i32_u;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(uint32_t *)&interp.memory[ptr + off] = (uint32_t)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_STORE) {
        uint64_t val = (--interp.stack)->i64_u;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(uint64_t *)&interp.memory[ptr + off] = (uint64_t)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_STORE) {
        float val = (--interp.stack)->f32;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(float *)&interp.memory[ptr + off] = (float)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_STORE) {
        double val = (--interp.stack)->f64;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(double *)&interp.memory[ptr + off] = (double)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_STORE8) {
        uint32_t val = (--interp.stack)->i32_u;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(uint8_t *)&interp.memory[ptr + off] = (uint8_t)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_STORE16) {
        uint32_t val = (--interp.stack)->i32_u;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(uint16_t *)&interp.memory[ptr + off] = (uint16_t)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_STORE8) {
        uint64_t val = (--interp.stack)->i64_u;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(uint8_t *)&interp.memory[ptr + off] = (uint8_t)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_STORE16) {
        uint64_t val = (--interp.stack)->i64_u;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(uint16_t *)&interp.memory[ptr + off] = (uint16_t)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_STORE32) {
        uint64_t val = (--interp.stack)->i64_u;
        uint32_t ptr = (--interp.stack)->i32_u;
        uint32_t off = head++->data.i32_u;
        *(uint32_t *)&interp.memory[ptr + off] = (uint32_t)val;
        NEXT();
    }
    LABEL(WEB49_OPCODE_MEMORY_SIZE) {
        interp.stack++->i32_u = (interp.extra->memsize) / (1 << 16);
        NEXT();
    }
    LABEL(WEB49_OPCODE_MEMORY_GROW) {
        uint32_t oldsize = (interp.extra->memsize) / (1 << 16);
        uint32_t newsize = (--interp.stack)->i32_u;
        interp.memory = web49_realloc(interp.memory, (oldsize + newsize) * (1 << 16));
        interp.stack++->i32_u = oldsize;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_CONST) {
        interp.stack++->i32_s = head++->data.i32_s;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_CONST) {
        interp.stack++->i64_s = head++->data.i64_s;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_CONST) {
        interp.stack++->f32 = head++->data.f32;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_CONST) {
        interp.stack++->f64 = head++->data.f64;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_EQZ) {
        interp.stack[-1].i32_u = interp.stack[-1].i32_u == 0 ? 1 : 0;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_EQZ) {
        interp.stack[-1].i32_u = interp.stack[-1].i64_u == 0 ? 1 : 0;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_CLZ) {
        uint32_t arg = (--interp.stack)->i32_u;
        interp.stack++->i32_u = __builtin_clz(arg);
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_CTZ) {
        uint32_t arg = (--interp.stack)->i32_u;
        interp.stack++->i32_u = __builtin_ctz(arg);
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_POPCNT) {
        uint32_t arg = (--interp.stack)->i32_u;
        interp.stack++->i32_u = __builtin_popcount(arg);
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_CLZ) {
        uint64_t arg = (--interp.stack)->i32_u;
        interp.stack++->i32_u = __builtin_clz(arg);
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_CTZ) {
        uint64_t arg = (--interp.stack)->i32_u;
        interp.stack++->i32_u = __builtin_ctz(arg);
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_POPCNT) {
        uint64_t arg = (--interp.stack)->i64_u;
        interp.stack++->i32_u = __builtin_popcount(arg);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_ABS) {
        interp.stack[-1].f32 = fabsf(interp.stack[-1].f32);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_NEG) {
        interp.stack[-1].f32 = -interp.stack[-1].f32;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_CEIL) {
        interp.stack[-1].f32 = ceilf(interp.stack[-1].f32);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_FLOOR) {
        interp.stack[-1].f32 = floorf(interp.stack[-1].f32);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_TRUNC) {
        interp.stack[-1].f32 = truncf(interp.stack[-1].f32);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_NEAREST) {
        interp.stack[-1].f32 = nearbyintf(interp.stack[-1].f32);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_SQRT) {
        interp.stack[-1].f32 = sqrt(interp.stack[-1].f32);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_ABS) {
        interp.stack[-1].f64 = fabs(interp.stack[-1].f64);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_NEG) {
        interp.stack[-1].f64 = -interp.stack[-1].f64;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_CEIL) {
        interp.stack[-1].f64 = ceil(interp.stack[-1].f64);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_FLOOR) {
        interp.stack[-1].f64 = floor(interp.stack[-1].f64);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_TRUNC) {
        interp.stack[-1].f64 = trunc(interp.stack[-1].f64);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_NEAREST) {
        interp.stack[-1].f64 = nearbyint(interp.stack[-1].f64);
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_SQRT) {
        interp.stack[-1].f64 = sqrt(interp.stack[-1].f64);
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_WRAP_I64) {
        interp.stack[-1].i32_s = (int32_t)interp.stack[-1].i64_s;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_TRUNC_S_F32) {
        interp.stack[-1].i32_s = (int32_t)interp.stack[-1].f32;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_TRUNC_U_F32) {
        interp.stack[-1].i32_u = (uint32_t)interp.stack[-1].f32;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_TRUNC_S_F64) {
        interp.stack[-1].i32_s = (int32_t)interp.stack[-1].f64;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I32_TRUNC_U_F64) {
        interp.stack[-1].i32_u = (uint32_t)interp.stack[-1].f64;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_EXTEND_S_I32) {
        interp.stack[-1].i64_s = (int64_t)interp.stack[-1].i64_s;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_EXTEND_U_I32) {
        interp.stack[-1].i64_u = (uint64_t)interp.stack[-1].i64_u;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_TRUNC_S_F32) {
        interp.stack[-1].i64_s = (int64_t)interp.stack[-1].f32;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_TRUNC_U_F32) {
        interp.stack[-1].i64_u = (uint64_t)interp.stack[-1].f32;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_TRUNC_S_F64) {
        interp.stack[-1].i64_s = (int64_t)interp.stack[-1].f64;
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_TRUNC_U_F64) {
        interp.stack[-1].i64_u = (uint64_t)interp.stack[-1].f64;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_CONVERT_S_I32) {
        interp.stack[-1].f32 = (float)interp.stack[-1].i32_s;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_CONVERT_U_I32) {
        interp.stack[-1].f32 = (float)interp.stack[-1].i32_u;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_CONVERT_S_I64) {
        interp.stack[-1].f32 = (float)interp.stack[-1].i64_s;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_CONVERT_U_I64) {
        interp.stack[-1].f32 = (float)interp.stack[-1].i64_u;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_DEMOTE_F64) {
        interp.stack[-1].f32 = (float)interp.stack[-1].f64;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_CONVERT_S_I32) {
        interp.stack[-1].f64 = (double)interp.stack[-1].i32_s;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_CONVERT_U_I32) {
        interp.stack[-1].f64 = (double)interp.stack[-1].i32_u;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_CONVERT_S_I64) {
        interp.stack[-1].f64 = (double)interp.stack[-1].i64_s;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_CONVERT_U_I64) {
        interp.stack[-1].f64 = (double)interp.stack[-1].i64_u;
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_PROMOTE_F32) {
        interp.stack[-1].f64 = (double)interp.stack[-1].f32;
    }
    LABEL(WEB49_OPCODE_I32_REINTERPRET_F32) {
        NEXT();
    }
    LABEL(WEB49_OPCODE_I64_REINTERPRET_F64) {
        NEXT();
    }
    LABEL(WEB49_OPCODE_F32_REINTERPRET_I32) {
        NEXT();
    }
    LABEL(WEB49_OPCODE_F64_REINTERPRET_I64) {
        NEXT();
    }
    LABEL(WEB49_OPCODE_MEMORY_INIT) {
        fprintf(stderr, "no impl for: %s\n", "memory_init");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_MEMORY_COPY) {
        fprintf(stderr, "no impl for: %s\n", "memory_copy");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_MEMORY_FILL) {
        fprintf(stderr, "no impl for: %s\n", "memory_fill");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_DATA_DROP) {
        fprintf(stderr, "no impl for: %s\n", "data_drop");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_TABLE_INIT) {
        fprintf(stderr, "no impl for: %s\n", "table_init");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_ELEM_DROP) {
        fprintf(stderr, "no impl for: %s\n", "elem_drop");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_TABLE_COPY) {
        fprintf(stderr, "no impl for: %s\n", "table_copy");
        __builtin_trap();
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
        *(uint32_t *)&interp.memory[result] = lseek(fd, offset, whence);
        interp.stack++->i32_u = 0;
        NEXT();
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
            *(uint32_t *)&interp.memory[argv + argc * 4] = head2;
            size_t memlen = strlen(interp.extra->args[i]) + 1;
            memcpy(&interp.memory[head2], interp.extra->args[i], memlen);
            head2 += memlen;
            argc += 1;
        }
        *(uint32_t *)&interp.memory[argv + argc * 4] = 0;
        interp.stack++->i32_u = 0;
        NEXT();
    }
    LABEL(WEB49_OPCODE_WASI_ARGS_SIZES_GET) {
        uint32_t argc = interp.locals[0].i32_u;
        uint32_t buf_size = interp.locals[1].i32_u;
        uint32_t buf_len = 0;
        size_t i = 0;
        while (interp.extra->args[i] != NULL) {
            buf_len += strlen(interp.extra->args[i]) + 1;
            i += 1;
        }
        *(uint32_t *)&interp.memory[argc] = i;
        *(uint32_t *)&interp.memory[buf_size] = buf_len;
        interp.stack++->i32_u = 0;
        NEXT();
    }
    LABEL(WEB49_OPCODE_WASI_CLOCK_RES_GET) {
        fprintf(stderr, "no impl for: wasi %s", "wasi_clock_res_get");
        __builtin_trap();
    }
    LABEL(WEB49_OPCODE_WASI_CLOCK_TIME_GET) {
        uint32_t wasi_clock_id = interp.locals[0].i32_u;
        uint64_t precision = interp.locals[1].i64_u;
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
        *(uint64_t *)&interp.memory[time] = (uint64_t)ts.tv_sec * UINT64_C(1000000000) + (uint64_t)ts.tv_nsec;
        interp.stack++->i32_u = 0;
        NEXT();
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
        interp.stack++->i32_u = close(fd);
        NEXT();
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
        *(uint16_t *)&interp.memory[fdstat + 0] = fs_filetype;
        *(uint16_t *)&interp.memory[fdstat + 2] = fs_flags;
        *(uint32_t *)&interp.memory[fdstat + 4] = 0;
        *(uint64_t *)&interp.memory[fdstat + 8] = fs_rights_base;
        *(uint64_t *)&interp.memory[fdstat + 16] = fs_rights_inheriting;
        interp.stack++->i32_u = 0;
        NEXT();
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
        *(uint32_t *)&interp.memory[nwritten] = 0;
        for (size_t i = 0; i < iovs_len; i++) {
            uint32_t ptr = *(uint32_t *)&interp.memory[iovs + i * 8];
            uint32_t len = *(uint32_t *)&interp.memory[iovs + i * 8 + 4];
            *(uint32_t *)&interp.memory[nwritten] += write(fd, &interp.memory[ptr], len);
        }
        interp.stack++->i32_u = 0;
        NEXT();
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
#if defined(WEB49_COUNT_INSTR)
    for (size_t i = 0; i < WEB49_MAX_OPCODE_INTERP_NUM; i++) {
        if (interp.names[i] != NULL) {
            fprintf(stderr, "%"PRIu64" of %s\n", interp.count[i], interp.names[i]+strlen("WEB49_OPCODE_"));
        }
    }
#endif
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
#define BLOCK(NAME) LABEL(NAME##_TO_STACK)
#define RHS (--interp.stack)
#define LHS (--interp.stack)
#define OUT(t) interp.stack++->t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_CONST_TO_STACK)
#define RHS (&head++->data)
#define LHS (--interp.stack)
#define OUT(t) interp.stack++->t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_LOCAL_TO_STACK)
#define RHS (&interp.locals[head++->data.i32_u])
#define LHS (--interp.stack)
#define OUT(t) interp.stack++->t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_CONST_NEXT_LOCAL_TO_STACK)
#define RHS (&head++->data)
#define LHS (&interp.locals[head++->data.i32_u])
#define OUT(t) interp.stack++->t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_LOCAL_NEXT_LOCAL_TO_STACK)
#define RHS (&interp.locals[head++->data.i32_u])
#define LHS (&interp.locals[head++->data.i32_u])
#define OUT(t) interp.stack++->t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TO_LOCAL)
#define RHS (--interp.stack)
#define LHS (--interp.stack)
#define OUT(t) interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_CONST_TO_LOCAL)
#define RHS (&head++->data)
#define LHS (--interp.stack)
#define OUT(t) interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_LOCAL_TO_LOCAL)
#define RHS (&interp.locals[head++->data.i32_u])
#define LHS (--interp.stack)
#define OUT(t) interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_CONST_NEXT_LOCAL_TO_LOCAL)
#define RHS (&head++->data)
#define LHS (&interp.locals[head++->data.i32_u])
#define OUT(t) interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_LOCAL_NEXT_LOCAL_TO_LOCAL)
#define RHS (&interp.locals[head++->data.i32_u])
#define LHS (&interp.locals[head++->data.i32_u])
#define OUT(t) interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TO_STACK_AND_LOCAL)
#define RHS (--interp.stack)
#define LHS (--interp.stack)
#define OUT(t) interp.stack++->t = interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_CONST_TO_STACK_AND_LOCAL)
#define RHS (&head++->data)
#define LHS (--interp.stack)
#define OUT(t) interp.stack++->t = interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_LOCAL_TO_STACK_AND_LOCAL)
#define RHS (&interp.locals[head++->data.i32_u])
#define LHS (--interp.stack)
#define OUT(t) interp.stack++->t = interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_CONST_NEXT_LOCAL_TO_STACK_AND_LOCAL)
#define RHS (&head++->data)
#define LHS (&interp.locals[head++->data.i32_u])
#define OUT(t) interp.stack++->t = interp.locals[head++->data.i32_u].t
#include "impl.inc"

#define BLOCK(NAME) LABEL(NAME##_TOP_LOCAL_NEXT_LOCAL_TO_STACK_AND_LOCAL)
#define RHS (&interp.locals[head++->data.i32_u])
#define LHS (&interp.locals[head++->data.i32_u])
#define OUT(t) interp.stack++->t = interp.locals[head++->data.i32_u].t
#include "impl.inc"
}

void web49_interp_module(web49_module_t mod, const char **args) {
    web49_section_type_t type_section = {0};
    web49_section_import_t import_section = {0};
    web49_section_code_t code_section = {0};
    web49_section_function_t function_section = {0};
    web49_section_global_t global_section = {0};
    web49_section_data_t data_section = {0};
    web49_section_table_t table_section = {0};
    web49_section_element_t element_section = {0};
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
    web49_interp_data_t *stack = web49_alloc0(sizeof(web49_interp_data_t) * (1 << 16));
    uint64_t memsize = 65536 * 256;
    uint8_t *memory = web49_alloc0(memsize);
#if defined(WEB49_COUNT_INSTR)
    uint64_t opcode[WEB49_MAX_OPCODE_INTERP_NUM] = {0};
    const char *names[WEB49_MAX_OPCODE_INTERP_NUM] = {0};
#endif
    uint64_t *data[256];
    web49_interp_t interp = (web49_interp_t) {
        .locals = stack,
        .stack = stack + 256,
        .memory = memory,
        .extra = &(web49_interp_extra_t){
            .table = NULL,
            .funcs = web49_malloc(sizeof(web49_interp_block_t) * num_funcs),
            .globals = web49_alloc0(sizeof(web49_interp_data_t) * (global_section.num_entries)),
            .args = args,
            .memsize = memsize,
            .data = &data[0],
            .type_section = type_section,
            .import_section = import_section,
            .code_section = code_section,
            .function_section = function_section,
            .global_section = global_section,
            .data_section = data_section,
            .table_section = table_section,
            .element_section = element_section,
        },
#if defined(WEB49_COUNT_INSTR)
        .count = &opcode[0],
        .names = &names[0],
#endif
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
        memcpy(&memory[entry.offset.immediate.varint32], entry.data, entry.size);
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
    web49_interp_block_t *func = &interp.extra->funcs[start];
    web49_interp_data_t *old_locals = interp.locals;
    web49_interp_data_t *old_stack = interp.stack;
    interp.locals = interp.stack - func->nparams;
    for (uint64_t i = 0; i < func->nlocals; i++) {
        interp.stack++->i64_u = 0;
    }
    web49_interp_block_run(interp, func);
    interp.stack = old_stack - func->nparams + func->nreturns;
    interp.locals = old_locals;
#if defined(WEB49_COUNT_INSTR)
    for (size_t i = 0; i < WEB49_MAX_OPCODE_INTERP_NUM; i++) {
        if (interp.names[i] != NULL) {
            fprintf(stderr, "%"PRIu64" of %s\n", interp.count[i], interp.names[i]+strlen("WEB49_OPCODE_"));
        }
    }
#endif
}
