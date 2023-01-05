#include "../src/ast.h"
#include "../src/interp/interp.h"
#include "../src/read_wat.h"
#include "../src/write_bin.h"

int web49_file_main(const char *inarg, const char *outarg) {
    web49_io_input_t infile = web49_io_input_open(inarg);
    web49_module_t mod = web49_readwat_module(&infile);
    web49_writebin_buf_t buf = {0};
    web49_writebin_module(&buf, mod);
    FILE *outfile = fopen(outarg, "wb");
    fwrite(buf.data, 1, buf.len, outfile);
    fclose(outfile);
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
