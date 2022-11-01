#if !defined(WEB49_HEADER_IO)
#define WEB49_HEADER_IO

#include "lib.h"

struct web49_io_input_t;
typedef struct web49_io_input_t web49_io_input_t;

struct web49_io_input_t {
    size_t byte_index;
    size_t byte_len;
    uint8_t *byte_buf;
};

web49_io_input_t web49_io_input_open(const char *filename);
bool web49_io_input_is_empty(web49_io_input_t *input);
size_t web49_io_input_ftell(web49_io_input_t *in);
size_t web49_io_input_fread(web49_io_input_t *in, size_t size, void *data);
char web49_io_input_fgetc(web49_io_input_t *in);
void web49_io_input_rewind(web49_io_input_t *in);

#endif
