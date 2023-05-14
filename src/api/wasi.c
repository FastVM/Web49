#include <fcntl.h>
#include <stdint.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "./api.h"

static web49_interp_data_t web49_api_wasi_random_get(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    uint32_t ptr = interp.locals[0].i32_u;
    uint32_t len = interp.locals[1].i32_u;
    getentropy(&interp.memory[ptr], len);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_fd_seek(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    int whence = -1;
    switch (interp.locals[2].i32_u) {
        case 0:
            whence = SEEK_CUR;
            break;
        case 1:
            whence = SEEK_END;
            break;
        case 2:
            whence = SEEK_SET;
            break;
        default:
            fprintf(stderr, "bad wasi whence: %" PRIu32 "\n", interp.locals[2].i32_u);
            __builtin_trap();
    }
    if (interp.locals[0].i32_u <= 2 && whence == SEEK_SET) {
        WEB49_INTERP_WRITE(int64_t, interp, interp.locals[3].i32_u, interp.locals[1].i64_s);
    } else {
        WEB49_INTERP_WRITE(int64_t, interp, interp.locals[3].i32_u, (int64_t)lseek((int)interp.locals[0].i32_u, interp.locals[1].i64_s, whence));
    }
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_args_get(void *wasi_untyped, web49_interp_t interp) {
    web49_wasi_t *wasi = wasi_untyped;
    uint32_t argv = interp.locals[0].i32_u;
    uint32_t buf = interp.locals[1].i32_u;
    uint32_t argc = 0;
    uint32_t head2 = buf;
    for (size_t i = 0; wasi->argv[i] != NULL; i++) {
        WEB49_INTERP_WRITE(uint32_t, interp, argv + argc * 4, head2);
        size_t memlen = strlen(wasi->argv[i]) + 1;
        memcpy(WEB49_INTERP_ADDR(void *, interp, head2, memlen), wasi->argv[i], memlen);
        head2 += memlen;
        argc += 1;
    }
    WEB49_INTERP_WRITE(uint32_t, interp, argv + argc * 4, 0);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_args_sizes_get(void *wasi_untyped, web49_interp_t interp) {
    web49_wasi_t *wasi = wasi_untyped;
    uint32_t argc = interp.locals[0].i32_u;
    uint32_t buf_size = interp.locals[1].i32_u;
    uint32_t buf_len = 0;
    uint32_t i = 0;
    while (wasi->argv[i] != NULL) {
        buf_len += strlen(wasi->argv[i]) + 1;
        i += 1;
    }
    WEB49_INTERP_WRITE(uint32_t, interp, argc, i);
    WEB49_INTERP_WRITE(uint32_t, interp, buf_size, buf_len);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_clock_time_get(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
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
        case 2:
            clock_id = CLOCK_PROCESS_CPUTIME_ID;
            break;
        case 3:
            clock_id = CLOCK_THREAD_CPUTIME_ID;
            break;
        default:
            fprintf(stderr, "unknown clock id: %zu\n", (size_t)wasi_clock_id);
            return (web49_interp_data_t){.i32_u = 28};
    }
    struct timespec ts;
    clock_gettime(clock_id, &ts);
    uint64_t n = ((uint64_t)ts.tv_sec * 1000000000 + (uint64_t)ts.tv_nsec);
    WEB49_INTERP_WRITE(uint64_t, interp, time, n);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_fd_close(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    uint32_t fd = interp.locals[0].i32_u;
    close((int)fd);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_fd_fdstat_get(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    uint32_t fd = interp.locals[0].i32_u;
    uint32_t fdstat = interp.locals[1].i32_u;

    struct stat fd_stat;
    fstat((int)fd, &fd_stat);
    int mode = (int)fd_stat.st_mode;
    uint8_t fs_filetype = (S_ISBLK(mode) ? 1 : 0) | (S_ISCHR(mode) ? 2 : 0) | (S_ISDIR(mode) ? 3 : 0) | (S_ISREG(mode) ? 4 : 0);
    uint16_t fs_flags = 0;
    uint64_t fs_rights_base = UINT64_MAX;
    uint64_t fs_rights_inheriting = UINT64_MAX;
    if (fd <= 2) {
        fs_rights_base &= ~(uint64_t)(4 | 32);
    }
    WEB49_INTERP_WRITE(uint8_t, interp, fdstat + 0, fs_filetype);
    WEB49_INTERP_WRITE(uint8_t, interp, fdstat + 1, 0);
    WEB49_INTERP_WRITE(uint16_t, interp, fdstat + 2, fs_flags);
    WEB49_INTERP_WRITE(uint32_t, interp, fdstat + 4, 0);
    WEB49_INTERP_WRITE(uint64_t, interp, fdstat + 8, fs_rights_base);
    WEB49_INTERP_WRITE(uint64_t, interp, fdstat + 16, fs_rights_inheriting);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_fd_prestat_get(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    uint32_t fd = interp.locals[0].i32_u;
    uint32_t buf = interp.locals[1].i32_u;
    WEB49_INTERP_WRITE(uint8_t, interp, buf, 0);
    if (fd == 3) {
        WEB49_INTERP_WRITE(uint32_t, interp, buf + 4, 1);
    } else if (fd == 4) {
        WEB49_INTERP_WRITE(uint32_t, interp, buf + 4, 2);
    } else {
        return (web49_interp_data_t){.i32_u = 8};
    }
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_path_open(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    uint32_t wdirfd = interp.locals[0].i32_u;
    // uint32_t dirflags = interp.locals[1].i32_u;
    uint32_t path = interp.locals[2].i32_u;
    uint32_t path_len = interp.locals[3].i32_u;
    uint32_t oflags = interp.locals[4].i32_u;
    uint32_t fs_rights_base = interp.locals[5].i32_u;
    // uint32_t fs_rights_inherit = interp.locals[6].i32_u;
    uint32_t fs_flags = interp.locals[7].i32_u;
    uint32_t pfd = interp.locals[8].i32_u;
    char host_path[512];
    memcpy(host_path, WEB49_INTERP_ADDR(void *, interp, path, path_len), path_len);
    host_path[path_len] = '\0';
    if (!strcmp(host_path, "/")) {
        WEB49_INTERP_WRITE(int32_t, interp, path, 3);
        return (web49_interp_data_t){.i32_u = 0};
    } else if (!strcmp(host_path, "./")) {
        WEB49_INTERP_WRITE(int32_t, interp, path, 4);
        return (web49_interp_data_t){.i32_u = 0};
    }
    int flags = ((oflags & 1) ? O_CREAT : 0) |
                ((oflags & 4) ? O_EXCL : 0) |
                ((oflags & 8) ? O_TRUNC : 0) |
                ((fs_flags & 1) ? O_APPEND : 0);
    if ((fs_rights_base & 2) && (fs_rights_base & 32)) {
        flags |= O_RDWR;
    } else if (fs_rights_base & 32) {
        flags |= O_WRONLY;
    } else if (fs_rights_base & 2) {
        flags |= O_RDONLY;
    }
    int dirfd;
    switch (wdirfd) {
        case 3:
            dirfd = open("/", O_RDONLY);
            break;
        case 4:
            dirfd = open("./", O_RDONLY);
            break;
        default:
            fprintf(stderr, "unknown dirfd: %i\n", wdirfd);
            __builtin_trap();
    }
#if defined(__WIN32__)
    int hostfd = open(host_path, flags, 0644);
#else
    int hostfd = openat((int)dirfd, host_path, flags, 0644);
#endif
    close((int)dirfd);
    if (hostfd < 0) {
        return (web49_interp_data_t){.i32_u = 44};
    }
    WEB49_INTERP_WRITE(uint32_t, interp, pfd, (uint32_t)hostfd);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_fd_read(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    uint32_t fd = interp.locals[0].i32_u;
    uint32_t iovs = interp.locals[1].i32_u;
    uint32_t iovs_len = interp.locals[2].i32_u;
    uint32_t nread = 0;
    for (size_t i = 0; i < iovs_len; i++) {
        uint32_t ptr = WEB49_INTERP_READ(uint32_t, interp, iovs + i * 8 + 0);
        uint32_t len = WEB49_INTERP_READ(uint32_t, interp, iovs + i * 8 + 4);
        nread += (uint32_t)read((int)fd, WEB49_INTERP_ADDR(void *, interp, ptr, len), len);
    }
    WEB49_INTERP_WRITE(uint32_t, interp, interp.locals[3].i32_u, nread);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_fd_write(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    uint32_t fd = interp.locals[0].i32_u;
    uint32_t iovs = interp.locals[1].i32_u;
    uint32_t iovs_len = interp.locals[2].i32_u;
    uint32_t nwritten = 0;
    for (size_t i = 0; i < iovs_len; i++) {
        uint32_t ptr = WEB49_INTERP_READ(uint32_t, interp, iovs + i * 8 + 0);
        uint32_t len = WEB49_INTERP_READ(uint32_t, interp, iovs + i * 8 + 4);
        nwritten += (uint32_t)write((int)fd, WEB49_INTERP_ADDR(void *, interp, ptr, len), len);
    }
    WEB49_INTERP_WRITE(uint32_t, interp, interp.locals[3].i32_u, nwritten);
    return (web49_interp_data_t){.i32_u = 0};
}
static web49_interp_data_t web49_api_wasi_proc_exit(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
    exit((int)interp.locals[0].i32_u);
}
static web49_interp_data_t web49_api_wasi_fd_prestat_dir_name(void *wasi_untyped, web49_interp_t interp) {
    (void)wasi_untyped;
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
    size_t max_len = strlen(name);
    if (n > max_len) {
        n = max_len;
    }
    memcpy(WEB49_INTERP_ADDR(void *, interp, interp.locals[1].i32_u, n), name, n);
    return (web49_interp_data_t){.i32_u = 0};
}

web49_wasi_t *web49_wasi_new(const char **argv, const char **envp) {
    web49_wasi_t *wasi = malloc(sizeof(web49_wasi_t));
    wasi->argv = argv;
    wasi->envp = envp;
    return wasi;
}

web49_env_t *web49_api_wasi(void *state, const char *module, const char *func) {
    web49_env_func_t ret = NULL;
    if (!strcmp(module, "wasi_unstable") || !strcmp(module, "wasi_snapshot_preview1")) {
        if (!strcmp(func, "random_get")) {
            ret = &web49_api_wasi_random_get;
        } else if (!strcmp(func, "fd_seek")) {
            ret = &web49_api_wasi_fd_seek;
        } else if (!strcmp(func, "args_get")) {
            ret = &web49_api_wasi_args_get;
        } else if (!strcmp(func, "args_sizes_get")) {
            ret = &web49_api_wasi_args_sizes_get;
        } else if (!strcmp(func, "clock_time_get")) {
            ret = &web49_api_wasi_clock_time_get;
        } else if (!strcmp(func, "fd_close")) {
            ret = &web49_api_wasi_fd_close;
        } else if (!strcmp(func, "fd_prestat_get")) {
            ret = &web49_api_wasi_fd_prestat_get;
        } else if (!strcmp(func, "fd_prestat_dir_name")) {
            ret = &web49_api_wasi_fd_prestat_dir_name;
        } else if (!strcmp(func, "fd_fdstat_get")) {
            ret = &web49_api_wasi_fd_fdstat_get;
        } else if (!strcmp(func, "path_open")) {
            ret = &web49_api_wasi_path_open;
        } else if (!strcmp(func, "fd_read")) {
            ret = &web49_api_wasi_fd_read;
        } else if (!strcmp(func, "fd_write")) {
            ret = &web49_api_wasi_fd_write;
        } else if (!strcmp(func, "proc_exit")) {
            ret = &web49_api_wasi_proc_exit;
        }
    }
    if (ret == NULL) {
        return NULL;
    }
    return web49_env_new(state, ret);
}
