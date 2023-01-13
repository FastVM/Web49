#include "../src/api/api.h"
#include "../src/ast.h"
#include "../src/interp/interp.h"
#include "../src/opt/tee.h"
#include "../src/opt/tree.h"
#include "../src/read_bin.h"
#include "../src/read_wat.h"

static web49_interp_data_t web49_main_import_silly(web49_interp_t interp) {
    return (web49_interp_data_t){0};
    // fprintf(stderr, "emscripten generated bad func: %s\n", "emscripten_asm_const_int");
    // __builtin_trap();
}

web49_env_func_t web49_main_import_func(void *state, const char *mod, const char *func) {
    if (!strcmp(mod, "wasi_snapshot_preview1")) {
        return web49_api_import_wasi(state, func);
    } else if (!strcmp(mod, "env")) {
        if (!strcmp(func, "emscripten_asm_const_int")) {
            return &web49_main_import_silly;
        }
        web49_env_func_t ret = web49_api_import_raylib(func);
        if (ret == NULL) {
            __builtin_trap();
        }
        return ret;
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
    uint32_t start = 0;
    web49_section_export_t exports = web49_module_get_section(mod, WEB49_SECTION_ID_EXPORT).export_section;
    for (size_t j = 0; j < exports.num_entries; j++) {
        web49_section_export_entry_t entry = exports.entries[j];
        if (!strcmp(entry.field_str, "_start")) {
            start = entry.index;
        }
    }
    web49_opt_tee_module(&mod);
    web49_opt_tree_module(&mod);
    web49_interp_t interp = web49_interp_module(mod, args);
    web49_free_module(mod);
    interp.import_func = web49_main_import_func;
    interp.import_state = NULL;
    web49_interp_block_run(&interp, &interp.funcs[start]);
    web49_free_interp(interp);
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