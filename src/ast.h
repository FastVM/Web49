
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
    WEB49_OPCODE_UNREACHABLE,
    WEB49_OPCODE_NOP,
    WEB49_OPCODE_BLOCK,
    WEB49_OPCODE_LOOP,
    WEB49_OPCODE_IF,
    WEB49_OPCODE_THEN,
    WEB49_OPCODE_ELSE,
    WEB49_OPCODE_END,
    WEB49_OPCODE_BR,
    WEB49_OPCODE_BR_IF,
    WEB49_OPCODE_BR_TABLE,
    WEB49_OPCODE_RETURN,

    // CALLS
    WEB49_OPCODE_CALL,
    WEB49_OPCODE_CALL_INDIRECT,

    // PARAMETRIC OPERATORS
    WEB49_OPCODE_DROP,
    WEB49_OPCODE_SELECT,

    // VARIBALE ACCESS
    WEB49_OPCODE_GET_LOCAL,
    WEB49_OPCODE_SET_LOCAL,
    WEB49_OPCODE_TEE_LOCAL,
    WEB49_OPCODE_GET_GLOBAL,
    WEB49_OPCODE_SET_GLOBAL,

    // MEMORY-RELATED OPERATORS
    WEB49_OPCODE_I32_LOAD,
    WEB49_OPCODE_I64_LOAD,
    WEB49_OPCODE_F32_LOAD,
    WEB49_OPCODE_F64_LOAD,
    WEB49_OPCODE_I32_LOAD8_S,
    WEB49_OPCODE_I32_LOAD8_U,
    WEB49_OPCODE_I32_LOAD16_S,
    WEB49_OPCODE_I32_LOAD16_U,
    WEB49_OPCODE_I64_LOAD8_S,
    WEB49_OPCODE_I64_LOAD8_U,
    WEB49_OPCODE_I64_LOAD16_S,
    WEB49_OPCODE_I64_LOAD16_U,
    WEB49_OPCODE_I64_LOAD32_S,
    WEB49_OPCODE_I64_LOAD32_U,
    WEB49_OPCODE_I32_STORE,
    WEB49_OPCODE_I64_STORE,
    WEB49_OPCODE_F32_STORE,
    WEB49_OPCODE_F64_STORE,
    WEB49_OPCODE_I32_STORE8,
    WEB49_OPCODE_I32_STORE16,
    WEB49_OPCODE_I64_STORE8,
    WEB49_OPCODE_I64_STORE16,
    WEB49_OPCODE_I64_STORE32,
    WEB49_OPCODE_MEMORY_SIZE,
    WEB49_OPCODE_MEMORY_GROW,

    // CONSTANTS
    WEB49_OPCODE_I32_CONST,
    WEB49_OPCODE_I64_CONST,
    WEB49_OPCODE_F32_CONST,
    WEB49_OPCODE_F64_CONST,

    // COMPARISON OPERATORS
    WEB49_OPCODE_I32_EQZ,
    WEB49_OPCODE_I32_EQ,
    WEB49_OPCODE_I32_NE,
    WEB49_OPCODE_I32_LT_S,
    WEB49_OPCODE_I32_LT_U,
    WEB49_OPCODE_I32_GT_S,
    WEB49_OPCODE_I32_GT_U,
    WEB49_OPCODE_I32_LE_S,
    WEB49_OPCODE_I32_LE_U,
    WEB49_OPCODE_I32_GE_S,
    WEB49_OPCODE_I32_GE_U,
    WEB49_OPCODE_I64_EQZ,
    WEB49_OPCODE_I64_EQ,
    WEB49_OPCODE_I64_NE,
    WEB49_OPCODE_I64_LT_S,
    WEB49_OPCODE_I64_LT_U,
    WEB49_OPCODE_I64_GT_S,
    WEB49_OPCODE_I64_GT_U,
    WEB49_OPCODE_I64_LE_S,
    WEB49_OPCODE_I64_LE_U,
    WEB49_OPCODE_I64_GE_S,
    WEB49_OPCODE_I64_GE_U,
    WEB49_OPCODE_F32_EQ,
    WEB49_OPCODE_F32_NE,
    WEB49_OPCODE_F32_LT,
    WEB49_OPCODE_F32_GT,
    WEB49_OPCODE_F32_LE,
    WEB49_OPCODE_F32_GE,
    WEB49_OPCODE_F64_EQ,
    WEB49_OPCODE_F64_NE,
    WEB49_OPCODE_F64_LT,
    WEB49_OPCODE_F64_GT,
    WEB49_OPCODE_F64_LE,
    WEB49_OPCODE_F64_GE,

    // NUMERIC OPERATORS
    WEB49_OPCODE_I32_CLZ,
    WEB49_OPCODE_I32_CTZ,
    WEB49_OPCODE_I32_POPCNT,
    WEB49_OPCODE_I32_ADD,
    WEB49_OPCODE_I32_SUB,
    WEB49_OPCODE_I32_MUL,
    WEB49_OPCODE_I32_DIV_S,
    WEB49_OPCODE_I32_DIV_U,
    WEB49_OPCODE_I32_REM_S,
    WEB49_OPCODE_I32_REM_U,
    WEB49_OPCODE_I32_AND,
    WEB49_OPCODE_I32_OR,
    WEB49_OPCODE_I32_XOR,
    WEB49_OPCODE_I32_SHL,
    WEB49_OPCODE_I32_SHR_S,
    WEB49_OPCODE_I32_SHR_U,
    WEB49_OPCODE_I32_ROTL,
    WEB49_OPCODE_I32_ROTR,
    WEB49_OPCODE_I64_CLZ,
    WEB49_OPCODE_I64_CTZ,
    WEB49_OPCODE_I64_POPCNT,
    WEB49_OPCODE_I64_ADD,
    WEB49_OPCODE_I64_SUB,
    WEB49_OPCODE_I64_MUL,
    WEB49_OPCODE_I64_DIV_S,
    WEB49_OPCODE_I64_DIV_U,
    WEB49_OPCODE_I64_REM_S,
    WEB49_OPCODE_I64_REM_U,
    WEB49_OPCODE_I64_AND,
    WEB49_OPCODE_I64_OR,
    WEB49_OPCODE_I64_XOR,
    WEB49_OPCODE_I64_SHL,
    WEB49_OPCODE_I64_SHR_S,
    WEB49_OPCODE_I64_SHR_U,
    WEB49_OPCODE_I64_ROTL,
    WEB49_OPCODE_I64_ROTR,
    WEB49_OPCODE_F32_ABS,
    WEB49_OPCODE_F32_NEG,
    WEB49_OPCODE_F32_CEIL,
    WEB49_OPCODE_F32_FLOOR,
    WEB49_OPCODE_F32_TRUNC,
    WEB49_OPCODE_F32_NEAREST,
    WEB49_OPCODE_F32_SQRT,
    WEB49_OPCODE_F32_ADD,
    WEB49_OPCODE_F32_SUB,
    WEB49_OPCODE_F32_MUL,
    WEB49_OPCODE_F32_DIV,
    WEB49_OPCODE_F32_MIN,
    WEB49_OPCODE_F32_MAX,
    WEB49_OPCODE_F32_COPYSIGN,
    WEB49_OPCODE_F64_ABS,
    WEB49_OPCODE_F64_NEG,
    WEB49_OPCODE_F64_CEIL,
    WEB49_OPCODE_F64_FLOOR,
    WEB49_OPCODE_F64_TRUNC,
    WEB49_OPCODE_F64_NEAREST,
    WEB49_OPCODE_F64_SQRT,
    WEB49_OPCODE_F64_ADD,
    WEB49_OPCODE_F64_SUB,
    WEB49_OPCODE_F64_MUL,
    WEB49_OPCODE_F64_DIV,
    WEB49_OPCODE_F64_MIN,
    WEB49_OPCODE_F64_MAX,
    WEB49_OPCODE_F64_COPYSIGN,

    // CONVERSIONS
    WEB49_OPCODE_I32_WRAP_I64,
    WEB49_OPCODE_I32_TRUNC_S_F32,
    WEB49_OPCODE_I32_TRUNC_U_F32,
    WEB49_OPCODE_I32_TRUNC_S_F64,
    WEB49_OPCODE_I32_TRUNC_U_F64,
    WEB49_OPCODE_I64_EXTEND_S_I32,
    WEB49_OPCODE_I64_EXTEND_U_I32,
    WEB49_OPCODE_I64_TRUNC_S_F32,
    WEB49_OPCODE_I64_TRUNC_U_F32,
    WEB49_OPCODE_I64_TRUNC_S_F64,
    WEB49_OPCODE_I64_TRUNC_U_F64,
    WEB49_OPCODE_F32_CONVERT_S_I32,
    WEB49_OPCODE_F32_CONVERT_U_I32,
    WEB49_OPCODE_F32_CONVERT_S_I64,
    WEB49_OPCODE_F32_CONVERT_U_I64,
    WEB49_OPCODE_F32_DEMOTE_F64,
    WEB49_OPCODE_F64_CONVERT_S_I32,
    WEB49_OPCODE_F64_CONVERT_U_I32,
    WEB49_OPCODE_F64_CONVERT_S_I64,
    WEB49_OPCODE_F64_CONVERT_U_I64,
    WEB49_OPCODE_F64_PROMOTE_F32,

    // REINTERPRETATIONS
    WEB49_OPCODE_I32_REINTERPRET_F32,
    WEB49_OPCODE_I64_REINTERPRET_F64,
    WEB49_OPCODE_F32_REINTERPRET_I32,
    WEB49_OPCODE_F64_REINTERPRET_I64,
    WEB49_OPCODE_I32_EXTEND8_S,
    WEB49_OPCODE_I32_EXTEND16_S,
    WEB49_OPCODE_I64_EXTEND8_S,
    WEB49_OPCODE_I64_EXTEND16_S,
    WEB49_OPCODE_I64_EXTEND32_S,
    WEB49_OPCODE_I32_TRUNC_SAT_F32_S,
    WEB49_OPCODE_I32_TRUNC_SAT_F32_U,
    WEB49_OPCODE_I32_TRUNC_SAT_F64_S,
    WEB49_OPCODE_I32_TRUNC_SAT_F64_U,
    WEB49_OPCODE_I64_TRUNC_SAT_F32_S,
    WEB49_OPCODE_I64_TRUNC_SAT_F32_U,
    WEB49_OPCODE_I64_TRUNC_SAT_F64_S,
    WEB49_OPCODE_I64_TRUNC_SAT_F64_U,
    WEB49_OPCODE_MEMORY_INIT,
    WEB49_OPCODE_MEMORY_COPY,
    WEB49_OPCODE_MEMORY_FILL,
    WEB49_OPCODE_DATA_DROP,
    WEB49_OPCODE_TABLE_INIT,
    WEB49_OPCODE_ELEM_DROP,
    WEB49_OPCODE_TABLE_COPY,
    WEB49_OPCODE_TABLE_GROW,
    WEB49_OPCODE_TABLE_SIZE,
    WEB49_OPCODE_TABLE_FILL,

    // for the interpreter
    WEB49_OPCODE_BEGIN0,
    WEB49_OPCODE_NOP1,
    WEB49_OPCODE_YIELD_PUSH,
    WEB49_OPCODE_YIELD_POP,
    WEB49_OPCODE_RETURN0,
    WEB49_OPCODE_RETURN1,
    WEB49_OPCODE_CALL0,
    WEB49_OPCODE_CALL1,

    // MEMORY OPCODES
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

struct web49_block_type_t;
typedef struct web49_block_type_t web49_block_type_t;

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
    uint32_t size;
    bool size_known;
};

struct web49_br_table_t {
    uint32_t num_targets;
    uint32_t *targets;
    uint32_t default_target;
};

struct web49_call_indirect_t {
    uint32_t index;
    uint8_t reserved;
};

struct web49_block_type_t {
    union {
        web49_lang_type_t type_value;
        uint32_t type_index;
    };
    bool is_type_index;
};

struct web49_memory_immediate_t {
    uint32_t align;
    uint32_t offset;
};

struct web49_type_function_t {
    uint32_t data;
};

struct web49_type_global_t {
    web49_lang_type_t content_type;
    uint8_t is_mutable;
};

struct web49_type_memory_t {
    uint32_t initial;
    uint32_t maximum;
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
    const char *name;
    void *payload;
};

struct web49_section_type_entry_t {
    web49_lang_type_t type;
    uint32_t num_params;
    web49_lang_type_t *params;
    uint32_t num_returns;
    web49_lang_type_t *return_types;
};

struct web49_section_type_t {
    uint32_t num_entries;
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
    uint32_t num_func_imports;
    uint32_t num_entries;
    web49_section_import_entry_t *entries;
};

struct web49_section_function_t {
    uint32_t num_entries;
    uint32_t *entries;
};

struct web49_section_export_entry_t {
    const char *field_str;
    web49_external_kind_t kind;
    uint32_t index;
};

struct web49_section_export_t {
    uint32_t num_entries;
    web49_section_export_entry_t *entries;
};

struct web49_section_table_t {
    uint32_t num_entries;
    web49_type_table_t *entries;
};

struct web49_section_memory_t {
    uint32_t num_entries;
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
        web49_block_type_t block_type;
        web49_br_table_t br_table;
        web49_call_indirect_t call_indirect;
        web49_memory_immediate_t memory_immediate;
        uint32_t data_index;
    };
    web49_immediate_id_t id;
};

struct web49_instr_t {
    web49_instr_immediate_t immediate;
    web49_opcode_t opcode;
    uint32_t nargs;
    web49_instr_t *args;
};

struct web49_section_global_entry_t {
    web49_type_global_t global;
    web49_instr_t init_expr;
};

struct web49_section_global_t {
    uint32_t num_entries;
    web49_section_global_entry_t *entries;
};

struct web49_section_start_t {
    uint32_t index;
};

struct web49_section_element_entry_t {
    uint32_t index;
    web49_instr_t offset;
    uint32_t num_elems;
    uint32_t *elems;
};

struct web49_section_element_t {
    uint32_t num_entries;
    web49_section_element_entry_t *entries;
};

struct web49_section_code_entry_local_t {
    uint32_t count;
    web49_lang_type_t type;
};

struct web49_section_code_entry_t {
    uint32_t num_locals;
    web49_section_code_entry_local_t *locals;
    uint32_t num_instrs;
    web49_instr_t *instrs;
};

struct web49_section_code_t {
    uint32_t num_entries;
    web49_section_code_entry_t *entries;
};

struct web49_section_data_entry_t {
    web49_instr_t offset;
    uint32_t size;
    uint8_t *data;
};

struct web49_section_data_t {
    uint32_t num_entries;
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
    uint32_t num_sections;
    web49_section_t *sections;
};

void web49_debug_print_instr(FILE *file, web49_instr_t instr);
void web49_free_module(web49_module_t mod);
void web49_free_instr(web49_instr_t instr);
web49_section_t web49_module_get_section(web49_module_t mod, web49_section_id_t id);
uint32_t web49_module_num_func_imports(web49_module_t mod);

#define web49_preamble_init ((web49_preamble_t){{0x00, 0x61, 0x73, 0x6D}, {0x01, 0x00, 0x00, 0x00}})
#define web49_block_type_value(num_) ((web49_block_type_t){.type_value = (num_), .is_type_index = false})

#endif
