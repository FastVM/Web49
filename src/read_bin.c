
#include "./read_bin.h"

#include "ast.h"
#include "io.h"
#include "tables.h"

uint64_t web49_readbin_uleb(web49_io_input_t *in) {
    uint8_t buf;
    uint64_t x = 0;
    size_t shift = 0;
    while (web49_io_input_fread(in, 1, &buf)) {
        x |= (uint64_t)(buf & 0x7f) << shift;
        if (!(buf & 0x80)) {
            break;
        }
        shift += 7;
    }
    return x;
}

int64_t web49_readbin_sleb(web49_io_input_t *in) {
    uint8_t buf;
    __int128 x = 0;
    size_t shift = 0;
    while (web49_io_input_fread(in, 1, &buf)) {
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

uint8_t web49_readbin_byte(web49_io_input_t *in) {
    uint8_t ret;
    web49_io_input_fread(in, 1, &ret);
    return ret;
}

web49_preamble_t web49_readbin_preamble(web49_io_input_t *in) {
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

web49_section_header_t web49_readbin_section_header(web49_io_input_t *in) {
    uint8_t id = web49_readbin_byte(in);
    uint64_t size = web49_readbin_uleb(in);
    return (web49_section_header_t){
        .id = id,
        .size = size,
        .size_known = true,
    };
}

uint8_t web49_readbin_varuint1(web49_io_input_t *in) {
    return web49_readbin_byte(in);
}

int32_t web49_readbin_varint32(web49_io_input_t *in) {
    return (int32_t)web49_readbin_sleb(in);
}

int64_t web49_readbin_varint64(web49_io_input_t *in) {
    return (int64_t)web49_readbin_sleb(in);
}

int32_t web49_readbin_varuint32(web49_io_input_t *in) {
    return (uint32_t)web49_readbin_uleb(in);
}

int64_t web49_readbin_varuint64(web49_io_input_t *in) {
    return (uint64_t)web49_readbin_uleb(in);
}

uint32_t web49_readbin_uint32(web49_io_input_t *in) {
    uint32_t ret;
    web49_io_input_fread(in, (sizeof(uint32_t)) * (1), &ret);
    return ret;
}

uint64_t web49_readbin_uint64(web49_io_input_t *in) {
    uint64_t ret;
    web49_io_input_fread(in, (sizeof(uint64_t)) * (1), &ret);
    return ret;
}

web49_block_type_t web49_readbin_block_type(web49_io_input_t *in) {
    web49_block_type_t bt;
    web49_lang_type_t type = web49_readbin_byte(in);
    switch (type) {
    case WEB49_TYPE_BLOCK_TYPE:
        bt.type_value = WEB49_TYPE_BLOCK_TYPE;
        bt.is_type_index = false;
        break;
    case WEB49_TYPE_I32:
        bt.type_value = WEB49_TYPE_I32;
        bt.is_type_index = false;
        break;
    case WEB49_TYPE_I64:
        bt.type_value = WEB49_TYPE_I64;
        bt.is_type_index = false;
        break;
    case WEB49_TYPE_F32:
        bt.type_value = WEB49_TYPE_F32;
        bt.is_type_index = false;
        break;
    case WEB49_TYPE_F64:
        bt.type_value = WEB49_TYPE_F64;
        bt.is_type_index = false;
        break;
    case WEB49_TYPE_ANYFUNC:
        bt.type_value = WEB49_TYPE_ANYFUNC;
        bt.is_type_index = false;
        break;
    case WEB49_TYPE_FUNC:
        bt.type_value = WEB49_TYPE_FUNC;
        bt.is_type_index = false;
        break;
    default: {
        web49_io_input_rewind(in);
        bt.is_type_index = true;
        bt.type_index = web49_readbin_sleb(in);
        break;
    }
    }
    return bt;
}

web49_br_table_t web49_readbin_br_table(web49_io_input_t *in) {
    uint32_t num = web49_readbin_uleb(in);
    uint32_t *targets = web49_malloc(sizeof(uint32_t) * num);
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

web49_call_indirect_t web49_readbin_call_indirect(web49_io_input_t *in) {
    return (web49_call_indirect_t){
        .index = web49_readbin_uleb(in),
        .reserved = web49_readbin_byte(in),
    };
}

web49_memory_immediate_t web49_readbin_memory_immediate(web49_io_input_t *in) {
    return (web49_memory_immediate_t){
        .align = web49_readbin_uleb(in),
        .offset = web49_readbin_uleb(in),
    };
}

web49_type_function_t web49_readbin_type_function(web49_io_input_t *in) {
    return (web49_type_function_t){
        .data = web49_readbin_uleb(in),
    };
}

web49_type_table_t web49_readbin_type_table(web49_io_input_t *in) {
    return (web49_type_table_t){
        .element_type = web49_readbin_byte(in),
        .limits = web49_readbin_type_memory(in),
    };
}

web49_type_global_t web49_readbin_type_global(web49_io_input_t *in) {
    return (web49_type_global_t){
        .content_type = web49_readbin_byte(in),
        .is_mutable = web49_readbin_byte(in),
    };
}

web49_type_memory_t web49_readbin_type_memory(web49_io_input_t *in) {
    uint64_t flags = web49_readbin_uleb(in);
    return (web49_type_memory_t){
        .initial = web49_readbin_uleb(in),
        .maximum = (flags == 1) ? web49_readbin_uleb(in) : UINT32_MAX,
    };
}

web49_type_t web49_readbin_type(web49_io_input_t *in, web49_external_kind_t tag) {
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
    fprintf(stderr, "unknown external kind: %zu\n", (size_t)tag);
    exit(1);
}

web49_section_custom_t web49_readbin_section_custom(web49_io_input_t *in, web49_section_header_t header) {
    uint64_t size = header.size;
    size_t begin = web49_io_input_ftell(in);
    uint64_t name_len = web49_readbin_uleb(in);
    char *name = web49_malloc(sizeof(char) * (name_len + 1));
    web49_io_input_fread(in, sizeof(char) * name_len, name);
    name[name_len] = '\0';
    size_t end = web49_io_input_ftell(in);
    size -= end - begin;
    void *payload = web49_malloc(size);
    web49_io_input_fread(in, (size), payload);
    return (web49_section_custom_t){
        .name = name,
        .payload = payload,
    };
}

web49_section_type_t web49_readbin_section_type(web49_io_input_t *in) {
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
        web49_lang_type_t *return_types = web49_malloc(sizeof(web49_lang_type_t) * num_returns);
        for (size_t n = 0; n < num_returns; n++) {
            return_types[n] = web49_readbin_byte(in);
        }
        entries[i] = (web49_section_type_entry_t){
            .type = type,
            .num_params = num_params,
            .params = params,
            .num_returns = num_returns,
            .return_types = return_types,
        };
    }
    return (web49_section_type_t){
        .num_entries = num,
        .entries = entries,
    };
}

web49_section_import_t web49_readbin_section_import(web49_io_input_t *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_import_entry_t *entries = web49_malloc(sizeof(web49_section_import_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t module_len = web49_readbin_uleb(in);
        char *module_str = web49_malloc(sizeof(char) * (module_len + 1));
        web49_io_input_fread(in, (module_len), module_str);
        module_str[module_len] = '\0';
        uint64_t field_len = web49_readbin_uleb(in);
        char *field_str = web49_malloc(sizeof(char) * (field_len + 1));
        web49_io_input_fread(in, (field_len), field_str);
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

web49_section_function_t web49_readbin_section_function(web49_io_input_t *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    uint32_t *entries = web49_malloc(sizeof(uint32_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = web49_readbin_uleb(in);
    }
    return (web49_section_function_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

web49_section_table_t web49_readbin_section_table(web49_io_input_t *in) {
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

web49_section_memory_t web49_readbin_section_memory(web49_io_input_t *in) {
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

web49_section_global_t web49_readbin_section_global(web49_io_input_t *in) {
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

web49_section_export_t web49_readbin_section_export(web49_io_input_t *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_export_entry_t *entries = web49_malloc(sizeof(web49_section_export_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t field_len = web49_readbin_uleb(in);
        char *field_str = web49_malloc(sizeof(char) * (field_len + 1));
        web49_io_input_fread(in, (field_len), field_str);
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

web49_section_start_t web49_readbin_section_start(web49_io_input_t *in) {
    return (web49_section_start_t){
        .index = web49_readbin_uleb(in),
    };
}

web49_section_element_t web49_readbin_section_element(web49_io_input_t *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_element_entry_t *entries = web49_malloc(sizeof(web49_section_element_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint32_t index = web49_readbin_uleb(in);
        web49_instr_t offset = web49_readbin_init_expr(in);
        uint32_t num_elems = web49_readbin_uleb(in);
        uint32_t *elems = web49_malloc(sizeof(uint32_t) * num_elems);
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

web49_section_code_t web49_readbin_section_code(web49_io_input_t *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_code_entry_t *entries = web49_malloc(sizeof(web49_section_code_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t body_len = web49_readbin_uleb(in);
        size_t end = web49_io_input_ftell(in) + body_len;
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
        while (web49_io_input_ftell(in) < end) {
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

web49_section_data_t web49_readbin_section_data(web49_io_input_t *in) {
    uint64_t num_entries = web49_readbin_uleb(in);
    web49_section_data_entry_t *entries = web49_malloc(sizeof(web49_section_data_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t tag = web49_readbin_byte(in);
        web49_instr_t offset = web49_readbin_init_expr(in);
        if (tag == 1) {
            fprintf(stderr, "passive data mode not yet implemented\n");
            exit(1);
        }
        if (tag == 2) {
            fprintf(stderr, "multiple memories for data not yet implemented\n");
            exit(1);
        }
        uint64_t size = web49_readbin_uleb(in);
        uint8_t *data = web49_malloc(sizeof(uint8_t) * size);
        web49_io_input_fread(in, (size), data);
        entries[i] = (web49_section_data_entry_t){
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

web49_instr_immediate_t web49_readbin_instr_immediate(web49_io_input_t *in, web49_immediate_id_t id) {
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
            .id = WEB49_IMMEDIATE_DATA_INDEX,
            .data_index = web49_readbin_varint32(in),
        };
    }
    return (web49_instr_immediate_t){
        .id = WEB49_IMMEDIATE_NONE,
    };
}

web49_instr_t web49_readbin_init_expr(web49_io_input_t *in) {
    web49_instr_t ret = web49_readbin_instr(in);
    web49_readbin_byte(in);
    return ret;
}

web49_instr_t web49_readbin_instr(web49_io_input_t *in) {
    uint8_t first_byte = web49_readbin_byte(in);
    uint8_t bytes[2] = {
        first_byte,
    };
    if (web49_opcode_is_multibyte(first_byte)) {
        bytes[1] = web49_readbin_byte(in);
    }
    web49_opcode_t opcode = web49_bytes_to_opcode(&bytes[0]);
    uint8_t skip = web49_opcode_skip(opcode);
    web49_immediate_id_t immediate_id = web49_opcode_immediate[opcode];
    web49_instr_immediate_t immediate = web49_readbin_instr_immediate(in, immediate_id);
    for (size_t i = 0; i < skip; i++) {
        (void)web49_readbin_byte(in);
    }
    return (web49_instr_t){
        .opcode = opcode,
        .immediate = immediate,
    };
}

web49_section_t web49_readbin_section(web49_io_input_t *in, web49_section_header_t header) {
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
    if (id == WEB49_SECTION_ID_DATA_COUNT) {
        void *mem = web49_malloc(sizeof(uint8_t) * header.size);
        web49_io_input_fread(in, header.size, mem);
        return (web49_section_t){
            .header = header,
            .custom_section.name = NULL,
            .custom_section.payload = mem,
        };
    }
    fprintf(stderr, "unknown section kind: 0x%zX starting at %zX\n", (size_t)id, (size_t)web49_io_input_ftell(in));
    exit(1);
}

web49_module_t web49_readbin_module(web49_io_input_t *in) {
    web49_preamble_t preamble = web49_readbin_preamble(in);
    uint64_t alloc_sections = 4;
    web49_section_t *sections = web49_malloc(sizeof(web49_section_t) * alloc_sections);
    uint64_t num_sections = 0;
    while (!web49_io_input_is_empty(in)) {
        if (num_sections + 1 >= alloc_sections) {
            alloc_sections = (alloc_sections + 1) * 2;
            sections = web49_realloc(sections, sizeof(web49_section_t) * alloc_sections);
        }
        web49_section_header_t header = web49_readbin_section_header(in);
        if (header.id >= WEB49_SECTION_HIGH_ID) {
            header.id = WEB49_SECTION_ID_CUSTOM;
        }
        if (web49_io_input_is_empty(in)) {
            break;
        }
        size_t a = web49_io_input_ftell(in);
        sections[num_sections] = web49_readbin_section(in, header);
        size_t b = web49_io_input_ftell(in);
        if (header.size != b - a) {
            fprintf(stderr, "read wrong number of bytes (read: %zu) (section size: %zu)\n", (size_t)header.size, b - a);
            exit(1);
        }
        num_sections += 1;
    }
    return (web49_module_t){
        .preamble = preamble,
        .num_sections = num_sections,
        .sections = sections,
    };
}
