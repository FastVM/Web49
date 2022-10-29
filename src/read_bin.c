
#include "./read_bin.h"

#include <stdint.h>

web49_immediate_id_t web49_immediates[WEB49_MAX_OPCODE_NUM] = {
    [WEB49_OPCODE_BLOCK] = WEB49_IMMEDIATE_BLOCK_TYPE,
    [WEB49_OPCODE_LOOP] = WEB49_IMMEDIATE_BLOCK_TYPE,
    [WEB49_OPCODE_IF] = WEB49_IMMEDIATE_BLOCK_TYPE,
    [WEB49_OPCODE_BR] = WEB49_IMMEDIATE_VARUINT32,
    [WEB49_OPCODE_BR_IF] = WEB49_IMMEDIATE_VARUINT32,
    [WEB49_OPCODE_BR_TABLE] = WEB49_IMMEDIATE_BR_TABLE,
    [WEB49_OPCODE_CALL] = WEB49_IMMEDIATE_VARUINT32,
    [WEB49_OPCODE_CALL_INDIRECT] = WEB49_IMMEDIATE_CALL_INDIRECT,
    [WEB49_OPCODE_GET_LOCAL] = WEB49_IMMEDIATE_VARUINT32,
    [WEB49_OPCODE_SET_LOCAL] = WEB49_IMMEDIATE_VARUINT32,
    [WEB49_OPCODE_TEE_LOCAL] = WEB49_IMMEDIATE_VARUINT32,
    [WEB49_OPCODE_GET_GLOBAL] = WEB49_IMMEDIATE_VARUINT32,
    [WEB49_OPCODE_SET_GLOBAL] = WEB49_IMMEDIATE_VARUINT32,
    [WEB49_OPCODE_I32_LOAD] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_LOAD] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_F32_LOAD] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_F64_LOAD] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I32_LOAD8_S] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I32_LOAD8_U] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I32_LOAD16_S] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I32_LOAD16_U] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_LOAD8_S] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_LOAD8_U] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_LOAD16_S] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_LOAD16_U] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_LOAD32_S] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_LOAD32_U] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I32_STORE] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_STORE] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_F32_STORE] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_F64_STORE] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I32_STORE8] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I32_STORE16] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_STORE8] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_STORE16] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I64_STORE32] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_MEMORY_SIZE] = WEB49_IMMEDIATE_VARUINT1,
    [WEB49_OPCODE_MEMORY_GROW] = WEB49_IMMEDIATE_VARUINT1,
    [WEB49_OPCODE_I32_CONST] = WEB49_IMMEDIATE_VARINT32,
    [WEB49_OPCODE_I64_CONST] = WEB49_IMMEDIATE_VARINT64,
    [WEB49_OPCODE_F32_CONST] = WEB49_IMMEDIATE_UINT32,
    [WEB49_OPCODE_F64_CONST] = WEB49_IMMEDIATE_UINT64,
    [WEB49_OPCODE_MEMORY_INIT] = WEB49_IMMEDIATE_DATA_INDEX,
    [WEB49_OPCODE_DATA_DROP] = WEB49_IMMEDIATE_DATA_INDEX,
};

uint64_t web49_readbin_uleb(FILE *in) {
    uint8_t buf;
    uint64_t x = 0;
    size_t shift = 0;
    while (fread(&buf, 1, 1, in)) {
        x |= (uint64_t)(buf & 0x7f) << shift;
        if (!(buf & 0x80)) {
            break;
        }
        shift += 7;
    }
    return x;
}

int64_t web49_readbin_sleb(FILE *in) {
    uint8_t buf;
    __int128 x = 0;
    size_t shift = 0;
    while (fread(&buf, 1, 1, in)) {
        x += (__int128)(buf & 0x7f) << shift;
        shift += 7;
        if (!(buf & 0x80)) {
            break;
        }
    }
    if (shift < 64 && (buf & 0x40)) {
        return (int64_t)(x - ((__int128)1 << shift));
    } else {
        return x;
    }
}

uint8_t web49_readbin_byte(FILE *in) {
    uint8_t ret;
    fread(&ret, 1, 1, in);
    return ret;
}

web49_preamble_t web49_readbin_preamble(FILE *in) {
    return (web49_preamble_t){
        .magic[0] = web49_readbin_byte(in),
        .magic[1] = web49_readbin_byte(in),
        .magic[2] = web49_readbin_byte(in),
        .magic[3] = web49_readbin_byte(in),
        .version[0] = web49_readbin_byte(in),
        .version[1] = web49_readbin_byte(in),
        .version[2] = web49_readbin_byte(in),
        .version[3] = web49_readbin_byte(in),
    };
}

web49_section_header_t web49_readbin_section_header(FILE *in) {
    uint8_t id = web49_readbin_byte(in);
    uint64_t size = web49_readbin_uleb(in);
    return (web49_section_header_t){
        .id = id,
        .size = size,
    };
}

uint8_t web49_readbin_varuint1(FILE *in) {
    return web49_readbin_byte(in);
}

int32_t web49_readbin_varint32(FILE *in) {
    return (int32_t)web49_readbin_sleb(in);
}

int64_t web49_readbin_varint64(FILE *in) {
    return (int64_t)web49_readbin_sleb(in);
}

int32_t web49_readbin_varuint32(FILE *in) {
    return (uint32_t)web49_readbin_uleb(in);
}

int64_t web49_readbin_varuint64(FILE *in) {
    return (uint64_t)web49_readbin_uleb(in);
}

uint32_t web49_readbin_uint32(FILE *in) {
    uint32_t ret;
    fread(&ret, sizeof(uint32_t), 1, in);
    return ret;
}

uint64_t web49_readbin_uint64(FILE *in) {
    uint64_t ret;
    fread(&ret, sizeof(uint64_t), 1, in);
    return ret;
}

web49_lang_type_t web49_readbin_block_type(FILE *in) {
    return web49_readbin_byte(in);
}

web49_br_table_t web49_readbin_br_table(FILE *in) {
    uint64_t num = web49_readbin_uleb(in);
    uint64_t *targets = web49_malloc(sizeof(uint64_t) * num);
    for (uint64_t i = 0; i < num; i++) {
        targets[i] = web49_readbin_uleb(in);
    }
    uint64_t default_target = web49_readbin_uleb(in);
    return (web49_br_table_t){
        .num_targets = num,
        .targets = targets,
        .default_target = default_target,
    };
}

web49_call_indirect_t web49_readbin_call_indirect(FILE *in) {
    return (web49_call_indirect_t){
        .index = web49_readbin_uleb(in),
        .reserved = web49_readbin_byte(in),
    };
}

web49_memory_immediate_t web49_readbin_memory_immediate(FILE *in) {
    return (web49_memory_immediate_t){
        .align = web49_readbin_uleb(in),
        .offset = web49_readbin_uleb(in),
    };
}

web49_type_function_t web49_readbin_type_function(FILE *in) {
    return (web49_type_function_t){
        .data = web49_readbin_uleb(in),
    };
}

web49_type_table_t web49_readbin_type_table(FILE *in) {
    return (web49_type_table_t){
        .element_type = web49_readbin_byte(in),
        .limits = web49_readbin_type_memory(in),
    };
}

web49_type_global_t web49_readbin_type_global(FILE *in) {
    return (web49_type_global_t){
        .content_type = web49_readbin_byte(in),
        .is_mutable = web49_readbin_byte(in),
    };
}

web49_type_memory_t web49_readbin_type_memory(FILE *in) {
    uint64_t flags = web49_readbin_uleb(in);
    return (web49_type_memory_t){
        .initial = web49_readbin_uleb(in),
        .maximum = (flags & 1) ? web49_readbin_uleb(in) : UINT64_MAX,
    };
}

web49_type_t web49_readbin_type(FILE *in, web49_external_kind_t tag) {
    if (tag == WEB49_EXTERNAL_KIND_FUNCTION) {
        return (web49_type_t){
            .function = web49_readbin_type_function(in),
            .tag = tag,
        };
    }
    if (tag == WEB49_EXTERNAL_KIND_TABLE) {
        return (web49_type_t){
            .table = web49_readbin_type_table(in),
            .tag = tag,
        };
    }
    if (tag == WEB49_EXTERNAL_KIND_GLOBAL) {
        return (web49_type_t){
            .global = web49_readbin_type_global(in),
            .tag = tag,
        };
    }
    if (tag == WEB49_EXTERNAL_KIND_MEMORY) {
        return (web49_type_t){
            .memory = web49_readbin_type_memory(in),
            .tag = tag,
        };
    }
    fprintf(stderr, "unknown external kind: %zu", (size_t)tag);
    exit(1);
}

web49_section_custom_t web49_readbin_section_custom(FILE *in, web49_section_header_t header) {
    uint64_t len = web49_readbin_uleb(in);
    char *custom_name = web49_malloc(sizeof(char) * (len + 1));
    fread(custom_name, 1, len, in);
    custom_name[len] = '\0';
    web49_readbin_byte(in);
    uint64_t size = header.size - len;
    void *payload = web49_malloc(size);
    fread(payload, 1, size, in);
    return (web49_section_custom_t){
        .custom_name = custom_name,
        .payload = payload,
    };
}

web49_section_type_t web49_readbin_section_type(FILE *in) {
    uint64_t num = web49_readbin_uleb(in);
    web49_section_type_entry_t *entries = web49_malloc(sizeof(web49_section_type_entry_t) * num);
    for (uint64_t i = 0; i < num; i++) {
        web49_lang_type_t type = web49_readbin_byte(in);
        uint64_t num_params = web49_readbin_uleb(in);
        web49_lang_type_t *params = web49_malloc(sizeof(web49_lang_type_t) * num_params);
        for (uint64_t j = 0; j < num_params; j++) {
            params[j] = web49_readbin_byte(in);
        }
        uint64_t num_returns = web49_readbin_uleb(in);
        web49_lang_type_t return_type = WEB49_TYPE_NOT_SPECIFIED;
        bool has_return_type = false;
        if (num_returns != 0) {
            has_return_type = true;
            return_type = web49_readbin_byte(in);
        }
        entries[i] = (web49_section_type_entry_t){
            .type = type,
            .num_params = num_params,
            .params = params,
            .num_returns = num_returns,
            .has_return_type = has_return_type,
            .return_type = return_type,
        };
    }
    return (web49_section_type_t){
        .num_entries = num,
        .entries = entries,
    };
}

web49_section_import_t web49_readbin_section_import(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_import_entry_t *entries = web49_malloc(sizeof(web49_section_import_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t module_len = web49_readbin_uleb(in);
        char *module_str = web49_malloc(sizeof(char) * (module_len + 1));
        fread(module_str, 1, module_len, in);
        module_str[module_len] = '\0';
        uint64_t field_len = web49_readbin_uleb(in);
        char *field_str = web49_malloc(sizeof(char) * (field_len + 1));
        fread(field_str, 1, field_len, in);
        field_str[field_len] = '\0';
        web49_external_kind_t kind = web49_readbin_byte(in);
        entries[i] = (web49_section_import_entry_t){
            .module_str = module_str,
            .field_str = field_str,
            .kind = kind,
        };
        switch (kind) {
            case WEB49_EXTERNAL_KIND_FUNCTION: {
                entries[i].func_type = web49_readbin_type_function(in);
                break;
            }
            case WEB49_EXTERNAL_KIND_TABLE: {
                entries[i].table_type = web49_readbin_type_table(in);
                break;
            }
            case WEB49_EXTERNAL_KIND_MEMORY: {
                entries[i].memory_type = web49_readbin_type_memory(in);
                break;
            }
            case WEB49_EXTERNAL_KIND_GLOBAL: {
                entries[i].global_type = web49_readbin_type_global(in);
                break;
            }
        }
    }
    return (web49_section_import_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_function_t web49_readbin_section_function(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    uint64_t *entries = web49_malloc(sizeof(uint64_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = web49_readbin_uleb(in);
    }
    return (web49_section_function_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_table_t web49_readbin_section_table(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_type_table_t *entries = web49_malloc(sizeof(web49_type_table_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = web49_readbin_type_table(in);
    }
    return (web49_section_table_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_memory_t web49_readbin_section_memory(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_type_memory_t *entries = web49_malloc(sizeof(web49_section_global_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = web49_readbin_type_memory(in);
    }
    return (web49_section_memory_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_global_t web49_readbin_section_global(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_global_entry_t *entries = web49_malloc(sizeof(web49_section_global_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = (web49_section_global_entry_t){
            .global = web49_readbin_type_global(in),
            .init_expr = web49_readbin_init_expr(in),
        };
    }
    return (web49_section_global_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_export_t web49_readbin_section_export(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_export_entry_t *entries = web49_malloc(sizeof(web49_section_export_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t field_len = web49_readbin_uleb(in);
        char *field_str = web49_malloc(sizeof(char) * (field_len + 1));
        fread(field_str, 1, field_len, in);
        field_str[field_len] = '\0';
        web49_external_kind_t kind = web49_readbin_byte(in);
        uint64_t index = web49_readbin_uleb(in);
        entries[i] = (web49_section_export_entry_t){
            .field_str = field_str,
            .kind = kind,
            .index = index,
        };
    }
    return (web49_section_export_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_start_t web49_readbin_section_start(FILE *in) {
    return (web49_section_start_t){
        .index = web49_readbin_uleb(in),
    };
}

web49_section_element_t web49_readbin_section_element(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_element_entry_t *entries = web49_malloc(sizeof(web49_section_element_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t index = web49_readbin_uleb(in);
        web49_instr_t offset = web49_readbin_init_expr(in);
        uint64_t num_elems = web49_readbin_uleb(in);
        uint64_t *elems = web49_malloc(sizeof(uint64_t) * num_elems);
        for (uint64_t j = 0; j < num_elems; j++) {
            elems[j] = web49_readbin_uleb(in);
        }
        entries[i] = (web49_section_element_entry_t){
            .index = index,
            .offset = offset,
            .num_elems = num_elems,
            .elems = elems,
        };
    }
    return (web49_section_element_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_code_t web49_readbin_section_code(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_code_entry_t *entries = web49_malloc(sizeof(web49_section_code_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t body_len = web49_readbin_uleb(in);
        long end = ftell(in) + (long)body_len;
        uint64_t num_locals = web49_readbin_uleb(in);
        web49_section_code_entry_local_t *locals = web49_malloc(sizeof(web49_section_code_entry_local_t) * num_locals);
        for (uint64_t j = 0; j < num_locals; j++) {
            uint64_t count = web49_readbin_uleb(in);
            web49_lang_type_t type = web49_readbin_byte(in);
            locals[j] = (web49_section_code_entry_local_t){
                .count = count,
                .type = type,
            };
        }
        uint64_t alloc_instrs = 4;
        web49_instr_t *instrs = web49_malloc(sizeof(web49_instr_t) * alloc_instrs);
        uint64_t num_instrs = 0;
        while (ftell(in) < end) {
            if (num_instrs + 1 >= alloc_instrs) {
                alloc_instrs = (alloc_instrs + 1) * 2;
                instrs = web49_realloc(instrs, sizeof(web49_instr_t) * alloc_instrs);
            }
            instrs[num_instrs] = web49_readbin_instr(in);
            num_instrs += 1;
        }
        entries[i] = (web49_section_code_entry_t){
            .num_locals = num_locals,
            .locals = locals,
            .num_instrs = num_instrs,
            .instrs = instrs,
        };
    }
    return (web49_section_code_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_data_t web49_readbin_section_data(FILE *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_data_entry_t *entries = web49_malloc(sizeof(web49_section_data_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t index = web49_readbin_uleb(in);
        web49_instr_t offset = web49_readbin_init_expr(in);
        uint64_t size = web49_readbin_uleb(in);
        uint8_t *data = web49_malloc(sizeof(uint8_t) * size);
        fread(data, 1, size, in);
        entries[i] = (web49_section_data_entry_t){
            .index = index,
            .offset = offset,
            .size = size,
            .data = data,
        };
    }
    return (web49_section_data_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_instr_immediate_t web49_readbin_instr_immediate(FILE *in, web49_immediate_id_t id) {
    if (id == WEB49_IMMEDIATE_BLOCK_TYPE) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_BLOCK_TYPE,
            .block_type = web49_readbin_block_type(in),
        };
    }
    if (id == WEB49_IMMEDIATE_VARUINT1) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_VARUINT1,
            .varuint1 = web49_readbin_varuint1(in),
        };
    }
    if (id == WEB49_IMMEDIATE_VARUINT32) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_VARUINT32,
            .varuint32 = web49_readbin_varuint32(in),
        };
    }
    if (id == WEB49_IMMEDIATE_VARUINT64) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_VARUINT64,
            .varuint64 = web49_readbin_varuint64(in),
        };
    }
    if (id == WEB49_IMMEDIATE_VARINT32) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_VARINT32,
            .varint32 = web49_readbin_varint32(in),
        };
    }
    if (id == WEB49_IMMEDIATE_VARINT64) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_VARINT64,
            .varint64 = web49_readbin_varint64(in),
        };
    }
    if (id == WEB49_IMMEDIATE_UINT32) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_UINT32,
            .uint32 = web49_readbin_uint32(in),
        };
    }
    if (id == WEB49_IMMEDIATE_UINT64) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_UINT64,
            .uint64 = web49_readbin_uint64(in),
        };
    }
    if (id == WEB49_IMMEDIATE_BR_TABLE) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_BR_TABLE,
            .br_table = web49_readbin_br_table(in),
        };
    }
    if (id == WEB49_IMMEDIATE_CALL_INDIRECT) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_CALL_INDIRECT,
            .call_indirect = web49_readbin_call_indirect(in),
        };
    }
    if (id == WEB49_IMMEDIATE_MEMORY_IMMEDIATE) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
            .memory_immediate = web49_readbin_memory_immediate(in),
        };
    }
    if (id == WEB49_IMMEDIATE_DATA_INDEX) {
        return (web49_instr_immediate_t){
            .id = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
            .data_index = web49_readbin_varint32(in),
        };
    }
    return (web49_instr_immediate_t){
        .id = WEB49_IMMEDIATE_NONE,
    };
}

web49_instr_t web49_readbin_init_expr(FILE *in) {
    web49_instr_t ret = web49_readbin_instr(in);
    web49_readbin_byte(in);
    return ret;
}

web49_instr_t web49_readbin_instr(FILE *in) {
    web49_opcode_t opcode = web49_readbin_byte(in);
    size_t skip = 0;
    if (opcode == 0xFC) {
        switch (web49_readbin_byte(in)) {
            case 0x8:
                opcode = WEB49_OPCODE_MEMORY_INIT;
                skip = 1;
                break;
            case 0x9:
                opcode = WEB49_OPCODE_DATA_DROP;
                skip = 0;
                break;
            case 0xA:
                opcode = WEB49_OPCODE_MEMORY_COPY;
                skip = 2;
                break;
            case 0xB:
                opcode = WEB49_OPCODE_MEMORY_FILL;
                skip = 1;
                break;
            default:
                break;
        }
    }
    web49_immediate_id_t immediate_id = web49_immediates[opcode];
    web49_instr_immediate_t immediate = web49_readbin_instr_immediate(in, immediate_id);
    for (size_t i = 0; i < skip; i++) {
        (void)web49_readbin_byte(in);
    }
    return (web49_instr_t){
        .opcode = opcode,
        .immediate = immediate,
    };
}

web49_section_t web49_readbin_section(FILE *in, web49_section_header_t header) {
    web49_section_id_t id = header.id;
    if (id == WEB49_SECTION_ID_CUSTOM) {
        return (web49_section_t){
            .header = header,
            .custom_section = web49_readbin_section_custom(in, header),
        };
    }
    if (id == WEB49_SECTION_ID_TYPE) {
        return (web49_section_t){
            .header = header,
            .type_section = web49_readbin_section_type(in),
        };
    }
    if (id == WEB49_SECTION_ID_IMPORT) {
        return (web49_section_t){
            .header = header,
            .import_section = web49_readbin_section_import(in),
        };
    }
    if (id == WEB49_SECTION_ID_FUNCTION) {
        return (web49_section_t){
            .header = header,
            .function_section = web49_readbin_section_function(in),
        };
    }
    if (id == WEB49_SECTION_ID_TABLE) {
        return (web49_section_t){
            .header = header,
            .table_section = web49_readbin_section_table(in),
        };
    }
    if (id == WEB49_SECTION_ID_MEMORY) {
        return (web49_section_t){
            .header = header,
            .memory_section = web49_readbin_section_memory(in),
        };
    }
    if (id == WEB49_SECTION_ID_GLOBAL) {
        return (web49_section_t){
            .header = header,
            .global_section = web49_readbin_section_global(in),
        };
    }
    if (id == WEB49_SECTION_ID_EXPORT) {
        return (web49_section_t){
            .header = header,
            .export_section = web49_readbin_section_export(in),
        };
    }
    if (id == WEB49_SECTION_ID_START) {
        return (web49_section_t){
            .header = header,
            .start_section = web49_readbin_section_start(in),
        };
    }
    if (id == WEB49_SECTION_ID_ELEMENT) {
        return (web49_section_t){
            .header = header,
            .element_section = web49_readbin_section_element(in),
        };
    }
    if (id == WEB49_SECTION_ID_CODE) {
        return (web49_section_t){
            .header = header,
            .code_section = web49_readbin_section_code(in),
        };
    }
    if (id == WEB49_SECTION_ID_DATA) {
        return (web49_section_t){
            .header = header,
            .data_section = web49_readbin_section_data(in),
        };
    }
    fprintf(stderr, "unknown section kind: 0x%zX starting at %zX", (size_t)id, (size_t)ftell(in));
    exit(1);
}

web49_module_t web49_readbin_module(FILE *in) {
    web49_preamble_t preamble = web49_readbin_preamble(in);
    uint64_t alloc_sections = 4;
    web49_section_t *sections = web49_malloc(sizeof(web49_section_t) * alloc_sections);
    uint64_t num_sections = 0;
    while (!feof(in)) {
        if (num_sections + 1 >= alloc_sections) {
            alloc_sections = (alloc_sections + 1) * 2;
            sections = web49_realloc(sections, sizeof(web49_section_t) * alloc_sections);
        }
        web49_section_header_t header = web49_readbin_section_header(in);
        if (header.id >= WEB49_SECTION_HIGH_ID) {
            header.id = WEB49_SECTION_ID_CUSTOM;
        }
        sections[num_sections] = web49_readbin_section(in, header);
        num_sections += 1;
    }
    return (web49_module_t){
        .preamble = preamble,
        .num_sections = num_sections,
        .sections = sections,
    };
}
