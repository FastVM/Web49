#include "interp.h"

#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "../tables.h"

const char *web49_interp_opcode_to_name(size_t opcode) {
    if (opcode < WEB49_MAX_OPCODE_NUM) {
        return web49_opcode_to_name(opcode);
    } else if (opcode == WEB49_OPCODE_BLOCK_RETURNS) {
        return "block_returns";
    } else if (opcode == WEB49_OPCODE_IF_RETURNS) {
        return "if_returns";
    } else if (opcode == WEB49_OPCODE_WASI_FD_SEEK) {
        return "fd_seek";
    } else if (opcode == WEB49_OPCODE_WASI_FD_FILESTAT_GET) {
        return "fd_filestat_get";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_FILESTAT_GET) {
        return "path_filestat_get";
    } else if (opcode == WEB49_OPCODE_WASI_ARGS_GET) {
        return "args_get";
    } else if (opcode == WEB49_OPCODE_WASI_ARGS_SIZES_GET) {
        return "args_sizes_get";
    } else if (opcode == WEB49_OPCODE_WASI_CLOCK_RES_GET) {
        return "clock_res_get";
    } else if (opcode == WEB49_OPCODE_WASI_CLOCK_TIME_GET) {
        return "clock_time_get";
    } else if (opcode == WEB49_OPCODE_WASI_ENVIRON_GET) {
        return "environ_get";
    } else if (opcode == WEB49_OPCODE_WASI_ENVIRON_SIZES_GET) {
        return "environ_sizes_get";
    } else if (opcode == WEB49_OPCODE_WASI_FD_ADVISE) {
        return "fd_advise";
    } else if (opcode == WEB49_OPCODE_WASI_FD_ALLOCATE) {
        return "fd_allocate";
    } else if (opcode == WEB49_OPCODE_WASI_FD_CLOSE) {
        return "fd_close";
    } else if (opcode == WEB49_OPCODE_WASI_FD_DATASYNC) {
        return "fd_datasync";
    } else if (opcode == WEB49_OPCODE_WASI_FD_FDSTAT_GET) {
        return "fd_fdstat_get";
    } else if (opcode == WEB49_OPCODE_WASI_FD_FDSTAT_SET_FLAGS) {
        return "fd_fdstat_set_flags";
    } else if (opcode == WEB49_OPCODE_WASI_FD_FDSTAT_SET_RIGHTS) {
        return "fd_fdstat_set_rights";
    } else if (opcode == WEB49_OPCODE_WASI_FD_FILESTAT_SET_SIZE) {
        return "fd_filestat_set_size";
    } else if (opcode == WEB49_OPCODE_WASI_FD_FILESTAT_SET_TIMES) {
        return "fd_filestat_set_times";
    } else if (opcode == WEB49_OPCODE_WASI_FD_PREAD) {
        return "fd_pread";
    } else if (opcode == WEB49_OPCODE_WASI_FD_PRESTAT_GET) {
        return "fd_prestat_get";
    } else if (opcode == WEB49_OPCODE_WASI_FD_PRESTAT_DIR_NAME) {
        return "fd_prestat_dir_name";
    } else if (opcode == WEB49_OPCODE_WASI_FD_PWRITE) {
        return "fd_pwrite";
    } else if (opcode == WEB49_OPCODE_WASI_FD_READ) {
        return "fd_read";
    } else if (opcode == WEB49_OPCODE_WASI_FD_READDIR) {
        return "fd_readdir";
    } else if (opcode == WEB49_OPCODE_WASI_FD_RENUMBER) {
        return "fd_renumber";
    } else if (opcode == WEB49_OPCODE_WASI_FD_SYNC) {
        return "fd_sync";
    } else if (opcode == WEB49_OPCODE_WASI_FD_TELL) {
        return "fd_tell";
    } else if (opcode == WEB49_OPCODE_WASI_FD_WRITE) {
        return "fd_write";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_CREATE_DIRECTORY) {
        return "path_create_directory";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_FILESTAT_SET_TIMES) {
        return "path_filestat_set_times";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_LINK) {
        return "path_link";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_OPEN) {
        return "path_open";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_READLINK) {
        return "path_readlink";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_REMOVE_DIRECTORY) {
        return "path_remove_directory";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_RENAME) {
        return "path_rename";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_SYMLINK) {
        return "path_symlink";
    } else if (opcode == WEB49_OPCODE_WASI_PATH_UNLINK_FILE) {
        return "path_unlink_file";
    } else if (opcode == WEB49_OPCODE_WASI_POLL_ONEOFF) {
        return "poll_oneoff";
    } else if (opcode == WEB49_OPCODE_WASI_PROC_EXIT) {
        return "proc_exit";
    } else if (opcode == WEB49_OPCODE_WASI_PROC_RAISE) {
        return "proc_raise";
    } else if (opcode == WEB49_OPCODE_WASI_RANDOM_GET) {
        return "random_get";
    } else if (opcode == WEB49_OPCODE_WASI_SCHED_YIELD) {
        return "sched_yield";
    } else if (opcode == WEB49_OPCODE_WASI_SOCK_RECV) {
        return "sock_recv";
    } else if (opcode == WEB49_OPCODE_WASI_SOCK_SEND) {
        return "sock_send";
    } else if (opcode == WEB49_OPCODE_WASI_SOCK_SHUTDOWN) {
        return "sock_shutdown";
    } else {
        return NULL;
    }
}

web49_interp_block_t *web49_interp_import(web49_interp_t *interp, const char *mod, const char *sym) {
    (void)interp;
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
        web49_interp_opcode_t *instrs = web49_malloc(sizeof(web49_interp_opcode_t) * 2);
        instrs[0].opcode = iit;
        instrs[1].opcode = WEB49_OPCODE_RETURN;
        web49_interp_block_t *block = web49_malloc(sizeof(web49_interp_block_t));
        block->code = instrs;
        block->nlocals = 0;
        block->nreturns = nreturns;
        block->nparams = nargs;
        return block;
    }
    fprintf(stderr, "unknown import module: %s\n", mod);
    exit(1);
}


web49_interp_block_t *web49_interp_read_block(web49_read_block_state_t *state) {
    web49_interp_instr_buf_t *instrs = &state->instrs;
    bool isfunc = instrs->head == 0;
    uint64_t alloc = 128;
    web49_interp_opcode_t *code = web49_malloc(sizeof(web49_interp_opcode_t) * alloc);
    uint64_t ncode = 0;
    while (instrs->head < instrs->len) {
        web49_instr_t cur = instrs->instrs[instrs->head++];
        if (cur.opcode == WEB49_OPCODE_END || cur.opcode == WEB49_OPCODE_ELSE) {
            break;
        }
        if (cur.opcode == WEB49_OPCODE_NOP) {
            continue;
        }
        if (ncode + 64 >= alloc) {
            alloc = (ncode + 64) * 2;
            code = web49_realloc(code, sizeof(web49_interp_opcode_t) * alloc);
        }
        if (cur.immediate.id == WEB49_IMMEDIATE_BLOCK_TYPE && cur.immediate.block_type != WEB49_TYPE_BLOCK_TYPE) {
            if (cur.opcode == WEB49_OPCODE_BLOCK) {
                code[ncode++].opcode = WEB49_OPCODE_BLOCK_RETURNS;
                code[ncode++].block = web49_interp_read_block(state);
                continue;
            } else if (cur.opcode == WEB49_OPCODE_IF) {
                code[ncode++].opcode = WEB49_OPCODE_IF_RETURNS;
                code[ncode++].block = web49_interp_read_block(state);
                if (instrs->instrs[instrs->head - 1].opcode == WEB49_OPCODE_ELSE) {
                    code[ncode++].block = web49_interp_read_block(state);
                } else {
                    fprintf(stderr, "if returns one value, has empty else. this will not work.");
                    __builtin_trap();
                }
                continue;
            } else {
                fprintf(stderr, "opcode %zu returns value, no clue how to compile that\n", (size_t)cur.opcode);
                __builtin_trap();
            }
        }
        code[ncode++].opcode = cur.opcode;
        switch (cur.immediate.id) {
            case WEB49_IMMEDIATE_NONE:
                break;
            case WEB49_IMMEDIATE_BLOCK_TYPE:
                break;
            case WEB49_IMMEDIATE_VARUINT1:
                break;
            case WEB49_IMMEDIATE_VARUINT32:
                code[ncode++].data.i32_u = cur.immediate.varuint32;
                break;
            case WEB49_IMMEDIATE_VARUINT64:
                code[ncode++].data.i64_u = cur.immediate.varuint64;
                break;
            case WEB49_IMMEDIATE_VARINT32:
                code[ncode++].data.i32_s = cur.immediate.varint32;
                break;
            case WEB49_IMMEDIATE_VARINT64:
                code[ncode++].data.i64_s = cur.immediate.varint64;
                break;
            case WEB49_IMMEDIATE_UINT32:
                code[ncode++].data.i32_u = cur.immediate.uint32;
                break;
            case WEB49_IMMEDIATE_UINT64:
                code[ncode++].data.i64_u = cur.immediate.uint64;
                break;
            case WEB49_IMMEDIATE_BR_TABLE:
                code[ncode++].data.i32_u = cur.immediate.br_table.num_targets;
                for (uint64_t i = 0; i < cur.immediate.br_table.num_targets; i++) {
                    code[ncode++].data.i32_u = cur.immediate.br_table.targets[i];
                }
                code[ncode++].data.i32_u = cur.immediate.br_table.default_target;
                break;
            case WEB49_IMMEDIATE_CALL_INDIRECT:
                break;
            case WEB49_IMMEDIATE_MEMORY_IMMEDIATE:
                code[ncode++].data.i32_u = cur.immediate.memory_immediate.offset;
                break;
            default:
                fprintf(stderr, "bad immediate: %zu\n", (size_t)cur.immediate.id);
                __builtin_trap();
        }
        if (cur.opcode == WEB49_OPCODE_BLOCK || cur.opcode == WEB49_OPCODE_LOOP) {
            code[ncode++].block = web49_interp_read_block(state);
        }
        if (cur.opcode == WEB49_OPCODE_IF) {
            code[ncode++].block = web49_interp_read_block(state);
            if (instrs->instrs[instrs->head - 1].opcode == WEB49_OPCODE_ELSE) {
                code[ncode++].block = web49_interp_read_block(state);
            } else {
                web49_interp_opcode_t *instrs = web49_malloc(sizeof(web49_interp_opcode_t));
                instrs[0].opcode = WEB49_OPCODE_END;
                web49_interp_block_t *block = web49_malloc(sizeof(web49_interp_block_t));
                block->code = instrs;
                block->nlocals = 0;
                block->nparams = 0;
                code[ncode++].block = block;
            }
        }
    }
    if (isfunc) {
        code[ncode++].opcode = WEB49_OPCODE_RETURN;
    } else {
        code[ncode++].opcode = WEB49_OPCODE_END;
    }
    web49_interp_block_t *block = web49_malloc(sizeof(web49_interp_block_t));
    block->code = code;
    block->nlocals = 0;
    block->nparams = 0;
    return block;
}

int32_t web49_interp_block_run(web49_interp_t interp, web49_interp_block_t *block) {
    web49_interp_opcode_t *head = block->code;
    while (true) {
        switch (head++->opcode) {
            case WEB49_OPCODE_UNREACHABLE: {
                fprintf(stderr, "unreachable was reached\n");
                __builtin_trap();
            }
            case WEB49_OPCODE_NOP: {
                break;
            }
            case WEB49_OPCODE_BLOCK: {
                int32_t ret = web49_interp_block_run(interp, head++->block);
                if (ret >= 0) {
                    return ret - 1;
                }
                break;
            }
            case WEB49_OPCODE_LOOP: {
                while (true) {
                    int32_t ret = web49_interp_block_run(interp, head->block);
                    if (ret == -1) {
                        continue;
                    } else if (ret >= 0) {
                        return ret - 1;
                    } else {
                        break;
                    }
                }
                head += 1;
                break;
            }
            case WEB49_OPCODE_IF: {
                int32_t ret;
                if ((--interp.stack)->i32_u) {
                    ret = web49_interp_block_run(interp, head[0].block);
                } else {
                    ret = web49_interp_block_run(interp, head[1].block);
                }
                if (ret >= 0) {
                    return ret - 1;
                }
                head += 2;
                break;
            }
            case WEB49_OPCODE_ELSE: {
                fprintf(stderr, "no impl for: %s\n", "else");
                __builtin_trap();
            }
            case WEB49_OPCODE_END: {
                interp.returns[0] = interp.stack[-1];
                return INT32_MIN;
            }
            case WEB49_OPCODE_BR: {
                interp.returns[0] = interp.stack[-1];
                return head[0].data.i32_u - 1;
            }
            case WEB49_OPCODE_BR_IF: {
                if ((--interp.stack)->i32_u) {
                    interp.returns[0] = interp.stack[-1];
                    return head[0].data.i32_u - 1;
                }
                head += 1;
                break;
            }
            case WEB49_OPCODE_BR_TABLE: {
                web49_interp_data_t data = *--interp.stack;
                uint32_t max = head++->data.i32_u;
                interp.returns[0] = interp.stack[-1];
                if (data.i32_u >= max) {
                    return head[max].data.i32_u - 1;
                } else {
                    return head[data.i32_u].data.i32_u - 1;
                }
                break;
            }
            case WEB49_OPCODE_RETURN: {
                interp.returns[0] = interp.stack[-1];
                return INT32_MAX;
            }
            case WEB49_OPCODE_CALL: {
                uint32_t funcno = head++->data.i32_u;
                web49_interp_block_t *func = interp.funcs[funcno];
                web49_interp_data_t *old_locals = interp.locals;
                web49_interp_data_t *old_stack = interp.stack;
                interp.locals = interp.stack - func->nparams;
                memset(interp.stack, 0, func->nlocals * sizeof(web49_interp_data_t));
                interp.stack += func->nlocals;
                web49_interp_block_run(interp, func);
                interp.stack = old_stack - func->nparams;
                switch (func->nreturns) {
                case 0:
                    break;
                case 1:
                    *interp.stack++ = interp.returns[0];
                    break;
                default:
                    __builtin_unreachable();
                }
                interp.locals = old_locals;
                break;
            }
            case WEB49_OPCODE_CALL_INDIRECT: {
                uint32_t funcno = (--interp.stack)->i32_u;
                web49_interp_block_t *func = interp.table[funcno];
                web49_interp_data_t *old_locals = interp.locals;
                web49_interp_data_t *old_stack = interp.stack;
                interp.locals = interp.stack - func->nparams;
                memset(interp.stack, 0, func->nlocals * sizeof(web49_interp_data_t));
                interp.stack += func->nlocals;
                web49_interp_block_run(interp, func);
                interp.stack = old_stack - func->nparams;
                switch (func->nreturns) {
                case 0:
                    break;
                case 1:
                    *interp.stack++ = interp.returns[0];
                    break;
                default:
                    __builtin_unreachable();
                }
                interp.locals = old_locals;
                break;
            }
            case WEB49_OPCODE_DROP: {
                interp.stack -= 1;
                break;
            }
            case WEB49_OPCODE_SELECT: {
                web49_interp_data_t cond = *--interp.stack;
                web49_interp_data_t iff = *--interp.stack;
                web49_interp_data_t ift = *--interp.stack;
                if (cond.i32_u) {
                    *interp.stack++ = ift;
                } else {
                    *interp.stack++ = iff;
                }
                break;
            }
            case WEB49_OPCODE_GET_LOCAL: {
                *interp.stack++ = interp.locals[head++->data.i32_u];
                break;
            }
            case WEB49_OPCODE_SET_LOCAL: {
                interp.locals[head++->data.i32_u] = *--interp.stack;
                break;
            }
            case WEB49_OPCODE_TEE_LOCAL: {
                interp.locals[head++->data.i32_u] = interp.stack[-1];
                break;
            }
            case WEB49_OPCODE_GET_GLOBAL: {
                *interp.stack++ = interp.globals[head++->data.i32_u];
                break;
            }
            case WEB49_OPCODE_SET_GLOBAL: {
                interp.globals[head++->data.i32_u] = *--interp.stack;
                break;
            }
            case WEB49_OPCODE_I32_LOAD: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i32_u = *(uint32_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I64_LOAD: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i64_u = *(uint64_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_F32_LOAD: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->f32 = *(float *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_F64_LOAD: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->f64 = *(double *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I32_LOAD8_S: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i32_s = (int32_t) *(int8_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I32_LOAD8_U: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i32_u = (uint32_t) *(uint8_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I32_LOAD16_S: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i32_s = (int32_t) *(int16_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I32_LOAD16_U: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i32_u = (uint32_t) *(uint16_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I64_LOAD8_S: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i64_s = (int64_t) *(int8_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I64_LOAD8_U: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i64_u = (uint64_t) *(uint8_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I64_LOAD16_S: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i64_s = (int64_t) *(int16_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I64_LOAD16_U: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i64_u = (uint64_t) *(uint16_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I64_LOAD32_S: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i64_s = (int64_t) *(int32_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I64_LOAD32_U: {
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                interp.stack++->i64_u = (uint64_t) *(uint32_t *)&interp.memory[ptr + off];
                break;
            }
            case WEB49_OPCODE_I32_STORE: {
                uint32_t val = (--interp.stack)->i32_u;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(uint32_t *)&interp.memory[ptr + off] = (uint32_t)val;
                break;
            }
            case WEB49_OPCODE_I64_STORE: {
                uint64_t val = (--interp.stack)->i64_u;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(uint64_t *)&interp.memory[ptr + off] = (uint64_t)val;
                break;
            }
            case WEB49_OPCODE_F32_STORE: {
                float val = (--interp.stack)->f32;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(float *)&interp.memory[ptr + off] = (float)val;
                break;
            }
            case WEB49_OPCODE_F64_STORE: {
                double val = (--interp.stack)->f64;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(double *)&interp.memory[ptr + off] = (double)val;
                break;
            }
            case WEB49_OPCODE_I32_STORE8: {
                uint32_t val = (--interp.stack)->i32_u;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(uint8_t *)&interp.memory[ptr + off] = (uint8_t)val;
                break;
            }
            case WEB49_OPCODE_I32_STORE16: {
                uint32_t val = (--interp.stack)->i32_u;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(uint16_t *)&interp.memory[ptr + off] = (uint16_t)val;
                break;
            }
            case WEB49_OPCODE_I64_STORE8: {
                uint64_t val = (--interp.stack)->i64_u;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(uint8_t *)&interp.memory[ptr + off] = (uint8_t)val;
                break;
            }
            case WEB49_OPCODE_I64_STORE16: {
                uint64_t val = (--interp.stack)->i64_u;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(uint16_t *)&interp.memory[ptr + off] = (uint16_t)val;
                break;
            }
            case WEB49_OPCODE_I64_STORE32: {
                uint64_t val = (--interp.stack)->i64_u;
                uint32_t ptr = (--interp.stack)->i32_u;
                uint32_t off = head++->data.i32_u;
                *(uint32_t *)&interp.memory[ptr + off] = (uint32_t)val;
                break;
            }
            case WEB49_OPCODE_MEMORY_SIZE: {
                interp.stack++->i32_u = (interp.memsize) / (1<<16);
                break;
            }
            case WEB49_OPCODE_MEMORY_GROW: {
                uint32_t oldsize = (interp.memsize) / (1<<16);
                uint32_t newsize = (--interp.stack)->i32_u;
                interp.memory = web49_realloc(interp.memory, (oldsize + newsize) * (1<<16));
                interp.stack++->i32_u = oldsize;
                break;
            }
            case WEB49_OPCODE_I32_CONST: {
                interp.stack++->i32_s = head++->data.i32_s;
                break;
            }
            case WEB49_OPCODE_I64_CONST: {
                interp.stack++->i64_s = head++->data.i64_s;
                break;
            }
            case WEB49_OPCODE_F32_CONST: {
                interp.stack++->f32 = head++->data.f32;
                break;
            }
            case WEB49_OPCODE_F64_CONST: {
                interp.stack++->f64 = head++->data.f64;
                break;
            }
            case WEB49_OPCODE_I32_EQZ: {
                interp.stack[-1].i32_u = interp.stack[-1].i32_u == 0 ? 1 : 0;
                break;
            }
            case WEB49_OPCODE_I32_EQ: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs == rhs);
                break;
            }
            case WEB49_OPCODE_I32_NE: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs != rhs);
                break;
            }
            case WEB49_OPCODE_I32_LT_S: {
                int32_t rhs = (--interp.stack)->i32_s;
                int32_t lhs = (--interp.stack)->i32_s;
                interp.stack++->i32_u = (uint32_t)(lhs < rhs);
                break;
            }
            case WEB49_OPCODE_I32_LT_U: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs < rhs);
                break;
            }
            case WEB49_OPCODE_I32_GT_S: {
                int32_t rhs = (--interp.stack)->i32_s;
                int32_t lhs = (--interp.stack)->i32_s;
                interp.stack++->i32_u = (uint32_t)(lhs > rhs);
                break;
            }
            case WEB49_OPCODE_I32_GT_U: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs > rhs);
                break;
            }
            case WEB49_OPCODE_I32_LE_S: {
                int32_t rhs = (--interp.stack)->i32_s;
                int32_t lhs = (--interp.stack)->i32_s;
                interp.stack++->i32_u = (uint32_t)(lhs <= rhs);
                break;
            }
            case WEB49_OPCODE_I32_LE_U: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs <= rhs);
                break;
            }
            case WEB49_OPCODE_I32_GE_S: {
                int32_t rhs = (--interp.stack)->i32_s;
                int32_t lhs = (--interp.stack)->i32_s;
                interp.stack++->i32_u = (uint32_t)(lhs >= rhs);
                break;
            }
            case WEB49_OPCODE_I32_GE_U: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs >= rhs);
                break;
            }
            case WEB49_OPCODE_I64_EQZ: {
                interp.stack[-1].i32_u = interp.stack[-1].i64_u == 0 ? 1 : 0;
                break;
            }
            case WEB49_OPCODE_I64_EQ: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i32_u = (uint32_t)(lhs == rhs);
                break;
            }
            case WEB49_OPCODE_I64_NE: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i32_u = (uint32_t)(lhs != rhs);
                break;
            }
            case WEB49_OPCODE_I64_LT_S: {
                int64_t rhs = (--interp.stack)->i64_s;
                int64_t lhs = (--interp.stack)->i64_s;
                interp.stack++->i32_u = (uint32_t)(lhs < rhs);
                break;
            }
            case WEB49_OPCODE_I64_LT_U: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i32_u = (uint32_t)(lhs < rhs);
                break;
            }
            case WEB49_OPCODE_I64_GT_S: {
                int64_t rhs = (--interp.stack)->i64_s;
                int64_t lhs = (--interp.stack)->i64_s;
                interp.stack++->i32_u = (uint32_t)(lhs > rhs);
                break;
            }
            case WEB49_OPCODE_I64_GT_U: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i32_u = (uint32_t)(lhs > rhs);
                break;
            }
            case WEB49_OPCODE_I64_LE_S: {
                int64_t rhs = (--interp.stack)->i64_s;
                int64_t lhs = (--interp.stack)->i64_s;
                interp.stack++->i32_u = (uint32_t)(lhs <= rhs);
                break;
            }
            case WEB49_OPCODE_I64_LE_U: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i32_u = (uint32_t)(lhs <= rhs);
                break;
            }
            case WEB49_OPCODE_I64_GE_S: {
                int64_t rhs = (--interp.stack)->i64_s;
                int64_t lhs = (--interp.stack)->i64_s;
                interp.stack++->i32_u = (uint32_t)(lhs >= rhs);
                break;
            }
            case WEB49_OPCODE_I64_GE_U: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i32_u = (uint32_t)(lhs >= rhs);
                break;
            }
            case WEB49_OPCODE_F32_EQ: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->i32_u = (uint32_t)(lhs == rhs);
                break;
            }
            case WEB49_OPCODE_F32_NE: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->i32_u = (uint32_t)(lhs != rhs);
                break;
            }
            case WEB49_OPCODE_F32_LT: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->i32_u = (uint32_t)(lhs < rhs);
                break;
            }
            case WEB49_OPCODE_F32_GT: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->i32_u = (uint32_t)(lhs > rhs);
                break;
            }
            case WEB49_OPCODE_F32_LE: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->i32_u = (uint32_t)(lhs <= rhs);
                break;
            }
            case WEB49_OPCODE_F32_GE: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->i32_u = (uint32_t)(lhs >= rhs);
                break;
            }
            case WEB49_OPCODE_F64_EQ: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->i32_u = (uint32_t)(lhs == rhs);
                break;
            }
            case WEB49_OPCODE_F64_NE: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->i32_u = (uint32_t)(lhs != rhs);
                break;
            }
            case WEB49_OPCODE_F64_LT: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->i32_u = (uint32_t)(lhs < rhs);
                break;
            }
            case WEB49_OPCODE_F64_GT: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->i32_u = (uint32_t)(lhs > rhs);
                break;
            }
            case WEB49_OPCODE_F64_LE: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->i32_u = (uint32_t)(lhs <= rhs);
                break;
            }
            case WEB49_OPCODE_F64_GE: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->i32_u = (uint32_t)(lhs >= rhs);
                break;
            }
            case WEB49_OPCODE_I32_CLZ: {
                double arg = (--interp.stack)->f64;
                interp.stack++->i32_u = __builtin_clz(arg);
                break;
            }
            case WEB49_OPCODE_I32_CTZ: {
                double arg = (--interp.stack)->f64;
                interp.stack++->i32_u = __builtin_ctz(arg);
                break;
            }
            case WEB49_OPCODE_I32_POPCNT: {
                double arg = (--interp.stack)->f64;
                interp.stack++->i32_u = __builtin_popcount(arg);
                break;
            }
            case WEB49_OPCODE_I32_ADD: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs + rhs);
                break;
            }
            case WEB49_OPCODE_I32_SUB: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs - rhs);
                break;
            }
            case WEB49_OPCODE_I32_MUL: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs * rhs);
                break;
            }
            case WEB49_OPCODE_I32_DIV_S: {
                int32_t rhs = (--interp.stack)->i32_s;
                int32_t lhs = (--interp.stack)->i32_s;
                interp.stack++->i32_s = (lhs / rhs);
                break;
            }
            case WEB49_OPCODE_I32_DIV_U: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs / rhs);
                break;
            }
            case WEB49_OPCODE_I32_REM_S: {
                int32_t rhs = (--interp.stack)->i32_s;
                int32_t lhs = (--interp.stack)->i32_s;
                interp.stack++->i32_s = (lhs % rhs);
                break;
            }
            case WEB49_OPCODE_I32_REM_U: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs % rhs);
                break;
            }
            case WEB49_OPCODE_I32_AND: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs & rhs);
                break;
            }
            case WEB49_OPCODE_I32_OR: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs | rhs);
                break;
            }
            case WEB49_OPCODE_I32_XOR: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (uint32_t)(lhs ^ rhs);
                break;
            }
            case WEB49_OPCODE_I32_SHL: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs << rhs);
                break;
            }
            case WEB49_OPCODE_I32_SHR_S: {
                uint32_t rhs = (--interp.stack)->i32_u;
                int32_t lhs = (--interp.stack)->i32_s;
                interp.stack++->i64_s = (lhs >> rhs);
                break;
            }
            case WEB49_OPCODE_I32_SHR_U: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs >> rhs);
                break;
            }
            case WEB49_OPCODE_I32_ROTL: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs >> rhs) | (lhs << (32 - rhs));
                break;
            }
            case WEB49_OPCODE_I32_ROTR: {
                uint32_t rhs = (--interp.stack)->i32_u;
                uint32_t lhs = (--interp.stack)->i32_u;
                interp.stack++->i32_u = (lhs << rhs) | (lhs >> (32 - rhs));
                break;
            }
            case WEB49_OPCODE_I64_ADD: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs + rhs);
                break;
            }
            case WEB49_OPCODE_I64_SUB: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs - rhs);
                break;
            }
            case WEB49_OPCODE_I64_MUL: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs * rhs);
                break;
            }
            case WEB49_OPCODE_I64_DIV_S: {
                int64_t rhs = (--interp.stack)->i64_s;
                int64_t lhs = (--interp.stack)->i64_s;
                interp.stack++->i64_s = (lhs / rhs);
                break;
            }
            case WEB49_OPCODE_I64_DIV_U: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs / rhs);
                break;
            }
            case WEB49_OPCODE_I64_REM_S: {
                int64_t rhs = (--interp.stack)->i64_s;
                int64_t lhs = (--interp.stack)->i64_s;
                interp.stack++->i64_s = (lhs % rhs);
                break;
            }
            case WEB49_OPCODE_I64_REM_U: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs % rhs);
                break;
            }
            case WEB49_OPCODE_I64_AND: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (uint64_t)(lhs & rhs);
                break;
            }
            case WEB49_OPCODE_I64_OR: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (uint64_t)(lhs | rhs);
                break;
            }
            case WEB49_OPCODE_I64_XOR: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (uint64_t)(lhs ^ rhs);
                break;
            }
            case WEB49_OPCODE_I64_SHL: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs << rhs);
                break;
            }
            case WEB49_OPCODE_I64_SHR_S: {
                uint64_t rhs = (--interp.stack)->i64_u;
                int64_t lhs = (--interp.stack)->i64_s;
                interp.stack++->i64_s = (lhs >> rhs);
                break;
            }
            case WEB49_OPCODE_I64_SHR_U: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs >> rhs);
                break;
            }
            case WEB49_OPCODE_I64_ROTL: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs >> rhs) | (lhs << (64 - rhs));
                break;
            }
            case WEB49_OPCODE_I64_ROTR: {
                uint64_t rhs = (--interp.stack)->i64_u;
                uint64_t lhs = (--interp.stack)->i64_u;
                interp.stack++->i64_u = (lhs << rhs) | (lhs >> (64 - rhs));
                break;
            }
            case WEB49_OPCODE_F32_ABS: {
                interp.stack[-1].f32 = fabsf(interp.stack[-1].f32);
                break;
            }
            case WEB49_OPCODE_F32_NEG: {
                interp.stack[-1].f32 = -interp.stack[-1].f32;
                break;
            }
            case WEB49_OPCODE_F32_CEIL: {
                interp.stack[-1].f32 = ceilf(interp.stack[-1].f32);
                break;
            }
            case WEB49_OPCODE_F32_FLOOR: {
                interp.stack[-1].f32 = floorf(interp.stack[-1].f32);
                break;
            }
            case WEB49_OPCODE_F32_TRUNC: {
                interp.stack[-1].f32 = truncf(interp.stack[-1].f32);
                break;
            }
            case WEB49_OPCODE_F32_NEAREST: {
                interp.stack[-1].f32 = nearbyintf(interp.stack[-1].f32);
                break;
            }
            case WEB49_OPCODE_F32_SQRT: {
                interp.stack[-1].f32 = sqrt(interp.stack[-1].f32);
                break;
            }
            case WEB49_OPCODE_F32_ADD: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->f32 = lhs + rhs;
                break;
            }
            case WEB49_OPCODE_F32_SUB: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->f32 = lhs - rhs;
                break;
            }
            case WEB49_OPCODE_F32_MUL: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->f32 = lhs * rhs;
                break;
            }
            case WEB49_OPCODE_F32_DIV: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->f32 = lhs / rhs;
                break;
            }
            case WEB49_OPCODE_F32_MIN: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->f32 = fminf(lhs, rhs);
                break;
            }
            case WEB49_OPCODE_F32_MAX: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->f32 = fmaxf(lhs, rhs);
                break;
            }
            case WEB49_OPCODE_F32_COPYSIGN: {
                float rhs = (--interp.stack)->f32;
                float lhs = (--interp.stack)->f32;
                interp.stack++->f32 = copysignf(lhs, rhs);
                break;
            }
            case WEB49_OPCODE_F64_ABS: {
                interp.stack[-1].f64 = fabsf(interp.stack[-1].f64);
                break;
            }
            case WEB49_OPCODE_F64_NEG: {
                interp.stack[-1].f64 = -interp.stack[-1].f64;
                break;
            }
            case WEB49_OPCODE_F64_CEIL: {
                interp.stack[-1].f64 = ceil(interp.stack[-1].f64);
                break;
            }
            case WEB49_OPCODE_F64_FLOOR: {
                interp.stack[-1].f64 = floor(interp.stack[-1].f64);
                break;
            }
            case WEB49_OPCODE_F64_TRUNC: {
                interp.stack[-1].f64 = trunc(interp.stack[-1].f64);
                break;
            }
            case WEB49_OPCODE_F64_NEAREST: {
                interp.stack[-1].f64 = nearbyint(interp.stack[-1].f64);
                break;
            }
            case WEB49_OPCODE_F64_SQRT: {
                interp.stack[-1].f64 = sqrt(interp.stack[-1].f64);
                break;
            }
            case WEB49_OPCODE_F64_ADD: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->f64 = lhs + rhs;
                break;
            }
            case WEB49_OPCODE_F64_SUB: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->f64 = lhs - rhs;
                break;
            }
            case WEB49_OPCODE_F64_MUL: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->f64 = lhs * rhs;
                break;
            }
            case WEB49_OPCODE_F64_DIV: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->f64 = lhs / rhs;
                break;
            }
            case WEB49_OPCODE_F64_MIN: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->f64 = fmin(lhs, rhs);
                break;
            }
            case WEB49_OPCODE_F64_MAX: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->f64 = fmax(lhs, rhs);
                break;
            }
            case WEB49_OPCODE_F64_COPYSIGN: {
                double rhs = (--interp.stack)->f64;
                double lhs = (--interp.stack)->f64;
                interp.stack++->f64 = copysign(lhs, rhs);
                break;
            }
            case WEB49_OPCODE_I32_WRAP_I64: {
                interp.stack[-1].i32_s = (int32_t)interp.stack[-1].i64_s;
                break;
            }
            case WEB49_OPCODE_I32_TRUNC_S_F32: {
                interp.stack[-1].i32_s = (int32_t)interp.stack[-1].f32;
                break;
            }
            case WEB49_OPCODE_I32_TRUNC_U_F32: {
                interp.stack[-1].i32_u = (uint32_t)interp.stack[-1].f32;
                break;
            }
            case WEB49_OPCODE_I32_TRUNC_S_F64: {
                interp.stack[-1].i32_s = (int32_t)interp.stack[-1].f64;
                break;
            }
            case WEB49_OPCODE_I32_TRUNC_U_F64: {
                interp.stack[-1].i32_u = (uint32_t)interp.stack[-1].f64;
                break;
            }
            case WEB49_OPCODE_I64_EXTEND_S_I32: {
                interp.stack[-1].i64_s = (int64_t)interp.stack[-1].i64_s;
                break;
            }
            case WEB49_OPCODE_I64_EXTEND_U_I32: {
                interp.stack[-1].i64_u = (uint64_t)interp.stack[-1].i64_u;
                break;
            }
            case WEB49_OPCODE_I64_TRUNC_S_F32: {
                interp.stack[-1].i64_s = (int64_t)interp.stack[-1].f32;
                break;
            }
            case WEB49_OPCODE_I64_TRUNC_U_F32: {
                interp.stack[-1].i64_u = (uint64_t)interp.stack[-1].f32;
                break;
            }
            case WEB49_OPCODE_I64_TRUNC_S_F64: {
                interp.stack[-1].i64_u = (int64_t)interp.stack[-1].f64;
                break;
            }
            case WEB49_OPCODE_I64_TRUNC_U_F64: {
                interp.stack[-1].i64_u = (uint64_t)interp.stack[-1].f64;
                break;
            }
            case WEB49_OPCODE_F32_CONVERT_S_I32: {
                interp.stack[-1].f32 = (float)interp.stack[-1].i32_s;
                break;
            }
            case WEB49_OPCODE_F32_CONVERT_U_I32: {
                interp.stack[-1].f32 = (float)interp.stack[-1].i32_u;
                break;
            }
            case WEB49_OPCODE_F32_CONVERT_S_I64: {
                interp.stack[-1].f32 = (float)interp.stack[-1].i64_s;
                break;
            }
            case WEB49_OPCODE_F32_CONVERT_U_I64: {
                interp.stack[-1].f32 = (float)interp.stack[-1].i64_u;
                break;
            }
            case WEB49_OPCODE_F32_DEMOTE_F64: {
                interp.stack[-1].f32 = (float)interp.stack[-1].f64;
                break;
            }
            case WEB49_OPCODE_F64_CONVERT_S_I32: {
                interp.stack[-1].f64 = (double)interp.stack[-1].i32_s;
                break;
            }
            case WEB49_OPCODE_F64_CONVERT_U_I32: {
                interp.stack[-1].f64 = (double)interp.stack[-1].i32_u;
                break;
            }
            case WEB49_OPCODE_F64_CONVERT_S_I64: {
                interp.stack[-1].f64 = (double)interp.stack[-1].i64_s;
                break;
            }
            case WEB49_OPCODE_F64_CONVERT_U_I64: {
                interp.stack[-1].f64 = (double)interp.stack[-1].i64_u;
                break;
            }
            case WEB49_OPCODE_F64_PROMOTE_F32: {
                interp.stack[-1].f64 = (double)interp.stack[-1].f32;
            }
            case WEB49_OPCODE_I32_REINTERPRET_F32: {
                break;
            }
            case WEB49_OPCODE_I64_REINTERPRET_F64: {
                break;
            }
            case WEB49_OPCODE_F32_REINTERPRET_I32: {
                break;
            }
            case WEB49_OPCODE_F64_REINTERPRET_I64: {
                break;
            }
            case WEB49_OPCODE_MEMORY_INIT: {
                fprintf(stderr, "no impl for: %s\n", "memory_init");
                __builtin_trap();
            }
            case WEB49_OPCODE_MEMORY_COPY: {
                fprintf(stderr, "no impl for: %s\n", "memory_copy");
                __builtin_trap();
            }
            case WEB49_OPCODE_MEMORY_FILL: {
                fprintf(stderr, "no impl for: %s\n", "memory_fill");
                __builtin_trap();
            }
            case WEB49_OPCODE_DATA_DROP: {
                fprintf(stderr, "no impl for: %s\n", "data_drop");
                __builtin_trap();
            }
            case WEB49_OPCODE_TABLE_INIT: {
                fprintf(stderr, "no impl for: %s\n", "table_init");
                __builtin_trap();
            }
            case WEB49_OPCODE_ELEM_DROP: {
                fprintf(stderr, "no impl for: %s\n", "elem_drop");
                __builtin_trap();
            }
            case WEB49_OPCODE_TABLE_COPY: {
                fprintf(stderr, "no impl for: %s\n", "table_copy");
                __builtin_trap();
            }
            case WEB49_OPCODE_BLOCK_RETURNS: {
                int32_t ret = web49_interp_block_run(interp, head++->block);
                if (ret >= 0) {
                    return ret - 1;
                }
                *interp.stack++ = interp.returns[0];
                break;
            }
            case WEB49_OPCODE_IF_RETURNS: {
                int32_t ret;
                if ((--interp.stack)->i32_u) {
                    ret = web49_interp_block_run(interp, head[0].block);
                } else {
                    ret = web49_interp_block_run(interp, head[1].block);
                }
                if (ret >= 0) {
                    return ret - 1;
                }
                *interp.stack++ = interp.returns[0];
                head += 2;
                break;
            }
            case WEB49_OPCODE_WASI_FD_SEEK: {
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
                break;
            }
            case WEB49_OPCODE_WASI_FD_FILESTAT_GET: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_filestat_get");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_FILESTAT_GET: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_filestat_get");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_ARGS_GET: {
                uint32_t argv = interp.locals[0].i32_u;
                uint32_t buf = interp.locals[1].i32_u;

                uint32_t argc = 0;
                uint32_t head = buf;
                for (size_t i = 0; interp.args[i] != NULL; i++) {
                    *(uint32_t *)&interp.memory[argv + argc * 4] = head;
                    size_t memlen = strlen(interp.args[i]) + 1;
                    memcpy(&interp.memory[head], interp.args[i], memlen);
                    head += memlen;
                    argc += 1;
                }
                *(uint32_t *)&interp.memory[argv + argc * 4] = 0;
                interp.stack++->i32_u = 0;
                break;
            }
            case WEB49_OPCODE_WASI_ARGS_SIZES_GET: {
                uint32_t argc = interp.locals[0].i32_u;
                uint32_t buf_size = interp.locals[1].i32_u;
                uint32_t buf_len = 0;
                size_t i = 0;
                while (interp.args[i] != NULL) {
                    buf_len += strlen(interp.args[i]) + 1;
                    i += 1;
                }
                *(uint32_t *)&interp.memory[argc] = i;
                *(uint32_t *)&interp.memory[buf_size] = buf_len;
                interp.stack++->i32_u = 0;
                break;
            }
            case WEB49_OPCODE_WASI_CLOCK_RES_GET: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_clock_res_get");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_CLOCK_TIME_GET: {
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
                *(uint64_t *)&interp.memory[time] = (uint64_t) ts.tv_sec * 1000000000 + (uint64_t) ts.tv_nsec;
                // fprintf(stderr, "%zu / %zu\n", (size_t) *(uint64_t *)&interp.memory[time], (size_t) precision);
                interp.stack++->i32_u = 0;
                break;
            }
            case WEB49_OPCODE_WASI_ENVIRON_GET: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_environ_get");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_ENVIRON_SIZES_GET: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_environ_sizes_get");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_ADVISE: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_advise");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_ALLOCATE: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_allocate");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_CLOSE: {
                uint32_t fd = interp.locals[0].i32_u;
                interp.stack++->i32_u = close(fd);
                break;
            }
            case WEB49_OPCODE_WASI_FD_DATASYNC: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_datasync");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_FDSTAT_GET: {
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
                break;
            }
            case WEB49_OPCODE_WASI_FD_FDSTAT_SET_FLAGS: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_fdstat_set_flags");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_FDSTAT_SET_RIGHTS: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_fdstat_set_rights");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_FILESTAT_SET_SIZE: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_filestat_set_size");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_FILESTAT_SET_TIMES: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_filestat_set_times");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_PREAD: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_pread");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_PRESTAT_GET: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_prestat_get");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_PRESTAT_DIR_NAME: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_prestat_dir_name");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_PWRITE: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_pwrite");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_READ: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_read");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_READDIR: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_readdir");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_RENUMBER: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_renumber");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_SYNC: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_sync");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_TELL: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_fd_tell");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_FD_WRITE: {
                uint32_t fd = interp.locals[0].i32_u;
                uint32_t iovs = interp.locals[1].i32_u;
                uint32_t iovs_len = interp.locals[2].i32_u;
                uint32_t nwritten = interp.locals[3].i32_u;
                *(uint32_t *)&interp.memory[nwritten] = 0;
                for (size_t i = 0; i < iovs_len; i++) {
                    uint32_t ptr = *(uint32_t *)&interp.memory[iovs + i * 8];
                    uint32_t len = *(uint32_t *)&interp.memory[iovs + i * 8 + 4];
                    // fprintf(stderr, ".ptr = %zu, .len = %zu\n", (size_t) ptr, (size_t) len);
                    *(uint32_t *)&interp.memory[nwritten] += write(fd, &interp.memory[ptr], len);
                }
                // interp.stack++->i32_u = *(uint32_t *)&interp.memory[nwritten];
                interp.stack++->i32_u = 0;
                break;
            }
            case WEB49_OPCODE_WASI_PATH_CREATE_DIRECTORY: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_create_directory");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_FILESTAT_SET_TIMES: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_filestat_set_times");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_LINK: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_link");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_OPEN: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_open");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_READLINK: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_readlink");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_REMOVE_DIRECTORY: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_remove_directory");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_RENAME: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_rename");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_SYMLINK: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_symlink");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PATH_UNLINK_FILE: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_path_unlink_file");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_POLL_ONEOFF: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_poll_oneoff");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_PROC_EXIT: {
                exit(interp.locals[0].i32_u);
                break;
            }
            case WEB49_OPCODE_WASI_PROC_RAISE: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_proc_raise");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_RANDOM_GET: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_random_get");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_SCHED_YIELD: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_sched_yield");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_SOCK_RECV: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_sock_recv");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_SOCK_SEND: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_sock_send");
                __builtin_trap();
            }
            case WEB49_OPCODE_WASI_SOCK_SHUTDOWN: {
                fprintf(stderr, "no impl for: wasi %s", "wasi_sock_shutdown");
                __builtin_trap();
            }
            default:
                fprintf(stderr, "unhandled: %s (opcode: %zu) @%zu\n", web49_interp_opcode_to_name(head[-1].opcode), (size_t)head[-1].opcode, &head[-1] - block->code);
                __builtin_trap();
        }
        // fprintf(stderr, "- OP\n");
    }
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
    web49_interp_block_t **blocks = web49_malloc(sizeof(web49_interp_block_t *) * num_funcs);
    web49_interp_data_t *globals = web49_malloc(sizeof(web49_interp_data_t) * (global_section.num_entries));
    web49_interp_data_t *stack = web49_alloc0(sizeof(web49_interp_data_t) * (1 << 16));
    uint64_t memsize = 65536 * 256;
    uint8_t *memory = web49_alloc0(memsize + (65536));
    web49_interp_data_t *returns = web49_alloc0(256);
    web49_interp_t interp = (web49_interp_t){
        .locals = stack,
        .stack = stack,
        .funcs = blocks,
        .globals = globals,
        .memsize = memsize,
        .memory = memory,
        .returns = returns,
        .args = args,
    };
    for (size_t j = 0; j < table_section.num_entries; j++) {
        web49_type_table_t entry = table_section.entries[j];
        if (entry.element_type == WEB49_TYPE_ANYFUNC) {
            interp.table = web49_malloc(sizeof(web49_interp_block_t *) * entry.limits.maximum);
        }
    }
    for (size_t j = 0; j < import_section.num_entries; j++) {
        web49_section_import_entry_t entry = import_section.entries[j];
        if (entry.kind == WEB49_EXTERNAL_KIND_FUNCTION) {
            web49_interp_block_t *block = web49_interp_import(&interp, entry.module_str, entry.field_str);
            blocks[cur_func] = block;
            cur_func += 1;
        }
    }
    for (size_t j = 0; j < global_section.num_entries; j++) {
        web49_section_global_entry_t global = global_section.entries[j];
        if (global.init_expr.opcode == WEB49_OPCODE_I32_CONST) {
            globals[j].i32_s = global.init_expr.immediate.varint32;
        } else if (global.init_expr.opcode == WEB49_OPCODE_I64_CONST) {
            globals[j].i64_s = global.init_expr.immediate.varint64;
        } else {
            globals[j].i64_u = 0;
        }
    }
    for (size_t j = 0; j < data_section.num_entries; j++) {
        web49_section_data_entry_t entry = data_section.entries[j];
        memcpy(&memory[entry.offset.immediate.varint32], entry.data, entry.size);
    }
    for (size_t j = 0; j < code_section.num_entries; j++) {
        web49_section_code_entry_t entry = code_section.entries[j];
        web49_interp_instr_buf_t buf;
        buf.head = 0;
        buf.len = entry.num_instrs;
        buf.instrs = entry.instrs;
        uint64_t nreturns[256] = {0};
        web49_read_block_state_t state;
        state.nreturns = &nreturns[0];
        state.instrs = buf;
        web49_interp_block_t *block = web49_interp_read_block(&state);
        block->nlocals = 0;
        for (uint64_t i = 0; i < entry.num_locals; i++) {
            block->nlocals += entry.locals[i].count;
        }
        // block->nlocals += 16;
        block->nparams = type_section.entries[function_section.entries[j]].num_params;
        block->nreturns = type_section.entries[function_section.entries[j]].num_returns;
        blocks[cur_func] = block;
        cur_func += 1;
    }
    for (size_t j = 0; j < element_section.num_entries; j++) {
        web49_section_element_entry_t entry = element_section.entries[j];
        for (uint64_t i = 0; i < entry.num_elems; i++) {
            // fprintf(stderr, "%zu=%zu\n", (size_t) (entry.offset.immediate.varint32 + i), entry.elems[i]);
            interp.table[i + entry.offset.immediate.varint32] = interp.funcs[entry.elems[i]];
        }
    }
    web49_interp_block_t *func = blocks[start];
    web49_interp_data_t *old_locals = interp.locals;
    web49_interp_data_t *old_stack = interp.stack;
    interp.locals = interp.stack - func->nparams;
    for (uint64_t i = 0; i < func->nlocals; i++) {
        interp.stack++->i64_u = 0;
    }
    web49_interp_block_run(interp, func);
    interp.stack = old_stack - func->nparams + func->nreturns;
    interp.locals = old_locals;
}
