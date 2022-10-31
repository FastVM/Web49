#include "read_wat.h"

#include <stdio.h>

static size_t web49_wat_instr_mem_size[WEB49_MAX_OPCODE_NUM] = {
    [WEB49_OPCODE_I32_LOAD] = 4,
    [WEB49_OPCODE_I64_LOAD] = 8,
    [WEB49_OPCODE_F32_LOAD] = 4,
    [WEB49_OPCODE_F64_LOAD] = 8,
    [WEB49_OPCODE_I32_LOAD8_S] = 1,
    [WEB49_OPCODE_I32_LOAD8_U] = 1,
    [WEB49_OPCODE_I32_LOAD16_S] = 2,
    [WEB49_OPCODE_I32_LOAD16_U] = 2,
    [WEB49_OPCODE_I64_LOAD8_S] = 1,
    [WEB49_OPCODE_I64_LOAD8_U] = 1,
    [WEB49_OPCODE_I64_LOAD16_S] = 2,
    [WEB49_OPCODE_I64_LOAD16_U] = 2,
    [WEB49_OPCODE_I64_LOAD32_S] = 4,
    [WEB49_OPCODE_I64_LOAD32_U] = 4,
    [WEB49_OPCODE_I32_STORE] = 4,
    [WEB49_OPCODE_I64_STORE] = 8,
    [WEB49_OPCODE_F32_STORE] = 4,
    [WEB49_OPCODE_F64_STORE] = 8,
    [WEB49_OPCODE_I32_STORE8] = 1,
    [WEB49_OPCODE_I32_STORE16] = 2,
    [WEB49_OPCODE_I64_STORE8] = 1,
    [WEB49_OPCODE_I64_STORE16] = 2,
    [WEB49_OPCODE_I64_STORE32] = 4,
};

static const web49_immediate_id_t web49_immediates[WEB49_MAX_OPCODE_NUM] = {
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

enum {
    WEB49_READWAT_EXPR_TAG_INIT,
    WEB49_READWAT_EXPR_TAG_FUN,
    WEB49_READWAT_EXPR_TAG_STR,
};

struct web49_readwat_table_t;
typedef struct web49_readwat_table_t web49_readwat_table_t;

struct web49_readwat_state_t;
typedef struct web49_readwat_state_t web49_readwat_state_t;

struct web49_readwat_expr_t;
typedef struct web49_readwat_expr_t web49_readwat_expr_t;

static uint64_t web49_readwat_expr_to_u64(const char *expr);
static int64_t web49_readwat_expr_to_i64(const char *expr);
static void web49_readwat_state_type_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_import_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_func_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_table_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_global_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_export_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_elem_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);
static void web49_readwat_state_data_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr);

struct web49_readwat_table_t {
    uint64_t len;
    const char **key;
    uint64_t *value;
    uint64_t alloc;
};

struct web49_readwat_state_t {
    uint64_t num_func_imports;

    web49_readwat_table_t func_table;
    web49_readwat_table_t type_table;
    web49_readwat_table_t import_table;
    web49_readwat_table_t export_table;
    web49_readwat_table_t data_table;
    web49_readwat_table_t global_table;

    uint64_t alloc_type;
    uint64_t alloc_import;
    uint64_t alloc_function;
    uint64_t alloc_table;
    uint64_t alloc_global;
    uint64_t alloc_memory;
    uint64_t alloc_export;
    uint64_t alloc_element;
    uint64_t alloc_code;
    uint64_t alloc_data;

    web49_section_type_t stype;
    web49_section_import_t simport;
    web49_section_function_t sfunction;
    web49_section_table_t stable;
    web49_section_global_t sglobal;
    web49_section_memory_t smemory;
    web49_section_export_t sexport;
    web49_section_element_t selement;
    web49_section_code_t scode;
    web49_section_data_t sdata;
};

struct web49_readwat_expr_t {
    uint64_t start;
    uint64_t end;
    union {
        struct {
            const char *fun_fun;
            uint64_t fun_nargs;
            web49_readwat_expr_t *fun_args;
        };
        const char *str;
    };
    uint8_t tag;
};

web49_opcode_t web49_readwat_name_to_opcode(const char *name) {
    if (!strcmp(name, "unreachable")) {
        return WEB49_OPCODE_UNREACHABLE;
    }
    if (!strcmp(name, "nop")) {
        return WEB49_OPCODE_NOP;
    }
    if (!strcmp(name, "block")) {
        return WEB49_OPCODE_BLOCK;
    }
    if (!strcmp(name, "loop")) {
        return WEB49_OPCODE_LOOP;
    }
    if (!strcmp(name, "if")) {
        return WEB49_OPCODE_IF;
    }
    if (!strcmp(name, "else")) {
        return WEB49_OPCODE_ELSE;
    }
    if (!strcmp(name, "end")) {
        return WEB49_OPCODE_END;
    }
    if (!strcmp(name, "br")) {
        return WEB49_OPCODE_BR;
    }
    if (!strcmp(name, "br_if")) {
        return WEB49_OPCODE_BR_IF;
    }
    if (!strcmp(name, "br_table")) {
        return WEB49_OPCODE_BR_TABLE;
    }
    if (!strcmp(name, "return")) {
        return WEB49_OPCODE_RETURN;
    }
    if (!strcmp(name, "call")) {
        return WEB49_OPCODE_CALL;
    }
    if (!strcmp(name, "call_indirect")) {
        return WEB49_OPCODE_CALL_INDIRECT;
    }
    if (!strcmp(name, "drop")) {
        return WEB49_OPCODE_DROP;
    }
    if (!strcmp(name, "select")) {
        return WEB49_OPCODE_SELECT;
    }
    if (!strcmp(name, "local.get")) {
        return WEB49_OPCODE_GET_LOCAL;
    }
    if (!strcmp(name, "local.set")) {
        return WEB49_OPCODE_SET_LOCAL;
    }
    if (!strcmp(name, "local.tee")) {
        return WEB49_OPCODE_TEE_LOCAL;
    }
    if (!strcmp(name, "global.get")) {
        return WEB49_OPCODE_GET_GLOBAL;
    }
    if (!strcmp(name, "global.set")) {
        return WEB49_OPCODE_SET_GLOBAL;
    }
    if (!strcmp(name, "i32.load")) {
        return WEB49_OPCODE_I32_LOAD;
    }
    if (!strcmp(name, "i64.load")) {
        return WEB49_OPCODE_I64_LOAD;
    }
    if (!strcmp(name, "f32.load")) {
        return WEB49_OPCODE_F32_LOAD;
    }
    if (!strcmp(name, "f64.load")) {
        return WEB49_OPCODE_F64_LOAD;
    }
    if (!strcmp(name, "i32.load8_s")) {
        return WEB49_OPCODE_I32_LOAD8_S;
    }
    if (!strcmp(name, "i32.load8_u")) {
        return WEB49_OPCODE_I32_LOAD8_U;
    }
    if (!strcmp(name, "i32.load16_s")) {
        return WEB49_OPCODE_I32_LOAD16_S;
    }
    if (!strcmp(name, "i32.load16_u")) {
        return WEB49_OPCODE_I32_LOAD16_U;
    }
    if (!strcmp(name, "i64.load8_s")) {
        return WEB49_OPCODE_I64_LOAD8_S;
    }
    if (!strcmp(name, "i64.load8_u")) {
        return WEB49_OPCODE_I64_LOAD8_U;
    }
    if (!strcmp(name, "i64.load16_s")) {
        return WEB49_OPCODE_I64_LOAD16_S;
    }
    if (!strcmp(name, "i64.load16_u")) {
        return WEB49_OPCODE_I64_LOAD16_U;
    }
    if (!strcmp(name, "i64.load32_s")) {
        return WEB49_OPCODE_I64_LOAD32_S;
    }
    if (!strcmp(name, "i64.load32_u")) {
        return WEB49_OPCODE_I64_LOAD32_U;
    }
    if (!strcmp(name, "i32.store")) {
        return WEB49_OPCODE_I32_STORE;
    }
    if (!strcmp(name, "i64.store")) {
        return WEB49_OPCODE_I64_STORE;
    }
    if (!strcmp(name, "f32.store")) {
        return WEB49_OPCODE_F32_STORE;
    }
    if (!strcmp(name, "f64.store")) {
        return WEB49_OPCODE_F64_STORE;
    }
    if (!strcmp(name, "i32.store8")) {
        return WEB49_OPCODE_I32_STORE8;
    }
    if (!strcmp(name, "i32.store16")) {
        return WEB49_OPCODE_I32_STORE16;
    }
    if (!strcmp(name, "i64.store8")) {
        return WEB49_OPCODE_I64_STORE8;
    }
    if (!strcmp(name, "i64.store16")) {
        return WEB49_OPCODE_I64_STORE16;
    }
    if (!strcmp(name, "i64.store32")) {
        return WEB49_OPCODE_I64_STORE32;
    }
    if (!strcmp(name, "memory.size")) {
        return WEB49_OPCODE_MEMORY_SIZE;
    }
    if (!strcmp(name, "memory.grow")) {
        return WEB49_OPCODE_MEMORY_GROW;
    }
    if (!strcmp(name, "i32.const")) {
        return WEB49_OPCODE_I32_CONST;
    }
    if (!strcmp(name, "i64.const")) {
        return WEB49_OPCODE_I64_CONST;
    }
    if (!strcmp(name, "f32.const")) {
        return WEB49_OPCODE_F32_CONST;
    }
    if (!strcmp(name, "f64.const")) {
        return WEB49_OPCODE_F64_CONST;
    }
    if (!strcmp(name, "i32.eqz")) {
        return WEB49_OPCODE_I32_EQZ;
    }
    if (!strcmp(name, "i32.eq")) {
        return WEB49_OPCODE_I32_EQ;
    }
    if (!strcmp(name, "i32.ne")) {
        return WEB49_OPCODE_I32_NE;
    }
    if (!strcmp(name, "i32.lt_s")) {
        return WEB49_OPCODE_I32_LT_S;
    }
    if (!strcmp(name, "i32.lt_u")) {
        return WEB49_OPCODE_I32_LT_U;
    }
    if (!strcmp(name, "i32.gt_s")) {
        return WEB49_OPCODE_I32_GT_S;
    }
    if (!strcmp(name, "i32.gt_u")) {
        return WEB49_OPCODE_I32_GT_U;
    }
    if (!strcmp(name, "i32.le_s")) {
        return WEB49_OPCODE_I32_LE_S;
    }
    if (!strcmp(name, "i32.le_u")) {
        return WEB49_OPCODE_I32_LE_U;
    }
    if (!strcmp(name, "i32.ge_s")) {
        return WEB49_OPCODE_I32_GE_S;
    }
    if (!strcmp(name, "i32.ge_u")) {
        return WEB49_OPCODE_I32_GE_U;
    }
    if (!strcmp(name, "i64.eqz")) {
        return WEB49_OPCODE_I64_EQZ;
    }
    if (!strcmp(name, "i64.eq")) {
        return WEB49_OPCODE_I64_EQ;
    }
    if (!strcmp(name, "i64.ne")) {
        return WEB49_OPCODE_I64_NE;
    }
    if (!strcmp(name, "i64.lt_s")) {
        return WEB49_OPCODE_I64_LT_S;
    }
    if (!strcmp(name, "i64.lt_u")) {
        return WEB49_OPCODE_I64_LT_U;
    }
    if (!strcmp(name, "i64.gt_s")) {
        return WEB49_OPCODE_I64_GT_S;
    }
    if (!strcmp(name, "i64.gt_u")) {
        return WEB49_OPCODE_I64_GT_U;
    }
    if (!strcmp(name, "i64.le_s")) {
        return WEB49_OPCODE_I64_LE_S;
    }
    if (!strcmp(name, "i64.le_u")) {
        return WEB49_OPCODE_I64_LE_U;
    }
    if (!strcmp(name, "i64.ge_s")) {
        return WEB49_OPCODE_I64_GE_S;
    }
    if (!strcmp(name, "i64.ge_u")) {
        return WEB49_OPCODE_I64_GE_U;
    }
    if (!strcmp(name, "f32.eq")) {
        return WEB49_OPCODE_F32_EQ;
    }
    if (!strcmp(name, "f32.ne")) {
        return WEB49_OPCODE_F32_NE;
    }
    if (!strcmp(name, "f32.lt")) {
        return WEB49_OPCODE_F32_LT;
    }
    if (!strcmp(name, "f32.gt")) {
        return WEB49_OPCODE_F32_GT;
    }
    if (!strcmp(name, "f32.le")) {
        return WEB49_OPCODE_F32_LE;
    }
    if (!strcmp(name, "f32.ge")) {
        return WEB49_OPCODE_F32_GE;
    }
    if (!strcmp(name, "f64.eq")) {
        return WEB49_OPCODE_F64_EQ;
    }
    if (!strcmp(name, "f64.ne")) {
        return WEB49_OPCODE_F64_NE;
    }
    if (!strcmp(name, "f64.lt")) {
        return WEB49_OPCODE_F64_LT;
    }
    if (!strcmp(name, "f64.gt")) {
        return WEB49_OPCODE_F64_GT;
    }
    if (!strcmp(name, "f64.le")) {
        return WEB49_OPCODE_F64_LE;
    }
    if (!strcmp(name, "f64.ge")) {
        return WEB49_OPCODE_F64_GE;
    }
    if (!strcmp(name, "i32.clz")) {
        return WEB49_OPCODE_I32_CLZ;
    }
    if (!strcmp(name, "i32.ctz")) {
        return WEB49_OPCODE_I32_CTZ;
    }
    if (!strcmp(name, "i32.popcnt")) {
        return WEB49_OPCODE_I32_POPCNT;
    }
    if (!strcmp(name, "i32.add")) {
        return WEB49_OPCODE_I32_ADD;
    }
    if (!strcmp(name, "i32.sub")) {
        return WEB49_OPCODE_I32_SUB;
    }
    if (!strcmp(name, "i32.mul")) {
        return WEB49_OPCODE_I32_MUL;
    }
    if (!strcmp(name, "i32.div_s")) {
        return WEB49_OPCODE_I32_DIV_S;
    }
    if (!strcmp(name, "i32.div_u")) {
        return WEB49_OPCODE_I32_DIV_U;
    }
    if (!strcmp(name, "i32.rem_s")) {
        return WEB49_OPCODE_I32_REM_S;
    }
    if (!strcmp(name, "i32.rem_u")) {
        return WEB49_OPCODE_I32_REM_U;
    }
    if (!strcmp(name, "i32.and")) {
        return WEB49_OPCODE_I32_AND;
    }
    if (!strcmp(name, "i32.or")) {
        return WEB49_OPCODE_I32_OR;
    }
    if (!strcmp(name, "i32.xor")) {
        return WEB49_OPCODE_I32_XOR;
    }
    if (!strcmp(name, "i32.shl")) {
        return WEB49_OPCODE_I32_SHL;
    }
    if (!strcmp(name, "i32.shr_s")) {
        return WEB49_OPCODE_I32_SHR_S;
    }
    if (!strcmp(name, "i32.shr_u")) {
        return WEB49_OPCODE_I32_SHR_U;
    }
    if (!strcmp(name, "i32.rotl")) {
        return WEB49_OPCODE_I32_ROTL;
    }
    if (!strcmp(name, "i32.rotr")) {
        return WEB49_OPCODE_I32_ROTR;
    }
    if (!strcmp(name, "i64.clz")) {
        return WEB49_OPCODE_I64_CLZ;
    }
    if (!strcmp(name, "i64.ctz")) {
        return WEB49_OPCODE_I64_CTZ;
    }
    if (!strcmp(name, "i64.popcnt")) {
        return WEB49_OPCODE_I64_POPCNT;
    }
    if (!strcmp(name, "i64.add")) {
        return WEB49_OPCODE_I64_ADD;
    }
    if (!strcmp(name, "i64.sub")) {
        return WEB49_OPCODE_I64_SUB;
    }
    if (!strcmp(name, "i64.mul")) {
        return WEB49_OPCODE_I64_MUL;
    }
    if (!strcmp(name, "i64.div_s")) {
        return WEB49_OPCODE_I64_DIV_S;
    }
    if (!strcmp(name, "i64.div_u")) {
        return WEB49_OPCODE_I64_DIV_U;
    }
    if (!strcmp(name, "i64.rem_s")) {
        return WEB49_OPCODE_I64_REM_S;
    }
    if (!strcmp(name, "i64.rem_u")) {
        return WEB49_OPCODE_I64_REM_U;
    }
    if (!strcmp(name, "i64.and")) {
        return WEB49_OPCODE_I64_AND;
    }
    if (!strcmp(name, "i64.or")) {
        return WEB49_OPCODE_I64_OR;
    }
    if (!strcmp(name, "i64.xor")) {
        return WEB49_OPCODE_I64_XOR;
    }
    if (!strcmp(name, "i64.shl")) {
        return WEB49_OPCODE_I64_SHL;
    }
    if (!strcmp(name, "i64.shr_s")) {
        return WEB49_OPCODE_I64_SHR_S;
    }
    if (!strcmp(name, "i64.shr_u")) {
        return WEB49_OPCODE_I64_SHR_U;
    }
    if (!strcmp(name, "i64.rotl")) {
        return WEB49_OPCODE_I64_ROTL;
    }
    if (!strcmp(name, "i64.rotr")) {
        return WEB49_OPCODE_I64_ROTR;
    }
    if (!strcmp(name, "f32.abs")) {
        return WEB49_OPCODE_F32_ABS;
    }
    if (!strcmp(name, "f32.neg")) {
        return WEB49_OPCODE_F32_NEG;
    }
    if (!strcmp(name, "f32.ceil")) {
        return WEB49_OPCODE_F32_CEIL;
    }
    if (!strcmp(name, "f32.floor")) {
        return WEB49_OPCODE_F32_FLOOR;
    }
    if (!strcmp(name, "f32.trunc")) {
        return WEB49_OPCODE_F32_TRUNC;
    }
    if (!strcmp(name, "f32.nearest")) {
        return WEB49_OPCODE_F32_NEAREST;
    }
    if (!strcmp(name, "f32.sqrt")) {
        return WEB49_OPCODE_F32_SQRT;
    }
    if (!strcmp(name, "f32.add")) {
        return WEB49_OPCODE_F32_ADD;
    }
    if (!strcmp(name, "f32.sub")) {
        return WEB49_OPCODE_F32_SUB;
    }
    if (!strcmp(name, "f32.mul")) {
        return WEB49_OPCODE_F32_MUL;
    }
    if (!strcmp(name, "f32.div")) {
        return WEB49_OPCODE_F32_DIV;
    }
    if (!strcmp(name, "f32.min")) {
        return WEB49_OPCODE_F32_MIN;
    }
    if (!strcmp(name, "f32.max")) {
        return WEB49_OPCODE_F32_MAX;
    }
    if (!strcmp(name, "f32.copysign")) {
        return WEB49_OPCODE_F32_COPYSIGN;
    }
    if (!strcmp(name, "f64.abs")) {
        return WEB49_OPCODE_F64_ABS;
    }
    if (!strcmp(name, "f64.neg")) {
        return WEB49_OPCODE_F64_NEG;
    }
    if (!strcmp(name, "f64.ceil")) {
        return WEB49_OPCODE_F64_CEIL;
    }
    if (!strcmp(name, "f64.floor")) {
        return WEB49_OPCODE_F64_FLOOR;
    }
    if (!strcmp(name, "f64.trunc")) {
        return WEB49_OPCODE_F64_TRUNC;
    }
    if (!strcmp(name, "f64.nearest")) {
        return WEB49_OPCODE_F64_NEAREST;
    }
    if (!strcmp(name, "f64.sqrt")) {
        return WEB49_OPCODE_F64_SQRT;
    }
    if (!strcmp(name, "f64.add")) {
        return WEB49_OPCODE_F64_ADD;
    }
    if (!strcmp(name, "f64.sub")) {
        return WEB49_OPCODE_F64_SUB;
    }
    if (!strcmp(name, "f64.mul")) {
        return WEB49_OPCODE_F64_MUL;
    }
    if (!strcmp(name, "f64.div")) {
        return WEB49_OPCODE_F64_DIV;
    }
    if (!strcmp(name, "f64.min")) {
        return WEB49_OPCODE_F64_MIN;
    }
    if (!strcmp(name, "f64.max")) {
        return WEB49_OPCODE_F64_MAX;
    }
    if (!strcmp(name, "f64.copysign")) {
        return WEB49_OPCODE_F64_COPYSIGN;
    }
    if (!strcmp(name, "i32.wrap_i64")) {
        return WEB49_OPCODE_I32_WRAP_I64;
    }
    if (!strcmp(name, "i32.trunc_f32_s")) {
        return WEB49_OPCODE_I32_TRUNC_S_F32;
    }
    if (!strcmp(name, "i32.trunc_f32_u")) {
        return WEB49_OPCODE_I32_TRUNC_U_F32;
    }
    if (!strcmp(name, "i32.trunc_f64_s")) {
        return WEB49_OPCODE_I32_TRUNC_S_F64;
    }
    if (!strcmp(name, "i32.trunc_f64_u")) {
        return WEB49_OPCODE_I32_TRUNC_U_F64;
    }
    if (!strcmp(name, "i64.extend_i32_s")) {
        return WEB49_OPCODE_I64_EXTEND_S_I32;
    }
    if (!strcmp(name, "i64.extend_i32_u")) {
        return WEB49_OPCODE_I64_EXTEND_U_I32;
    }
    if (!strcmp(name, "i64.trunc_f32_s")) {
        return WEB49_OPCODE_I64_TRUNC_S_F32;
    }
    if (!strcmp(name, "i64.trunc_f32_u")) {
        return WEB49_OPCODE_I64_TRUNC_U_F32;
    }
    if (!strcmp(name, "i64.trunc_f64_s")) {
        return WEB49_OPCODE_I64_TRUNC_S_F64;
    }
    if (!strcmp(name, "i64.trunc_f64_u")) {
        return WEB49_OPCODE_I64_TRUNC_U_F64;
    }
    if (!strcmp(name, "f32.convert_i32_s")) {
        return WEB49_OPCODE_F32_CONVERT_S_I32;
    }
    if (!strcmp(name, "f32.convert_i32_u")) {
        return WEB49_OPCODE_F32_CONVERT_U_I32;
    }
    if (!strcmp(name, "f32.convert_i64_s")) {
        return WEB49_OPCODE_F32_CONVERT_S_I64;
    }
    if (!strcmp(name, "f32.convert_i64_u")) {
        return WEB49_OPCODE_F32_CONVERT_U_I64;
    }
    if (!strcmp(name, "f32.demote_f64")) {
        return WEB49_OPCODE_F32_DEMOTE_F64;
    }
    if (!strcmp(name, "f64.convert_i32_s")) {
        return WEB49_OPCODE_F64_CONVERT_S_I32;
    }
    if (!strcmp(name, "f64.convert_i32_u")) {
        return WEB49_OPCODE_F64_CONVERT_U_I32;
    }
    if (!strcmp(name, "f64.convert_i64_s")) {
        return WEB49_OPCODE_F64_CONVERT_S_I64;
    }
    if (!strcmp(name, "f64.convert_i64_u")) {
        return WEB49_OPCODE_F64_CONVERT_U_I64;
    }
    if (!strcmp(name, "f64.promote_f32")) {
        return WEB49_OPCODE_F64_PROMOTE_F32;
    }
    if (!strcmp(name, "i32.reinterpret_f32")) {
        return WEB49_OPCODE_I32_REINTERPRET_F32;
    }
    if (!strcmp(name, "i64.reinterpret_f64")) {
        return WEB49_OPCODE_I64_REINTERPRET_F64;
    }
    if (!strcmp(name, "f32.reinterpret_i32")) {
        return WEB49_OPCODE_F32_REINTERPRET_I32;
    }
    if (!strcmp(name, "f64.reinterpret_i64")) {
        return WEB49_OPCODE_F64_REINTERPRET_I64;
    }
    if (!strcmp(name, "memory.init")) {
        return WEB49_OPCODE_MEMORY_INIT;
    }
    if (!strcmp(name, "memory.copy")) {
        return WEB49_OPCODE_MEMORY_COPY;
    }
    if (!strcmp(name, "memory.fill")) {
        return WEB49_OPCODE_MEMORY_FILL;
    }
    if (!strcmp(name, "data.drop")) {
        return WEB49_OPCODE_DATA_DROP;
    }
    if (!strcmp(name, "table.init")) {
        return WEB49_OPCODE_TABLE_INIT;
    }
    if (!strcmp(name, "elem.drop")) {
        return WEB49_OPCODE_ELEM_DROP;
    }
    if (!strcmp(name, "table.copy")) {
        return WEB49_OPCODE_TABLE_COPY;
    }
    return WEB49_MAX_OPCODE_NUM;
}

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

const char *web49_readwat_name(FILE *in) {
redo:;
    char first = fgetc(in);
    if (first == ';') {
        if (fgetc(in) != ';') {
            ungetc(';', in);
            return ";";
        }
        while (fgetc(in) != '\n') {
        }
    }
    uint64_t alloc = 16;
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
        first = fgetc(in);
    }
    ungetc(first, in);
    buf[len] = '\0';
    return buf;
}

web49_readwat_expr_t web49_readwat_expr(FILE *in) {
redo:;
    uint64_t start = ftell(in);
    char first = fgetc(in);
    while (isspace(first)) {
        first = fgetc(in);
    }
    if (first == ';') {
        char second = fgetc(in);
        if (second == ';') {
            while (fgetc(in) != '\n') {
            }
            goto redo;
        }
        ungetc(second, in);
    }
    if (first == '(') {
        const char *name = web49_readwat_name(in);
        if (!strcmp(name, ";")) {
            uint64_t depth = 1;
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
        uint64_t alloc = 4;
        web49_readwat_expr_t *args = web49_malloc(sizeof(web49_readwat_expr_t) * alloc);
        uint64_t nargs = 0;
        while (true) {
            if (nargs + 2 >= alloc) {
                alloc *= 2;
                args = web49_realloc(args, sizeof(web49_readwat_expr_t) * alloc);
            }
            first = fgetc(in);
            while (isspace(first)) {
                first = fgetc(in);
            }
            if (first == ')' || first == '\0' || first == EOF) {
                break;
            }
            ungetc(first, in);
            args[nargs++] = web49_readwat_expr(in);
        }
        return (web49_readwat_expr_t){
            .start = start,
            .end = ftell(in),
            .fun_fun = name,
            .fun_nargs = nargs,
            .fun_args = args,
            .tag = WEB49_READWAT_EXPR_TAG_FUN,
        };
    }
    if (first == '"') {
        uint64_t alloc = 16;
        char *buf = web49_malloc(sizeof(char) * alloc);
        uint64_t len = 0;
        first = fgetc(in);
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
                    uint64_t high = (escape - '0');
                    uint64_t low = (fgetc(in) - '0');
                    buf[len++] = (char)(high * 16 + low);
                } else {
                    buf[len++] = escape;
                }
            } else {
                buf[len++] = first;
            }
            first = fgetc(in);
        }
        buf[len] = '\0';
        return (web49_readwat_expr_t){
            .start = start,
            .end = ftell(in),
            .str = buf,
            .tag = WEB49_READWAT_EXPR_TAG_STR,
        };
    }
    ungetc(first, in);
    return (web49_readwat_expr_t){
        .start = start,
        .end = ftell(in),
        .str = web49_readwat_name(in),
        .tag = WEB49_READWAT_EXPR_TAG_STR,
    };
}

static uint64_t web49_readwat_expr_to_u64(const char *arg) {
    uint64_t x = 0;
    for (const char *str = arg; *str != '\0'; str += 1) {
        x *= 10;
        x += *str - '0';
    }
    return x;
}

static int64_t web49_readwat_expr_to_i64(const char *arg) {
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

static void web49_readwat_state_type_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_lang_type_t type;

    uint64_t num_params = 0;
    web49_lang_type_t *params = NULL;
    uint64_t alloc_params = 0;

    uint64_t num_returns = 0;
    web49_lang_type_t return_type;

    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
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
        for (uint64_t j = 0; j < func.fun_nargs; j++) {
            web49_readwat_expr_t arg = func.fun_args[j];
            if (arg.tag != WEB49_READWAT_EXPR_TAG_FUN) {
                web49_readwat_table_set(&out->type_table, arg.str, out->stype.num_entries);
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
                for (uint64_t k = 0; k < arg.fun_nargs; k++) {
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
    out->stype.entries[out->stype.num_entries++] = (web49_section_type_entry_t){
        .type = type,
        .num_params = num_params,
        .params = params,
        .num_returns = num_returns,
        .return_type = return_type,
        .has_return_type = num_returns != 0,
    };
}

static void web49_readwat_state_import_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_section_import_entry_t entry = (web49_section_import_entry_t){
        .module_str = expr.fun_args[0].str,
        .field_str = expr.fun_args[1].str,
    };
    if (expr.fun_args[2].tag != WEB49_READWAT_EXPR_TAG_FUN) {
        fprintf(stderr, "expected (func ...) or (table ...) or (memory ...) or (global ..), not `%s`\n", expr.fun_args[2].str);
    }
    if (!strcmp(expr.fun_args[2].fun_fun, "func")) {
        entry.kind = WEB49_EXTERNAL_KIND_FUNCTION;
        for (uint64_t i = 0; i < expr.fun_args[2].fun_nargs; i++) {
            web49_readwat_expr_t func = expr.fun_args[2].fun_args[i];
            if (func.tag == WEB49_READWAT_EXPR_TAG_STR) {
                web49_readwat_table_set(&out->func_table, func.str, out->simport.num_entries);
            } else if (!strcmp(func.fun_fun, "type")) {
                entry.func_type.data = web49_readwat_expr_to_u64(func.fun_args[0].str);
            } else {
                fprintf(stderr, "expected $name or (type ...)");
                exit(1);
            }
        }
        out->num_func_imports += 1;
    } else if (!strcmp(expr.fun_args[2].fun_fun, "table")) {
        entry.kind = WEB49_EXTERNAL_KIND_TABLE;
    } else if (!strcmp(expr.fun_args[2].fun_fun, "memory")) {
        entry.kind = WEB49_EXTERNAL_KIND_MEMORY;
        if (expr.fun_args[2].fun_nargs == 1) {
            entry.memory_type.initial = web49_readwat_expr_to_u64(expr.fun_args[2].fun_args[0].str);
            entry.memory_type.maximum = UINT64_MAX;
        } else if (expr.fun_args[2].fun_nargs == 1) {
            entry.memory_type.initial = web49_readwat_expr_to_u64(expr.fun_args[2].fun_args[0].str);
            entry.memory_type.maximum = web49_readwat_expr_to_u64(expr.fun_args[2].fun_args[1].str);
        }
    } else if (!strcmp(expr.fun_args[2].fun_fun, "global")) {
        entry.kind = WEB49_EXTERNAL_KIND_GLOBAL;
        bool ismut = false;
        web49_readwat_expr_t tglobal = (web49_readwat_expr_t){.tag = WEB49_READWAT_EXPR_TAG_INIT};
        for (uint64_t i = 0; i < expr.fun_args[2].fun_nargs; i++) {
            web49_readwat_expr_t arg = expr.fun_args[2].fun_args[i];
            if (arg.tag == WEB49_READWAT_EXPR_TAG_STR) {
                if (arg.str[0] == '$') {
                    web49_readwat_table_set(&out->global_table, arg.str, out->simport.num_entries);
                } else {
                    tglobal = arg;
                }
            } else if (!strcmp(arg.fun_fun, "mut")) {
                if (arg.fun_nargs < 1) {
                    fprintf(stderr, "expected argument inside of parens of (mut), not just `mut`\n");
                    exit(1);
                }
                if (arg.fun_nargs > 1) {
                    fprintf(stderr, "expected only one argument inside of parens of (mut), not `mut` + %zu others\n", arg.fun_nargs);
                    exit(1);
                }
                tglobal = arg.fun_args[0];
                ismut = true;
            } else {
                fprintf(stderr, "expected $name, (mut ...) or a language type\n");
                exit(1);
            }
        }
        if (tglobal.tag != WEB49_READWAT_EXPR_TAG_STR) {
            fprintf(stderr, "expected a type for the global\n");
            exit(1);
        }
        if (!strcmp(tglobal.str, "i32")) {
            entry.global_type.content_type = WEB49_TYPE_I32;
        } else if (!strcmp(tglobal.str, "i64")) {
            entry.global_type.content_type = WEB49_TYPE_I64;
        } else if (!strcmp(tglobal.str, "f32")) {
            entry.global_type.content_type = WEB49_TYPE_F32;
        } else if (!strcmp(tglobal.str, "f64")) {
            entry.global_type.content_type = WEB49_TYPE_F64;
        } else {
            fprintf(stderr, "exepcted a type name for the global, not `%s`", tglobal.str);
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

static void web49_readwat_state_func_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    {
        uint64_t entry = UINT64_MAX;
        for (uint64_t i = 0; i < expr.fun_nargs; i++) {
            web49_readwat_expr_t code = expr.fun_args[i];
            if (code.tag == WEB49_READWAT_EXPR_TAG_FUN) {
                if (!strcmp(code.fun_fun, "type")) {
                    entry = web49_readwat_expr_to_u64(code.fun_args[0].str);
                    break;
                }
                if (!strcmp(code.fun_fun, "param") || !strcmp(code.fun_fun, "result")) {
                    web49_lang_type_t type = WEB49_TYPE_FUNC;
                    uint64_t num_params = 0;
                    web49_lang_type_t *params = NULL;
                    uint64_t alloc_params = 0;
                    uint64_t num_returns = 0;
                    web49_lang_type_t return_type;
                    web49_readwat_expr_t expr = expr.fun_args[i++];
                    if (!strcmp(expr.fun_fun, "param")) {
                        for (uint64_t k = 0; k < expr.fun_nargs; k++) {
                            if (num_params + 2 >= alloc_params) {
                                alloc_params = (num_params + 2) * 2;
                                params = web49_realloc(params, sizeof(web49_lang_type_t) * alloc_params);
                            }
                            web49_readwat_expr_t name = expr.fun_args[k];
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
                        expr = expr.fun_args[i++];
                    }
                    if (!strcmp(expr.fun_fun, "result")) {
                        for (uint64_t k = 0; k < expr.fun_nargs; k++) {
                            if (num_returns != 0) {
                                fprintf(stderr, "expected you not to use multi-results :(\n");
                                exit(1);
                            }
                            web49_readwat_expr_t name = expr.fun_args[k];
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
            if (code.tag == WEB49_READWAT_EXPR_TAG_STR) {
                web49_opcode_t opcode = web49_readwat_name_to_opcode(code.str);
                if (opcode < WEB49_MAX_OPCODE_NUM) {
                    web49_immediate_id_t id = web49_immediates[opcode];
                    web49_instr_immediate_t imm = (web49_instr_immediate_t){
                        .id = id,
                    };
                    switch (id) {
                        case WEB49_IMMEDIATE_NONE:
                            break;
                        case WEB49_IMMEDIATE_BLOCK_TYPE:
                            if (expr.fun_args[i].tag == WEB49_READWAT_EXPR_TAG_FUN && !strcmp(expr.fun_args[i + 1].fun_fun, "result")) {
                                web49_readwat_expr_t arg = expr.fun_args[i + 1].fun_args[0];
                                if (arg.tag != WEB49_READWAT_EXPR_TAG_STR) {
                                    fprintf(stderr, "expected basic type\n");
                                    exit(1);
                                }
                                if (!strcmp(arg.str, "i32")) {
                                    imm.block_type = WEB49_TYPE_I32;
                                } else if (!strcmp(arg.str, "i64")) {
                                    imm.block_type = WEB49_TYPE_I64;
                                } else if (!strcmp(arg.str, "f32")) {
                                    imm.block_type = WEB49_TYPE_F32;
                                } else if (!strcmp(arg.str, "f64")) {
                                    imm.block_type = WEB49_TYPE_F64;
                                } else {
                                    fprintf(stderr, "expected basic type name, not `%s`\n", arg.str);
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
                            imm.varuint32 = (uint32_t)web49_readwat_expr_to_u64(expr.fun_args[++i].str);
                            break;
                        case WEB49_IMMEDIATE_VARUINT64:
                            imm.varuint64 = (uint64_t)web49_readwat_expr_to_u64(expr.fun_args[++i].str);
                            break;
                        case WEB49_IMMEDIATE_VARINT32:
                            imm.varuint64 = (int32_t)web49_readwat_expr_to_i64(expr.fun_args[++i].str);
                            break;
                        case WEB49_IMMEDIATE_VARINT64:
                            imm.varuint64 = (int64_t)web49_readwat_expr_to_i64(expr.fun_args[++i].str);
                            break;
                        case WEB49_IMMEDIATE_UINT32:
                            imm.varuint32 = (uint32_t)web49_readwat_expr_to_u64(expr.fun_args[++i].str);
                            break;
                        case WEB49_IMMEDIATE_UINT64:
                            imm.varuint64 = (uint64_t)web49_readwat_expr_to_u64(expr.fun_args[++i].str);
                            break;
                        case WEB49_IMMEDIATE_BR_TABLE: {
                            i += 1;
                            uint64_t alloc = 0;
                            while (i < expr.fun_nargs && isdigit(expr.fun_args[i + 1].str[0])) {
                                if (imm.br_table.num_targets + 2 >= alloc) {
                                    alloc = (imm.br_table.num_targets + 2) * 2;
                                    imm.br_table.targets = web49_realloc(imm.br_table.targets, sizeof(uint64_t) * alloc);
                                }
                                imm.br_table.targets[imm.br_table.num_targets++] = web49_readwat_expr_to_u64(expr.fun_args[i++].str);
                            }
                            imm.br_table.default_target = web49_readwat_expr_to_u64(expr.fun_args[i].str);
                            break;
                        }
                        case WEB49_IMMEDIATE_CALL_INDIRECT:
                            imm.call_indirect.index = (uint64_t)web49_readwat_expr_to_u64(expr.fun_args[++i].fun_args[0].str);
                            break;
                        case WEB49_IMMEDIATE_MEMORY_IMMEDIATE: {
                            switch (web49_wat_instr_mem_size[opcode]) {
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
                            if (arg.tag == WEB49_READWAT_EXPR_TAG_STR) {
                                if (!strncmp(arg.str, "align=", 6)) {
                                    uint64_t n = web49_readwat_expr_to_u64(&arg.str[6]);
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
                                if (!strncmp(arg.str, "offset=", 7)) {
                                    imm.memory_immediate.offset = web49_readwat_expr_to_u64(&arg.str[7]);
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
                    fprintf(stderr, "unexpected word: `%s` byte=%zu\n", code.str, (size_t)code.start);
                    exit(1);
                }
            } else if (!strcmp(code.fun_fun, "param") || !strcmp(code.fun_fun, "type") || !strcmp(code.fun_fun, "result")) {
                // nothing goes here
            } else if (!strcmp(code.fun_fun, "local")) {
                for (uint64_t j = 0; j < code.fun_nargs; j++) {
                    web49_readwat_expr_t name = code.fun_args[j];
                    web49_lang_type_t local_type;
                    if (!strcmp(name.str, "i32")) {
                        local_type = WEB49_TYPE_I32;
                    } else if (!strcmp(name.str, "i64")) {
                        local_type = WEB49_TYPE_I64;
                    } else if (!strcmp(name.str, "f32")) {
                        local_type = WEB49_TYPE_F32;
                    } else if (!strcmp(name.str, "f64")) {
                        local_type = WEB49_TYPE_F64;
                    } else {
                        fprintf(stderr, "expected local to be `i32` or `i64` or `f32` or `f64`, not `%s`\n", name.str);
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

static void web49_readwat_state_table_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_type_table_t entry;
    entry.limits.maximum = UINT64_MAX;
    bool init = false;
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t arg = expr.fun_args[i];
        if (arg.tag != WEB49_READWAT_EXPR_TAG_STR) {
            fprintf(stderr, "did not expect a paren\n");
            exit(1);
        }
        if (isdigit(arg.str[0])) {
            if (!init) {
                entry.limits.initial = web49_readwat_expr_to_u64(arg.str);
                init = true;
            } else {
                entry.limits.maximum = web49_readwat_expr_to_u64(arg.str);
            }
        } else if (!strcmp(arg.str, "i32")) {
            entry.element_type = WEB49_TYPE_I32;
        } else if (!strcmp(arg.str, "i64")) {
            entry.element_type = WEB49_TYPE_I64;
        } else if (!strcmp(arg.str, "f32")) {
            entry.element_type = WEB49_TYPE_F32;
        } else if (!strcmp(arg.str, "f64")) {
            entry.element_type = WEB49_TYPE_F64;
        } else if (!strcmp(arg.str, "funcref")) {
            entry.element_type = WEB49_TYPE_ANYFUNC;
        } else {
            fprintf(stderr, "expected a type, not `%s`", arg.str);
            exit(1);
        }
    }
    if (out->stable.num_entries + 2 >= out->alloc_table) {
        out->alloc_table = (out->stable.num_entries + 2) * 2;
        out->stable.entries = web49_realloc(out->stable.entries, sizeof(web49_type_table_t) * out->alloc_table);
    }
    out->stable.entries[out->stable.num_entries++] = entry;
}

static web49_instr_t web49_readwat_instr(web49_readwat_expr_t code) {
    if (code.tag == WEB49_READWAT_EXPR_TAG_FUN) {
        web49_opcode_t opcode = web49_readwat_name_to_opcode(code.fun_fun);
        if (opcode < WEB49_MAX_OPCODE_NUM) {
            web49_immediate_id_t id = web49_immediates[opcode];
            web49_instr_immediate_t imm = (web49_instr_immediate_t){
                .id = id,
            };
            switch (id) {
                case WEB49_IMMEDIATE_NONE:
                    break;
                case WEB49_IMMEDIATE_BLOCK_TYPE:
                    if (code.fun_args[0].tag == WEB49_READWAT_EXPR_TAG_FUN && !strcmp(code.fun_args[0].fun_fun, "result")) {
                        web49_readwat_expr_t arg = code.fun_args[0].fun_args[0];
                        if (arg.tag != WEB49_READWAT_EXPR_TAG_STR) {
                            fprintf(stderr, "expected basic type\n");
                            exit(1);
                        }
                        if (!strcmp(arg.str, "i32")) {
                            imm.block_type = WEB49_TYPE_I32;
                        } else if (!strcmp(arg.str, "i64")) {
                            imm.block_type = WEB49_TYPE_I64;
                        } else if (!strcmp(arg.str, "f32")) {
                            imm.block_type = WEB49_TYPE_F32;
                        } else if (!strcmp(arg.str, "f64")) {
                            imm.block_type = WEB49_TYPE_F64;
                        } else {
                            fprintf(stderr, "expected basic type name, not `%s`\n", arg.str);
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
                    imm.varuint32 = (uint32_t)web49_readwat_expr_to_u64(code.fun_args[0].str);
                    break;
                case WEB49_IMMEDIATE_VARUINT64:
                    imm.varuint64 = (uint64_t)web49_readwat_expr_to_u64(code.fun_args[0].str);
                    break;
                case WEB49_IMMEDIATE_VARINT32:
                    imm.varuint64 = (int32_t)web49_readwat_expr_to_i64(code.fun_args[0].str);
                    break;
                case WEB49_IMMEDIATE_VARINT64:
                    imm.varuint64 = (int64_t)web49_readwat_expr_to_i64(code.fun_args[0].str);
                    break;
                case WEB49_IMMEDIATE_UINT32:
                    imm.varuint32 = (uint32_t)web49_readwat_expr_to_u64(code.fun_args[0].str);
                    break;
                case WEB49_IMMEDIATE_UINT64:
                    imm.varuint64 = (uint64_t)web49_readwat_expr_to_u64(code.fun_args[0].str);
                    break;
                case WEB49_IMMEDIATE_BR_TABLE: {
                    uint64_t i = 0;
                    uint64_t alloc = 0;
                    while (i < code.fun_nargs && isdigit(code.fun_args[i + 1].str[0])) {
                        if (imm.br_table.num_targets + 2 >= alloc) {
                            alloc = (imm.br_table.num_targets + 2) * 2;
                            imm.br_table.targets = web49_realloc(imm.br_table.targets, sizeof(uint64_t) * alloc);
                        }
                        imm.br_table.targets[imm.br_table.num_targets++] = web49_readwat_expr_to_u64(code.fun_args[i++].str);
                    }
                    imm.br_table.default_target = web49_readwat_expr_to_u64(code.fun_args[i].str);
                    break;
                }
                case WEB49_IMMEDIATE_CALL_INDIRECT:
                    imm.call_indirect.index = (uint64_t)web49_readwat_expr_to_u64(code.fun_args[0].fun_args[0].str);
                    break;
                case WEB49_IMMEDIATE_MEMORY_IMMEDIATE: {
                    switch (web49_wat_instr_mem_size[opcode]) {
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
                    if (arg.tag == WEB49_READWAT_EXPR_TAG_STR) {
                        if (!strncmp(arg.str, "align=", 6)) {
                            uint64_t n = web49_readwat_expr_to_u64(&arg.str[6]);
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
                        if (!strncmp(arg.str, "offset=", 7)) {
                            imm.memory_immediate.offset = web49_readwat_expr_to_u64(&arg.str[7]);
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
            fprintf(stderr, "unexpected word: `%s` byte=%zu\n", code.str, (size_t)code.start);
            exit(1);
        }
    } else {
        fprintf(stderr, "unexpected expr: (%s ...) byte=%zu\n", code.fun_fun, (size_t)code.start);
    }
    fprintf(stderr, "expected an instruction\n");
    exit(1);
}

static void web49_readwat_state_global_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_section_global_entry_t entry;
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t arg = expr.fun_args[i];
        if (arg.tag == WEB49_READWAT_EXPR_TAG_STR) {
            if (!strcmp(arg.str, "i32")) {
                entry.global.content_type = WEB49_TYPE_I32;
            } else if (!strcmp(arg.str, "i64")) {
                entry.global.content_type = WEB49_TYPE_I64;
            } else if (!strcmp(arg.str, "f32")) {
                entry.global.content_type = WEB49_TYPE_F32;
            } else if (!strcmp(arg.str, "f64")) {
                entry.global.content_type = WEB49_TYPE_F64;
            } else if (!strcmp(arg.str, "funcref")) {
                entry.global.content_type = WEB49_TYPE_ANYFUNC;
            } else {
                fprintf(stderr, "expected a global type, not `%s`\n", arg.str);
                exit(1);
            }
        } else {
            if (!strcmp(arg.fun_fun, "mut")) {
                if (arg.fun_nargs < 0) {
                    fprintf(stderr, "expected word after (mut\n");
                    exit(0);
                }
                entry.global.is_mutable = true;
                if (!strcmp(arg.fun_args[0].str, "i32")) {
                    entry.global.content_type = WEB49_TYPE_I32;
                } else if (!strcmp(arg.fun_args[0].str, "i64")) {
                    entry.global.content_type = WEB49_TYPE_I64;
                } else if (!strcmp(arg.fun_args[0].str, "f32")) {
                    entry.global.content_type = WEB49_TYPE_F32;
                } else if (!strcmp(arg.fun_args[0].str, "f64")) {
                    entry.global.content_type = WEB49_TYPE_F64;
                } else if (!strcmp(arg.fun_args[0].str, "funcref")) {
                    entry.global.content_type = WEB49_TYPE_ANYFUNC;
                } else {
                    fprintf(stderr, "expected a global (mut typename), not (mut %s)\n", arg.str);
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
static void web49_readwat_state_export_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
    web49_section_export_entry_t entry;
    entry.field_str = expr.fun_args[0].str;
    if (expr.fun_args[1].tag != WEB49_READWAT_EXPR_TAG_FUN) {
        fprintf(stderr, "expected paren after `(export \"...\"`, but was missing paren\n");
        exit(1);
    }
    if (!strcmp(expr.fun_args[1].str, "func")) {
        entry.kind = WEB49_EXTERNAL_KIND_FUNCTION;
    } else if (!strcmp(expr.fun_args[1].str, "table")) {
        entry.kind = WEB49_EXTERNAL_KIND_TABLE;
    } else if (!strcmp(expr.fun_args[1].str, "memory")) {
        entry.kind = WEB49_EXTERNAL_KIND_MEMORY;
    } else if (!strcmp(expr.fun_args[1].str, "global")) {
        entry.kind = WEB49_EXTERNAL_KIND_GLOBAL;
    } else {
        fprintf(stderr, "expected `func` or `table` or `memory` or `global`, not `%s`\n", expr.fun_args[1].str);
    }
    entry.index = web49_readwat_expr_to_u64(expr.fun_args[1].fun_args[0].str);
    if (out->sexport.num_entries + 2 >= out->alloc_export) {
        out->alloc_export = (out->sexport.num_entries + 2) * 2;
        out->sexport.entries = web49_realloc(out->sexport.entries, sizeof(web49_section_export_entry_t) * out->alloc_export);
    }
    out->sexport.entries[out->sexport.num_entries++] = entry;
}
static void web49_readwat_state_elem_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
}
static void web49_readwat_state_data_entry(web49_readwat_state_t *out, web49_readwat_expr_t expr) {
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
    }
    for (uint64_t i = 0; i < expr.fun_nargs; i++) {
        web49_readwat_expr_t type = expr.fun_args[i];
        if (!strcmp(type.fun_fun, "func")) {
            web49_readwat_state_func_entry(out, type);
        }
    }
}

web49_module_t web49_readwat_module(FILE *in) {
    web49_readwat_state_t state = {0};
    web49_readwat_expr_t expr = web49_readwat_expr(in);
    web49_readwat_state_toplevel(&state, expr);
    uint64_t num_sections = 0;
    web49_section_t *sections = web49_malloc(sizeof(web49_section_t) * 12);
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
    if (state.sglobal.num_entries != 0) {
        sections[num_sections++] = (web49_section_t){
            .header = (web49_section_header_t){
                .id = WEB49_SECTION_ID_GLOBAL,
                .size_known = false,
            },
            .global_section = state.sglobal,
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
