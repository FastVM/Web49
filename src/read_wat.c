#include "read_wat.h"

#include "tables.h"

void web49_readwat_table_set(web49_readwat_table_t *restrict table, const char *key, uint64_t value) {
    if (table->len + 2 >= table->alloc) {
        table->alloc = (table->len + 2) * 2;
        table->key = web49_realloc(table->key, sizeof(const char *) * table->alloc);
        table->value = web49_realloc(table->value, sizeof(uint64_t) * table->alloc);
    }
    table->key[table->len] = key;
    table->value[table->len] = value;
    table->len += 1;
}

uint64_t web49_readwat_table_get(web49_readwat_table_t *restrict table, const char *key) {
    for (uint64_t i = 0; i < table->len; i++) {
        if (!strcmp(table->key[i], key)) {
            return table->value[i];
        }
    }
    return UINT64_MAX;
}

const char *web49_readwat_name(web49_io_input_t *in) {
    char first = web49_io_input_fgetc(in);
    if (first == ';') {
        if (web49_io_input_fgetc(in) != ';') {
            web49_io_input_rewind(in);
            return ";";
        }
        while (web49_io_input_fgetc(in) != '\n') {
        }
    }
    uint64_t alloc = 8;
    char *buf = web49_malloc(sizeof(char) * alloc);
    uint64_t len = 0;
    while (true) {
        if (isspace(first) || first == '(' || first == ')' || first == '\0' || first == EOF) {
            break;
        }
        if (len + 2 >= alloc) {
            alloc *= 2;
            buf = web49_realloc(buf, sizeof(char) * alloc);
        }
        buf[len++] = first;
        first = web49_io_input_fgetc(in);
    }
    web49_io_input_rewind(in);
    buf[len] = '\0';
    return buf;
}

web49_readwat_expr_t web49_readwat_expr(web49_io_input_t *in) {
redo:;
    uint64_t start = web49_io_input_ftell(in);
    char first = web49_io_input_fgetc(in);
    while (isspace(first)) {
        first = web49_io_input_fgetc(in);
    }
    if (first == ';') {
        char second = web49_io_input_fgetc(in);
        if (second == ';') {
            while (web49_io_input_fgetc(in) != '\n') {
            }
            goto redo;
        }
        web49_io_input_rewind(in);
    }
    if (first == '(') {
        const char *name = web49_readwat_name(in);
        if (!strcmp(name, ";")) {
            uint64_t depth = 1;
            while (depth != 0) {
                char comment = web49_io_input_fgetc(in);
                if (comment == '(') {
                    depth += 1;
                }
                if (comment == ')') {
                    depth -= 1;
                }
            }
            goto redo;
        }
        uint64_t alloc = 4;
        web49_readwat_expr_t *args = web49_malloc(sizeof(web49_readwat_expr_t) * alloc);
        uint64_t nargs = 0;
        while (true) {
            if (nargs + 2 >= alloc) {
                alloc *= 2;
                args = web49_realloc(args, sizeof(web49_readwat_expr_t) * alloc);
            }
            first = web49_io_input_fgetc(in);
            while (isspace(first)) {
                first = web49_io_input_fgetc(in);
            }
            if (first == ')' || first == '\0' || first == EOF) {
                break;
            }
            web49_io_input_rewind(in);
            args[nargs++] = web49_readwat_expr(in);
        }
        return (web49_readwat_expr_t){
            .start = start,
            .end = web49_io_input_ftell(in),
            .fun_fun = name,
            .fun_nargs = nargs,
            .fun_args = args,
            .tag = WEB49_READWAT_EXPR_TAG_FUN,
        };
    }
    if (first == '"') {
        uint64_t alloc = 16;
        uint8_t *buf = web49_malloc(sizeof(uint8_t) * alloc);
        uint64_t len = 0;
        first = web49_io_input_fgetc(in);
        while (true) {
            if (first == '"') {
                break;
            }
            if (len + 2 >= alloc) {
                alloc *= 2;
                buf = web49_realloc(buf, sizeof(uint8_t) * alloc);
            }
            if (first == '\\') {
                char escape = web49_io_input_fgetc(in);
                if (isdigit(escape) || ('a' <= escape && escape <= 'f')) {
                    char c1 = escape;
                    char c2 = web49_io_input_fgetc(in);
                    uint64_t high = isdigit(c1) ? c1 - '0' : c1 - 'a' + 10;
                    uint64_t low = isdigit(c2) ? c2 - '0' : c2 - 'a' + 10;
                    buf[len++] = (uint8_t)(high * 16 + low);
                } else {
                    buf[len++] = escape;
                }
            } else {
                buf[len++] = first;
            }
            first = web49_io_input_fgetc(in);
        }
        buf[len] = '\0';
        return (web49_readwat_expr_t){
            .start = start,
            .end = web49_io_input_ftell(in),
            .len_str = len,
            .str = buf,
            .tag = WEB49_READWAT_EXPR_TAG_STR,
        };
    }
    web49_io_input_rewind(in);
    return (web49_readwat_expr_t){
        .start = start,
        .end = web49_io_input_ftell(in),
        .sym = web49_readwat_name(in),
        .tag = WEB49_READWAT_EXPR_TAG_SYM,
    };
}

uint64_t web49_readwat_expr_to_u64(const char *arg) {
    uint64_t x = 0;
    for (const char *str = arg; *str != '\0'; str += 1) {
        x *= 10;
        x += *str - '0';
    }
    return x;
}

int64_t web49_readwat_expr_to_i64(const char *arg) {
    const char *str = arg;
    bool pos = true;
    if (*str == '-') {
        pos = false;
        str += 1;
    } else if (*str == '+') {
        pos = true;
        str += 1;
    }
    __int128 x = 0;
    while (*str != '\0') {
        x *= 10;
        x += *str - '0';
        str += 1;
    }
    if (!pos) {
        x *= -1;
    }
    return (int64_t)x;
}

void web49_readwat_state_type_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_lang_type_t type;

    uint64_t num_params = 0;
    web49_lang_type_t *params = NULL;
    uint64_t alloc_params = 0;

    uint64_t num_returns = 0;
    web49_lang_type_t return_type;

    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t func = expr.fun_args[i];
        if (func.tag != WEB49_READWAT_EXPR_TAG_FUN) {
            fprintf(stderr, "expected (func ...) type, not `%s`\n", func.sym);
            exit(1);
        }
        if (!!strcmp(func.fun_fun, "func")) {
            fprintf(stderr, "expected (func ...) type, not (%s ...)\n", func.fun_fun);
            exit(1);
        }
        type = WEB49_TYPE_FUNC;
        for (uint64_t j = 0; j < func.fun_nargs; j++) {
            web49_readwat_expr_t arg = func.fun_args[j];
            if (arg.tag != WEB49_READWAT_EXPR_TAG_FUN) {
                web49_readwat_table_set(&out->type_table, arg.sym, out->stype.num_entries);
                continue;
            }
            if (arg.tag != WEB49_READWAT_EXPR_TAG_FUN) {
                fprintf(stderr, "expected (param ...) or (result ...)\n");
                exit(1);
            }
            if (!strcmp(arg.fun_fun, "param")) {
                for (uint64_t k = 0; k < arg.fun_nargs; k++) {
                    if (num_params + 2 >= alloc_params) {
                        alloc_params = (num_params + 2) * 2;
                        params = web49_realloc(params, sizeof(web49_lang_type_t) * alloc_params);
                    }
                    web49_readwat_expr_t name = arg.fun_args[k];
                    if (name.tag != WEB49_READWAT_EXPR_TAG_SYM) {
                        fprintf(stderr, "expected param to be `i32` or `i64` or `f32` or `f64`\n");
                        exit(1);
                    }
                    if (!strcmp(name.sym, "i32")) {
                        params[num_params++] = WEB49_TYPE_I32;
                    } else if (!strcmp(name.sym, "i64")) {
                        params[num_params++] = WEB49_TYPE_I64;
                    } else if (!strcmp(name.sym, "f32")) {
                        params[num_params++] = WEB49_TYPE_F32;
                    } else if (!strcmp(name.sym, "f64")) {
                        params[num_params++] = WEB49_TYPE_F64;
                    } else {
                        fprintf(stderr, "expected param to be `i32` or `i64` or `f32` or `f64`, not `%s`\n", name.sym);
                        exit(1);
                    }
                }
            } else if (!strcmp(arg.fun_fun, "result")) {
                for (uint64_t k = 0; k < arg.fun_nargs; k++) {
                    if (num_returns != 0) {
                        fprintf(stderr, "expected you not to use multi-results :(\n");
                        exit(1);
                    }
                    web49_readwat_expr_t name = arg.fun_args[k];
                    if (name.tag != WEB49_READWAT_EXPR_TAG_SYM) {
                        fprintf(stderr, "expected result to be `i32` or `i64` or `f32` or `f64`\n");
                        exit(1);
                    }
                    if (!strcmp(name.sym, "i32")) {
                        return_type = WEB49_TYPE_I32;
                    } else if (!strcmp(name.sym, "i64")) {
                        return_type = WEB49_TYPE_I64;
                    } else if (!strcmp(name.sym, "f32")) {
                        return_type = WEB49_TYPE_F32;
                    } else if (!strcmp(name.sym, "f64")) {
                        return_type = WEB49_TYPE_F64;
                    } else {
                        fprintf(stderr, "expected result to be `i32` or `i64` or `f32` or `f64`, not `%s`\n", name.sym);
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
    out->stype.entries[out->stype.num_entries++] = (web49_section_type_entry_t){
        .type = type,
        .num_params = num_params,
        .params = params,
        .num_returns = num_returns,
        .return_type = return_type,
        .has_return_type = num_returns != 0,
    };
}

const char *web49_readwat_sym_to_str(web49_readwat_expr_t expr) {
    char *str = web49_malloc(sizeof(char) * (expr.len_str + 1));
    memcpy(str, expr.str, expr.len_str);
    str[expr.len_str] = '\0';
    return str;
}

void web49_readwat_state_import_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_section_import_entry_t entry = (web49_section_import_entry_t){
        .module_str = web49_readwat_sym_to_str(expr.fun_args[0]),
        .field_str = web49_readwat_sym_to_str(expr.fun_args[1]),
    };
    if (expr.fun_args[2].tag != WEB49_READWAT_EXPR_TAG_FUN) {
        fprintf(stderr, "expected (func ...) or (table ...) or (memory ...) or (global ..), not `%s`\n", expr.fun_args[2].sym);
    }
    if (!strcmp(expr.fun_args[2].fun_fun, "func")) {
        entry.kind = WEB49_EXTERNAL_KIND_FUNCTION;
        for (uint64_t i = 0; i < expr.fun_args[2].fun_nargs; i++) {
            web49_readwat_expr_t func = expr.fun_args[2].fun_args[i];
            if (func.tag == WEB49_READWAT_EXPR_TAG_SYM) {
                web49_readwat_table_set(&out->func_table, func.sym, out->simport.num_entries);
            } else if (!strcmp(func.fun_fun, "type")) {
                entry.func_type.data = web49_readwat_expr_to_u64(func.fun_args[0].sym);
            } else {
                fprintf(stderr, "expected $name or (type ...)\n");
                exit(1);
            }
        }
        out->num_func_imports += 1;
    } else if (!strcmp(expr.fun_args[2].fun_fun, "table")) {
        entry.kind = WEB49_EXTERNAL_KIND_TABLE;
    } else if (!strcmp(expr.fun_args[2].fun_fun, "memory")) {
        entry.kind = WEB49_EXTERNAL_KIND_MEMORY;
        if (expr.fun_args[2].fun_nargs == 1) {
            entry.memory_type.initial = web49_readwat_expr_to_u64(expr.fun_args[2].fun_args[0].sym);
            entry.memory_type.maximum = UINT64_MAX;
        } else if (expr.fun_args[2].fun_nargs == 1) {
            entry.memory_type.initial = web49_readwat_expr_to_u64(expr.fun_args[2].fun_args[0].sym);
            entry.memory_type.maximum = web49_readwat_expr_to_u64(expr.fun_args[2].fun_args[1].sym);
        }
    } else if (!strcmp(expr.fun_args[2].fun_fun, "global")) {
        entry.kind = WEB49_EXTERNAL_KIND_GLOBAL;
        bool ismut = false;
        web49_readwat_expr_t tglobal = (web49_readwat_expr_t){.tag = WEB49_READWAT_EXPR_TAG_INIT};
        for (uint64_t i = 0; i < expr.fun_args[2].fun_nargs; i++) {
            web49_readwat_expr_t arg = expr.fun_args[2].fun_args[i];
            if (arg.tag == WEB49_READWAT_EXPR_TAG_SYM) {
                if (arg.sym[0] == '$') {
                    web49_readwat_table_set(&out->global_table, arg.sym, out->simport.num_entries);
                } else {
                    tglobal = arg;
                }
            } else if (!strcmp(arg.fun_fun, "mut")) {
                if (arg.fun_nargs < 1) {
                    fprintf(stderr, "expected argument inside of parens of (mut), not just `mut`\n");
                    exit(1);
                }
                if (arg.fun_nargs > 1) {
                    fprintf(stderr, "expected only one argument inside of parens of (mut), not `mut` + %zu others\n", (size_t)arg.fun_nargs);
                    exit(1);
                }
                tglobal = arg.fun_args[0];
                ismut = true;
            } else {
                fprintf(stderr, "expected $name, (mut ...) or a language type\n");
                exit(1);
            }
        }
        if (tglobal.tag != WEB49_READWAT_EXPR_TAG_SYM) {
            fprintf(stderr, "expected a type for the global\n");
            exit(1);
        }
        if (!strcmp(tglobal.sym, "i32")) {
            entry.global_type.content_type = WEB49_TYPE_I32;
        } else if (!strcmp(tglobal.sym, "i64")) {
            entry.global_type.content_type = WEB49_TYPE_I64;
        } else if (!strcmp(tglobal.sym, "f32")) {
            entry.global_type.content_type = WEB49_TYPE_F32;
        } else if (!strcmp(tglobal.sym, "f64")) {
            entry.global_type.content_type = WEB49_TYPE_F64;
        } else {
            fprintf(stderr, "exepcted a type name for the global, not `%s`", tglobal.sym);
            exit(1);
        }
        entry.global_type.is_mutable = ismut;
    }
    if (out->simport.num_entries + 1 >= out->alloc_import) {
        out->alloc_import = (out->simport.num_entries + 1) * 2;
        out->simport.entries = web49_realloc(out->simport.entries, sizeof(web49_section_import_entry_t) * out->alloc_import);
    }
    out->simport.entries[out->simport.num_entries++] = entry;
}

void web49_readwat_state_func_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    {
        uint64_t entry = UINT64_MAX;
        for (uint64_t i = 0; i < expr.fun_nargs; i++) {
            web49_readwat_expr_t code = expr.fun_args[i];
            if (code.tag == WEB49_READWAT_EXPR_TAG_FUN) {
                if (!strcmp(code.fun_fun, "type")) {
                    entry = web49_readwat_expr_to_u64(code.fun_args[0].sym);
                    break;
                } else {
                    web49_lang_type_t type = WEB49_TYPE_FUNC;
                    uint64_t num_params = 0;
                    web49_lang_type_t *params = NULL;
                    uint64_t alloc_params = 0;
                    uint64_t num_returns = 0;
                    web49_lang_type_t return_type;
                    web49_readwat_expr_t paramres = expr.fun_args[i++];
                    if (!strcmp(paramres.fun_fun, "param")) {
                        for (uint64_t k = 0; k < paramres.fun_nargs; k++) {
                            if (num_params + 2 >= alloc_params) {
                                alloc_params = (num_params + 2) * 2;
                                params = web49_realloc(params, sizeof(web49_lang_type_t) * alloc_params);
                            }
                            web49_readwat_expr_t name = paramres.fun_args[k];
                            if (name.tag != WEB49_READWAT_EXPR_TAG_SYM) {
                                fprintf(stderr, "expected param to be `i32` or `i64` or `f32` or `f64`\n");
                                exit(1);
                            }
                            if (!strcmp(name.sym, "i32")) {
                                params[num_params++] = WEB49_TYPE_I32;
                            } else if (!strcmp(name.sym, "i64")) {
                                params[num_params++] = WEB49_TYPE_I64;
                            } else if (!strcmp(name.sym, "f32")) {
                                params[num_params++] = WEB49_TYPE_F32;
                            } else if (!strcmp(name.sym, "f64")) {
                                params[num_params++] = WEB49_TYPE_F64;
                            } else {
                                fprintf(stderr, "expected param to be `i32` or `i64` or `f32` or `f64`, not `%s`\n", name.sym);
                                exit(1);
                            }
                        }
                        paramres = expr.fun_args[i++];
                    }
                    if (!strcmp(paramres.fun_fun, "result")) {
                        for (uint64_t k = 0; k < paramres.fun_nargs; k++) {
                            if (num_returns != 0) {
                                fprintf(stderr, "expected you not to use multi-results :(\n");
                                exit(1);
                            }
                            web49_readwat_expr_t name = paramres.fun_args[k];
                            if (name.tag != WEB49_READWAT_EXPR_TAG_SYM) {
                                fprintf(stderr, "expected result to be `i32` or `i64` or `f32` or `f64`\n");
                                exit(1);
                            }
                            if (!strcmp(name.sym, "i32")) {
                                return_type = WEB49_TYPE_I32;
                            } else if (!strcmp(name.sym, "i64")) {
                                return_type = WEB49_TYPE_I64;
                            } else if (!strcmp(name.sym, "f32")) {
                                return_type = WEB49_TYPE_F32;
                            } else if (!strcmp(name.sym, "f64")) {
                                return_type = WEB49_TYPE_F64;
                            } else {
                                fprintf(stderr, "expected result to be `i32` or `i64` or `f32` or `f64`, not `%s`\n", name.sym);
                                exit(1);
                            }
                            num_returns += 1;
                        }
                    }
                    if (out->stype.num_entries + 1 >= out->alloc_type) {
                        out->alloc_type = (out->stype.num_entries + 1) * 2;
                        out->stype.entries = web49_realloc(out->stype.entries, sizeof(web49_section_type_entry_t) * out->alloc_type);
                    }
                    entry = out->stype.num_entries;
                    out->stype.entries[out->stype.num_entries++] = (web49_section_type_entry_t){
                        .type = type,
                        .num_params = num_params,
                        .params = params,
                        .num_returns = num_returns,
                        .return_type = return_type,
                        .has_return_type = num_returns != 0,
                    };
                    break;
                }
            }
        }
        if (entry == UINT64_MAX) {
            if (out->stype.num_entries + 1 >= out->alloc_type) {
                out->alloc_type = (out->stype.num_entries + 1) * 2;
                out->stype.entries = web49_realloc(out->stype.entries, sizeof(web49_section_type_entry_t) * out->alloc_type);
            }
            entry = out->stype.num_entries;
            out->stype.entries[out->stype.num_entries++] = (web49_section_type_entry_t){
                .type = WEB49_TYPE_FUNC,
                .num_params = 0,
                .params = NULL,
                .num_returns = 0,
                .return_type = 0,
                .has_return_type = false,
            };
        }
        if (out->sfunction.num_entries + 1 >= out->alloc_function) {
            out->alloc_function = (out->sfunction.num_entries + 1) * 2;
            out->sfunction.entries = web49_realloc(out->sfunction.entries, sizeof(uint64_t) * out->alloc_function);
        }
        out->sfunction.entries[out->sfunction.num_entries++] = entry;
    }
    {
        uint64_t alloc_locals = 0;
        uint64_t alloc_instrs = 0;
        web49_section_code_entry_t entry = (web49_section_code_entry_t){
            .num_locals = 0,
            .locals = NULL,
            .num_instrs = 0,
            .instrs = NULL,
        };
        for (uint64_t i = 0; i < expr.fun_nargs; i++) {
            web49_readwat_expr_t code = expr.fun_args[i];
            if (code.tag == WEB49_READWAT_EXPR_TAG_SYM) {
                web49_opcode_t opcode = web49_name_to_opcode(code.sym);
                if (opcode < WEB49_MAX_OPCODE_NUM) {
                    web49_immediate_id_t id = web49_opcode_immediate[opcode];
                    web49_instr_immediate_t imm = (web49_instr_immediate_t){
                        .id = id,
                    };
                    switch (id) {
                        case WEB49_IMMEDIATE_NONE:
                            break;
                        case WEB49_IMMEDIATE_BLOCK_TYPE:
                            if (expr.fun_args[i + 1].tag == WEB49_READWAT_EXPR_TAG_FUN && !strcmp(expr.fun_args[i + 1].fun_fun, "result")) {
                                web49_readwat_expr_t arg = expr.fun_args[i + 1].fun_args[0];
                                if (arg.tag != WEB49_READWAT_EXPR_TAG_SYM) {
                                    fprintf(stderr, "expected basic type\n");
                                    exit(1);
                                }
                                if (!strcmp(arg.sym, "i32")) {
                                    imm.block_type = WEB49_TYPE_I32;
                                } else if (!strcmp(arg.sym, "i64")) {
                                    imm.block_type = WEB49_TYPE_I64;
                                } else if (!strcmp(arg.sym, "f32")) {
                                    imm.block_type = WEB49_TYPE_F32;
                                } else if (!strcmp(arg.sym, "f64")) {
                                    imm.block_type = WEB49_TYPE_F64;
                                } else {
                                    fprintf(stderr, "expected basic type name, not `%s`\n", arg.sym);
                                    exit(1);
                                }
                            } else {
                                imm.block_type = WEB49_TYPE_BLOCK_TYPE;
                            }
                            break;
                        case WEB49_IMMEDIATE_VARUINT1:
                            imm.varuint1 = 0;
                            break;
                        case WEB49_IMMEDIATE_VARUINT32:
                            imm.varuint32 = (uint32_t)web49_readwat_expr_to_u64(expr.fun_args[++i].sym);
                            break;
                        case WEB49_IMMEDIATE_VARUINT64:
                            imm.varuint64 = (uint64_t)web49_readwat_expr_to_u64(expr.fun_args[++i].sym);
                            break;
                        case WEB49_IMMEDIATE_VARINT32:
                            imm.varuint64 = (int32_t)web49_readwat_expr_to_i64(expr.fun_args[++i].sym);
                            break;
                        case WEB49_IMMEDIATE_VARINT64:
                            imm.varuint64 = (int64_t)web49_readwat_expr_to_i64(expr.fun_args[++i].sym);
                            break;
                        case WEB49_IMMEDIATE_UINT32:
                            imm.varuint32 = (uint32_t)web49_readwat_expr_to_u64(expr.fun_args[++i].sym);
                            break;
                        case WEB49_IMMEDIATE_UINT64:
                            imm.varuint64 = (uint64_t)web49_readwat_expr_to_u64(expr.fun_args[++i].sym);
                            break;
                        case WEB49_IMMEDIATE_BR_TABLE: {
                            i += 1;
                            uint64_t alloc = 0;
                            while (i + 1 < expr.fun_nargs && isdigit(expr.fun_args[i + 1].sym[0])) {
                                if (imm.br_table.num_targets + 2 >= alloc) {
                                    alloc = (imm.br_table.num_targets + 2) * 2;
                                    imm.br_table.targets = web49_realloc(imm.br_table.targets, sizeof(uint64_t) * alloc);
                                }
                                imm.br_table.targets[imm.br_table.num_targets++] = web49_readwat_expr_to_u64(expr.fun_args[i++].sym);
                            }
                            imm.br_table.default_target = web49_readwat_expr_to_u64(expr.fun_args[i].sym);
                            break;
                        }
                        case WEB49_IMMEDIATE_CALL_INDIRECT:
                            imm.call_indirect.index = (uint64_t)web49_readwat_expr_to_u64(expr.fun_args[++i].fun_args[0].sym);
                            break;
                        case WEB49_IMMEDIATE_MEMORY_IMMEDIATE: {
                            switch (web49_opcode_memsize[opcode]) {
                                case 1:
                                    imm.memory_immediate.align = 0;
                                    break;
                                case 2:
                                    imm.memory_immediate.align = 1;
                                    break;
                                case 4:
                                    imm.memory_immediate.align = 2;
                                    break;
                                case 8:
                                    imm.memory_immediate.align = 3;
                                    break;
                                case 16:
                                    imm.memory_immediate.align = 4;
                                    break;
                            }
                        redo:;
                            web49_readwat_expr_t arg = expr.fun_args[i + 1];
                            if (arg.tag == WEB49_READWAT_EXPR_TAG_SYM) {
                                if (!strncmp(arg.sym, "align=", 6)) {
                                    uint64_t n = web49_readwat_expr_to_u64(&arg.sym[6]);
                                    uint64_t nat_align = imm.memory_immediate.align;
                                    switch (n) {
                                        case 1:
                                            imm.memory_immediate.align = 0;
                                            break;
                                        case 2:
                                            imm.memory_immediate.align = 1;
                                            break;
                                        case 4:
                                            imm.memory_immediate.align = 2;
                                            break;
                                        case 8:
                                            imm.memory_immediate.align = 3;
                                            break;
                                        default:
                                            fprintf(stderr, "bad align: %zu\n", (size_t)n);
                                            exit(1);
                                    }
                                    if (imm.memory_immediate.align > nat_align) {
                                        fprintf(stderr, "alignment (%zu) must not be bigger than natural alignment (%zu)\n", (size_t)1 << imm.memory_immediate.align, (size_t)1 << n);
                                    }
                                    i += 1;
                                    goto redo;
                                }
                                if (!strncmp(arg.sym, "offset=", 7)) {
                                    imm.memory_immediate.offset = web49_readwat_expr_to_u64(&arg.sym[7]);
                                    i += 1;
                                    goto redo;
                                }
                            }
                            break;
                        }
                    }
                    if (entry.num_instrs + 2 >= alloc_instrs) {
                        alloc_instrs = (entry.num_instrs + 2) * 2;
                        entry.instrs = web49_realloc(entry.instrs, sizeof(web49_instr_t) * alloc_instrs);
                    }
                    entry.instrs[entry.num_instrs++] = (web49_instr_t){
                        .opcode = opcode,
                        .immediate = imm,
                    };
                } else {
                    fprintf(stderr, "unexpected word: `%s` byte=%zu\n", code.sym, (size_t)code.start);
                    exit(1);
                }
            } else if (!strcmp(code.fun_fun, "param") || !strcmp(code.fun_fun, "type") || !strcmp(code.fun_fun, "result")) {
                // nothing goes here
            } else if (!strcmp(code.fun_fun, "local")) {
                for (uint64_t j = 0; j < code.fun_nargs; j++) {
                    web49_readwat_expr_t name = code.fun_args[j];
                    web49_lang_type_t local_type;
                    if (!strcmp(name.sym, "i32")) {
                        local_type = WEB49_TYPE_I32;
                    } else if (!strcmp(name.sym, "i64")) {
                        local_type = WEB49_TYPE_I64;
                    } else if (!strcmp(name.sym, "f32")) {
                        local_type = WEB49_TYPE_F32;
                    } else if (!strcmp(name.sym, "f64")) {
                        local_type = WEB49_TYPE_F64;
                    } else {
                        fprintf(stderr, "expected local to be `i32` or `i64` or `f32` or `f64`, not `%s`\n", name.sym);
                        exit(1);
                    }
                    if (entry.num_locals + 2 >= alloc_locals) {
                        alloc_locals = (entry.num_locals + 2) * 2;
                        entry.locals = web49_realloc(entry.locals, sizeof(web49_section_code_entry_local_t) * alloc_locals);
                    }
                    if (entry.num_locals > 0 && entry.locals[entry.num_locals - 1].type == local_type) {
                        entry.locals[entry.num_locals - 1].count += 1;
                    } else {
                        entry.locals[entry.num_locals++] = (web49_section_code_entry_local_t){
                            .count = 1,
                            .type = local_type,
                        };
                    }
                }
            } else {
                fprintf(stderr, "unexpected word: (%s ...) byte=%zu\n", code.fun_fun, (size_t)code.start);
                exit(1);
            }
        }
        if (entry.num_instrs + 2 >= alloc_instrs) {
            alloc_instrs = (entry.num_instrs + 2) * 2;
            entry.instrs = web49_realloc(entry.instrs, sizeof(web49_instr_t) * alloc_instrs);
        }
        entry.instrs[entry.num_instrs++] = (web49_instr_t){
            .opcode = WEB49_OPCODE_END,
            .immediate.id = WEB49_IMMEDIATE_NONE,
        };
        if (out->scode.num_entries + 2 >= out->alloc_code) {
            out->alloc_code = (out->scode.num_entries + 2) * 2;
            out->scode.entries = web49_realloc(out->scode.entries, sizeof(web49_section_code_entry_t) * out->alloc_code);
        }
        out->scode.entries[out->scode.num_entries++] = entry;
    }
}

void web49_readwat_state_table_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_type_table_t entry;
    entry.limits.maximum = UINT64_MAX;
    bool init = false;
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t arg = expr.fun_args[i];
        if (arg.tag != WEB49_READWAT_EXPR_TAG_SYM) {
            fprintf(stderr, "did not expect a paren\n");
            exit(1);
        }
        if (isdigit(arg.sym[0])) {
            if (!init) {
                entry.limits.initial = web49_readwat_expr_to_u64(arg.sym);
                init = true;
            } else {
                entry.limits.maximum = web49_readwat_expr_to_u64(arg.sym);
            }
        } else if (!strcmp(arg.sym, "i32")) {
            entry.element_type = WEB49_TYPE_I32;
        } else if (!strcmp(arg.sym, "i64")) {
            entry.element_type = WEB49_TYPE_I64;
        } else if (!strcmp(arg.sym, "f32")) {
            entry.element_type = WEB49_TYPE_F32;
        } else if (!strcmp(arg.sym, "f64")) {
            entry.element_type = WEB49_TYPE_F64;
        } else if (!strcmp(arg.sym, "funcref")) {
            entry.element_type = WEB49_TYPE_ANYFUNC;
        } else {
            fprintf(stderr, "expected a type, not `%s`\n", arg.sym);
            exit(1);
        }
    }
    if (out->stable.num_entries + 2 >= out->alloc_table) {
        out->alloc_table = (out->stable.num_entries + 2) * 2;
        out->stable.entries = web49_realloc(out->stable.entries, sizeof(web49_type_table_t) * out->alloc_table);
    }
    out->stable.entries[out->stable.num_entries++] = entry;
}

web49_instr_t web49_readwat_instr(web49_readwat_expr_t code) {
    if (code.tag == WEB49_READWAT_EXPR_TAG_FUN) {
        web49_opcode_t opcode = web49_name_to_opcode(code.fun_fun);
        if (opcode < WEB49_MAX_OPCODE_NUM) {
            web49_immediate_id_t id = web49_opcode_immediate[opcode];
            web49_instr_immediate_t imm = (web49_instr_immediate_t){
                .id = id,
            };
            switch (id) {
                case WEB49_IMMEDIATE_NONE:
                    break;
                case WEB49_IMMEDIATE_BLOCK_TYPE:
                    if (code.fun_args[0].tag == WEB49_READWAT_EXPR_TAG_FUN && !strcmp(code.fun_args[0].fun_fun, "result")) {
                        web49_readwat_expr_t arg = code.fun_args[0].fun_args[0];
                        if (arg.tag != WEB49_READWAT_EXPR_TAG_SYM) {
                            fprintf(stderr, "expected basic type\n");
                            exit(1);
                        }
                        if (!strcmp(arg.sym, "i32")) {
                            imm.block_type = WEB49_TYPE_I32;
                        } else if (!strcmp(arg.sym, "i64")) {
                            imm.block_type = WEB49_TYPE_I64;
                        } else if (!strcmp(arg.sym, "f32")) {
                            imm.block_type = WEB49_TYPE_F32;
                        } else if (!strcmp(arg.sym, "f64")) {
                            imm.block_type = WEB49_TYPE_F64;
                        } else {
                            fprintf(stderr, "expected basic type name, not `%s`\n", arg.sym);
                            exit(1);
                        }
                    } else {
                        imm.block_type = WEB49_TYPE_BLOCK_TYPE;
                    }
                    break;
                case WEB49_IMMEDIATE_VARUINT1:
                    imm.varuint1 = 0;
                    break;
                case WEB49_IMMEDIATE_VARUINT32:
                    imm.varuint32 = (uint32_t)web49_readwat_expr_to_u64(code.fun_args[0].sym);
                    break;
                case WEB49_IMMEDIATE_VARUINT64:
                    imm.varuint64 = (uint64_t)web49_readwat_expr_to_u64(code.fun_args[0].sym);
                    break;
                case WEB49_IMMEDIATE_VARINT32:
                    imm.varuint64 = (int32_t)web49_readwat_expr_to_i64(code.fun_args[0].sym);
                    break;
                case WEB49_IMMEDIATE_VARINT64:
                    imm.varuint64 = (int64_t)web49_readwat_expr_to_i64(code.fun_args[0].sym);
                    break;
                case WEB49_IMMEDIATE_UINT32:
                    imm.varuint32 = (uint32_t)web49_readwat_expr_to_u64(code.fun_args[0].sym);
                    break;
                case WEB49_IMMEDIATE_UINT64:
                    imm.varuint64 = (uint64_t)web49_readwat_expr_to_u64(code.fun_args[0].sym);
                    break;
                case WEB49_IMMEDIATE_BR_TABLE: {
                    uint64_t i = 0;
                    uint64_t alloc = 0;
                    while (i + 1 < code.fun_nargs && isdigit(code.fun_args[i + 1].sym[0])) {
                        if (imm.br_table.num_targets + 2 >= alloc) {
                            alloc = (imm.br_table.num_targets + 2) * 2;
                            imm.br_table.targets = web49_realloc(imm.br_table.targets, sizeof(uint64_t) * alloc);
                        }
                        imm.br_table.targets[imm.br_table.num_targets++] = web49_readwat_expr_to_u64(code.fun_args[i++].sym);
                    }
                    imm.br_table.default_target = web49_readwat_expr_to_u64(code.fun_args[i].sym);
                    break;
                }
                case WEB49_IMMEDIATE_CALL_INDIRECT:
                    imm.call_indirect.index = (uint64_t)web49_readwat_expr_to_u64(code.fun_args[0].fun_args[0].sym);
                    break;
                case WEB49_IMMEDIATE_MEMORY_IMMEDIATE: {
                    switch (web49_opcode_memsize[opcode]) {
                        case 1:
                            imm.memory_immediate.align = 0;
                            break;
                        case 2:
                            imm.memory_immediate.align = 1;
                            break;
                        case 4:
                            imm.memory_immediate.align = 2;
                            break;
                        case 8:
                            imm.memory_immediate.align = 3;
                            break;
                        case 16:
                            imm.memory_immediate.align = 4;
                            break;
                    }
                    uint64_t i = 0;
                redo:;
                    web49_readwat_expr_t arg = code.fun_args[i];
                    if (arg.tag == WEB49_READWAT_EXPR_TAG_SYM) {
                        if (!strncmp(arg.sym, "align=", 6)) {
                            uint64_t n = web49_readwat_expr_to_u64(&arg.sym[6]);
                            uint64_t nat_align = imm.memory_immediate.align;
                            switch (n) {
                                case 1:
                                    imm.memory_immediate.align = 0;
                                    break;
                                case 2:
                                    imm.memory_immediate.align = 1;
                                    break;
                                case 4:
                                    imm.memory_immediate.align = 2;
                                    break;
                                case 8:
                                    imm.memory_immediate.align = 3;
                                    break;
                                default:
                                    fprintf(stderr, "bad align: %zu\n", (size_t)n);
                                    exit(1);
                            }
                            if (imm.memory_immediate.align > nat_align) {
                                fprintf(stderr, "alignment (%zu) must not be bigger than natural alignment (%zu)\n", (size_t)1 << imm.memory_immediate.align, (size_t)1 << n);
                            }
                            i += 1;
                            goto redo;
                        }
                        if (!strncmp(arg.sym, "offset=", 7)) {
                            imm.memory_immediate.offset = web49_readwat_expr_to_u64(&arg.sym[7]);
                            i += 1;
                            goto redo;
                        }
                    }
                    break;
                }
            }
            return (web49_instr_t){
                .opcode = opcode,
                .immediate = imm,
            };
        } else {
            fprintf(stderr, "unexpected word: `%s` byte=%zu\n", code.sym, (size_t)code.start);
            exit(1);
        }
    } else {
        fprintf(stderr, "unexpected expr: (%s ...) byte=%zu\n", code.fun_fun, (size_t)code.start);
        exit(1);
    }
    fprintf(stderr, "expected an instruction\n");
    exit(1);
}

void web49_readwat_state_global_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_section_global_entry_t entry;
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t arg = expr.fun_args[i];
        if (arg.tag == WEB49_READWAT_EXPR_TAG_SYM) {
            if (!strcmp(arg.sym, "i32")) {
                entry.global.content_type = WEB49_TYPE_I32;
            } else if (!strcmp(arg.sym, "i64")) {
                entry.global.content_type = WEB49_TYPE_I64;
            } else if (!strcmp(arg.sym, "f32")) {
                entry.global.content_type = WEB49_TYPE_F32;
            } else if (!strcmp(arg.sym, "f64")) {
                entry.global.content_type = WEB49_TYPE_F64;
            } else if (!strcmp(arg.sym, "funcref")) {
                entry.global.content_type = WEB49_TYPE_ANYFUNC;
            } else {
                fprintf(stderr, "expected a global type, not `%s`\n", arg.sym);
                exit(1);
            }
        } else {
            if (!strcmp(arg.fun_fun, "mut")) {
                if (arg.fun_nargs < 1) {
                    fprintf(stderr, "expected word after (mut\n");
                    exit(0);
                }
                entry.global.is_mutable = true;
                if (!strcmp(arg.fun_args[0].sym, "i32")) {
                    entry.global.content_type = WEB49_TYPE_I32;
                } else if (!strcmp(arg.fun_args[0].sym, "i64")) {
                    entry.global.content_type = WEB49_TYPE_I64;
                } else if (!strcmp(arg.fun_args[0].sym, "f32")) {
                    entry.global.content_type = WEB49_TYPE_F32;
                } else if (!strcmp(arg.fun_args[0].sym, "f64")) {
                    entry.global.content_type = WEB49_TYPE_F64;
                } else if (!strcmp(arg.fun_args[0].sym, "funcref")) {
                    entry.global.content_type = WEB49_TYPE_ANYFUNC;
                } else {
                    fprintf(stderr, "expected a global (mut typename), not (mut %s)\n", arg.sym);
                    exit(1);
                }
                if (arg.fun_nargs > 1) {
                    fprintf(stderr, "expected (mut ...) to only have one word (a type) after (mut\n");
                    exit(1);
                }
            } else {
                entry.init_expr = web49_readwat_instr(arg);
            }
        }
    }
    if (out->sglobal.num_entries + 2 >= out->alloc_global) {
        out->alloc_global = (out->sglobal.num_entries + 2) * 2;
        out->sglobal.entries = web49_realloc(out->sglobal.entries, sizeof(web49_section_global_entry_t) * out->alloc_global);
    }
    out->sglobal.entries[out->sglobal.num_entries++] = entry;
}

void web49_readwat_state_export_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_section_export_entry_t entry;
    entry.field_str = web49_readwat_sym_to_str(expr.fun_args[0]);
    if (expr.fun_args[1].tag != WEB49_READWAT_EXPR_TAG_FUN) {
        fprintf(stderr, "expected paren after `(export \"...\"`, but was missing paren\n");
        exit(1);
    }
    if (!strcmp(expr.fun_args[1].sym, "func")) {
        entry.kind = WEB49_EXTERNAL_KIND_FUNCTION;
    } else if (!strcmp(expr.fun_args[1].sym, "table")) {
        entry.kind = WEB49_EXTERNAL_KIND_TABLE;
    } else if (!strcmp(expr.fun_args[1].sym, "memory")) {
        entry.kind = WEB49_EXTERNAL_KIND_MEMORY;
    } else if (!strcmp(expr.fun_args[1].sym, "global")) {
        entry.kind = WEB49_EXTERNAL_KIND_GLOBAL;
    } else {
        fprintf(stderr, "expected `func` or `table` or `memory` or `global`, not `%s`\n", expr.fun_args[1].sym);
    }
    entry.index = web49_readwat_expr_to_u64(expr.fun_args[1].fun_args[0].sym);
    if (out->sexport.num_entries + 2 >= out->alloc_export) {
        out->alloc_export = (out->sexport.num_entries + 2) * 2;
        out->sexport.entries = web49_realloc(out->sexport.entries, sizeof(web49_section_export_entry_t) * out->alloc_export);
    }
    out->sexport.entries[out->sexport.num_entries++] = entry;
}

void web49_readwat_state_elem_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_section_element_entry_t entry;
    entry.index = out->selement.num_entries;
    entry.offset = web49_readwat_instr(expr.fun_args[0]);
    entry.num_elems = 0;
    entry.elems = web49_malloc(sizeof(uint64_t) * expr.fun_nargs);
    for (uint64_t i = 2; i < expr.fun_nargs; i++) {
        entry.elems[entry.num_elems++] = web49_readwat_expr_to_u64(expr.fun_args[i].sym);
    }
    if (out->selement.num_entries + 2 >= out->alloc_element) {
        out->alloc_element = (out->selement.num_entries + 2) * 2;
        out->selement.entries = web49_realloc(out->selement.entries, sizeof(web49_section_element_entry_t) * out->alloc_element);
    }
    out->selement.entries[out->selement.num_entries++] = entry;
}

void web49_readwat_state_data_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_section_data_entry_t entry;
    entry.offset = web49_readwat_instr(expr.fun_args[0]);
    entry.size = expr.fun_args[expr.fun_nargs - 1].len_str;
    entry.data = expr.fun_args[expr.fun_nargs - 1].str;
    if (out->sdata.num_entries + 2 >= out->alloc_data) {
        out->alloc_data = (out->sdata.num_entries + 2) * 2;
        out->sdata.entries = web49_realloc(out->sdata.entries, sizeof(web49_section_element_entry_t) * out->alloc_data);
    }
    out->sdata.entries[out->sdata.num_entries++] = entry;
}

void web49_readwat_state_memory_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_type_memory_t entry;
    if (expr.fun_nargs == 1) {
        entry.initial = web49_readwat_expr_to_u64(expr.fun_args[0].sym);
    } else if (expr.fun_nargs == 2) {
        entry.initial = web49_readwat_expr_to_u64(expr.fun_args[0].sym);
        entry.maximum = web49_readwat_expr_to_u64(expr.fun_args[1].sym);
    } else {
        fprintf(stderr, "(memory ...) expected two args after `memory`, not %zu\n", (size_t)expr.fun_nargs);
        exit(1);
    }
    if (out->smemory.num_entries + 2 >= out->alloc_memory) {
        out->alloc_memory = (out->smemory.num_entries + 2) * 2;
        out->smemory.entries = web49_realloc(out->smemory.entries, sizeof(web49_section_element_entry_t) * out->alloc_memory);
    }
    out->smemory.entries[out->smemory.num_entries++] = entry;
}

void web49_readwat_state_toplevel(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    if (expr.tag != WEB49_READWAT_EXPR_TAG_FUN) {
        fprintf(stderr, "expected `(` at toplevel of file\n");
        exit(1);
    }
    if (!!strcmp(expr.fun_fun, "module")) {
        fprintf(stderr, "expected module to be the first expression in the file\n");
        exit(1);
    }
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t type = expr.fun_args[i];
        if (type.tag != WEB49_READWAT_EXPR_TAG_FUN) {
            fprintf(stderr, "expected `(` at module of file\n");
        }
    }
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t type = expr.fun_args[i];
        if (!strcmp(type.fun_fun, "type")) {
            web49_readwat_state_type_entry(out, type);
        }
    }
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t type = expr.fun_args[i];
        if (!strcmp(type.fun_fun, "import")) {
            web49_readwat_state_import_entry(out, type);
        }
        if (!strcmp(type.fun_fun, "export")) {
            web49_readwat_state_export_entry(out, type);
        }
        if (!strcmp(type.fun_fun, "table")) {
            web49_readwat_state_table_entry(out, type);
        }
        if (!strcmp(type.fun_fun, "global")) {
            web49_readwat_state_global_entry(out, type);
        }
        if (!strcmp(type.fun_fun, "elem")) {
            web49_readwat_state_elem_entry(out, type);
        }
        if (!strcmp(type.fun_fun, "data")) {
            web49_readwat_state_data_entry(out, type);
        }
        if (!strcmp(type.fun_fun, "memory")) {
            web49_readwat_state_memory_entry(out, type);
        }
    }
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t type = expr.fun_args[i];
        if (!strcmp(type.fun_fun, "func")) {
            web49_readwat_state_func_entry(out, type);
        }
    }
}

web49_module_t web49_readwat_module(web49_io_input_t *in) {
    web49_readwat_state_t state = {0};
    web49_readwat_expr_t expr = web49_readwat_expr(in);
    web49_readwat_state_toplevel(&state, expr);
    uint64_t num_sections = 0;
    web49_section_t *sections = web49_malloc(sizeof(web49_section_t) * 16);
    if (state.stype.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_TYPE,
                .size_known = false,
            },
            .type_section = state.stype,
        };
    }
    if (state.simport.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_IMPORT,
                .size_known = false,
            },
            .import_section = state.simport,
        };
    }
    if (state.sfunction.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_FUNCTION,
                .size_known = false,
            },
            .function_section = state.sfunction,
        };
    }
    if (state.stable.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_TABLE,
                .size_known = false,
            },
            .table_section = state.stable,
        };
    }
    if (state.smemory.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_MEMORY,
                .size_known = false,
            },
            .memory_section = state.smemory,
        };
    }
    if (state.sglobal.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_GLOBAL,
                .size_known = false,
            },
            .global_section = state.sglobal,
        };
    }
    if (state.sexport.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_EXPORT,
                .size_known = false,
            },
            .export_section = state.sexport,
        };
    }
    if (state.selement.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_ELEMENT,
                .size_known = false,
            },
            .element_section = state.selement,
        };
    }
    if (state.scode.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_CODE,
                .size_known = false,
            },
            .code_section = state.scode,
        };
    }
    if (state.sdata.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_DATA,
                .size_known = false,
            },
            .data_section = state.sdata,
        };
    }
    return (web49_module_t){
        .num_sections = num_sections,
        .sections = sections,
        .preamble = web49_preamble_init,
    };
}
