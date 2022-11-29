#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "../src/ast.h"
#include "../src/interp/interp.h"
#include "../src/opt/tee.h"
#include "../src/opt/tree.h"
#include "../src/read_bin.h"
#include "../src/read_wat.h"

web49_interp_data_t web49_main_import_wasi_fd_seek(web49_interp_t interp) {
    int whence = -1;
    switch (interp.locals[2].i32_u) {
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
    *(uint32_t *)&interp.memory[interp.locals[3].i32_u] = lseek(interp.locals[0].i32_u, interp.locals[1].i32_u, whence);
    return (web49_interp_data_t){.i32_u = 0};
}
web49_interp_data_t web49_main_import_wasi_args_get(web49_interp_t interp) {
    uint32_t argv = interp.locals[0].i32_u;
    uint32_t buf = interp.locals[1].i32_u;
    uint32_t argc = 0;
    uint32_t head2 = buf;
    for (size_t i = 0; interp.args[i] != NULL; i++) {
        *(uint32_t *)&interp.memory[argv + argc * 4] = head2;
        size_t memlen = strlen(interp.args[i]) + 1;
        memcpy(&interp.memory[head2], interp.args[i], memlen);
        head2 += memlen;
        argc += 1;
    }
    *(uint32_t *)&interp.memory[argv + argc * 4] = 0;
    return (web49_interp_data_t){.i32_u = 0};
}
web49_interp_data_t web49_main_import_wasi_args_sizes_get(web49_interp_t interp) {
    uint32_t argc = interp.locals[0].i32_u;
    uint32_t buf_size = interp.locals[1].i32_u;
    uint32_t buf_len = 0;
    uint32_t i = 0;
    while (interp.args[i] != NULL) {
        buf_len += strlen(interp.args[i]) + 1;
        i += 1;
    }
    *(uint32_t *)&interp.memory[argc] = i;
    *(uint32_t *)&interp.memory[buf_size] = buf_len;
    return (web49_interp_data_t){.i32_u = 0};
}
web49_interp_data_t web49_main_import_wasi_clock_time_get(web49_interp_t interp) {
    uint32_t wasi_clock_id = interp.locals[0].i32_u;
    // uint64_t precision = interp.locals[1].i64_u;
    uint32_t time = interp.locals[2].i32_u;
    clockid_t clock_id;
    switch (wasi_clock_id) {
        case 0:
            clock_id = CLOCK_REALTIME;
            break;
        case 1:
            clock_id = CLOCK_MONOTONIC;
            break;
        default:
            clock_id = (clockid_t)wasi_clock_id;
            break;
    }
    struct timespec ts;
    clock_gettime(clock_id, &ts);
    *(uint64_t *)&interp.memory[time] = (uint64_t)ts.tv_sec * 1000000000 + (uint64_t)ts.tv_nsec;
    return (web49_interp_data_t){.i32_u = 0};
}
web49_interp_data_t web49_main_import_wasi_fd_close(web49_interp_t interp) {
    uint32_t fd = interp.locals[0].i32_u;
    close(fd);
    return (web49_interp_data_t){.i32_u = 0};
}
web49_interp_data_t web49_main_import_wasi_fd_fdstat_get(web49_interp_t interp) {
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
    return (web49_interp_data_t){.i32_u = 0};
}
web49_interp_data_t web49_main_import_wasi_fd_write(web49_interp_t interp) {
    uint32_t fd = interp.locals[0].i32_u;
    uint32_t iovs = interp.locals[1].i32_u;
    uint32_t iovs_len = interp.locals[2].i32_u;
    uint32_t nwritten = interp.locals[3].i32_u;
    *(uint32_t *)&interp.memory[nwritten] = 0;
    for (size_t i = 0; i < iovs_len; i++) {
        uint32_t ptr = *(uint32_t *)&interp.memory[iovs + i * 8];
        uint32_t len = *(uint32_t *)&interp.memory[iovs + i * 8 + 4];
        *(uint32_t *)&interp.memory[nwritten] += (uint32_t)write(fd, &interp.memory[ptr], len);
    }
    return (web49_interp_data_t){.i32_u = 0};
}
web49_interp_data_t web49_main_import_wasi_proc_exit(web49_interp_t interp) {
    exit((int)interp.locals[0].i32_u);
}
web49_interp_data_t web49_main_import_wasi_fd_prestat_dir_name(web49_interp_t interp) {
    // char *path = &interp.memory[interp.locals[1].i32_u];
    if (interp.locals[0].i32_u <= 2) {
        return (web49_interp_data_t){.i32_u = 0};
    } else {
        const char *name;
        switch (interp.locals[0].i32_u) {
            case 3:
                name = "/";
                break;
            case 4:
                name = "./";
                break;
            default:
                return (web49_interp_data_t){.i32_u = 9};
        }
        size_t n = interp.locals[2].i32_u;
        if (strlen(name) < n) {
            n = strlen(name);
        }
        memcpy(&interp.memory[interp.locals[1].i32_u], name, n);
        return (web49_interp_data_t){.i32_u = 0};
    }
}
web49_interp_data_t web49_main_import_wasi_fd_prestat_get(web49_interp_t interp) {
    return (web49_interp_data_t){.i32_u = 0};
}

web49_env_func_t web49_main_import_wasi(void *wasi, const char *func) {
    if (!strcmp(func, "fd_seek")) {
        return &web49_main_import_wasi_fd_seek;
    } else if (!strcmp(func, "args_get")) {
        return &web49_main_import_wasi_args_get;
    } else if (!strcmp(func, "args_sizes_get")) {
        return &web49_main_import_wasi_args_sizes_get;
    } else if (!strcmp(func, "clock_time_get")) {
        return &web49_main_import_wasi_clock_time_get;
    } else if (!strcmp(func, "fd_close")) {
        return &web49_main_import_wasi_fd_close;
    } else if (!strcmp(func, "fd_prestat_get")) {
        return &web49_main_import_wasi_fd_prestat_dir_name;
    } else if (!strcmp(func, "fd_prestat_dir_name")) {
        return &web49_main_import_wasi_fd_prestat_get;
    } else if (!strcmp(func, "fd_fdstat_get")) {
        return &web49_main_import_wasi_fd_fdstat_get;
    } else if (!strcmp(func, "fd_write")) {
        return &web49_main_import_wasi_fd_write;
    } else if (!strcmp(func, "proc_exit")) {
        return &web49_main_import_wasi_proc_exit;
    } else {
        return NULL;
    }
}

web49_env_func_t web49_main_import_func(void *state, const char *mod, const char *func) {
    if (!strcmp(mod, "wasi_snapshot_preview1")) {
        return web49_main_import_wasi(state, func);
    } else {
        return NULL;
    }
}

int web49_file_main(const char *inarg, const char **args) {
    web49_io_input_t infile = web49_io_input_open(inarg);
    web49_module_t mod;
    if (memcmp(infile.byte_buf, "\0asm", 4) == 0) {
        mod = web49_readbin_module(&infile);
    } else {
        const char *v = strrchr(inarg, '.');
        if (!strcmp(v, ".wast")) {
            fprintf(stderr, "miniwasm cannot handle \"wasm spec test\" files yet!\n");
            return 1;
        } else {
            mod = web49_readwat_module(&infile);
        }
    }
    web49_opt_tee_module(&mod);
    web49_opt_tree_module(&mod);
    web49_interp_t interp = web49_interp_module(mod, args);
    interp.import_func = web49_main_import_func;
    interp.import_state = NULL;
    for (size_t i = 0; i < mod.num_sections; i++) {
        web49_section_t section = mod.sections[i];
        if (section.header.id == WEB49_SECTION_ID_EXPORT) {
            for (size_t j = 0; j < section.export_section.num_entries; j++) {
                web49_section_export_entry_t entry = section.export_section.entries[j];
                if (!strcmp(entry.field_str, "_start")) {
                    web49_interp_block_run(interp, &interp.funcs[entry.index]);
                }
            }
        }
    }
    web49_free_interp(interp);
    web49_free_module(mod);
    return 0;
}

int main(int argc, const char **argv) {
    const char *inarg = NULL;
    const char **args = argv + 1;
    for (int i = 1; i <= argc; i += 1) {
        if (inarg == NULL) {
            inarg = argv[i];
            args = &argv[i];
        } else {
            break;
        }
    }
    return web49_file_main(inarg, args);
}
