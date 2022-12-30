
#include "io.h"

web49_io_input_t web49_io_input_open(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "cannot open file: %s\n", filename);
        exit(1);
    }
    size_t len = 0;
    uint8_t *str = NULL;
    // if (fseek(file, 0, SEEK_SET) >= 0) {
    //     fseek(file, 0, SEEK_END);
    //     len = (size_t)ftell(file);
    //     fseek(file, 0, SEEK_SET);
    //     str = web49_malloc(sizeof(uint8_t) * len);
    //     if (fread(str, 1, len, file) != len) {
    //         fprintf(stderr, "cannot read file: %s\n", filename);
    //         exit(1);
    //     }
    //     // printf("stream.szie = %zu bytes\n", len);
    // } else {
        size_t alloc = 512;
        str = web49_malloc(sizeof(uint8_t) * alloc);
        while (!feof(file)) {
            if (len + 256 >= alloc) {
                alloc = (len + 256) * 2;
                str = web49_realloc(str, sizeof(uint8_t) * alloc);
            }
            len += fread(&str[len], 1, 128, file);
        }
        // printf("infile.size = %zu bytes\n", len);
        str[len] = 0;
    // }
    fclose(file);
    return (web49_io_input_t){
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
    return (char)in->byte_buf[in->byte_index++];
}
void web49_io_input_rewind(web49_io_input_t *in) {
    in->byte_index -= 1;
}
void web49_file_output_dump(web49_io_output_t out, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "cannot open file: %s\n", filename);
        exit(1);
    }
    fwrite(out.byte_buf, 1, out.byte_index, file);
    fclose(file);
}
void web49_io_output_fprintf(web49_io_output_t *out, const char *format, ...) {
    if (out->byte_index + 2048 >= out->byte_alloc) {
        out->byte_alloc = (out->byte_index + 2048) * 2;
        out->byte_buf = web49_realloc(out->byte_buf, sizeof(uint8_t) * out->byte_alloc);
    }
    va_list ap;
    va_start(ap, format);
    out->byte_index += vsnprintf((char *)&out->byte_buf[out->byte_index], out->byte_alloc - out->byte_index, format, ap);
    va_end(ap);
}
void web49_io_output_write_len_str(web49_io_output_t *out, size_t len, const char *str) {
    if (out->byte_index + len + (2048) >= out->byte_alloc) {
        out->byte_alloc = (out->byte_index + len + 2048) * 2;
        out->byte_buf = web49_realloc(out->byte_buf, sizeof(uint8_t) * out->byte_alloc);
    }
    memcpy(&out->byte_buf[out->byte_index], str, len);
    out->byte_index += len;
}
