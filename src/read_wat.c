#include "read_wat.h"
#include <ctype.h>
#include <stdio.h>

struct web49_readwat_expr_t;
typedef struct web49_readwat_expr_t web49_readwat_expr_t;

enum {
    WEB49_READWAT_EXPR_TAG_FUN,
    WEB49_READWAT_EXPR_TAG_STR,
};

struct web49_readwat_expr_t {
    union {
        struct {
            const char *fun_fun;
            size_t fun_nargs;
            web49_readwat_expr_t *fun_args;
        };
        const char *str;
    };
    uint8_t tag;
};

const char *web49_readwat_name(FILE *in) {
    char first = fgetc(in);
    if (first == ';') {
        return ";";
    }
    size_t alloc = 16;
    char *buf = web49_malloc(sizeof(char) * alloc);
    size_t len = 0;
    while (true) {
        if (isspace(first) || first == '(' || first == ')') {
            break;
        }
        if (len + 2 >= alloc) {
            alloc *= 2;
            buf = web49_realloc(buf, sizeof(char) * alloc);
        }
        buf[len++] = first;
        first = fgetc(in);
    }
    ungetc(first, in);
    buf[len] = '\0';
    return buf;
}

web49_readwat_expr_t web49_readwat_expr(FILE *in) {
redo:;
    char first = fgetc(in);
    while (isspace(first)) {
        first = fgetc(in);
    }
    if (first == '(') {
        const char *name = web49_readwat_name(in);
        if (!strcmp(name, ";")) {
            size_t depth = 1;
            while (depth != 0) {
                char comment = fgetc(in);
                if (comment == '(') {
                    depth += 1;
                }
                if (comment == ')') {
                    depth -= 1;
                }
            }
            goto redo;
        }
        size_t alloc = 4;
        web49_readwat_expr_t *args = web49_malloc(sizeof(web49_readwat_expr_t) * alloc);
        size_t nargs = 0;
        while (true) {
            if (nargs + 2 >= alloc) {
                alloc *= 2;
                args = web49_realloc(args, sizeof(web49_readwat_expr_t) * alloc);
            }
            first = fgetc(in);
            while (isspace(first)) {
                first = fgetc(in);
            }
            if (first == ')') {
                break;
            }
            ungetc(first, in);
            args[nargs++] = web49_readwat_expr(in);
        }
        return (web49_readwat_expr_t) {
            .fun_fun = name,
            .fun_nargs = nargs,
            .fun_args = args,
            .tag = WEB49_READWAT_EXPR_TAG_FUN,
        };
    }
    ungetc(first, in);
    return (web49_readwat_expr_t) {
        .str = web49_readwat_name(in),
        .tag = WEB49_READWAT_EXPR_TAG_STR,
    };
}

web49_module_t web49_readwat_module(FILE *in) {
    web49_section_type_t stype = (web49_section_type_t) {};
    web49_section_import_t simport = (web49_section_import_t) {};
    web49_section_function_t sfunction = (web49_section_function_t) {};
    web49_section_table_t stable = (web49_section_table_t) {};
    web49_section_memory_t smemory = (web49_section_memory_t) {};
    web49_section_export_t sexport = (web49_section_export_t) {};
    web49_section_element_t selement = (web49_section_element_t) {};
    web49_section_data_t sdata = (web49_section_data_t) {};
    web49_readwat_expr_t expr = web49_readwat_expr(in);
    uint64_t num_sections = 0;
    web49_section_t *sections = web49_malloc(sizeof(web49_section_t) * 12);
    if (stype.num_entries != 0) {
        sections[num_sections] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_TYPE,
                .size_known = false,
            },
            .type_section = stype,
        };
    }
    if (simport.num_entries != 0) {
        sections[num_sections] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_IMPORT,
                .size_known = false,
            },
            .import_section = simport,
        };
    }
    if (sfunction.num_entries != 0) {
        sections[num_sections] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_FUNCTION,
                .size_known = false,
            },
            .function_section = sfunction,
        };
    }
    if (stable.num_entries != 0) {
        sections[num_sections] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_TABLE,
                .size_known = false,
            },
            .table_section = stable,
        };
    }
    if (smemory.num_entries != 0) {
        sections[num_sections] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_MEMORY,
                .size_known = false,
            },
            .memory_section = smemory,
        };
    }
    if (sexport.num_entries != 0) {
        sections[num_sections] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_EXPORT,
                .size_known = false,
            },
            .export_section = sexport,
        };
    }
    if (selement.num_entries != 0) {
        sections[num_sections] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_ELEMENT,
                .size_known = false,
            },
            .element_section = selement,
        };
    }
    if (sdata.num_entries != 0) {
        sections[num_sections] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_DATA,
                .size_known = false,
            },
            .data_section = sdata,
        };
    }
    return (web49_module_t) {
        .num_sections = num_sections,
        .sections = sections,
        .preamble = web49_preamble_init,
    };
}
