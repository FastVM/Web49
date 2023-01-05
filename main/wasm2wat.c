#include "../src/ast.h"
#include "../src/interp/interp.h"
#include "../src/read_bin.h"
#include "../src/write_wat.h"

int web49_file_main(const char *inarg, const char *outarg) {
    web49_io_input_t infile = web49_io_input_open(inarg);
    web49_module_t mod = web49_readbin_module(&infile);
    web49_io_output_t outfile = {0};
    web49_wat_print_module(&outfile, mod);
    if (outarg == NULL) {
        fwrite(outfile.byte_buf, 1, outfile.byte_index, stdout);
    } else {
        web49_file_output_dump(outfile, outarg);
    }
    return 0;
}

int main(int argc, const char **argv) {
    const char *inarg = NULL;
    const char *outarg = NULL;
    for (int i = 1; i < argc; i += 1) {
        if (!strcmp(argv[i], "-o")) {
            i += 1;
            outarg = argv[i];
        } else if (inarg == NULL) {
            inarg = argv[i];
        } else {
            fprintf(stderr, "extra cli arg: %s\n", argv[i]);
            return 1;
        }
    }
    return web49_file_main(inarg, outarg);
}
