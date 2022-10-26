
#if !defined(VM_HEADER_WASM)
#define VM_HEADER_WASM

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define vm_malloc(size) (malloc(size))
#define vm_realloc(ptr, size) (realloc(ptr, size))
#define vm_free(ptr) (free((void *)ptr))

typedef uint8_t vm_wasm_immediate_id_t;
typedef uint16_t vm_wasm_opcode_t;
typedef uint8_t vm_wasm_section_id_t;
typedef uint8_t vm_wasm_lang_type_t;
typedef uint8_t vm_wasm_external_kind_t;

enum vm_wasm_lang_type_enum_t {
    VM_WASM_TYPE_NOT_SPECIFIED = 0x00,
    VM_WASM_TYPE_I32 = 0x7f,
    VM_WASM_TYPE_I64 = 0x7e,
    VM_WASM_TYPE_F32 = 0x7d,
    VM_WASM_TYPE_F64 = 0x7c,
    VM_WASM_TYPE_ANYFUNC = 0x70,
    VM_WASM_TYPE_FUNC = 0x60,
    VM_WASM_TYPE_BLOCK_TYPE = 0x40,
};

enum vm_wasm_external_kind_enum_t {
    VM_WASM_EXTERNAL_KIND_FUNCTION = 0,
    VM_WASM_EXTERNAL_KIND_TABLE = 1,
    VM_WASM_EXTERNAL_KIND_MEMORY = 2,
    VM_WASM_EXTERNAL_KIND_GLOBAL = 3,
};

enum vm_wasm_section_id_enum_t {
    VM_WASM_SECTION_ID_CUSTOM = 0,
    VM_WASM_SECTION_ID_TYPE = 1,
    VM_WASM_SECTION_ID_IMPORT = 2,
    VM_WASM_SECTION_ID_FUNCTION = 3,
    VM_WASM_SECTION_ID_TABLE = 4,
    VM_WASM_SECTION_ID_MEMORY = 5,
    VM_WASM_SECTION_ID_GLOBAL = 6,
    VM_WASM_SECTION_ID_EXPORT = 7,
    VM_WASM_SECTION_ID_START = 8,
    VM_WASM_SECTION_ID_ELEMENT = 9,
    VM_WASM_SECTION_ID_CODE = 10,
    VM_WASM_SECTION_ID_DATA = 11,
};

enum vm_wasm_opcode_enum_t {
    // FLOW CONTROL
    VM_WASM_OPCODE_UNREACHABLE = 0x0,
    VM_WASM_OPCODE_NOP = 0x1,
    VM_WASM_OPCODE_BLOCK = 0x2,
    VM_WASM_OPCODE_LOOP = 0x3,
    VM_WASM_OPCODE_IF = 0x4,
    VM_WASM_OPCODE_ELSE = 0x5,
    VM_WASM_OPCODE_END = 0xB,
    VM_WASM_OPCODE_BR = 0xC,
    VM_WASM_OPCODE_BR_IF = 0xD,
    VM_WASM_OPCODE_BR_TABLE = 0xE,
    VM_WASM_OPCODE_RETURN = 0xF,

    // CALLS
    VM_WASM_OPCODE_CALL = 0x10,
    VM_WASM_OPCODE_CALL_INDIRECT = 0x11,

    // PARAMETRIC OPERATORS
    VM_WASM_OPCODE_DROP = 0x1A,
    VM_WASM_OPCODE_SELECT = 0x1B,

    // VARIBALE ACCESS
    VM_WASM_OPCODE_GET_LOCAL = 0x20,
    VM_WASM_OPCODE_SET_LOCAL = 0x21,
    VM_WASM_OPCODE_TEE_LOCAL = 0x22,
    VM_WASM_OPCODE_GET_GLOBAL = 0x23,
    VM_WASM_OPCODE_SET_GLOBAL = 0x24,

    // MEMORY-RELATED OPERATORS
    VM_WASM_OPCODE_I32_LOAD = 0x28,
    VM_WASM_OPCODE_I64_LOAD = 0x29,
    VM_WASM_OPCODE_F32_LOAD = 0x2A,
    VM_WASM_OPCODE_F64_LOAD = 0x2B,
    VM_WASM_OPCODE_I32_LOAD8_S = 0x2C,
    VM_WASM_OPCODE_I32_LOAD8_U = 0x2D,
    VM_WASM_OPCODE_I32_LOAD16_S = 0x2E,
    VM_WASM_OPCODE_I32_LOAD16_U = 0x2F,
    VM_WASM_OPCODE_I64_LOAD8_S = 0x30,
    VM_WASM_OPCODE_I64_LOAD8_U = 0x31,
    VM_WASM_OPCODE_I64_LOAD16_S = 0x32,
    VM_WASM_OPCODE_I64_LOAD16_U = 0x33,
    VM_WASM_OPCODE_I64_LOAD32_S = 0x34,
    VM_WASM_OPCODE_I64_LOAD32_U = 0x35,
    VM_WASM_OPCODE_I32_STORE = 0x36,
    VM_WASM_OPCODE_I64_STORE = 0x37,
    VM_WASM_OPCODE_F32_STORE = 0x38,
    VM_WASM_OPCODE_F64_STORE = 0x39,
    VM_WASM_OPCODE_I32_STORE8 = 0x3A,
    VM_WASM_OPCODE_I32_STORE16 = 0x3B,
    VM_WASM_OPCODE_I64_STORE8 = 0x3C,
    VM_WASM_OPCODE_I64_STORE16 = 0x3D,
    VM_WASM_OPCODE_I64_STORE32 = 0x3E,
    VM_WASM_OPCODE_MEMORY_SIZE = 0x3F,
    VM_WASM_OPCODE_MEMORY_GROW = 0x40,

    // CONSTANTS
    VM_WASM_OPCODE_I32_CONST = 0x41,
    VM_WASM_OPCODE_I64_CONST = 0x42,
    VM_WASM_OPCODE_F32_CONST = 0x43,
    VM_WASM_OPCODE_F64_CONST = 0x44,

    // COMPARISON OPERATORS
    VM_WASM_OPCODE_I32_EQZ = 0x45,
    VM_WASM_OPCODE_I32_EQ = 0x46,
    VM_WASM_OPCODE_I32_NE = 0x47,
    VM_WASM_OPCODE_I32_LT_S = 0x48,
    VM_WASM_OPCODE_I32_LT_U = 0x49,
    VM_WASM_OPCODE_I32_GT_S = 0x4A,
    VM_WASM_OPCODE_I32_GT_U = 0x4B,
    VM_WASM_OPCODE_I32_LE_S = 0x4C,
    VM_WASM_OPCODE_I32_LE_U = 0x4D,
    VM_WASM_OPCODE_I32_GE_S = 0x4E,
    VM_WASM_OPCODE_I32_GE_U = 0x4F,
    VM_WASM_OPCODE_I64_EQZ = 0x50,
    VM_WASM_OPCODE_I64_EQ = 0x51,
    VM_WASM_OPCODE_I64_NE = 0x52,
    VM_WASM_OPCODE_I64_LT_S = 0x53,
    VM_WASM_OPCODE_I64_LT_U = 0x54,
    VM_WASM_OPCODE_I64_GT_S = 0x55,
    VM_WASM_OPCODE_I64_GT_U = 0x56,
    VM_WASM_OPCODE_I64_LE_S = 0x57,
    VM_WASM_OPCODE_I64_LE_U = 0x58,
    VM_WASM_OPCODE_I64_GE_S = 0x59,
    VM_WASM_OPCODE_I64_GE_U = 0x5A,
    VM_WASM_OPCODE_F32_EQ = 0x5B,
    VM_WASM_OPCODE_F32_NE = 0x5C,
    VM_WASM_OPCODE_F32_LT = 0x5D,
    VM_WASM_OPCODE_F32_GT = 0x5E,
    VM_WASM_OPCODE_F32_LE = 0x5F,
    VM_WASM_OPCODE_F32_GE = 0x60,
    VM_WASM_OPCODE_F64_EQ = 0x61,
    VM_WASM_OPCODE_F64_NE = 0x62,
    VM_WASM_OPCODE_F64_LT = 0x63,
    VM_WASM_OPCODE_F64_GT = 0x64,
    VM_WASM_OPCODE_F64_LE = 0x65,
    VM_WASM_OPCODE_F64_GE = 0x66,

    // NUMERIC OPERATORS
    VM_WASM_OPCODE_I32_CLZ = 0x67,
    VM_WASM_OPCODE_I32_CTZ = 0x68,
    VM_WASM_OPCODE_I32_POPCNT = 0x69,
    VM_WASM_OPCODE_I32_ADD = 0x6A,
    VM_WASM_OPCODE_I32_SUB = 0x6B,
    VM_WASM_OPCODE_I32_MUL = 0x6C,
    VM_WASM_OPCODE_I32_DIV_S = 0x6D,
    VM_WASM_OPCODE_I32_DIV_U = 0x6E,
    VM_WASM_OPCODE_I32_REM_S = 0x6F,
    VM_WASM_OPCODE_I32_REM_U = 0x70,
    VM_WASM_OPCODE_I32_AND = 0x71,
    VM_WASM_OPCODE_I32_OR = 0x72,
    VM_WASM_OPCODE_I32_XOR = 0x73,
    VM_WASM_OPCODE_I32_SHL = 0x74,
    VM_WASM_OPCODE_I32_SHR_S = 0x75,
    VM_WASM_OPCODE_I32_SHR_U = 0x76,
    VM_WASM_OPCODE_I32_ROTL = 0x77,
    VM_WASM_OPCODE_I32_ROTR = 0x78,
    VM_WASM_OPCODE_I64_CLZ = 0x79,
    VM_WASM_OPCODE_I64_CTZ = 0x7A,
    VM_WASM_OPCODE_I64_POPCNT = 0x7B,
    VM_WASM_OPCODE_I64_ADD = 0x7C,
    VM_WASM_OPCODE_I64_SUB = 0x7D,
    VM_WASM_OPCODE_I64_MUL = 0x7E,
    VM_WASM_OPCODE_I64_DIV_S = 0x7F,
    VM_WASM_OPCODE_I64_DIV_U = 0x80,
    VM_WASM_OPCODE_I64_REM_S = 0x81,
    VM_WASM_OPCODE_I64_REM_U = 0x82,
    VM_WASM_OPCODE_I64_AND = 0x83,
    VM_WASM_OPCODE_I64_OR = 0x84,
    VM_WASM_OPCODE_I64_XOR = 0x85,
    VM_WASM_OPCODE_I64_SHL = 0x86,
    VM_WASM_OPCODE_I64_SHR_S = 0x87,
    VM_WASM_OPCODE_I64_SHR_U = 0x88,
    VM_WASM_OPCODE_I64_ROTL = 0x89,
    VM_WASM_OPCODE_I64_ROTR = 0x8A,
    VM_WASM_OPCODE_F32_ABS = 0x8B,
    VM_WASM_OPCODE_F32_NEG = 0x8C,
    VM_WASM_OPCODE_F32_CEIL = 0x8D,
    VM_WASM_OPCODE_F32_FLOOR = 0x8E,
    VM_WASM_OPCODE_F32_TRUNC = 0x8F,
    VM_WASM_OPCODE_F32_NEAREST = 0x90,
    VM_WASM_OPCODE_F32_SQRT = 0x91,
    VM_WASM_OPCODE_F32_ADD = 0x92,
    VM_WASM_OPCODE_F32_SUB = 0x93,
    VM_WASM_OPCODE_F32_MUL = 0x94,
    VM_WASM_OPCODE_F32_DIV = 0x95,
    VM_WASM_OPCODE_F32_MIN = 0x96,
    VM_WASM_OPCODE_F32_MAX = 0x97,
    VM_WASM_OPCODE_F32_COPYSIGN = 0x98,
    VM_WASM_OPCODE_F64_ABS = 0x99,
    VM_WASM_OPCODE_F64_NEG = 0x9A,
    VM_WASM_OPCODE_F64_CEIL = 0x9B,
    VM_WASM_OPCODE_F64_FLOOR = 0x9C,
    VM_WASM_OPCODE_F64_TRUNC = 0x9D,
    VM_WASM_OPCODE_F64_NEAREST = 0x9E,
    VM_WASM_OPCODE_F64_SQRT = 0x9F,
    VM_WASM_OPCODE_F64_ADD = 0xA0,
    VM_WASM_OPCODE_F64_SUB = 0xA1,
    VM_WASM_OPCODE_F64_MUL = 0xA2,
    VM_WASM_OPCODE_F64_DIV = 0xA3,
    VM_WASM_OPCODE_F64_MIN = 0xA4,
    VM_WASM_OPCODE_F64_MAX = 0xA5,
    VM_WASM_OPCODE_F64_COPYSIGN = 0xA6,

    // CONVERSIONS
    VM_WASM_OPCODE_I32_WRAP_I64 = 0xA7,
    VM_WASM_OPCODE_I32_TRUNC_S_F32 = 0xA8,
    VM_WASM_OPCODE_I32_TRUNC_U_F32 = 0xA9,
    VM_WASM_OPCODE_I32_TRUNC_S_F64 = 0xAA,
    VM_WASM_OPCODE_I32_TRUNC_U_F64 = 0xAB,
    VM_WASM_OPCODE_I64_EXTEND_S_I32 = 0xAC,
    VM_WASM_OPCODE_I64_EXTEND_U_I32 = 0xAD,
    VM_WASM_OPCODE_I64_TRUNC_S_F32 = 0xAE,
    VM_WASM_OPCODE_I64_TRUNC_U_F32 = 0xAF,
    VM_WASM_OPCODE_I64_TRUNC_S_F64 = 0xB0,
    VM_WASM_OPCODE_I64_TRUNC_U_F64 = 0xB1,
    VM_WASM_OPCODE_F32_CONVERT_S_I32 = 0xB2,
    VM_WASM_OPCODE_F32_CONVERT_U_I32 = 0xB3,
    VM_WASM_OPCODE_F32_CONVERT_S_I64 = 0xB4,
    VM_WASM_OPCODE_F32_CONVERT_U_I64 = 0xB5,
    VM_WASM_OPCODE_F32_DEMOTE_F64 = 0xB6,
    VM_WASM_OPCODE_F64_CONVERT_S_I32 = 0xB7,
    VM_WASM_OPCODE_F64_CONVERT_U_I32 = 0xB8,
    VM_WASM_OPCODE_F64_CONVERT_S_I64 = 0xB9,
    VM_WASM_OPCODE_F64_CONVERT_U_I64 = 0xBA,
    VM_WASM_OPCODE_F64_PROMOTE_F32 = 0xBB,

    // REINTERPRETATIONS
    VM_WASM_OPCODE_I32_REINTERPRET_F32 = 0xBC,
    VM_WASM_OPCODE_I64_REINTERPRET_F64 = 0xBD,
    VM_WASM_OPCODE_F32_REINTERPRET_I32 = 0xBE,
    VM_WASM_OPCODE_F64_REINTERPRET_I64 = 0xBF,

    // MEMORY OPCODES
    VM_WASM_256_OPCODE = 256,
    VM_WASM_OPCODE_MEMORY_INIT,
    VM_WASM_OPCODE_MEMORY_COPY,
    VM_WASM_OPCODE_MEMORY_FILL,
    VM_WASM_OPCODE_DATA_DROP,
    VM_WASM_OPCODE_TABLE_INIT,
    VM_WASM_OPCODE_ELEM_DROP,
    VM_WASM_OPCODE_TABLE_COPY,
    VM_WASM_MAX_OPCODE_NUM,
};

enum vm_wasm_memory_immediate_id_enum_t {
    VM_WASM_IMMEDIATE_NONE,
    VM_WASM_IMMEDIATE_BLOCK_TYPE,
    VM_WASM_IMMEDIATE_VARUINT1,
    VM_WASM_IMMEDIATE_VARUINT32,
    VM_WASM_IMMEDIATE_VARUINT64,
    VM_WASM_IMMEDIATE_VARINT32,
    VM_WASM_IMMEDIATE_VARINT64,
    VM_WASM_IMMEDIATE_UINT32,
    VM_WASM_IMMEDIATE_UINT64,
    VM_WASM_IMMEDIATE_BR_TABLE,
    VM_WASM_IMMEDIATE_CALL_INDIRECT,
    VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    VM_WASM_IMMEDIATE_DATA_INDEX,
};

struct vm_wasm_preamble_t;
typedef struct vm_wasm_preamble_t vm_wasm_preamble_t;

struct vm_wasm_section_header_t;
typedef struct vm_wasm_section_header_t vm_wasm_section_header_t;

struct vm_wasm_br_table_t;
typedef struct vm_wasm_br_table_t vm_wasm_br_table_t;

struct vm_wasm_call_indirect_t;
typedef struct vm_wasm_call_indirect_t vm_wasm_call_indirect_t;

struct vm_wasm_memory_immediate_t;
typedef struct vm_wasm_memory_immediate_t vm_wasm_memory_immediate_t;

struct vm_wasm_type_function_t;
typedef struct vm_wasm_type_function_t vm_wasm_type_function_t;
 
struct vm_wasm_type_table_t;
typedef struct vm_wasm_type_table_t vm_wasm_type_table_t;

struct vm_wasm_type_t;
typedef struct vm_wasm_type_t vm_wasm_type_t;
 
struct vm_wasm_type_global_t;
typedef struct vm_wasm_type_global_t vm_wasm_type_global_t;
 
struct vm_wasm_type_memory_t;
typedef struct vm_wasm_type_memory_t vm_wasm_type_memory_t;
 
struct vm_wasm_section_custom_t;
typedef struct vm_wasm_section_custom_t vm_wasm_section_custom_t;

struct vm_wasm_section_type_entry_t;
typedef struct vm_wasm_section_type_entry_t vm_wasm_section_type_entry_t;

struct vm_wasm_section_type_t;
typedef struct vm_wasm_section_type_t vm_wasm_section_type_t;

struct vm_wasm_section_export_entry_t;
typedef struct vm_wasm_section_export_entry_t vm_wasm_section_export_entry_t;

struct vm_wasm_section_export_t;
typedef struct vm_wasm_section_export_t vm_wasm_section_export_t;

struct vm_wasm_section_import_entry_t;
typedef struct vm_wasm_section_import_entry_t vm_wasm_section_import_entry_t;

struct vm_wasm_section_import_t;
typedef struct vm_wasm_section_import_t vm_wasm_section_import_t;

struct vm_wasm_section_function_t;
typedef struct vm_wasm_section_function_t vm_wasm_section_function_t;

struct vm_wasm_section_table_t;
typedef struct vm_wasm_section_table_t vm_wasm_section_table_t;

struct vm_wasm_section_memory_t;
typedef struct vm_wasm_section_memory_t vm_wasm_section_memory_t;

struct vm_wasm_section_global_entry_t;
typedef struct vm_wasm_section_global_entry_t vm_wasm_section_global_entry_t;

struct vm_wasm_section_global_t;
typedef struct vm_wasm_section_global_t vm_wasm_section_global_t;

struct vm_wasm_section_start_t;
typedef struct vm_wasm_section_start_t vm_wasm_section_start_t;

struct vm_wasm_section_element_entry_t;
typedef struct vm_wasm_section_element_entry_t vm_wasm_section_element_entry_t;

struct vm_wasm_section_element_t;
typedef struct vm_wasm_section_element_t vm_wasm_section_element_t;

struct vm_wasm_section_code_entry_local_t;
typedef struct vm_wasm_section_code_entry_local_t vm_wasm_section_code_entry_local_t;

struct vm_wasm_section_code_entry_t;
typedef struct vm_wasm_section_code_entry_t vm_wasm_section_code_entry_t;

struct vm_wasm_section_code_t;
typedef struct vm_wasm_section_code_t vm_wasm_section_code_t;

struct vm_wasm_section_data_entry_t;
typedef struct vm_wasm_section_data_entry_t vm_wasm_section_data_entry_t;

struct vm_wasm_section_data_t;
typedef struct vm_wasm_section_data_t vm_wasm_section_data_t;

struct vm_wasm_instr_immediate_t;
typedef struct vm_wasm_instr_immediate_t vm_wasm_instr_immediate_t;

struct vm_wasm_instr_t;
typedef struct vm_wasm_instr_t vm_wasm_instr_t;

struct vm_wasm_section_t;
typedef struct vm_wasm_section_t vm_wasm_section_t;

struct vm_wasm_module_t;
typedef struct vm_wasm_module_t vm_wasm_module_t;


struct vm_wasm_preamble_t {
    uint8_t magic[4];
    uint8_t version[4];
};

struct vm_wasm_section_header_t {
    vm_wasm_section_id_t id;
    uint64_t size;
    const char *custom_name;
};

struct vm_wasm_br_table_t {
    uint64_t num_targets;
    uint64_t *targets;
    uint64_t default_target;
};

struct vm_wasm_call_indirect_t {
    uint64_t index;
    uint8_t reserved;
};

struct vm_wasm_memory_immediate_t {
    uint64_t align;
    uint64_t offset;
};

struct vm_wasm_type_function_t {
    uint64_t data;
};

struct vm_wasm_type_global_t {
    vm_wasm_lang_type_t content_type;
    uint8_t is_mutable;
};

struct vm_wasm_type_memory_t {
    uint64_t flags;
    uint64_t initial;
    uint64_t maximum;
};

struct vm_wasm_type_table_t {
    vm_wasm_lang_type_t element_type;
    vm_wasm_type_memory_t limits;
};

struct vm_wasm_type_t {
    union {
        vm_wasm_type_function_t function;  
        vm_wasm_type_global_t global; 
        vm_wasm_type_memory_t memory; 
        vm_wasm_type_table_t table; 
    };
    vm_wasm_lang_type_t tag;
};

// enum {
//     VM_WASM_SECTION_TYPE_CUSTOM = 0, 
//     VM_WASM_SECTION_TYPE_TYPE = 1, 
//     VM_WASM_SECTION_TYPE_IMPORT = 2, 
//     VM_WASM_SECTION_TYPE_FUNCTION = 3, 
//     VM_WASM_SECTION_TYPE_TABLE = 4, 
//     VM_WASM_SECTION_TYPE_MEMORY = 5, 
//     VM_WASM_SECTION_TYPE_GLOBAL = 6, 
//     VM_WASM_SECTION_TYPE_EXPORT = 7, 
//     VM_WASM_SECTION_TYPE_START = 8, 
//     VM_WASM_SECTION_TYPE_ELEMENT = 9, 
//     VM_WASM_SECTION_TYPE_CODE = 10, 
//     VM_WASM_SECTION_TYPE_DAT = 11, 
// };

struct vm_wasm_section_custom_t {
    void *payload;
};

struct vm_wasm_section_type_entry_t {
    vm_wasm_lang_type_t type;
    uint64_t num_params;
    vm_wasm_lang_type_t *params;
    uint64_t num_returns;
    vm_wasm_lang_type_t return_type;
    bool has_return_type;
};

struct vm_wasm_section_type_t {
    uint64_t num_entries;
    vm_wasm_section_type_entry_t *entries;
};

struct vm_wasm_section_import_entry_t {
    const char *module_str;
    const char *field_str;
    vm_wasm_external_kind_t kind;
    union {
        vm_wasm_type_function_t func_type;
        vm_wasm_type_table_t table_type;
        vm_wasm_type_memory_t memory_type;
        vm_wasm_type_global_t global_type;
    };
};

struct vm_wasm_section_import_t {
    uint64_t num_entries;
    vm_wasm_section_import_entry_t *entries;
};

struct vm_wasm_section_function_t {
    uint64_t num_entries;
    uint64_t *entries;
};

struct vm_wasm_section_export_entry_t {
    const char *field_str;
    vm_wasm_external_kind_t kind;
    uint64_t index;
};

struct vm_wasm_section_export_t {
    uint64_t num_entries;
    vm_wasm_section_export_entry_t *entries;
};

struct vm_wasm_section_table_t {
    uint64_t num_entries;
    vm_wasm_type_table_t *entries;
};

struct vm_wasm_section_memory_t {
    uint64_t num_entries;
    vm_wasm_type_memory_t *entries;
};

struct vm_wasm_instr_immediate_t {
    union {
        uint8_t varuint1;
        uint32_t varuint32;
        uint64_t varuint64;
        int32_t varint32;
        int64_t varint64;
        uint32_t uint32;
        uint64_t uint64;
        vm_wasm_lang_type_t block_type;
        vm_wasm_br_table_t br_table;
        vm_wasm_call_indirect_t call_indirect;
        vm_wasm_memory_immediate_t memory_immediate;
        uint32_t data_index;
    };
    vm_wasm_immediate_id_t id;
};

struct vm_wasm_instr_t {
    vm_wasm_opcode_t opcode;
    vm_wasm_instr_immediate_t immediate;
};

struct vm_wasm_section_global_entry_t {
    vm_wasm_type_global_t global;
    vm_wasm_instr_t init_expr;
};

struct vm_wasm_section_global_t {
    uint64_t num_entries;
    vm_wasm_section_global_entry_t *entries;
};

struct vm_wasm_section_start_t {
    uint64_t index;
};

struct vm_wasm_section_element_entry_t {
    uint64_t index;
    vm_wasm_instr_t offset;
    uint64_t num_elems;
    uint64_t *elems;
};

struct vm_wasm_section_element_t {
    uint64_t num_entries;
    vm_wasm_section_element_entry_t *entries;
};

struct vm_wasm_section_code_entry_local_t {
    uint64_t count;
    vm_wasm_lang_type_t type;
};

struct vm_wasm_section_code_entry_t {
    uint64_t num_locals;
    vm_wasm_section_code_entry_local_t *locals;
    uint64_t num_instrs;
    vm_wasm_instr_t *instrs;
};

struct vm_wasm_section_code_t {
    uint64_t num_entries;
    vm_wasm_section_code_entry_t *entries;
};

struct vm_wasm_section_data_entry_t {
    uint64_t index;
    vm_wasm_instr_t offset;
    uint64_t size;
    uint8_t *data;
};

struct vm_wasm_section_data_t {
    uint64_t num_entries;
    vm_wasm_section_data_entry_t *entries;
};

struct vm_wasm_section_t {
    union {
        vm_wasm_section_custom_t custom_section;
        vm_wasm_section_type_t type_section;
        vm_wasm_section_import_t import_section;
        vm_wasm_section_function_t function_section;
        vm_wasm_section_table_t table_section;
        vm_wasm_section_memory_t memory_section;
        vm_wasm_section_global_t global_section;
        vm_wasm_section_export_t export_section;
        vm_wasm_section_start_t start_section;
        vm_wasm_section_element_t element_section;
        vm_wasm_section_code_t code_section;
        vm_wasm_section_data_t data_section;
    };
    vm_wasm_section_id_t id;
};

struct vm_wasm_module_t {
    vm_wasm_preamble_t preamble;
    uint64_t num_sections;
    vm_wasm_section_t *sections;
};

uint64_t vm_wasm_parse_uleb(FILE *in);
int64_t vm_wasm_parse_sleb(FILE *in);
uint8_t vm_wasm_parse_byte(FILE *in);
vm_wasm_preamble_t vm_wasm_parse_preamble(FILE *in);
vm_wasm_section_header_t vm_wasm_parse_section_header(FILE *in);
uint8_t vm_wasm_parse_varuint1(FILE *in);
int32_t vm_wasm_parse_varuint32(FILE *in);
int64_t vm_wasm_parse_varuint64(FILE *in);
uint32_t vm_wasm_parse_uint32(FILE *in);
uint64_t vm_wasm_parse_uint64(FILE *in);
vm_wasm_lang_type_t vm_wasm_parse_block_type(FILE *in);
vm_wasm_br_table_t vm_wasm_parse_br_table(FILE *in);
vm_wasm_call_indirect_t vm_wasm_parse_call_indirect(FILE *in);
vm_wasm_memory_immediate_t vm_wasm_parse_memory_immediate(FILE *in);
vm_wasm_type_function_t vm_wasm_parse_type_function(FILE *in);
vm_wasm_type_table_t vm_wasm_parse_type_table(FILE *in);
vm_wasm_type_global_t vm_wasm_parse_type_global(FILE *in);
vm_wasm_type_memory_t vm_wasm_parse_type_memory(FILE *in);
vm_wasm_type_t vm_wasm_parse_type(FILE *in, vm_wasm_lang_type_t tag);
vm_wasm_section_custom_t vm_wasm_parse_section_custom(FILE *in, vm_wasm_section_header_t header);
vm_wasm_section_type_t vm_wasm_parse_section_type(FILE *in);
vm_wasm_section_import_t vm_wasm_parse_section_import(FILE *in);
vm_wasm_section_function_t vm_wasm_parse_section_function(FILE *in);
vm_wasm_section_table_t vm_wasm_parse_section_table(FILE *in);
vm_wasm_section_memory_t vm_wasm_parse_section_memory(FILE *in);
vm_wasm_section_global_t vm_wasm_parse_section_global(FILE *in);
vm_wasm_section_export_t vm_wasm_parse_section_export(FILE *in);
vm_wasm_section_start_t vm_wasm_parse_section_start(FILE *in);
vm_wasm_section_element_t vm_wasm_parse_section_element(FILE *in);
vm_wasm_section_code_t vm_wasm_parse_section_code(FILE *in);
vm_wasm_section_data_t vm_wasm_parse_section_data(FILE *in);
vm_wasm_instr_immediate_t vm_wasm_parse_instr_immediate(FILE *in, vm_wasm_immediate_id_t id);
vm_wasm_instr_t vm_wasm_parse_init_expr(FILE *in);
vm_wasm_instr_t vm_wasm_parse_instr(FILE *in);
vm_wasm_section_t vm_wasm_parse_section(FILE *in, vm_wasm_section_header_t id);
vm_wasm_module_t vm_wasm_parse_module(FILE *in);

#endif
