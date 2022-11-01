
#include "io.h"
#include <math.h>
#include <stdio.h>

web49_io_input_t web49_io_input_open(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "cannot open file: %s\n", filename);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size_t len = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);
    uint8_t *str = web49_malloc(sizeof(uint8_t) * len);
    if (fread(str, 1, len, file) != len) {
        fprintf(stderr, "cannot read file: %s\n", filename);
        exit(1);
    }
    fclose(file);
    return (web49_io_input_t) {
        .byte_index = 0,
        .byte_len = len,
        .byte_buf = str,
    };
}
bool web49_io_input_is_empty(web49_io_input_t *in) {
    return in->byte_len == in->byte_index;
}
size_t web49_io_input_ftell(web49_io_input_t *in) {
    return in->byte_index;
}
size_t web49_io_input_fread(web49_io_input_t *in, size_t size, void *data) {
    memcpy(data, &in->byte_buf[in->byte_index], size);
    in->byte_index += size;
    return size;
}
char web49_io_input_fgetc(web49_io_input_t *in) {
    return (char) in->byte_buf[in->byte_index++];
}
void web49_io_input_rewind(web49_io_input_t *in) {
    in->byte_index -= 1;
}
