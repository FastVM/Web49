
#include "./parse.h"

vm_wasm_immediate_id_t vm_wasm_immediates[] = {
    [VM_WASM_OPCODE_BLOCK] = VM_WASM_IMMEDIATE_BLOCK_TYPE,
    [VM_WASM_OPCODE_LOOP] = VM_WASM_IMMEDIATE_BLOCK_TYPE,
    [VM_WASM_OPCODE_IF] = VM_WASM_IMMEDIATE_BLOCK_TYPE,
    [VM_WASM_OPCODE_BR] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_BR_IF] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_BR_TABLE] = VM_WASM_IMMEDIATE_BR_TABLE,
    [VM_WASM_OPCODE_CALL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_CALL_INDIRECT] = VM_WASM_IMMEDIATE_CALL_INDIRECT,
    [VM_WASM_OPCODE_GET_LOCAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_SET_LOCAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_TEE_LOCAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_GET_GLOBAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_SET_GLOBAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_I32_LOAD] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_F32_LOAD] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_F64_LOAD] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_LOAD8_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_LOAD8_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_LOAD16_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_LOAD16_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD8_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD8_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD16_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD16_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD32_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD32_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_STORE] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_STORE] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_F32_STORE] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_F64_STORE] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_STORE8] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_STORE16] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_STORE8] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_STORE16] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_STORE32] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_CURRENT_MEMORY] = VM_WASM_IMMEDIATE_VARUINT1,
    [VM_WASM_OPCODE_GROW_MEMORY] = VM_WASM_IMMEDIATE_VARUINT1,
    [VM_WASM_OPCODE_I32_CONST] = VM_WASM_IMMEDIATE_VARINT32,
    [VM_WASM_OPCODE_I64_CONST] = VM_WASM_IMMEDIATE_VARINT64,
    [VM_WASM_OPCODE_F32_CONST] = VM_WASM_IMMEDIATE_UINT32,
    [VM_WASM_OPCODE_F64_CONST] = VM_WASM_IMMEDIATE_UINT64,
};

uint64_t vm_wasm_parse_uleb(FILE *in) {
    unsigned char buf;
    uint64_t x = 0;
    size_t bytes = 0;
    while (fread(&buf, 1, 1, in)) {
        x |= (buf & 0x7fULL) << (7 * bytes++);
        if (!(buf & 0x80U)) {
            break;
        }
    }
    return x;
}

int64_t vm_wasm_parse_sleb(FILE *in) {
    uint64_t ret = vm_wasm_parse_uleb(in);
    return *(int64_t *)&ret;
}

uint8_t vm_wasm_parse_byte(FILE *in) {
    uint8_t ret;
    fread(&ret, 1, 1, in);
    return ret;
}

vm_wasm_preamble_t vm_wasm_parse_preamble(FILE *in) {
    return (vm_wasm_preamble_t){
        .magic[0] = vm_wasm_parse_byte(in),
        .magic[1] = vm_wasm_parse_byte(in),
        .magic[2] = vm_wasm_parse_byte(in),
        .magic[3] = vm_wasm_parse_byte(in),
        .version[0] = vm_wasm_parse_byte(in),
        .version[1] = vm_wasm_parse_byte(in),
        .version[2] = vm_wasm_parse_byte(in),
        .version[3] = vm_wasm_parse_byte(in),
    };
}

vm_wasm_section_header_t vm_wasm_parse_section_header(FILE *in) {
    uint8_t id = vm_wasm_parse_byte(in);
    uint64_t size = vm_wasm_parse_uleb(in);
    return (vm_wasm_section_header_t){
        .id = id,
        .size = size,
    };
}

uint8_t vm_wasm_parse_varuint1(FILE *in) {
    return vm_wasm_parse_byte(in);
}

int32_t vm_wasm_parse_varint32(FILE *in) {
    return (int32_t)vm_wasm_parse_sleb(in);
}

int64_t vm_wasm_parse_varint64(FILE *in) {
    return (int64_t)vm_wasm_parse_sleb(in);
}

int32_t vm_wasm_parse_varuint32(FILE *in) {
    return (uint32_t)vm_wasm_parse_uleb(in);
}

int64_t vm_wasm_parse_varuint64(FILE *in) {
    return (uint64_t)vm_wasm_parse_uleb(in);
}

uint32_t vm_wasm_parse_uint32(FILE *in) {
    uint32_t ret;
    fread(&ret, sizeof(uint32_t), 1, in);
    return ret;
}

uint64_t vm_wasm_parse_uint64(FILE *in) {
    uint64_t ret;
    fread(&ret, sizeof(uint64_t), 1, in);
    return ret;
}

vm_wasm_lang_type_t vm_wasm_parse_block_type(FILE *in) {
    return vm_wasm_parse_byte(in);
}

vm_wasm_br_table_t vm_wasm_parse_br_table(FILE *in) {
    uint64_t num = vm_wasm_parse_uleb(in);
    uint64_t *targets = vm_malloc(sizeof(uint64_t) * num);
    for (uint64_t i = 0; i < num; i++) {
        targets[i] = vm_wasm_parse_uleb(in);
    }
    uint64_t default_target = vm_wasm_parse_uleb(in);
    return (vm_wasm_br_table_t){
        .num_targets = num,
        .targets = targets,
        .default_target = default_target,
    };
}

vm_wasm_call_indirect_t vm_wasm_parse_call_indirect(FILE *in) {
    return (vm_wasm_call_indirect_t){
        .index = vm_wasm_parse_uleb(in),
        .reserved = vm_wasm_parse_byte(in),
    };
}

vm_wasm_memory_immediate_t vm_wasm_parse_memory_immediate(FILE *in) {
    return (vm_wasm_memory_immediate_t){
        .flags = vm_wasm_parse_uleb(in),
        .offset = vm_wasm_parse_uleb(in),
    };
}

vm_wasm_type_function_t vm_wasm_parse_type_function(FILE *in) {
    return (vm_wasm_type_function_t){
        .data = vm_wasm_parse_uleb(in),
    };
}

vm_wasm_type_table_t vm_wasm_parse_type_table(FILE *in) {
    return (vm_wasm_type_table_t){
        .element_type = vm_wasm_parse_byte(in),
        .limits = vm_wasm_parse_type_memory(in),
    };
}

vm_wasm_type_global_t vm_wasm_parse_type_global(FILE *in) {
    return (vm_wasm_type_global_t){
        .content_type = vm_wasm_parse_byte(in),
        .mutability = vm_wasm_parse_byte(in),
    };
}

vm_wasm_type_memory_t vm_wasm_parse_type_memory(FILE *in) {
    uint64_t flags = vm_wasm_parse_uleb(in);
    return (vm_wasm_type_memory_t){
        .flags = flags,
        .initial = vm_wasm_parse_uleb(in),
        .maximum = (flags % 2 == 1) ? vm_wasm_parse_uleb(in) : UINT64_MAX,
    };
}

vm_wasm_type_t vm_wasm_parse_type(FILE *in, vm_wasm_external_kind_t tag) {
    if (tag == VM_WASM_EXTERNAL_KIND_FUNCTION) {
        return (vm_wasm_type_t){
            .function = vm_wasm_parse_type_function(in),
            .tag = tag,
        };
    }
    if (tag == VM_WASM_EXTERNAL_KIND_TABLE) {
        return (vm_wasm_type_t){
            .table = vm_wasm_parse_type_table(in),
            .tag = tag,
        };
    }
    if (tag == VM_WASM_EXTERNAL_KIND_GLOBAL) {
        return (vm_wasm_type_t){
            .global = vm_wasm_parse_type_global(in),
            .tag = tag,
        };
    }
    if (tag == VM_WASM_EXTERNAL_KIND_MEMORY) {
        return (vm_wasm_type_t){
            .memory = vm_wasm_parse_type_memory(in),
            .tag = tag,
        };
    }
    exit(1);
}

vm_wasm_section_custom_t vm_wasm_parse_section_custom(FILE *in, vm_wasm_section_header_t header) {
    void *payload = vm_malloc(header.size);
    fread(payload, 1, header.size, in);
    return (vm_wasm_section_custom_t){
        .payload = payload,
    };
}

vm_wasm_section_type_t vm_wasm_parse_section_type(FILE *in) {
    uint64_t num = vm_wasm_parse_uleb(in);
    vm_wasm_section_type_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_type_entry_t) * num);
    for (uint64_t i = 0; i < num; i++) {
        vm_wasm_section_type_entry_t entry;
        vm_wasm_lang_type_t type = vm_wasm_parse_byte(in);
        uint64_t num_params = vm_wasm_parse_uleb(in);
        vm_wasm_lang_type_t *params = vm_malloc(sizeof(vm_wasm_lang_type_t) * num_params);
        for (uint64_t j = 0; j < num_params; j++) {
            params[j] = vm_wasm_parse_byte(in);
        }
        uint64_t num_returns = vm_wasm_parse_uleb(in);
        vm_wasm_lang_type_t return_type = VM_WASM_TYPE_NOT_SPECIFIED;
        bool has_return_type = false;
        if (num_returns != 0) {
            has_return_type = true;
            return_type = vm_wasm_parse_byte(in);
        }
        entries[i] = (vm_wasm_section_type_entry_t){
            .type = type,
            .num_params = num_params,
            .params = params,
            .num_returns = num_returns,
            .has_return_type = has_return_type,
            .return_type = return_type,
        };
    }
    return (vm_wasm_section_type_t){
        .num_entries = num,
        .entries = entries,
    };
}

vm_wasm_section_import_t vm_wasm_parse_section_import(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_import_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_import_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t module_len = vm_wasm_parse_uleb(in);
        char *module_str = vm_malloc(sizeof(char) * (module_len + 1));
        fread(module_str, 1, module_len, in);
        module_str[module_len] = '\0';
        uint64_t field_len = vm_wasm_parse_uleb(in);
        char *field_str = vm_malloc(sizeof(char) * (field_len + 1));
        fread(field_str, 1, field_len, in);
        field_str[field_len] = '\0';
        vm_wasm_external_kind_t kind = vm_wasm_parse_byte(in);
        vm_wasm_type_t type = vm_wasm_parse_type(in, kind);
        entries[i] = (vm_wasm_section_import_entry_t){
            .module_str = module_str,
            .field_str = field_str,
            .kind = kind,
            .type = type,
        };
    }
    return (vm_wasm_section_import_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_function_t vm_wasm_parse_section_function(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    uint64_t *entries = vm_malloc(sizeof(uint64_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = vm_wasm_parse_uleb(in);
    }
    return (vm_wasm_section_function_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_table_t vm_wasm_parse_section_table(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_type_table_t *entries = vm_malloc(sizeof(vm_wasm_type_table_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = vm_wasm_parse_type_table(in);
    }
    return (vm_wasm_section_table_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_memory_t vm_wasm_parse_section_memory(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_type_memory_t *entries = vm_malloc(sizeof(vm_wasm_section_global_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = vm_wasm_parse_type_memory(in);
    }
    return (vm_wasm_section_memory_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_global_t vm_wasm_parse_section_global(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_global_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_global_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = (vm_wasm_section_global_entry_t){
            .global = vm_wasm_parse_type_global(in),
            .init_expr = vm_wasm_parse_init_expr(in),
        };
    }
    return (vm_wasm_section_global_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_export_t vm_wasm_parse_section_export(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_export_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_export_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t field_len = vm_wasm_parse_uleb(in);
        char *field_str = vm_malloc(sizeof(char) * (field_len + 1));
        fread(field_str, 1, field_len, in);
        field_str[field_len] = '\0';
        vm_wasm_external_kind_t kind = vm_wasm_parse_byte(in);
        uint64_t index = vm_wasm_parse_uleb(in);
        entries[i] = (vm_wasm_section_export_entry_t){
            .field_str = field_str,
            .kind = kind,
            .index = index,
        };
    }
    return (vm_wasm_section_export_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_start_t vm_wasm_parse_section_start(FILE *in) {
    return (vm_wasm_section_start_t){
        .index = vm_wasm_parse_uleb(in),
    };
}

vm_wasm_section_element_t vm_wasm_parse_section_element(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_element_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_element_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t index = vm_wasm_parse_uleb(in);
        vm_wasm_instr_t offset = vm_wasm_parse_init_expr(in);
        uint64_t num_elems = vm_wasm_parse_uleb(in);
        uint64_t *elems = vm_malloc(sizeof(uint64_t) * num_elems);
        for (uint64_t j = 0; j < num_elems; j++) {
            elems[j] = vm_wasm_parse_uleb(in);
        }
        entries[i] = (vm_wasm_section_element_entry_t){
            .index = index,
            .offset = offset,
            .num_elems = num_elems,
            .elems = elems,
        };
    }
    return (vm_wasm_section_element_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_code_t vm_wasm_parse_section_code(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_code_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_code_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t body_len = vm_wasm_parse_uleb(in);
        long end = ftell(in) + (long)body_len;
        uint64_t num_locals = vm_wasm_parse_uleb(in);
        vm_wasm_section_code_entry_local_t *locals = vm_malloc(sizeof(vm_wasm_section_code_entry_local_t) * num_locals);
        for (uint64_t j = 0; j < num_locals; j++) {
            uint64_t count = vm_wasm_parse_uleb(in);
            vm_wasm_lang_type_t type = vm_wasm_parse_byte(in);
            locals[j] = (vm_wasm_section_code_entry_local_t){
                .count = count,
                .type = type,
            };
        }
        uint64_t alloc_instrs = 4;
        vm_wasm_instr_t *instrs = vm_malloc(sizeof(vm_wasm_instr_t) * alloc_instrs);
        uint64_t num_instrs = 0;
        while (ftell(in) < end) {
            if (num_instrs + 1 >= alloc_instrs) {
                alloc_instrs = (alloc_instrs + 1) * 2;
                instrs = vm_realloc(instrs, sizeof(vm_wasm_instr_t) * alloc_instrs);
            }
            instrs[num_instrs] = vm_wasm_parse_instr(in);
            num_instrs += 1;
        }
        entries[i] = (vm_wasm_section_code_entry_t){
            .num_locals = num_locals,
            .locals = locals,
            .num_instrs = num_instrs,
            .instrs = instrs,
        };
    }
    return (vm_wasm_section_code_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_data_t vm_wasm_parse_section_data(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_data_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_data_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t index = vm_wasm_parse_uleb(in);
        vm_wasm_instr_t offset = vm_wasm_parse_init_expr(in);
        uint64_t size = vm_wasm_parse_uleb(in);
        uint8_t *data = vm_malloc(sizeof(uint8_t) * size);
        fread(data, 1, size, in);
        entries[i] = (vm_wasm_section_data_entry_t){
            .index = index,
            .offset = offset,
            .size = size,
            .data = data,
        };
    }
    return (vm_wasm_section_data_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_instr_immediate_t vm_wasm_parse_instr_immediate(FILE *in, vm_wasm_immediate_id_t id) {
    if (id == VM_WASM_IMMEDIATE_BLOCK_TYPE) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_BLOCK_TYPE,
            .block_type = vm_wasm_parse_block_type(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARUINT1) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_VARUINT1,
            .varuint1 = vm_wasm_parse_varuint1(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARUINT32) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_VARUINT32,
            .varuint32 = vm_wasm_parse_varuint32(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARUINT64) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_VARUINT64,
            .varuint64 = vm_wasm_parse_varuint64(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARINT32) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_VARINT32,
            .varint32 = vm_wasm_parse_varint32(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARINT64) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_VARINT64,
            .varint64 = vm_wasm_parse_varint64(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_UINT32) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_UINT32,
            .uint32 = vm_wasm_parse_uint32(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_UINT64) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_UINT64,
            .uint64 = vm_wasm_parse_uint64(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_BR_TABLE) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_BR_TABLE,
            .br_table = vm_wasm_parse_br_table(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_CALL_INDIRECT) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_CALL_INDIRECT,
            .call_indirect = vm_wasm_parse_call_indirect(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE) {
        return (vm_wasm_instr_immediate_t){
            .id = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
            .memory_immediate = vm_wasm_parse_memory_immediate(in),
        };
    }
    return (vm_wasm_instr_immediate_t) {
        .id = VM_WASM_IMMEDIATE_NONE,
    };
}

vm_wasm_instr_t vm_wasm_parse_init_expr(FILE *in) {
    vm_wasm_instr_t ret = vm_wasm_parse_instr(in);
    vm_wasm_parse_byte(in);
    return ret;
}

vm_wasm_instr_t vm_wasm_parse_instr(FILE *in) {
    vm_wasm_opcode_t opcode = vm_wasm_parse_sleb(in);
    vm_wasm_immediate_id_t immediate_id = vm_wasm_immediates[opcode];
    vm_wasm_instr_immediate_t immediate = vm_wasm_parse_instr_immediate(in, immediate_id);
    return (vm_wasm_instr_t){
        .opcode = opcode,
        .immediate = immediate,
    };
}

vm_wasm_section_t vm_wasm_parse_section(FILE *in, vm_wasm_section_header_t header) {
    vm_wasm_section_id_t id = header.id;
    if (id == VM_WASM_SECTION_ID_CUSTOM) {
        return (vm_wasm_section_t) {
            .id = id,
            .custom_section = vm_wasm_parse_section_custom(in, header),
        };
    }
    if (id == VM_WASM_SECTION_ID_TYPE) {
        return (vm_wasm_section_t) {
            .id = id,
            .type_section = vm_wasm_parse_section_type(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_IMPORT) {
        return (vm_wasm_section_t) {
            .id = id,
            .import_section = vm_wasm_parse_section_import(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_FUNCTION) {
        return (vm_wasm_section_t) {
            .id = id,
            .function_section = vm_wasm_parse_section_function(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_TABLE) {
        return (vm_wasm_section_t) {
            .id = id,
            .table_section = vm_wasm_parse_section_table(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_MEMORY) {
        return (vm_wasm_section_t) {
            .id = id,
            .memory_section = vm_wasm_parse_section_memory(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_GLOBAL) {
        return (vm_wasm_section_t) {
            .id = id,
            .global_section = vm_wasm_parse_section_global(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_EXPORT) {
        return (vm_wasm_section_t) {
            .id = id,
            .export_section = vm_wasm_parse_section_export(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_START) {
        return (vm_wasm_section_t) {
            .id = id,
            .start_section = vm_wasm_parse_section_start(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_ELEMENT) {
        return (vm_wasm_section_t) {
            .id = id,
            .element_section = vm_wasm_parse_section_element(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_CODE) {
        return (vm_wasm_section_t) {
            .id = id,
            .code_section = vm_wasm_parse_section_code(in),
        };
    }
    if (id == VM_WASM_SECTION_ID_DATA) {
        return (vm_wasm_section_t) {
            .id = id,
            .data_section = vm_wasm_parse_section_data(in),
        };
    }
    exit(1);
}

vm_wasm_module_t vm_wasm_parse_module(FILE *in) {
    vm_wasm_preamble_t preamble = vm_wasm_parse_preamble(in);
    uint64_t alloc_sections = 4;
    vm_wasm_section_t *sections = vm_malloc(sizeof(vm_wasm_section_t) * alloc_sections);
    uint64_t num_sections = 0;
    while (!feof(in)) {
        if (num_sections + 1 >= alloc_sections) {
            alloc_sections = (alloc_sections + 1) * 2;
            sections = vm_realloc(sections, sizeof(vm_wasm_section_t) * alloc_sections);
        }
        vm_wasm_section_header_t header = vm_wasm_parse_section_header(in);
        sections[num_sections] = vm_wasm_parse_section(in, header);
        num_sections += 1;
    }
    return (vm_wasm_module_t){
        .preamble = preamble,
        .num_sections = num_sections,
        .sections = sections,
    };
}
