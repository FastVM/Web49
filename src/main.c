#include "./parse.h"
#include "./wat.h"

int main(int argc, const char **argv) {
    FILE *in = fopen(argv[1], "rb");
    vm_wasm_module_t mod = vm_wasm_parse_module(in);
    fclose(in);
    vm_wat_print_module(stdout, mod);
    return 0;
}
