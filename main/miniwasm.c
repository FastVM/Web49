#include "../src/ast.h"
#include "../src/interp/interp.h"
#include "../src/read_bin.h"

int web49_file_main(const char *inarg) {
    web49_io_input_t infile = web49_io_input_open(inarg);
    web49_module_t mod = web49_readbin_module(&infile);
    web49_interp_module(mod);
    return 0;
}

int main(int argc, const char **argv) {
    const char *inarg = NULL;
    for (int i = 1; i < argc; i += 1) {
        if (inarg == NULL) {
            inarg = argv[i];
        } else {
            fprintf(stderr, "extra cli arg: %s\n", argv[i]);
            return 1;
        }
    }
    return web49_file_main(inarg);
}
