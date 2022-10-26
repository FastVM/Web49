#include "./parse.h"
#include "./wat.h"

int main(int argc, const char **argv) {
    const char *inarg = NULL;
    const char *outarg = NULL;
    for (size_t i = 1; i < argc; i+=1) {
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
    FILE *infile = fopen(inarg, "rb");
    if (infile == NULL) {
        fprintf(stderr, "cannot open file: %s\n", inarg);
        return 1;
    }
    vm_wasm_module_t mod = vm_wasm_parse_module(infile);
    fclose(infile);
    if (outarg == NULL) {
        vm_wat_print_module(stdout, mod);
    } else {
        FILE *outfile = fopen(outarg, "wb");
        vm_wat_print_module(outfile, mod);
        fclose(outfile);
    }
    return 0;
}
