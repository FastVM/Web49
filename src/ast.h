
#if !defined(WEB49_HEADER_AST)
#define WEB49_HEADER_AST

#include "lib.h"

typedef uint8_t web49_immediate_id_t;
typedef uint16_t web49_opcode_t;
typedef uint8_t web49_section_id_t;
typedef uint8_t web49_lang_type_t;
typedef uint8_t web49_external_kind_t;

enum web49_lang_type_enum_t {
    WEB49_TYPE_NOT_SPECIFIED = 0x00,
    WEB49_TYPE_I32 = 0x7f,
    WEB49_TYPE_I64 = 0x7e,
    WEB49_TYPE_F32 = 0x7d,
    WEB49_TYPE_F64 = 0x7c,
    WEB49_TYPE_ANYFUNC = 0x70,
    WEB49_TYPE_FUNC = 0x60,
    WEB49_TYPE_BLOCK_TYPE = 0x40,
};

enum web49_external_kind_enum_t {
    WEB49_EXTERNAL_KIND_FUNCTION = 0,
    WEB49_EXTERNAL_KIND_TABLE = 1,
    WEB49_EXTERNAL_KIND_MEMORY = 2,
    WEB49_EXTERNAL_KIND_GLOBAL = 3,
};

enum web49_section_id_enum_t {
    WEB49_SECTION_ID_CUSTOM = 0,
    WEB49_SECTION_ID_TYPE = 1,
    WEB49_SECTION_ID_IMPORT = 2,
    WEB49_SECTION_ID_FUNCTION = 3,
    WEB49_SECTION_ID_TABLE = 4,
    WEB49_SECTION_ID_MEMORY = 5,
    WEB49_SECTION_ID_GLOBAL = 6,
    WEB49_SECTION_ID_EXPORT = 7,
    WEB49_SECTION_ID_START = 8,
    WEB49_SECTION_ID_ELEMENT = 9,
    WEB49_SECTION_ID_CODE = 10,
    WEB49_SECTION_ID_DATA = 11,
    WEB49_SECTION_ID_DATA_COUNT = 12,
    WEB49_SECTION_HIGH_ID,
};

enum web49_opcode_enum_t {
    // FLOW CONTROL
    WEB49_OPCODE_UNREACHABLE = 0x0,
    WEB49_OPCODE_NOP = 0x1,
    WEB49_OPCODE_BLOCK = 0x2,
    WEB49_OPCODE_LOOP = 0x3,
    WEB49_OPCODE_IF = 0x4,
    WEB49_OPCODE_ELSE = 0x5,
    WEB49_OPCODE_END = 0xB,
    WEB49_OPCODE_BR = 0xC,
    WEB49_OPCODE_BR_IF = 0xD,
    WEB49_OPCODE_BR_TABLE = 0xE,
    WEB49_OPCODE_RETURN = 0xF,

    // CALLS
    WEB49_OPCODE_CALL = 0x10,
    WEB49_OPCODE_CALL_INDIRECT = 0x11,

    // PARAMETRIC OPERATORS
    WEB49_OPCODE_DROP = 0x1A,
    WEB49_OPCODE_SELECT = 0x1B,

    // VARIBALE ACCESS
    WEB49_OPCODE_GET_LOCAL = 0x20,
    WEB49_OPCODE_SET_LOCAL = 0x21,
    WEB49_OPCODE_TEE_LOCAL = 0x22,
    WEB49_OPCODE_GET_GLOBAL = 0x23,
    WEB49_OPCODE_SET_GLOBAL = 0x24,

    // MEMORY-RELATED OPERATORS
    WEB49_OPCODE_I32_LOAD = 0x28,
    WEB49_OPCODE_I64_LOAD = 0x29,
    WEB49_OPCODE_F32_LOAD = 0x2A,
    WEB49_OPCODE_F64_LOAD = 0x2B,
    WEB49_OPCODE_I32_LOAD8_S = 0x2C,
    WEB49_OPCODE_I32_LOAD8_U = 0x2D,
    WEB49_OPCODE_I32_LOAD16_S = 0x2E,
    WEB49_OPCODE_I32_LOAD16_U = 0x2F,
    WEB49_OPCODE_I64_LOAD8_S = 0x30,
    WEB49_OPCODE_I64_LOAD8_U = 0x31,
    WEB49_OPCODE_I64_LOAD16_S = 0x32,
    WEB49_OPCODE_I64_LOAD16_U = 0x33,
    WEB49_OPCODE_I64_LOAD32_S = 0x34,
    WEB49_OPCODE_I64_LOAD32_U = 0x35,
    WEB49_OPCODE_I32_STORE = 0x36,
    WEB49_OPCODE_I64_STORE = 0x37,
    WEB49_OPCODE_F32_STORE = 0x38,
    WEB49_OPCODE_F64_STORE = 0x39,
    WEB49_OPCODE_I32_STORE8 = 0x3A,
    WEB49_OPCODE_I32_STORE16 = 0x3B,
    WEB49_OPCODE_I64_STORE8 = 0x3C,
    WEB49_OPCODE_I64_STORE16 = 0x3D,
    WEB49_OPCODE_I64_STORE32 = 0x3E,
    WEB49_OPCODE_MEMORY_SIZE = 0x3F,
    WEB49_OPCODE_MEMORY_GROW = 0x40,

    // CONSTANTS
    WEB49_OPCODE_I32_CONST = 0x41,
    WEB49_OPCODE_I64_CONST = 0x42,
    WEB49_OPCODE_F32_CONST = 0x43,
    WEB49_OPCODE_F64_CONST = 0x44,

    // COMPARISON OPERATORS
    WEB49_OPCODE_I32_EQZ = 0x45,
    WEB49_OPCODE_I32_EQ = 0x46,
    WEB49_OPCODE_I32_NE = 0x47,
    WEB49_OPCODE_I32_LT_S = 0x48,
    WEB49_OPCODE_I32_LT_U = 0x49,
    WEB49_OPCODE_I32_GT_S = 0x4A,
    WEB49_OPCODE_I32_GT_U = 0x4B,
    WEB49_OPCODE_I32_LE_S = 0x4C,
    WEB49_OPCODE_I32_LE_U = 0x4D,
    WEB49_OPCODE_I32_GE_S = 0x4E,
    WEB49_OPCODE_I32_GE_U = 0x4F,
    WEB49_OPCODE_I64_EQZ = 0x50,
    WEB49_OPCODE_I64_EQ = 0x51,
    WEB49_OPCODE_I64_NE = 0x52,
    WEB49_OPCODE_I64_LT_S = 0x53,
    WEB49_OPCODE_I64_LT_U = 0x54,
    WEB49_OPCODE_I64_GT_S = 0x55,
    WEB49_OPCODE_I64_GT_U = 0x56,
    WEB49_OPCODE_I64_LE_S = 0x57,
    WEB49_OPCODE_I64_LE_U = 0x58,
    WEB49_OPCODE_I64_GE_S = 0x59,
    WEB49_OPCODE_I64_GE_U = 0x5A,
    WEB49_OPCODE_F32_EQ = 0x5B,
    WEB49_OPCODE_F32_NE = 0x5C,
    WEB49_OPCODE_F32_LT = 0x5D,
    WEB49_OPCODE_F32_GT = 0x5E,
    WEB49_OPCODE_F32_LE = 0x5F,
    WEB49_OPCODE_F32_GE = 0x60,
    WEB49_OPCODE_F64_EQ = 0x61,
    WEB49_OPCODE_F64_NE = 0x62,
    WEB49_OPCODE_F64_LT = 0x63,
    WEB49_OPCODE_F64_GT = 0x64,
    WEB49_OPCODE_F64_LE = 0x65,
    WEB49_OPCODE_F64_GE = 0x66,

    // NUMERIC OPERATORS
    WEB49_OPCODE_I32_CLZ = 0x67,
    WEB49_OPCODE_I32_CTZ = 0x68,
    WEB49_OPCODE_I32_POPCNT = 0x69,
    WEB49_OPCODE_I32_ADD = 0x6A,
    WEB49_OPCODE_I32_SUB = 0x6B,
    WEB49_OPCODE_I32_MUL = 0x6C,
    WEB49_OPCODE_I32_DIV_S = 0x6D,
    WEB49_OPCODE_I32_DIV_U = 0x6E,
    WEB49_OPCODE_I32_REM_S = 0x6F,
    WEB49_OPCODE_I32_REM_U = 0x70,
    WEB49_OPCODE_I32_AND = 0x71,
    WEB49_OPCODE_I32_OR = 0x72,
    WEB49_OPCODE_I32_XOR = 0x73,
    WEB49_OPCODE_I32_SHL = 0x74,
    WEB49_OPCODE_I32_SHR_S = 0x75,
    WEB49_OPCODE_I32_SHR_U = 0x76,
    WEB49_OPCODE_I32_ROTL = 0x77,
    WEB49_OPCODE_I32_ROTR = 0x78,
    WEB49_OPCODE_I64_CLZ = 0x79,
    WEB49_OPCODE_I64_CTZ = 0x7A,
    WEB49_OPCODE_I64_POPCNT = 0x7B,
    WEB49_OPCODE_I64_ADD = 0x7C,
    WEB49_OPCODE_I64_SUB = 0x7D,
    WEB49_OPCODE_I64_MUL = 0x7E,
    WEB49_OPCODE_I64_DIV_S = 0x7F,
    WEB49_OPCODE_I64_DIV_U = 0x80,
    WEB49_OPCODE_I64_REM_S = 0x81,
    WEB49_OPCODE_I64_REM_U = 0x82,
    WEB49_OPCODE_I64_AND = 0x83,
    WEB49_OPCODE_I64_OR = 0x84,
    WEB49_OPCODE_I64_XOR = 0x85,
    WEB49_OPCODE_I64_SHL = 0x86,
    WEB49_OPCODE_I64_SHR_S = 0x87,
    WEB49_OPCODE_I64_SHR_U = 0x88,
    WEB49_OPCODE_I64_ROTL = 0x89,
    WEB49_OPCODE_I64_ROTR = 0x8A,
    WEB49_OPCODE_F32_ABS = 0x8B,
    WEB49_OPCODE_F32_NEG = 0x8C,
    WEB49_OPCODE_F32_CEIL = 0x8D,
    WEB49_OPCODE_F32_FLOOR = 0x8E,
    WEB49_OPCODE_F32_TRUNC = 0x8F,
    WEB49_OPCODE_F32_NEAREST = 0x90,
    WEB49_OPCODE_F32_SQRT = 0x91,
    WEB49_OPCODE_F32_ADD = 0x92,
    WEB49_OPCODE_F32_SUB = 0x93,
    WEB49_OPCODE_F32_MUL = 0x94,
    WEB49_OPCODE_F32_DIV = 0x95,
    WEB49_OPCODE_F32_MIN = 0x96,
    WEB49_OPCODE_F32_MAX = 0x97,
    WEB49_OPCODE_F32_COPYSIGN = 0x98,
    WEB49_OPCODE_F64_ABS = 0x99,
    WEB49_OPCODE_F64_NEG = 0x9A,
    WEB49_OPCODE_F64_CEIL = 0x9B,
    WEB49_OPCODE_F64_FLOOR = 0x9C,
    WEB49_OPCODE_F64_TRUNC = 0x9D,
    WEB49_OPCODE_F64_NEAREST = 0x9E,
    WEB49_OPCODE_F64_SQRT = 0x9F,
    WEB49_OPCODE_F64_ADD = 0xA0,
    WEB49_OPCODE_F64_SUB = 0xA1,
    WEB49_OPCODE_F64_MUL = 0xA2,
    WEB49_OPCODE_F64_DIV = 0xA3,
    WEB49_OPCODE_F64_MIN = 0xA4,
    WEB49_OPCODE_F64_MAX = 0xA5,
    WEB49_OPCODE_F64_COPYSIGN = 0xA6,

    // CONVERSIONS
    WEB49_OPCODE_I32_WRAP_I64 = 0xA7,
    WEB49_OPCODE_I32_TRUNC_S_F32 = 0xA8,
    WEB49_OPCODE_I32_TRUNC_U_F32 = 0xA9,
    WEB49_OPCODE_I32_TRUNC_S_F64 = 0xAA,
    WEB49_OPCODE_I32_TRUNC_U_F64 = 0xAB,
    WEB49_OPCODE_I64_EXTEND_S_I32 = 0xAC,
    WEB49_OPCODE_I64_EXTEND_U_I32 = 0xAD,
    WEB49_OPCODE_I64_TRUNC_S_F32 = 0xAE,
    WEB49_OPCODE_I64_TRUNC_U_F32 = 0xAF,
    WEB49_OPCODE_I64_TRUNC_S_F64 = 0xB0,
    WEB49_OPCODE_I64_TRUNC_U_F64 = 0xB1,
    WEB49_OPCODE_F32_CONVERT_S_I32 = 0xB2,
    WEB49_OPCODE_F32_CONVERT_U_I32 = 0xB3,
    WEB49_OPCODE_F32_CONVERT_S_I64 = 0xB4,
    WEB49_OPCODE_F32_CONVERT_U_I64 = 0xB5,
    WEB49_OPCODE_F32_DEMOTE_F64 = 0xB6,
    WEB49_OPCODE_F64_CONVERT_S_I32 = 0xB7,
    WEB49_OPCODE_F64_CONVERT_U_I32 = 0xB8,
    WEB49_OPCODE_F64_CONVERT_S_I64 = 0xB9,
    WEB49_OPCODE_F64_CONVERT_U_I64 = 0xBA,
    WEB49_OPCODE_F64_PROMOTE_F32 = 0xBB,

    // REINTERPRETATIONS
    WEB49_OPCODE_I32_REINTERPRET_F32 = 0xBC,
    WEB49_OPCODE_I64_REINTERPRET_F64 = 0xBD,
    WEB49_OPCODE_F32_REINTERPRET_I32 = 0xBE,
    WEB49_OPCODE_F64_REINTERPRET_I64 = 0xBF,

    // MEMORY OPCODES
    WEB49_256_OPCODE = 256,
    WEB49_OPCODE_MEMORY_INIT,
    WEB49_OPCODE_MEMORY_COPY,
    WEB49_OPCODE_MEMORY_FILL,
    WEB49_OPCODE_DATA_DROP,
    WEB49_OPCODE_TABLE_INIT,
    WEB49_OPCODE_ELEM_DROP,
    WEB49_OPCODE_TABLE_COPY,
    WEB49_MAX_OPCODE_NUM,
};

enum web49_memory_immediate_id_enum_t {
    WEB49_IMMEDIATE_NONE,
    WEB49_IMMEDIATE_BLOCK_TYPE,
    WEB49_IMMEDIATE_VARUINT1,
    WEB49_IMMEDIATE_VARUINT32,
    WEB49_IMMEDIATE_VARUINT64,
    WEB49_IMMEDIATE_VARINT32,
    WEB49_IMMEDIATE_VARINT64,
    WEB49_IMMEDIATE_UINT32,
    WEB49_IMMEDIATE_UINT64,
    WEB49_IMMEDIATE_BR_TABLE,
    WEB49_IMMEDIATE_CALL_INDIRECT,
    WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    WEB49_IMMEDIATE_DATA_INDEX,
};

struct web49_preamble_t;
typedef struct web49_preamble_t web49_preamble_t;

struct web49_section_header_t;
typedef struct web49_section_header_t web49_section_header_t;

struct web49_br_table_t;
typedef struct web49_br_table_t web49_br_table_t;

struct web49_call_indirect_t;
typedef struct web49_call_indirect_t web49_call_indirect_t;

struct web49_memory_immediate_t;
typedef struct web49_memory_immediate_t web49_memory_immediate_t;

struct web49_type_function_t;
typedef struct web49_type_function_t web49_type_function_t;

struct web49_type_table_t;
typedef struct web49_type_table_t web49_type_table_t;

struct web49_type_t;
typedef struct web49_type_t web49_type_t;

struct web49_type_global_t;
typedef struct web49_type_global_t web49_type_global_t;

struct web49_type_memory_t;
typedef struct web49_type_memory_t web49_type_memory_t;

struct web49_section_custom_t;
typedef struct web49_section_custom_t web49_section_custom_t;

struct web49_section_type_entry_t;
typedef struct web49_section_type_entry_t web49_section_type_entry_t;

struct web49_section_type_t;
typedef struct web49_section_type_t web49_section_type_t;

struct web49_section_export_entry_t;
typedef struct web49_section_export_entry_t web49_section_export_entry_t;

struct web49_section_export_t;
typedef struct web49_section_export_t web49_section_export_t;

struct web49_section_import_entry_t;
typedef struct web49_section_import_entry_t web49_section_import_entry_t;

struct web49_section_import_t;
typedef struct web49_section_import_t web49_section_import_t;

struct web49_section_function_t;
typedef struct web49_section_function_t web49_section_function_t;

struct web49_section_table_t;
typedef struct web49_section_table_t web49_section_table_t;

struct web49_section_memory_t;
typedef struct web49_section_memory_t web49_section_memory_t;

struct web49_section_global_entry_t;
typedef struct web49_section_global_entry_t web49_section_global_entry_t;

struct web49_section_global_t;
typedef struct web49_section_global_t web49_section_global_t;

struct web49_section_start_t;
typedef struct web49_section_start_t web49_section_start_t;

struct web49_section_element_entry_t;
typedef struct web49_section_element_entry_t web49_section_element_entry_t;

struct web49_section_element_t;
typedef struct web49_section_element_t web49_section_element_t;

struct web49_section_code_entry_local_t;
typedef struct web49_section_code_entry_local_t web49_section_code_entry_local_t;

struct web49_section_code_entry_t;
typedef struct web49_section_code_entry_t web49_section_code_entry_t;

struct web49_section_code_t;
typedef struct web49_section_code_t web49_section_code_t;

struct web49_section_data_entry_t;
typedef struct web49_section_data_entry_t web49_section_data_entry_t;

struct web49_section_data_t;
typedef struct web49_section_data_t web49_section_data_t;

struct web49_instr_immediate_t;
typedef struct web49_instr_immediate_t web49_instr_immediate_t;

struct web49_instr_t;
typedef struct web49_instr_t web49_instr_t;

struct web49_section_t;
typedef struct web49_section_t web49_section_t;

struct web49_module_t;
typedef struct web49_module_t web49_module_t;

struct web49_preamble_t {
    uint8_t magic[4];
    uint8_t version[4];
};

struct web49_section_header_t {
    web49_section_id_t id;
    uint64_t size;
    bool size_known;
};

struct web49_br_table_t {
    uint64_t num_targets;
    uint64_t *targets;
    uint64_t default_target;
};

struct web49_call_indirect_t {
    uint64_t index;
    uint8_t reserved;
};

struct web49_memory_immediate_t {
    uint64_t align;
    uint64_t offset;
};

struct web49_type_function_t {
    uint64_t data;
};

struct web49_type_global_t {
    web49_lang_type_t content_type;
    uint8_t is_mutable;
};

struct web49_type_memory_t {
    uint64_t initial;
    uint64_t maximum;
};

struct web49_type_table_t {
    web49_lang_type_t element_type;
    web49_type_memory_t limits;
};

struct web49_type_t {
    union {
        web49_type_function_t function;
        web49_type_global_t global;
        web49_type_memory_t memory;
        web49_type_table_t table;
    };
    web49_lang_type_t tag;
};

// enum {
//     WEB49_SECTION_TYPE_CUSTOM = 0,
//     WEB49_SECTION_TYPE_TYPE = 1,
//     WEB49_SECTION_TYPE_IMPORT = 2,
//     WEB49_SECTION_TYPE_FUNCTION = 3,
//     WEB49_SECTION_TYPE_TABLE = 4,
//     WEB49_SECTION_TYPE_MEMORY = 5,
//     WEB49_SECTION_TYPE_GLOBAL = 6,
//     WEB49_SECTION_TYPE_EXPORT = 7,
//     WEB49_SECTION_TYPE_START = 8,
//     WEB49_SECTION_TYPE_ELEMENT = 9,
//     WEB49_SECTION_TYPE_CODE = 10,
//     WEB49_SECTION_TYPE_DAT = 11,
// };

struct web49_section_custom_t {
    void *payload;
};

struct web49_section_type_entry_t {
    web49_lang_type_t type;
    uint64_t num_params;
    web49_lang_type_t *params;
    uint64_t num_returns;
    web49_lang_type_t return_type;
    bool has_return_type;
};

struct web49_section_type_t {
    uint64_t num_entries;
    web49_section_type_entry_t *entries;
};

struct web49_section_import_entry_t {
    const char *module_str;
    const char *field_str;
    web49_external_kind_t kind;
    union {
        web49_type_function_t func_type;
        web49_type_table_t table_type;
        web49_type_memory_t memory_type;
        web49_type_global_t global_type;
    };
};

struct web49_section_import_t {
    uint64_t num_entries;
    web49_section_import_entry_t *entries;
};

struct web49_section_function_t {
    uint64_t num_entries;
    uint64_t *entries;
};

struct web49_section_export_entry_t {
    const char *field_str;
    web49_external_kind_t kind;
    uint64_t index;
};

struct web49_section_export_t {
    uint64_t num_entries;
    web49_section_export_entry_t *entries;
};

struct web49_section_table_t {
    uint64_t num_entries;
    web49_type_table_t *entries;
};

struct web49_section_memory_t {
    uint64_t num_entries;
    web49_type_memory_t *entries;
};

struct web49_instr_immediate_t {
    union {
        uint8_t varuint1;
        uint32_t varuint32;
        uint64_t varuint64;
        int32_t varint32;
        int64_t varint64;
        uint32_t uint32;
        uint64_t uint64;
        web49_lang_type_t block_type;
        web49_br_table_t br_table;
        web49_call_indirect_t call_indirect;
        web49_memory_immediate_t memory_immediate;
        uint32_t data_index;
    };
    web49_immediate_id_t id;
};

struct web49_instr_t {
    web49_opcode_t opcode;
    web49_instr_immediate_t immediate;
};

struct web49_section_global_entry_t {
    web49_type_global_t global;
    web49_instr_t init_expr;
};

struct web49_section_global_t {
    uint64_t num_entries;
    web49_section_global_entry_t *entries;
};

struct web49_section_start_t {
    uint64_t index;
};

struct web49_section_element_entry_t {
    uint64_t index;
    web49_instr_t offset;
    uint64_t num_elems;
    uint64_t *elems;
};

struct web49_section_element_t {
    uint64_t num_entries;
    web49_section_element_entry_t *entries;
};

struct web49_section_code_entry_local_t {
    uint64_t count;
    web49_lang_type_t type;
};

struct web49_section_code_entry_t {
    uint64_t num_locals;
    web49_section_code_entry_local_t *locals;
    uint64_t num_instrs;
    web49_instr_t *instrs;
};

struct web49_section_code_t {
    uint64_t num_entries;
    web49_section_code_entry_t *entries;
};

struct web49_section_data_entry_t {
    uint64_t index;
    web49_instr_t offset;
    uint64_t size;
    uint8_t *data;
};

struct web49_section_data_t {
    uint64_t num_entries;
    web49_section_data_entry_t *entries;
};

struct web49_section_t {
    union {
        web49_section_custom_t custom_section;
        web49_section_type_t type_section;
        web49_section_import_t import_section;
        web49_section_function_t function_section;
        web49_section_table_t table_section;
        web49_section_memory_t memory_section;
        web49_section_global_t global_section;
        web49_section_export_t export_section;
        web49_section_start_t start_section;
        web49_section_element_t element_section;
        web49_section_code_t code_section;
        web49_section_data_t data_section;
    };
    web49_section_header_t header;
};

struct web49_module_t {
    web49_preamble_t preamble;
    uint64_t num_sections;
    web49_section_t *sections;
};

#define web49_preamble_init ((web49_preamble_t) { 0x00, 0x61, 0x73, 0x6D, 0x01, 0x00, 0x00, 0x00 })

#endif
