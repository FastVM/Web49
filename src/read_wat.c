#include "read_wat.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum {
    WEB49_READWAT_EXPR_TAG_INIT,
    WEB49_READWAT_EXPR_TAG_FUN,
    WEB49_READWAT_EXPR_TAG_STR,
};

struct web49_readwat_state_t;
typedef struct web49_readwat_state_t web49_readwat_state_t;

struct web49_readwat_expr_t;
typedef struct web49_readwat_expr_t web49_readwat_expr_t;

struct web49_readwat_state_t {
    size_t alloc_type;
    size_t alloc_import;
    size_t alloc_function;
    size_t alloc_table;
    size_t alloc_memory;
    size_t alloc_export;
    size_t alloc_element;
    size_t alloc_data;
    web49_section_type_t stype;
    web49_section_import_t simport;
    web49_section_function_t sfunction;
    web49_section_table_t stable;
    web49_section_memory_t smemory;
    web49_section_export_t sexport;
    web49_section_element_t selement;
    web49_section_data_t sdata;
};

struct web49_readwat_expr_t {
    size_t start;
    size_t end;
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
    size_t start = ftell(in);
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
            .start = start,
            .end = ftell(in),
            .fun_fun = name,
            .fun_nargs = nargs,
            .fun_args = args,
            .tag = WEB49_READWAT_EXPR_TAG_FUN,
        };
    }
    if (first == '"') {
        size_t alloc = 16;
        char *buf = web49_malloc(sizeof(char) * alloc);
        size_t len = 0;
        while (true) {
            if (first == '"') {
                break;
            }
            if (len + 2 >= alloc) {
                alloc *= 2;
                buf = web49_realloc(buf, sizeof(char) * alloc);
            }
            if (first == '\\') {
                char escape = fgetc(in);
                if (isdigit(escape)) {
                    size_t high = (escape - '0');
                    size_t low = (fgetc(in) - '0');
                    buf[len++] = (char) (high * 16 + low);
                } else {
                    buf[len++] = escape;
                }
            } else {
                buf[len++] = first;
            }
            first = fgetc(in);
        }
        buf[len] = '\0';
        return (web49_readwat_expr_t) {
            .start = start,
            .end = ftell(in),
            .str = buf,
            .tag = WEB49_READWAT_EXPR_TAG_STR,
        };
    }
    ungetc(first, in);
    return (web49_readwat_expr_t) {
        .start = start,
        .end = ftell(in),
        .str = web49_readwat_name(in),
        .tag = WEB49_READWAT_EXPR_TAG_STR,
    };
}

static uint64_t web49_readwat_expr_to_u64(web49_readwat_expr_t expr);
static void web49_readwat_state_type_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_import_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_function_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_table_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_memory_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_export_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_element_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_data_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);

static uint64_t web49_readwat_expr_to_u64(web49_readwat_expr_t expr) {
    uint64_t x = 0;
    for (const char *str = expr.str; *str != '\0'; str += 1) {
        x *= 10;
        x += *str - '0';
    }
    return x;
}

static void web49_readwat_state_type_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_lang_type_t type;
    
    uint64_t num_params = 0;
    web49_lang_type_t *params = NULL;
    uint64_t alloc_params = 0;

    uint64_t num_returns = 0;
    web49_lang_type_t return_type;
    
    for (size_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t func = expr.fun_args[i];
        if (func.tag != WEB49_READWAT_EXPR_TAG_FUN) {
            fprintf(stderr, "expected (func ...) type, not `%s`\n", func.str);
            exit(1);
        }
        if (!!strcmp(func.fun_fun, "func")) {
            fprintf(stderr, "expected (func ...) type, not (%s ...)\n", func.fun_fun);
            exit(1);
        }
        type = WEB49_TYPE_FUNC;
        for (size_t j = 0; j < func.fun_nargs; j++) {
            web49_readwat_expr_t arg = func.fun_args[j];
            if (arg.tag != WEB49_READWAT_EXPR_TAG_FUN) {
                fprintf(stderr, "expected `result` or `param`, not `%s`\n", arg.fun_fun);
                exit(1);
            }
            if (arg.tag != WEB49_READWAT_EXPR_TAG_FUN) {
                fprintf(stderr, "expected (param ...) or (result ...)\n");
                exit(1);
            }
            if (!strcmp(arg.fun_fun, "param")) {
                for (size_t k = 0; k < arg.fun_nargs; k++) {
                    if (num_params + 2 >= alloc_params) {
                        alloc_params = (num_params + 2) * 2;
                        params = web49_realloc(params, sizeof(web49_lang_type_t) * alloc_params);
                    }
                    web49_readwat_expr_t name = arg.fun_args[k];
                    if (name.tag != WEB49_READWAT_EXPR_TAG_STR) {
                        fprintf(stderr, "expected param to be `i32` or `i64` or `f32` or `f64`\n");
                        exit(1);
                    }
                    if (!strcmp(name.str, "i32")) {
                        params[num_params++] = WEB49_TYPE_I32;
                    } else if (!strcmp(name.str, "i64")) {
                        params[num_params++] = WEB49_TYPE_I64;
                    } else if (!strcmp(name.str, "f32")) {
                        params[num_params++] = WEB49_TYPE_F32;
                    } else if (!strcmp(name.str, "f64")) {
                        params[num_params++] = WEB49_TYPE_F64;
                    } else {
                        fprintf(stderr, "expected param to be `i32` or `i64` or `f32` or `f64`, not `%s`\n", name.str);
                        exit(1);
                    }
                }
            } else if (!strcmp(arg.fun_fun, "result")) {
                for (size_t k = 0; k < arg.fun_nargs; k++) {
                    if (num_returns != 0) {
                        fprintf(stderr, "expected you not to use multi-results :(\n");
                        exit(1);
                    }
                    web49_readwat_expr_t name = arg.fun_args[k];
                    if (name.tag != WEB49_READWAT_EXPR_TAG_STR) {
                        fprintf(stderr, "expected result to be `i32` or `i64` or `f32` or `f64`\n");
                        exit(1);
                    }
                    if (!strcmp(name.str, "i32")) {
                        return_type = WEB49_TYPE_I32;
                    } else if (!strcmp(name.str, "i64")) {
                        return_type = WEB49_TYPE_I64;
                    } else if (!strcmp(name.str, "f32")) {
                        return_type = WEB49_TYPE_F32;
                    } else if (!strcmp(name.str, "f64")) {
                        return_type = WEB49_TYPE_F64;
                    } else {
                        fprintf(stderr, "expected result to be `i32` or `i64` or `f32` or `f64`, not `%s`\n", name.str);
                        exit(1);
                    } 
                    num_returns += 1;
                }
            } else {
                fprintf(stderr, "expected (result ...) or (param ...)\n");
                exit(1);
            }
        }
    }
    if (type == 0) {
        fprintf(stderr, "could not figure out type\n");
        exit(1);
    }
    if (out->stype.num_entries + 1 >= out->alloc_type) {
        out->alloc_type = (out->stype.num_entries + 1) * 2;
        out->stype.entries = web49_realloc(out->stype.entries, sizeof(web49_section_type_entry_t) * out->alloc_type);
    }
    out->stype.entries[out->stype.num_entries++] = (web49_section_type_entry_t) {
        .type = type,
        .num_params = num_params,
        .params = params,
        .num_returns = num_returns,
        .return_type = return_type,
        .has_return_type = num_returns != 0,
    };
}

static void web49_readwat_state_modlevel(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    if (expr.tag != WEB49_READWAT_EXPR_TAG_FUN) {
        fprintf(stderr, "expected `(` at module of file\n");
    }
    if (!strcmp(expr.fun_fun, "type")) {
        web49_readwat_state_type_entry(out, expr);
    }
}

static void web49_readwat_state_toplevel(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    if (expr.tag != WEB49_READWAT_EXPR_TAG_FUN) {
        fprintf(stderr, "expected `(` at toplevel of file\n");
        exit(1);
    }
    if (!!strcmp(expr.fun_fun, "module")) {
        fprintf(stderr, "expected module to be the first expression in the file\n");
        exit(1);
    }
    for (size_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_state_modlevel(out, expr.fun_args[i]);
    }
}

web49_module_t web49_readwat_module(FILE *in) {
    web49_readwat_state_t state = { 0 };
    web49_readwat_expr_t expr = web49_readwat_expr(in);
    web49_readwat_state_toplevel(&state, expr);
    uint64_t num_sections = 0;
    web49_section_t *sections = web49_malloc(sizeof(web49_section_t) * 12);
    if (state.stype.num_entries != 0) {
        sections[num_sections++] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_TYPE,
                .size_known = false,
            },
            .type_section = state.stype,
        };
    }
    if (state.simport.num_entries != 0) {
        sections[num_sections++] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_IMPORT,
                .size_known = false,
            },
            .import_section = state.simport,
        };
    }
    if (state.sfunction.num_entries != 0) {
        sections[num_sections++] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_FUNCTION,
                .size_known = false,
            },
            .function_section = state.sfunction,
        };
    }
    if (state.stable.num_entries != 0) {
        sections[num_sections++] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_TABLE,
                .size_known = false,
            },
            .table_section = state.stable,
        };
    }
    if (state.smemory.num_entries != 0) {
        sections[num_sections++] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_MEMORY,
                .size_known = false,
            },
            .memory_section = state.smemory,
        };
    }
    if (state.sexport.num_entries != 0) {
        sections[num_sections++] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_EXPORT,
                .size_known = false,
            },
            .export_section = state.sexport,
        };
    }
    if (state.selement.num_entries != 0) {
        sections[num_sections++] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_ELEMENT,
                .size_known = false,
            },
            .element_section = state.selement,
        };
    }
    if (state.sdata.num_entries != 0) {
        sections[num_sections++] = (web49_section_t) {
            .header = (web49_section_header_t) {
                .id = WEB49_SECTION_ID_DATA,
                .size_known = false,
            },
            .data_section = state.sdata,
        };
    }
    return (web49_module_t) {
        .num_sections = num_sections,
        .sections = sections,
        .preamble = web49_preamble_init,
    };
}
