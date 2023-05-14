
#include "tables.h"

#include "ast.h"

const web49_table_stack_effect_t web49_stack_effects[WEB49_MAX_OPCODE_NUM] = {
    [WEB49_OPCODE_UNREACHABLE] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_NOP] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_BLOCK] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_BLOCK,
        .branch = true,
    },
    [WEB49_OPCODE_LOOP] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_BLOCK,
        .branch = true,
    },
    [WEB49_OPCODE_IF] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_BLOCK,
        .branch = true,
    },
    [WEB49_OPCODE_ELSE] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_END] = (web49_table_stack_effect_t){
        .branch = true,
    },
    [WEB49_OPCODE_BR] = (web49_table_stack_effect_t){
        .branch = true,
    },
    [WEB49_OPCODE_BR_IF] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .branch = true,
    },
    [WEB49_OPCODE_BR_TABLE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .branch = true,
    },
    [WEB49_OPCODE_RETURN] = (web49_table_stack_effect_t){
        .branch = true,
    },
    [WEB49_OPCODE_CALL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ARGS,
    },
    [WEB49_OPCODE_CALL_INDIRECT] = (web49_table_stack_effect_t){
        .in[1] = WEB49_TABLE_STACK_EFFECT_ARGS_INDIRECT,
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_DROP] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_SELECT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_ANY,
        .in[2] = WEB49_TABLE_STACK_EFFECT_ANY,
        .out[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_GET_LOCAL] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_SET_LOCAL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_TEE_LOCAL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ANY,
        .out[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_GET_GLOBAL] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_SET_GLOBAL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_I32_LOAD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_LOAD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_F32_LOAD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F64_LOAD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I32_LOAD8_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_LOAD8_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_LOAD16_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_LOAD16_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_LOAD8_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_LOAD8_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_LOAD16_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_LOAD16_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_LOAD32_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_LOAD32_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I32_STORE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_STORE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F32_STORE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F64_STORE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_STORE8] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_STORE16] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_STORE8] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_STORE16] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_STORE32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_MEMORY_SIZE] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_MEMORY_GROW] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_CONST] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_CONST] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_F32_CONST] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F64_CONST] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I32_EQZ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_EQ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_NE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_LT_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_LT_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_GT_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_GT_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_LE_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_LE_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_GE_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_GE_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_EQZ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_EQ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_NE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_LT_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_LT_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_GT_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_GT_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_LE_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_LE_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_GE_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_GE_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F32_EQ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F32_NE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F32_LT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F32_GT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F32_LE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F32_GE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F64_EQ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F64_NE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F64_LT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F64_GT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F64_LE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_F64_GE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_CLZ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_CTZ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_POPCNT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_ADD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_SUB] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_MUL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_DIV_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_DIV_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_REM_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_REM_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_AND] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_OR] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_XOR] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_SHL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_SHR_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_SHR_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_ROTL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_ROTR] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_CLZ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_CTZ] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_POPCNT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_ADD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_SUB] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_MUL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_DIV_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_DIV_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_REM_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_REM_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_AND] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_OR] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_XOR] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_SHL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_SHR_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_SHR_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_ROTL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_ROTR] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_F32_ABS] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_NEG] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_CEIL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_FLOOR] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_TRUNC] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_NEAREST] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_SQRT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_ADD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_SUB] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_MUL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_DIV] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_MIN] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_MAX] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_COPYSIGN] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F64_ABS] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_NEG] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_CEIL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_FLOOR] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_TRUNC] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_NEAREST] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_SQRT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_ADD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_SUB] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_MUL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_DIV] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_MIN] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_MAX] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .in[1] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_COPYSIGN] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I32_WRAP_I64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_S_F32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_U_F32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_S_F64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_U_F64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_EXTEND_S_I32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_EXTEND_U_I32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_S_F32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_U_F32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_S_F64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_U_F64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_F32_CONVERT_S_I32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_CONVERT_U_I32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_CONVERT_S_I64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_CONVERT_U_I64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32_DEMOTE_F64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F64_CONVERT_S_I32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_CONVERT_U_I32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_CONVERT_S_I64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_CONVERT_U_I64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64_PROMOTE_F32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I32_REINTERPRET_F32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_REINTERPRET_F64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_F32_REINTERPRET_I32] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F64_REINTERPRET_I64] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I32_EXTEND8_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I32_EXTEND16_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I64_EXTEND8_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I64_EXTEND16_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_I64_EXTEND32_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_MEMORY_INIT] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_MEMORY_COPY] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[2] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_MEMORY_FILL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[2] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_SAT_F32_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_SAT_F32_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_SAT_F64_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_SAT_F64_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64_TRUNC_SAT_F32_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_SAT_F32_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_SAT_F64_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_SAT_F64_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_DATA_DROP] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_REF_NULL] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_REF_IS_NULL] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_REF_FUNC] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_GET] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_SET] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_SIZE] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_GROW] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_FILL] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_COPY] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_INIT] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_ELEM_DROP] = (web49_table_stack_effect_t){
        .fail = true,
    },

    [WEB49_OPCODE_YIELD_PUSH] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_YIELD_POP] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_RETURN0] = (web49_table_stack_effect_t){
        .branch = true,
    },
    [WEB49_OPCODE_RETURN1] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ANY,
        .branch = true,
    },
    [WEB49_OPCODE_CALL0] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ARGS,
    },
    [WEB49_OPCODE_CALL1] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ARGS,
        .out[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_CALL_INDIRECT0] = (web49_table_stack_effect_t){
        .in[1] = WEB49_TABLE_STACK_EFFECT_ARGS_INDIRECT,
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_CALL_INDIRECT1] = (web49_table_stack_effect_t){
        .in[1] = WEB49_TABLE_STACK_EFFECT_ARGS_INDIRECT,
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_ANY,
    },
    [WEB49_OPCODE_V128_LOAD] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD8X8_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD8X8_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD16X4_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD16X4_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD32X2_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD32X2_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD8_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD16_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD32_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_LOAD64_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_STORE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_V128_CONST] = (web49_table_stack_effect_t){
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_I8X16_SHUFFLE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .in[1] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_I8X16_SWIZZLE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .in[1] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_I8X16_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_I16X8_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_I32X4_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_I64X2_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_F32X4_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F32,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_F64X2_SPLAT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_F64,
        .out[0] = WEB49_TABLE_STACK_EFFECT_V128,
    },
    [WEB49_OPCODE_I8X16_EXTRACT_LANE_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I8X16_EXTRACT_LANE_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I8X16_REPLACE_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I16X8_EXTRACT_LANE_S] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I16X8_EXTRACT_LANE_U] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I16X8_REPLACE_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32X4_EXTRACT_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I32X4_REPLACE_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I32,
    },
    [WEB49_OPCODE_I64X2_EXTRACT_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_I64X2_REPLACE_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_I64,
    },
    [WEB49_OPCODE_F32X4_EXTRACT_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F32,
    },
    [WEB49_OPCODE_F32X4_REPLACE_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64X2_EXTRACT_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
    [WEB49_OPCODE_F64X2_REPLACE_LANE] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_V128,
        .out[0] = WEB49_TABLE_STACK_EFFECT_F64,
    },
};

const size_t web49_opcode_memsize[WEB49_MAX_OPCODE_NUM] = {
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
    [WEB49_OPCODE_V128_LOAD] = 16,
    [WEB49_OPCODE_V128_LOAD8X8_S] = 16,
    [WEB49_OPCODE_V128_LOAD8X8_U] = 16,
    [WEB49_OPCODE_V128_LOAD16X4_S] = 16,
    [WEB49_OPCODE_V128_LOAD16X4_U] = 16,
    [WEB49_OPCODE_V128_LOAD32X2_S] = 16,
    [WEB49_OPCODE_V128_LOAD32X2_U] = 16,
    [WEB49_OPCODE_V128_LOAD8_SPLAT] = 1,
    [WEB49_OPCODE_V128_LOAD16_SPLAT] = 2,
    [WEB49_OPCODE_V128_LOAD32_SPLAT] = 4,
    [WEB49_OPCODE_V128_LOAD64_SPLAT] = 8,
    [WEB49_OPCODE_V128_STORE] = 16,
};

const web49_immediate_id_t web49_opcode_immediate[WEB49_MAX_OPCODE_NUM] = {
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
    // [WEB49_OPCODE_REF_NULL] = WEB49_IMMEDIATE_TABLE_INDEX,
    // [WEB49_OPCODE_REF_IS_NULL] = WEB49_IMMEDIATE_TABLE_INDEX,
    // [WEB49_OPCODE_REF_FUNC] = WEB49_IMMEDIATE_TABLE_INDEX,
    [WEB49_OPCODE_TABLE_GET] = WEB49_IMMEDIATE_TABLE_INDEX,
    [WEB49_OPCODE_TABLE_SET] = WEB49_IMMEDIATE_TABLE_INDEX,
    [WEB49_OPCODE_TABLE_SIZE] = WEB49_IMMEDIATE_TABLE_INDEX,
    [WEB49_OPCODE_TABLE_GROW] = WEB49_IMMEDIATE_TABLE_INDEX,
    [WEB49_OPCODE_TABLE_FILL] = WEB49_IMMEDIATE_TABLE_INDEX,
    [WEB49_OPCODE_TABLE_COPY] = WEB49_IMMEDIATE_TABLE_INDEX,
    [WEB49_OPCODE_TABLE_INIT] = WEB49_IMMEDIATE_ELEM_INDEX,
    [WEB49_OPCODE_ELEM_DROP] = WEB49_IMMEDIATE_ELEM_INDEX,
    [WEB49_OPCODE_V128_CONST] = WEB49_IMMEDIATE_V128,
    [WEB49_OPCODE_V128_LOAD] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD8X8_S] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD8X8_U] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD16X4_S] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD16X4_U] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD32X2_S] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD32X2_U] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD8_SPLAT] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD16_SPLAT] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD32_SPLAT] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_LOAD64_SPLAT] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_V128_STORE] = WEB49_IMMEDIATE_MEMORY_IMMEDIATE,
    [WEB49_OPCODE_I8X16_EXTRACT_LANE_S] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I8X16_EXTRACT_LANE_U] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I8X16_REPLACE_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I16X8_EXTRACT_LANE_S] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I16X8_EXTRACT_LANE_U] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I16X8_REPLACE_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I32X4_EXTRACT_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I32X4_REPLACE_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I64X2_EXTRACT_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_I64X2_REPLACE_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_F32X4_EXTRACT_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_F32X4_REPLACE_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_F64X2_EXTRACT_LANE] = WEB49_IMMEDIATE_LANE,
    [WEB49_OPCODE_F64X2_REPLACE_LANE] = WEB49_IMMEDIATE_LANE,
};

bool web49_opcode_is_simd(web49_opcode_t opcode) {
    return WEB49_MIN_SIMD_OPCODE_NUM <= opcode && opcode <= WEB49_MAX_SIMD_OPCODE_NUM;
}

size_t web49_opcode_byte_count(uint8_t first_byte) {
    if (first_byte == 0xF8 || first_byte == 0xFB || first_byte == 0xFC || first_byte == 0xFE) {
        return 2;
    }
    return 1;
}

#define web49_error(...)          \
    fprintf(stderr, __VA_ARGS__); \
    __builtin_trap()

web49_opcode_t web49_bytes_to_opcode(uint8_t *bytes) {
    switch (bytes[0]) {
        case 0x00:
            return WEB49_OPCODE_UNREACHABLE;
        case 0x01:
            return WEB49_OPCODE_NOP;
        case 0x02:
            return WEB49_OPCODE_BLOCK;
        case 0x03:
            return WEB49_OPCODE_LOOP;
        case 0x04:
            return WEB49_OPCODE_IF;
        case 0x05:
            return WEB49_OPCODE_ELSE;
        case 0x06:
            web49_error("unknown opcode: staring with byte 0x6\n");
        case 0x07:
            web49_error("unknown opcode: staring with byte 0x7\n");
        case 0x08:
            web49_error("unknown opcode: staring with byte 0x8\n");
        case 0x09:
            web49_error("unknown opcode: staring with byte 0x9\n");
        case 0x0A:
            web49_error("unknown opcode: staring with byte 0xA\n");
        case 0x0B:
            return WEB49_OPCODE_END;
        case 0x0C:
            return WEB49_OPCODE_BR;
        case 0x0D:
            return WEB49_OPCODE_BR_IF;
        case 0x0E:
            return WEB49_OPCODE_BR_TABLE;
        case 0x0F:
            return WEB49_OPCODE_RETURN;
        case 0x10:
            return WEB49_OPCODE_CALL;
        case 0x11:
            return WEB49_OPCODE_CALL_INDIRECT;
        case 0x12:
            web49_error("unknown opcode: staring with byte 0x12\n");
        case 0x13:
            web49_error("unknown opcode: staring with byte 0x13\n");
        case 0x14:
            web49_error("unknown opcode: staring with byte 0x14\n");
        case 0x15:
            web49_error("unknown opcode: staring with byte 0x15\n");
        case 0x16:
            web49_error("unknown opcode: staring with byte 0x16\n");
        case 0x17:
            web49_error("unknown opcode: staring with byte 0x17\n");
        case 0x18:
            web49_error("unknown opcode: staring with byte 0x18\n");
        case 0x19:
            web49_error("unknown opcode: staring with byte 0x19\n");
        case 0x1A:
            return WEB49_OPCODE_DROP;
        case 0x1B:
            return WEB49_OPCODE_SELECT;
        case 0x1C:
            web49_error("unknown opcode: staring with byte 0x1C\n");
        case 0x1D:
            web49_error("unknown opcode: staring with byte 0x1D\n");
        case 0x1E:
            web49_error("unknown opcode: staring with byte 0x1E\n");
        case 0x1F:
            web49_error("unknown opcode: staring with byte 0x1F\n");
        case 0x20:
            return WEB49_OPCODE_GET_LOCAL;
        case 0x21:
            return WEB49_OPCODE_SET_LOCAL;
        case 0x22:
            return WEB49_OPCODE_TEE_LOCAL;
        case 0x23:
            return WEB49_OPCODE_GET_GLOBAL;
        case 0x24:
            return WEB49_OPCODE_SET_GLOBAL;
        case 0x25:
            web49_error("unknown opcode: staring with byte 0x25\n");
        case 0x26:
            web49_error("unknown opcode: staring with byte 0x26\n");
        case 0x27:
            web49_error("unknown opcode: staring with byte 0x27\n");
        case 0x28:
            return WEB49_OPCODE_I32_LOAD;
        case 0x29:
            return WEB49_OPCODE_I64_LOAD;
        case 0x2A:
            return WEB49_OPCODE_F32_LOAD;
        case 0x2B:
            return WEB49_OPCODE_F64_LOAD;
        case 0x2C:
            return WEB49_OPCODE_I32_LOAD8_S;
        case 0x2D:
            return WEB49_OPCODE_I32_LOAD8_U;
        case 0x2E:
            return WEB49_OPCODE_I32_LOAD16_S;
        case 0x2F:
            return WEB49_OPCODE_I32_LOAD16_U;
        case 0x30:
            return WEB49_OPCODE_I64_LOAD8_S;
        case 0x31:
            return WEB49_OPCODE_I64_LOAD8_U;
        case 0x32:
            return WEB49_OPCODE_I64_LOAD16_S;
        case 0x33:
            return WEB49_OPCODE_I64_LOAD16_U;
        case 0x34:
            return WEB49_OPCODE_I64_LOAD32_S;
        case 0x35:
            return WEB49_OPCODE_I64_LOAD32_U;
        case 0x36:
            return WEB49_OPCODE_I32_STORE;
        case 0x37:
            return WEB49_OPCODE_I64_STORE;
        case 0x38:
            return WEB49_OPCODE_F32_STORE;
        case 0x39:
            return WEB49_OPCODE_F64_STORE;
        case 0x3A:
            return WEB49_OPCODE_I32_STORE8;
        case 0x3B:
            return WEB49_OPCODE_I32_STORE16;
        case 0x3C:
            return WEB49_OPCODE_I64_STORE8;
        case 0x3D:
            return WEB49_OPCODE_I64_STORE16;
        case 0x3E:
            return WEB49_OPCODE_I64_STORE32;
        case 0x3F:
            return WEB49_OPCODE_MEMORY_SIZE;
        case 0x40:
            return WEB49_OPCODE_MEMORY_GROW;
        case 0x41:
            return WEB49_OPCODE_I32_CONST;
        case 0x42:
            return WEB49_OPCODE_I64_CONST;
        case 0x43:
            return WEB49_OPCODE_F32_CONST;
        case 0x44:
            return WEB49_OPCODE_F64_CONST;
        case 0x45:
            return WEB49_OPCODE_I32_EQZ;
        case 0x46:
            return WEB49_OPCODE_I32_EQ;
        case 0x47:
            return WEB49_OPCODE_I32_NE;
        case 0x48:
            return WEB49_OPCODE_I32_LT_S;
        case 0x49:
            return WEB49_OPCODE_I32_LT_U;
        case 0x4A:
            return WEB49_OPCODE_I32_GT_S;
        case 0x4B:
            return WEB49_OPCODE_I32_GT_U;
        case 0x4C:
            return WEB49_OPCODE_I32_LE_S;
        case 0x4D:
            return WEB49_OPCODE_I32_LE_U;
        case 0x4E:
            return WEB49_OPCODE_I32_GE_S;
        case 0x4F:
            return WEB49_OPCODE_I32_GE_U;
        case 0x50:
            return WEB49_OPCODE_I64_EQZ;
        case 0x51:
            return WEB49_OPCODE_I64_EQ;
        case 0x52:
            return WEB49_OPCODE_I64_NE;
        case 0x53:
            return WEB49_OPCODE_I64_LT_S;
        case 0x54:
            return WEB49_OPCODE_I64_LT_U;
        case 0x55:
            return WEB49_OPCODE_I64_GT_S;
        case 0x56:
            return WEB49_OPCODE_I64_GT_U;
        case 0x57:
            return WEB49_OPCODE_I64_LE_S;
        case 0x58:
            return WEB49_OPCODE_I64_LE_U;
        case 0x59:
            return WEB49_OPCODE_I64_GE_S;
        case 0x5A:
            return WEB49_OPCODE_I64_GE_U;
        case 0x5B:
            return WEB49_OPCODE_F32_EQ;
        case 0x5C:
            return WEB49_OPCODE_F32_NE;
        case 0x5D:
            return WEB49_OPCODE_F32_LT;
        case 0x5E:
            return WEB49_OPCODE_F32_GT;
        case 0x5F:
            return WEB49_OPCODE_F32_LE;
        case 0x60:
            return WEB49_OPCODE_F32_GE;
        case 0x61:
            return WEB49_OPCODE_F64_EQ;
        case 0x62:
            return WEB49_OPCODE_F64_NE;
        case 0x63:
            return WEB49_OPCODE_F64_LT;
        case 0x64:
            return WEB49_OPCODE_F64_GT;
        case 0x65:
            return WEB49_OPCODE_F64_LE;
        case 0x66:
            return WEB49_OPCODE_F64_GE;
        case 0x67:
            return WEB49_OPCODE_I32_CLZ;
        case 0x68:
            return WEB49_OPCODE_I32_CTZ;
        case 0x69:
            return WEB49_OPCODE_I32_POPCNT;
        case 0x6A:
            return WEB49_OPCODE_I32_ADD;
        case 0x6B:
            return WEB49_OPCODE_I32_SUB;
        case 0x6C:
            return WEB49_OPCODE_I32_MUL;
        case 0x6D:
            return WEB49_OPCODE_I32_DIV_S;
        case 0x6E:
            return WEB49_OPCODE_I32_DIV_U;
        case 0x6F:
            return WEB49_OPCODE_I32_REM_S;
        case 0x70:
            return WEB49_OPCODE_I32_REM_U;
        case 0x71:
            return WEB49_OPCODE_I32_AND;
        case 0x72:
            return WEB49_OPCODE_I32_OR;
        case 0x73:
            return WEB49_OPCODE_I32_XOR;
        case 0x74:
            return WEB49_OPCODE_I32_SHL;
        case 0x75:
            return WEB49_OPCODE_I32_SHR_S;
        case 0x76:
            return WEB49_OPCODE_I32_SHR_U;
        case 0x77:
            return WEB49_OPCODE_I32_ROTL;
        case 0x78:
            return WEB49_OPCODE_I32_ROTR;
        case 0x79:
            return WEB49_OPCODE_I64_CLZ;
        case 0x7A:
            return WEB49_OPCODE_I64_CTZ;
        case 0x7B:
            return WEB49_OPCODE_I64_POPCNT;
        case 0x7C:
            return WEB49_OPCODE_I64_ADD;
        case 0x7D:
            return WEB49_OPCODE_I64_SUB;
        case 0x7E:
            return WEB49_OPCODE_I64_MUL;
        case 0x7F:
            return WEB49_OPCODE_I64_DIV_S;
        case 0x80:
            return WEB49_OPCODE_I64_DIV_U;
        case 0x81:
            return WEB49_OPCODE_I64_REM_S;
        case 0x82:
            return WEB49_OPCODE_I64_REM_U;
        case 0x83:
            return WEB49_OPCODE_I64_AND;
        case 0x84:
            return WEB49_OPCODE_I64_OR;
        case 0x85:
            return WEB49_OPCODE_I64_XOR;
        case 0x86:
            return WEB49_OPCODE_I64_SHL;
        case 0x87:
            return WEB49_OPCODE_I64_SHR_S;
        case 0x88:
            return WEB49_OPCODE_I64_SHR_U;
        case 0x89:
            return WEB49_OPCODE_I64_ROTL;
        case 0x8A:
            return WEB49_OPCODE_I64_ROTR;
        case 0x8B:
            return WEB49_OPCODE_F32_ABS;
        case 0x8C:
            return WEB49_OPCODE_F32_NEG;
        case 0x8D:
            return WEB49_OPCODE_F32_CEIL;
        case 0x8E:
            return WEB49_OPCODE_F32_FLOOR;
        case 0x8F:
            return WEB49_OPCODE_F32_TRUNC;
        case 0x90:
            return WEB49_OPCODE_F32_NEAREST;
        case 0x91:
            return WEB49_OPCODE_F32_SQRT;
        case 0x92:
            return WEB49_OPCODE_F32_ADD;
        case 0x93:
            return WEB49_OPCODE_F32_SUB;
        case 0x94:
            return WEB49_OPCODE_F32_MUL;
        case 0x95:
            return WEB49_OPCODE_F32_DIV;
        case 0x96:
            return WEB49_OPCODE_F32_MIN;
        case 0x97:
            return WEB49_OPCODE_F32_MAX;
        case 0x98:
            return WEB49_OPCODE_F32_COPYSIGN;
        case 0x99:
            return WEB49_OPCODE_F64_ABS;
        case 0x9A:
            return WEB49_OPCODE_F64_NEG;
        case 0x9B:
            return WEB49_OPCODE_F64_CEIL;
        case 0x9C:
            return WEB49_OPCODE_F64_FLOOR;
        case 0x9D:
            return WEB49_OPCODE_F64_TRUNC;
        case 0x9E:
            return WEB49_OPCODE_F64_NEAREST;
        case 0x9F:
            return WEB49_OPCODE_F64_SQRT;
        case 0xA0:
            return WEB49_OPCODE_F64_ADD;
        case 0xA1:
            return WEB49_OPCODE_F64_SUB;
        case 0xA2:
            return WEB49_OPCODE_F64_MUL;
        case 0xA3:
            return WEB49_OPCODE_F64_DIV;
        case 0xA4:
            return WEB49_OPCODE_F64_MIN;
        case 0xA5:
            return WEB49_OPCODE_F64_MAX;
        case 0xA6:
            return WEB49_OPCODE_F64_COPYSIGN;
        case 0xA7:
            return WEB49_OPCODE_I32_WRAP_I64;
        case 0xA8:
            return WEB49_OPCODE_I32_TRUNC_S_F32;
        case 0xA9:
            return WEB49_OPCODE_I32_TRUNC_U_F32;
        case 0xAA:
            return WEB49_OPCODE_I32_TRUNC_S_F64;
        case 0xAB:
            return WEB49_OPCODE_I32_TRUNC_U_F64;
        case 0xAC:
            return WEB49_OPCODE_I64_EXTEND_S_I32;
        case 0xAD:
            return WEB49_OPCODE_I64_EXTEND_U_I32;
        case 0xAE:
            return WEB49_OPCODE_I64_TRUNC_S_F32;
        case 0xAF:
            return WEB49_OPCODE_I64_TRUNC_U_F32;
        case 0xB0:
            return WEB49_OPCODE_I64_TRUNC_S_F64;
        case 0xB1:
            return WEB49_OPCODE_I64_TRUNC_U_F64;
        case 0xB2:
            return WEB49_OPCODE_F32_CONVERT_S_I32;
        case 0xB3:
            return WEB49_OPCODE_F32_CONVERT_U_I32;
        case 0xB4:
            return WEB49_OPCODE_F32_CONVERT_S_I64;
        case 0xB5:
            return WEB49_OPCODE_F32_CONVERT_U_I64;
        case 0xB6:
            return WEB49_OPCODE_F32_DEMOTE_F64;
        case 0xB7:
            return WEB49_OPCODE_F64_CONVERT_S_I32;
        case 0xB8:
            return WEB49_OPCODE_F64_CONVERT_U_I32;
        case 0xB9:
            return WEB49_OPCODE_F64_CONVERT_S_I64;
        case 0xBA:
            return WEB49_OPCODE_F64_CONVERT_U_I64;
        case 0xBB:
            return WEB49_OPCODE_F64_PROMOTE_F32;
        case 0xBC:
            return WEB49_OPCODE_I32_REINTERPRET_F32;
        case 0xBD:
            return WEB49_OPCODE_I64_REINTERPRET_F64;
        case 0xBE:
            return WEB49_OPCODE_F32_REINTERPRET_I32;
        case 0xBF:
            return WEB49_OPCODE_F64_REINTERPRET_I64;
        case 0xC0:
            return WEB49_OPCODE_I32_EXTEND8_S;
        case 0xC1:
            return WEB49_OPCODE_I32_EXTEND16_S;
        case 0xC2:
            return WEB49_OPCODE_I64_EXTEND8_S;
        case 0xC3:
            return WEB49_OPCODE_I64_EXTEND16_S;
        case 0xC4:
            return WEB49_OPCODE_I64_EXTEND32_S;
        case 0xC5:
            web49_error("unknown opcode: staring with byte 0xC5\n");
        case 0xC6:
            web49_error("unknown opcode: staring with byte 0xC6\n");
        case 0xC7:
            web49_error("unknown opcode: staring with byte 0xC7\n");
        case 0xC8:
            web49_error("unknown opcode: staring with byte 0xC8\n");
        case 0xC9:
            web49_error("unknown opcode: staring with byte 0xC9\n");
        case 0xCA:
            web49_error("unknown opcode: staring with byte 0xCA\n");
        case 0xCB:
            web49_error("unknown opcode: staring with byte 0xCB\n");
        case 0xCC:
            web49_error("unknown opcode: staring with byte 0xCC\n");
        case 0xCD:
            web49_error("unknown opcode: staring with byte 0xCD\n");
        case 0xCE:
            web49_error("unknown opcode: staring with byte 0xCE\n");
        case 0xCF:
            web49_error("unknown opcode: staring with byte 0xCF\n");
        case 0xD0:
            web49_error("unknown opcode: staring with byte 0xD0\n");
        case 0xD1:
            return WEB49_OPCODE_REF_NULL;
        case 0xD2:
            return WEB49_OPCODE_REF_IS_NULL;
        case 0xD3:
            return WEB49_OPCODE_REF_FUNC;
        case 0xD4:
            web49_error("unknown opcode: staring with byte 0xD4\n");
        case 0xD5:
            web49_error("unknown opcode: staring with byte 0xD5\n");
        case 0xD6:
            web49_error("unknown opcode: staring with byte 0xD6\n");
        case 0xD7:
            web49_error("unknown opcode: staring with byte 0xD7\n");
        case 0xD8:
            web49_error("unknown opcode: staring with byte 0xD8\n");
        case 0xD9:
            web49_error("unknown opcode: staring with byte 0xD9\n");
        case 0xDA:
            web49_error("unknown opcode: staring with byte 0xDA\n");
        case 0xDB:
            web49_error("unknown opcode: staring with byte 0xDB\n");
        case 0xDC:
            web49_error("unknown opcode: staring with byte 0xDC\n");
        case 0xDD:
            web49_error("unknown opcode: staring with byte 0xDD\n");
        case 0xDE:
            web49_error("unknown opcode: staring with byte 0xDE\n");
        case 0xDF:
            web49_error("unknown opcode: staring with byte 0xDF\n");
        case 0xE0:
            web49_error("unknown opcode: staring with byte 0xE0\n");
        case 0xE1:
            web49_error("unknown opcode: staring with byte 0xE1\n");
        case 0xE2:
            web49_error("unknown opcode: staring with byte 0xE2\n");
        case 0xE3:
            web49_error("unknown opcode: staring with byte 0xE3\n");
        case 0xE4:
            web49_error("unknown opcode: staring with byte 0xE4\n");
        case 0xE5:
            web49_error("unknown opcode: staring with byte 0xE5\n");
        case 0xE6:
            web49_error("unknown opcode: staring with byte 0xE6\n");
        case 0xE7:
            web49_error("unknown opcode: staring with byte 0xE7\n");
        case 0xE8:
            web49_error("unknown opcode: staring with byte 0xE8\n");
        case 0xE9:
            web49_error("unknown opcode: staring with byte 0xE9\n");
        case 0xEA:
            web49_error("unknown opcode: staring with byte 0xEA\n");
        case 0xEB:
            web49_error("unknown opcode: staring with byte 0xEB\n");
        case 0xEC:
            web49_error("unknown opcode: staring with byte 0xEC\n");
        case 0xED:
            web49_error("unknown opcode: staring with byte 0xED\n");
        case 0xEE:
            web49_error("unknown opcode: staring with byte 0xEE\n");
        case 0xEF:
            web49_error("unknown opcode: staring with byte 0xEF\n");
        case 0xF0:
            web49_error("unknown opcode: staring with byte 0xF0\n");
        case 0xF1:
            web49_error("unknown opcode: staring with byte 0xF1\n");
        case 0xF2:
            web49_error("unknown opcode: staring with byte 0xF2\n");
        case 0xF3:
            web49_error("unknown opcode: staring with byte 0xF3\n");
        case 0xF4:
            web49_error("unknown opcode: staring with byte 0xF4\n");
        case 0xF5:
            web49_error("unknown opcode: staring with byte 0xF5\n");
        case 0xF6:
            web49_error("unknown opcode: staring with byte 0xF6\n");
        case 0xF7:
            web49_error("unknown opcode: staring with byte 0xF7\n");
        case 0xF8:
            web49_error("unknown opcode: staring with byte 0xF8 0x%02" PRIX8 "\n", bytes[1]);
        case 0xF9:
            web49_error("unknown opcode: staring with byte 0xF9\n");
        case 0xFA:
            web49_error("unknown opcode: staring with byte 0xFA\n");
        case 0xFB:
            switch (bytes[1]) {
                default:
                    web49_error("unknown gc/ref-strings sequence: 0xFB 0x%" PRIu8 "\n", bytes[1]);
            }
        case 0xFC:
            switch (bytes[1]) {
                case 0x00:
                    return WEB49_OPCODE_I32_TRUNC_SAT_F32_S;
                case 0x01:
                    return WEB49_OPCODE_I32_TRUNC_SAT_F32_U;
                case 0x02:
                    return WEB49_OPCODE_I32_TRUNC_SAT_F64_S;
                case 0x03:
                    return WEB49_OPCODE_I32_TRUNC_SAT_F64_U;
                case 0x04:
                    return WEB49_OPCODE_I64_TRUNC_SAT_F32_S;
                case 0x05:
                    return WEB49_OPCODE_I64_TRUNC_SAT_F32_U;
                case 0x06:
                    return WEB49_OPCODE_I64_TRUNC_SAT_F64_S;
                case 0x07:
                    return WEB49_OPCODE_I64_TRUNC_SAT_F64_U;
                case 0x08:
                    return WEB49_OPCODE_MEMORY_INIT;
                case 0x09:
                    return WEB49_OPCODE_DATA_DROP;
                case 0x0A:
                    return WEB49_OPCODE_MEMORY_COPY;
                case 0x0B:
                    return WEB49_OPCODE_MEMORY_FILL;
                case 0x0C:
                    return WEB49_OPCODE_TABLE_INIT;
                case 0x0D:
                    return WEB49_OPCODE_ELEM_DROP;
                case 0x0E:
                    return WEB49_OPCODE_TABLE_COPY;
                case 0x0F:
                    return WEB49_OPCODE_TABLE_GROW;
                case 0x10:
                    return WEB49_OPCODE_TABLE_SIZE;
                case 0x11:
                    return WEB49_OPCODE_TABLE_FILL;
                default:
                    web49_error("unknown opcode sequence: 0xFC 0x%" PRIu8 "\n", bytes[1]);
            }
        case 0xFD:
            // printf("0x%02" PRIX8 " 0x%02" PRIX8 " 0x%02" PRIX8 " = %zu\n", bytes[1], bytes[2], bytes[3], (size_t) (bytes[1] + (bytes[2] << 7) + (bytes[3] << 14)));
            switch (bytes[1] + (bytes[2] << 7) + (bytes[3] << 14)) {
                case 0x00:
                    return WEB49_OPCODE_V128_LOAD;
                case 0x01:
                    return WEB49_OPCODE_V128_LOAD8X8_S;
                case 0x02:
                    return WEB49_OPCODE_V128_LOAD8X8_U;
                case 0x03:
                    return WEB49_OPCODE_V128_LOAD16X4_S;
                case 0x04:
                    return WEB49_OPCODE_V128_LOAD16X4_U;
                case 0x05:
                    return WEB49_OPCODE_V128_LOAD32X2_S;
                case 0x06:
                    return WEB49_OPCODE_V128_LOAD32X2_U;
                case 0x07:
                    return WEB49_OPCODE_V128_LOAD8_SPLAT;
                case 0x08:
                    return WEB49_OPCODE_V128_LOAD16_SPLAT;
                case 0x09:
                    return WEB49_OPCODE_V128_LOAD32_SPLAT;
                case 0x0A:
                    return WEB49_OPCODE_V128_LOAD64_SPLAT;
                case 0x0B:
                    return WEB49_OPCODE_V128_STORE;
                case 0x0C:
                    return WEB49_OPCODE_V128_CONST;
                case 0x0D:
                    return WEB49_OPCODE_I8X16_SHUFFLE;
                case 0x0E:
                    return WEB49_OPCODE_I8X16_SWIZZLE;
                case 0x0F:
                    return WEB49_OPCODE_I8X16_SPLAT;
                case 0x10:
                    return WEB49_OPCODE_I16X8_SPLAT;
                case 0x11:
                    return WEB49_OPCODE_I32X4_SPLAT;
                case 0x12:
                    return WEB49_OPCODE_I64X2_SPLAT;
                case 0x13:
                    return WEB49_OPCODE_F32X4_SPLAT;
                case 0x14:
                    return WEB49_OPCODE_F64X2_SPLAT;
                case 0x15:
                    return WEB49_OPCODE_I8X16_EXTRACT_LANE_S;
                case 0x16:
                    return WEB49_OPCODE_I8X16_EXTRACT_LANE_U;
                case 0x17:
                    return WEB49_OPCODE_I8X16_REPLACE_LANE;
                case 0x18:
                    return WEB49_OPCODE_I16X8_EXTRACT_LANE_S;
                case 0x19:
                    return WEB49_OPCODE_I16X8_EXTRACT_LANE_U;
                case 0x1A:
                    return WEB49_OPCODE_I16X8_REPLACE_LANE;
                case 0x1B:
                    return WEB49_OPCODE_I32X4_EXTRACT_LANE;
                case 0x1C:
                    return WEB49_OPCODE_I32X4_REPLACE_LANE;
                case 0x1D:
                    return WEB49_OPCODE_I64X2_EXTRACT_LANE;
                case 0x1E:
                    return WEB49_OPCODE_I64X2_REPLACE_LANE;
                case 0x1F:
                    return WEB49_OPCODE_F32X4_EXTRACT_LANE;
                case 0x20:
                    return WEB49_OPCODE_F32X4_REPLACE_LANE;
                case 0x21:
                    return WEB49_OPCODE_F64X2_EXTRACT_LANE;
                case 0x22:
                    return WEB49_OPCODE_F64X2_REPLACE_LANE;
                case 0x23:
                    return WEB49_OPCODE_I8X16_EQ;
                case 0x24:
                    return WEB49_OPCODE_I8X16_NE;
                case 0x25:
                    return WEB49_OPCODE_I8X16_LT_S;
                case 0x26:
                    return WEB49_OPCODE_I8X16_LT_U;
                case 0x27:
                    return WEB49_OPCODE_I8X16_GT_S;
                case 0x28:
                    return WEB49_OPCODE_I8X16_GT_U;
                case 0x29:
                    return WEB49_OPCODE_I8X16_LE_S;
                case 0x2A:
                    return WEB49_OPCODE_I8X16_LE_U;
                case 0x2B:
                    return WEB49_OPCODE_I8X16_GE_S;
                case 0x2C:
                    return WEB49_OPCODE_I8X16_GE_U;
                case 0x2D:
                    return WEB49_OPCODE_I16X8_EQ;
                case 0x2E:
                    return WEB49_OPCODE_I16X8_NE;
                case 0x2F:
                    return WEB49_OPCODE_I16X8_LT_S;
                case 0x30:
                    return WEB49_OPCODE_I16X8_LT_U;
                case 0x31:
                    return WEB49_OPCODE_I16X8_GT_S;
                case 0x32:
                    return WEB49_OPCODE_I16X8_GT_U;
                case 0x33:
                    return WEB49_OPCODE_I16X8_LE_S;
                case 0x34:
                    return WEB49_OPCODE_I16X8_LE_U;
                case 0x35:
                    return WEB49_OPCODE_I16X8_GE_S;
                case 0x36:
                    return WEB49_OPCODE_I16X8_GE_U;
                case 0x37:
                    return WEB49_OPCODE_I32X4_EQ;
                case 0x38:
                    return WEB49_OPCODE_I32X4_NE;
                case 0x39:
                    return WEB49_OPCODE_I32X4_LT_S;
                case 0x3A:
                    return WEB49_OPCODE_I32X4_LT_U;
                case 0x3B:
                    return WEB49_OPCODE_I32X4_GT_S;
                case 0x3C:
                    return WEB49_OPCODE_I32X4_GT_U;
                case 0x3D:
                    return WEB49_OPCODE_I32X4_LE_S;
                case 0x3E:
                    return WEB49_OPCODE_I32X4_LE_U;
                case 0x3F:
                    return WEB49_OPCODE_I32X4_GE_S;
                case 0x40:
                    return WEB49_OPCODE_I32X4_GE_U;
                case 0x41:
                    return WEB49_OPCODE_F32X4_EQ;
                case 0x42:
                    return WEB49_OPCODE_F32X4_NE;
                case 0x43:
                    return WEB49_OPCODE_F32X4_LT;
                case 0x44:
                    return WEB49_OPCODE_F32X4_GT;
                case 0x45:
                    return WEB49_OPCODE_F32X4_LE;
                case 0x46:
                    return WEB49_OPCODE_F32X4_GE;
                case 0x47:
                    return WEB49_OPCODE_F64X2_EQ;
                case 0x48:
                    return WEB49_OPCODE_F64X2_NE;
                case 0x49:
                    return WEB49_OPCODE_F64X2_LT;
                case 0x4A:
                    return WEB49_OPCODE_F64X2_GT;
                case 0x4B:
                    return WEB49_OPCODE_F64X2_LE;
                case 0x4C:
                    return WEB49_OPCODE_F64X2_GE;
                case 0x4D:
                    return WEB49_OPCODE_V128_NOT;
                case 0x4E:
                    return WEB49_OPCODE_V128_AND;
                case 0x4F:
                    return WEB49_OPCODE_V128_ANDNOT;
                case 0x50:
                    return WEB49_OPCODE_V128_OR;
                case 0x51:
                    return WEB49_OPCODE_V128_XOR;
                case 0x52:
                    return WEB49_OPCODE_V128_BITSELECT;
                case 0x53:
                    return WEB49_OPCODE_V128_ANY_TRUE;
                case 0x54:
                    return WEB49_OPCODE_V128_LOAD8_LANE;
                case 0x55:
                    return WEB49_OPCODE_V128_LOAD16_LANE;
                case 0x56:
                    return WEB49_OPCODE_V128_LOAD32_LANE;
                case 0x57:
                    return WEB49_OPCODE_V128_LOAD64_LANE;
                case 0x58:
                    return WEB49_OPCODE_V128_STORE8_LANE;
                case 0x59:
                    return WEB49_OPCODE_V128_STORE16_LANE;
                case 0x5A:
                    return WEB49_OPCODE_V128_STORE32_LANE;
                case 0x5B:
                    return WEB49_OPCODE_V128_STORE64_LANE;
                case 0x5C:
                    return WEB49_OPCODE_V128_LOAD32_ZERO;
                case 0x5D:
                    return WEB49_OPCODE_V128_LOAD64_ZERO;
                case 0x5E:
                    return WEB49_OPCODE_F32X4_DEMOTE_F64X2_ZERO;
                case 0x5F:
                    return WEB49_OPCODE_F64X2_PROMOTE_LOW_F32X4;
                case 0x60:
                    return WEB49_OPCODE_I8X16_ABS;
                case 0x61:
                    return WEB49_OPCODE_I8X16_NEG;
                case 0x62:
                    return WEB49_OPCODE_I8X16_POPCNT;
                case 0x63:
                    return WEB49_OPCODE_I8X16_ALL_TRUE;
                case 0x64:
                    return WEB49_OPCODE_I8X16_BITMASK;
                case 0x65:
                    return WEB49_OPCODE_I8X16_NARROW_I16X8_S;
                case 0x66:
                    return WEB49_OPCODE_I8X16_NARROW_I16X8_U;
                case 0x67:
                    return WEB49_OPCODE_F32X4_CEIL;
                case 0x68:
                    return WEB49_OPCODE_F32X4_FLOOR;
                case 0x69:
                    return WEB49_OPCODE_F32X4_TRUNC;
                case 0x6A:
                    return WEB49_OPCODE_F32X4_NEAREST;
                case 0x6B:
                    return WEB49_OPCODE_I8X16_SHL;
                case 0x6C:
                    return WEB49_OPCODE_I8X16_SHR_S;
                case 0x6D:
                    return WEB49_OPCODE_I8X16_SHR_U;
                case 0x6E:
                    return WEB49_OPCODE_I8X16_ADD;
                case 0x6F:
                    return WEB49_OPCODE_I8X16_ADD_SAT_S;
                case 0x70:
                    return WEB49_OPCODE_I8X16_ADD_SAT_U;
                case 0x71:
                    return WEB49_OPCODE_I8X16_SUB;
                case 0x72:
                    return WEB49_OPCODE_I8X16_SUB_SAT_S;
                case 0x73:
                    return WEB49_OPCODE_I8X16_SUB_SAT_U;
                case 0x74:
                    return WEB49_OPCODE_F64X2_CEIL;
                case 0x75:
                    return WEB49_OPCODE_F64X2_FLOOR;
                case 0x76:
                    return WEB49_OPCODE_I8X16_MIN_S;
                case 0x77:
                    return WEB49_OPCODE_I8X16_MIN_U;
                case 0x78:
                    return WEB49_OPCODE_I8X16_MAX_S;
                case 0x79:
                    return WEB49_OPCODE_I8X16_MAX_U;
                case 0x7A:
                    return WEB49_OPCODE_F64X2_TRUNC;
                case 0x7B:
                    return WEB49_OPCODE_I8X16_AVGR_U;
                case 0x7C:
                    return WEB49_OPCODE_I16X8_EXTADD_PAIRWISE_I8X16_S;
                case 0x7D:
                    return WEB49_OPCODE_I16X8_EXTADD_PAIRWISE_I8X16_U;
                case 0x7E:
                    return WEB49_OPCODE_I32X4_EXTADD_PAIRWISE_I16X8_S;
                case 0x7F:
                    return WEB49_OPCODE_I32X4_EXTADD_PAIRWISE_I16X8_U;
                case 0x80:
                    return WEB49_OPCODE_I16X8_ABS;
                case 0x81:
                    return WEB49_OPCODE_I16X8_NEG;
                case 0x82:
                    return WEB49_OPCODE_I16X8_Q15MULR_SAT_S;
                case 0x83:
                    return WEB49_OPCODE_I16X8_ALL_TRUE;
                case 0x84:
                    return WEB49_OPCODE_I16X8_BITMASK;
                case 0x85:
                    return WEB49_OPCODE_I16X8_NARROW_I32X4_S;
                case 0x86:
                    return WEB49_OPCODE_I16X8_NARROW_I32X4_U;
                case 0x87:
                    return WEB49_OPCODE_I16X8_EXTEND_LOW_I8X16_S;
                case 0x88:
                    return WEB49_OPCODE_I16X8_EXTEND_HIGH_I8X16_S;
                case 0x89:
                    return WEB49_OPCODE_I16X8_EXTEND_LOW_I8X16_U;
                case 0x8A:
                    return WEB49_OPCODE_I16X8_EXTEND_HIGH_I8X16_U;
                case 0x8B:
                    return WEB49_OPCODE_I16X8_SHL;
                case 0x8C:
                    return WEB49_OPCODE_I16X8_SHR_S;
                case 0x8D:
                    return WEB49_OPCODE_I16X8_SHR_U;
                case 0x8E:
                    return WEB49_OPCODE_I16X8_ADD;
                case 0x8F:
                    return WEB49_OPCODE_I16X8_ADD_SAT_S;
                case 0x90:
                    return WEB49_OPCODE_I16X8_ADD_SAT_U;
                case 0x91:
                    return WEB49_OPCODE_I16X8_SUB;
                case 0x92:
                    return WEB49_OPCODE_I16X8_SUB_SAT_S;
                case 0x93:
                    return WEB49_OPCODE_I16X8_SUB_SAT_U;
                case 0x94:
                    return WEB49_OPCODE_F64X2_NEAREST;
                case 0x95:
                    return WEB49_OPCODE_I16X8_MUL;
                case 0x96:
                    return WEB49_OPCODE_I16X8_MIN_S;
                case 0x97:
                    return WEB49_OPCODE_I16X8_MIN_U;
                case 0x98:
                    return WEB49_OPCODE_I16X8_MAX_S;
                case 0x99:
                    return WEB49_OPCODE_I16X8_MAX_U;
                case 0x9B:
                    return WEB49_OPCODE_I16X8_AVGR_U;
                case 0x9C:
                    return WEB49_OPCODE_I16X8_EXTMUL_LOW_I8X16_S;
                case 0x9D:
                    return WEB49_OPCODE_I16X8_EXTMUL_HIGH_I8X16_S;
                case 0x9E:
                    return WEB49_OPCODE_I16X8_EXTMUL_LOW_I8X16_U;
                case 0x9F:
                    return WEB49_OPCODE_I16X8_EXTMUL_HIGH_I8X16_U;
                case 0xA0:
                    return WEB49_OPCODE_I32X4_ABS;
                case 0xA1:
                    return WEB49_OPCODE_I32X4_NEG;
                case 0xA3:
                    return WEB49_OPCODE_I32X4_ALL_TRUE;
                case 0xA4:
                    return WEB49_OPCODE_I32X4_BITMASK;
                case 0xA7:
                    return WEB49_OPCODE_I32X4_EXTEND_LOW_I16X8_S;
                case 0xA8:
                    return WEB49_OPCODE_I32X4_EXTEND_HIGH_I16X8_S;
                case 0xA9:
                    return WEB49_OPCODE_I32X4_EXTEND_LOW_I16X8_U;
                case 0xAA:
                    return WEB49_OPCODE_I32X4_EXTEND_HIGH_I16X8_U;
                case 0xAB:
                    return WEB49_OPCODE_I32X4_SHL;
                case 0xAC:
                    return WEB49_OPCODE_I32X4_SHR_S;
                case 0xAD:
                    return WEB49_OPCODE_I32X4_SHR_U;
                case 0xAE:
                    return WEB49_OPCODE_I32X4_ADD;
                case 0xB1:
                    return WEB49_OPCODE_I32X4_SUB;
                case 0xB5:
                    return WEB49_OPCODE_I32X4_MUL;
                case 0xB6:
                    return WEB49_OPCODE_I32X4_MIN_S;
                case 0xB7:
                    return WEB49_OPCODE_I32X4_MIN_U;
                case 0xB8:
                    return WEB49_OPCODE_I32X4_MAX_S;
                case 0xB9:
                    return WEB49_OPCODE_I32X4_MAX_U;
                case 0xBA:
                    return WEB49_OPCODE_I32X4_DOT_I16X8_S;
                case 0xBC:
                    return WEB49_OPCODE_I32X4_EXTMUL_LOW_I16X8_S;
                case 0xBD:
                    return WEB49_OPCODE_I32X4_EXTMUL_HIGH_I16X8_S;
                case 0xBE:
                    return WEB49_OPCODE_I32X4_EXTMUL_LOW_I16X8_U;
                case 0xBF:
                    return WEB49_OPCODE_I32X4_EXTMUL_HIGH_I16X8_U;
                case 0xC0:
                    return WEB49_OPCODE_I64X2_ABS;
                case 0xC1:
                    return WEB49_OPCODE_I64X2_NEG;
                case 0xC3:
                    return WEB49_OPCODE_I64X2_ALL_TRUE;
                case 0xC4:
                    return WEB49_OPCODE_I64X2_BITMASK;
                case 0xC7:
                    return WEB49_OPCODE_I64X2_EXTEND_LOW_I32X4_S;
                case 0xC8:
                    return WEB49_OPCODE_I64X2_EXTEND_HIGH_I32X4_S;
                case 0xC9:
                    return WEB49_OPCODE_I64X2_EXTEND_LOW_I32X4_U;
                case 0xCA:
                    return WEB49_OPCODE_I64X2_EXTEND_HIGH_I32X4_U;
                case 0xCB:
                    return WEB49_OPCODE_I64X2_SHL;
                case 0xCC:
                    return WEB49_OPCODE_I64X2_SHR_S;
                case 0xCD:
                    return WEB49_OPCODE_I64X2_SHR_U;
                case 0xCE:
                    return WEB49_OPCODE_I64X2_ADD;
                case 0xD1:
                    return WEB49_OPCODE_I64X2_SUB;
                case 0xD5:
                    return WEB49_OPCODE_I64X2_MUL;
                case 0xD6:
                    return WEB49_OPCODE_I64X2_EQ;
                case 0xD7:
                    return WEB49_OPCODE_I64X2_NE;
                case 0xD8:
                    return WEB49_OPCODE_I64X2_LT_S;
                case 0xD9:
                    return WEB49_OPCODE_I64X2_GT_S;
                case 0xDA:
                    return WEB49_OPCODE_I64X2_LE_S;
                case 0xDB:
                    return WEB49_OPCODE_I64X2_GE_S;
                case 0xDC:
                    return WEB49_OPCODE_I64X2_EXTMUL_LOW_I32X4_S;
                case 0xDD:
                    return WEB49_OPCODE_I64X2_EXTMUL_HIGH_I32X4_S;
                case 0xDE:
                    return WEB49_OPCODE_I64X2_EXTMUL_LOW_I32X4_U;
                case 0xDF:
                    return WEB49_OPCODE_I64X2_EXTMUL_HIGH_I32X4_U;
                case 0xE0:
                    return WEB49_OPCODE_F32X4_ABS;
                case 0xE1:
                    return WEB49_OPCODE_F32X4_NEG;
                case 0xE3:
                    return WEB49_OPCODE_F32X4_SQRT;
                case 0xE4:
                    return WEB49_OPCODE_F32X4_ADD;
                case 0xE5:
                    return WEB49_OPCODE_F32X4_SUB;
                case 0xE6:
                    return WEB49_OPCODE_F32X4_MUL;
                case 0xE7:
                    return WEB49_OPCODE_F32X4_DIV;
                case 0xE8:
                    return WEB49_OPCODE_F32X4_MIN;
                case 0xE9:
                    return WEB49_OPCODE_F32X4_MAX;
                case 0xEA:
                    return WEB49_OPCODE_F32X4_PMIN;
                case 0xEB:
                    return WEB49_OPCODE_F32X4_PMAX;
                case 0xEC:
                    return WEB49_OPCODE_F64X2_ABS;
                case 0xED:
                    return WEB49_OPCODE_F64X2_NEG;
                case 0xEF:
                    return WEB49_OPCODE_F64X2_SQRT;
                case 0xF0:
                    return WEB49_OPCODE_F64X2_ADD;
                case 0xF1:
                    return WEB49_OPCODE_F64X2_SUB;
                case 0xF2:
                    return WEB49_OPCODE_F64X2_MUL;
                case 0xF3:
                    return WEB49_OPCODE_F64X2_DIV;
                case 0xF4:
                    return WEB49_OPCODE_F64X2_MIN;
                case 0xF5:
                    return WEB49_OPCODE_F64X2_MAX;
                case 0xF6:
                    return WEB49_OPCODE_F64X2_PMIN;
                case 0xF7:
                    return WEB49_OPCODE_F64X2_PMAX;
                case 0xF8:
                    return WEB49_OPCODE_I32X4_TRUNC_SAT_F32X4_S;
                case 0xF9:
                    return WEB49_OPCODE_I32X4_TRUNC_SAT_F32X4_U;
                case 0xFA:
                    return WEB49_OPCODE_F32X4_CONVERT_I32X4_S;
                case 0xFB:
                    return WEB49_OPCODE_F32X4_CONVERT_I32X4_U;
                case 0xFC:
                    return WEB49_OPCODE_I32X4_TRUNC_SAT_F64X2_S_ZERO;
                case 0xFD:
                    return WEB49_OPCODE_I32X4_TRUNC_SAT_F64X2_U_ZERO;
                case 0xFE:
                    return WEB49_OPCODE_F64X2_CONVERT_LOW_I32X4_S;
                case 0xFF:
                    return WEB49_OPCODE_F64X2_CONVERT_LOW_I32X4_U;
                default:
                    web49_error("unknown simd sequence: 0xFD 0x%02" PRIX8 "\n", bytes[1]);
            }
        case 0xFE:
            switch (bytes[1]) {
                default:
                    web49_error("unknown threads sequence: 0xFE 0x%02" PRIX8 "\n", bytes[1]);
            }
        case 0xFF:
            web49_error("unknown opcode: staring with byte 0xFF\n");
    }
    __builtin_trap();
}

void web49_opcode_to_bytes(web49_opcode_t opcode, size_t *len, uint8_t *buf) {
    switch (opcode) {
        case WEB49_OPCODE_UNREACHABLE:
            buf[(*len)++] = 0x00;
            break;
        case WEB49_OPCODE_NOP:
            buf[(*len)++] = 0x01;
            break;
        case WEB49_OPCODE_BLOCK:
            buf[(*len)++] = 0x02;
            break;
        case WEB49_OPCODE_LOOP:
            buf[(*len)++] = 0x03;
            break;
        case WEB49_OPCODE_IF:
            buf[(*len)++] = 0x04;
            break;
        case WEB49_OPCODE_ELSE:
            buf[(*len)++] = 0x05;
            break;
        case WEB49_OPCODE_END:
            buf[(*len)++] = 0x0B;
            break;
        case WEB49_OPCODE_BR:
            buf[(*len)++] = 0x0C;
            break;
        case WEB49_OPCODE_BR_IF:
            buf[(*len)++] = 0x0D;
            break;
        case WEB49_OPCODE_BR_TABLE:
            buf[(*len)++] = 0x0E;
            break;
        case WEB49_OPCODE_RETURN:
            buf[(*len)++] = 0x0F;
            break;
        case WEB49_OPCODE_CALL:
            buf[(*len)++] = 0x10;
            break;
        case WEB49_OPCODE_CALL_INDIRECT:
            buf[(*len)++] = 0x11;
            break;
        case WEB49_OPCODE_DROP:
            buf[(*len)++] = 0x1A;
            break;
        case WEB49_OPCODE_SELECT:
            buf[(*len)++] = 0x1B;
            break;
        case WEB49_OPCODE_GET_LOCAL:
            buf[(*len)++] = 0x20;
            break;
        case WEB49_OPCODE_SET_LOCAL:
            buf[(*len)++] = 0x21;
            break;
        case WEB49_OPCODE_TEE_LOCAL:
            buf[(*len)++] = 0x22;
            break;
        case WEB49_OPCODE_GET_GLOBAL:
            buf[(*len)++] = 0x23;
            break;
        case WEB49_OPCODE_SET_GLOBAL:
            buf[(*len)++] = 0x24;
            break;
        case WEB49_OPCODE_I32_LOAD:
            buf[(*len)++] = 0x28;
            break;
        case WEB49_OPCODE_I64_LOAD:
            buf[(*len)++] = 0x29;
            break;
        case WEB49_OPCODE_F32_LOAD:
            buf[(*len)++] = 0x2A;
            break;
        case WEB49_OPCODE_F64_LOAD:
            buf[(*len)++] = 0x2B;
            break;
        case WEB49_OPCODE_I32_LOAD8_S:
            buf[(*len)++] = 0x2C;
            break;
        case WEB49_OPCODE_I32_LOAD8_U:
            buf[(*len)++] = 0x2D;
            break;
        case WEB49_OPCODE_I32_LOAD16_S:
            buf[(*len)++] = 0x2E;
            break;
        case WEB49_OPCODE_I32_LOAD16_U:
            buf[(*len)++] = 0x2F;
            break;
        case WEB49_OPCODE_I64_LOAD8_S:
            buf[(*len)++] = 0x30;
            break;
        case WEB49_OPCODE_I64_LOAD8_U:
            buf[(*len)++] = 0x31;
            break;
        case WEB49_OPCODE_I64_LOAD16_S:
            buf[(*len)++] = 0x32;
            break;
        case WEB49_OPCODE_I64_LOAD16_U:
            buf[(*len)++] = 0x33;
            break;
        case WEB49_OPCODE_I64_LOAD32_S:
            buf[(*len)++] = 0x34;
            break;
        case WEB49_OPCODE_I64_LOAD32_U:
            buf[(*len)++] = 0x35;
            break;
        case WEB49_OPCODE_I32_STORE:
            buf[(*len)++] = 0x36;
            break;
        case WEB49_OPCODE_I64_STORE:
            buf[(*len)++] = 0x37;
            break;
        case WEB49_OPCODE_F32_STORE:
            buf[(*len)++] = 0x38;
            break;
        case WEB49_OPCODE_F64_STORE:
            buf[(*len)++] = 0x39;
            break;
        case WEB49_OPCODE_I32_STORE8:
            buf[(*len)++] = 0x3A;
            break;
        case WEB49_OPCODE_I32_STORE16:
            buf[(*len)++] = 0x3B;
            break;
        case WEB49_OPCODE_I64_STORE8:
            buf[(*len)++] = 0x3C;
            break;
        case WEB49_OPCODE_I64_STORE16:
            buf[(*len)++] = 0x3D;
            break;
        case WEB49_OPCODE_I64_STORE32:
            buf[(*len)++] = 0x3E;
            break;
        case WEB49_OPCODE_MEMORY_SIZE:
            buf[(*len)++] = 0x3F;
            break;
        case WEB49_OPCODE_MEMORY_GROW:
            buf[(*len)++] = 0x40;
            break;
        case WEB49_OPCODE_I32_CONST:
            buf[(*len)++] = 0x41;
            break;
        case WEB49_OPCODE_I64_CONST:
            buf[(*len)++] = 0x42;
            break;
        case WEB49_OPCODE_F32_CONST:
            buf[(*len)++] = 0x43;
            break;
        case WEB49_OPCODE_F64_CONST:
            buf[(*len)++] = 0x44;
            break;
        case WEB49_OPCODE_I32_EQZ:
            buf[(*len)++] = 0x45;
            break;
        case WEB49_OPCODE_I32_EQ:
            buf[(*len)++] = 0x46;
            break;
        case WEB49_OPCODE_I32_NE:
            buf[(*len)++] = 0x47;
            break;
        case WEB49_OPCODE_I32_LT_S:
            buf[(*len)++] = 0x48;
            break;
        case WEB49_OPCODE_I32_LT_U:
            buf[(*len)++] = 0x49;
            break;
        case WEB49_OPCODE_I32_GT_S:
            buf[(*len)++] = 0x4A;
            break;
        case WEB49_OPCODE_I32_GT_U:
            buf[(*len)++] = 0x4B;
            break;
        case WEB49_OPCODE_I32_LE_S:
            buf[(*len)++] = 0x4C;
            break;
        case WEB49_OPCODE_I32_LE_U:
            buf[(*len)++] = 0x4D;
            break;
        case WEB49_OPCODE_I32_GE_S:
            buf[(*len)++] = 0x4E;
            break;
        case WEB49_OPCODE_I32_GE_U:
            buf[(*len)++] = 0x4F;
            break;
        case WEB49_OPCODE_I64_EQZ:
            buf[(*len)++] = 0x50;
            break;
        case WEB49_OPCODE_I64_EQ:
            buf[(*len)++] = 0x51;
            break;
        case WEB49_OPCODE_I64_NE:
            buf[(*len)++] = 0x52;
            break;
        case WEB49_OPCODE_I64_LT_S:
            buf[(*len)++] = 0x53;
            break;
        case WEB49_OPCODE_I64_LT_U:
            buf[(*len)++] = 0x54;
            break;
        case WEB49_OPCODE_I64_GT_S:
            buf[(*len)++] = 0x55;
            break;
        case WEB49_OPCODE_I64_GT_U:
            buf[(*len)++] = 0x56;
            break;
        case WEB49_OPCODE_I64_LE_S:
            buf[(*len)++] = 0x57;
            break;
        case WEB49_OPCODE_I64_LE_U:
            buf[(*len)++] = 0x58;
            break;
        case WEB49_OPCODE_I64_GE_S:
            buf[(*len)++] = 0x59;
            break;
        case WEB49_OPCODE_I64_GE_U:
            buf[(*len)++] = 0x5A;
            break;
        case WEB49_OPCODE_F32_EQ:
            buf[(*len)++] = 0x5B;
            break;
        case WEB49_OPCODE_F32_NE:
            buf[(*len)++] = 0x5C;
            break;
        case WEB49_OPCODE_F32_LT:
            buf[(*len)++] = 0x5D;
            break;
        case WEB49_OPCODE_F32_GT:
            buf[(*len)++] = 0x5E;
            break;
        case WEB49_OPCODE_F32_LE:
            buf[(*len)++] = 0x5F;
            break;
        case WEB49_OPCODE_F32_GE:
            buf[(*len)++] = 0x60;
            break;
        case WEB49_OPCODE_F64_EQ:
            buf[(*len)++] = 0x61;
            break;
        case WEB49_OPCODE_F64_NE:
            buf[(*len)++] = 0x62;
            break;
        case WEB49_OPCODE_F64_LT:
            buf[(*len)++] = 0x63;
            break;
        case WEB49_OPCODE_F64_GT:
            buf[(*len)++] = 0x64;
            break;
        case WEB49_OPCODE_F64_LE:
            buf[(*len)++] = 0x65;
            break;
        case WEB49_OPCODE_F64_GE:
            buf[(*len)++] = 0x66;
            break;
        case WEB49_OPCODE_I32_CLZ:
            buf[(*len)++] = 0x67;
            break;
        case WEB49_OPCODE_I32_CTZ:
            buf[(*len)++] = 0x68;
            break;
        case WEB49_OPCODE_I32_POPCNT:
            buf[(*len)++] = 0x69;
            break;
        case WEB49_OPCODE_I32_ADD:
            buf[(*len)++] = 0x6A;
            break;
        case WEB49_OPCODE_I32_SUB:
            buf[(*len)++] = 0x6B;
            break;
        case WEB49_OPCODE_I32_MUL:
            buf[(*len)++] = 0x6C;
            break;
        case WEB49_OPCODE_I32_DIV_S:
            buf[(*len)++] = 0x6D;
            break;
        case WEB49_OPCODE_I32_DIV_U:
            buf[(*len)++] = 0x6E;
            break;
        case WEB49_OPCODE_I32_REM_S:
            buf[(*len)++] = 0x6F;
            break;
        case WEB49_OPCODE_I32_REM_U:
            buf[(*len)++] = 0x70;
            break;
        case WEB49_OPCODE_I32_AND:
            buf[(*len)++] = 0x71;
            break;
        case WEB49_OPCODE_I32_OR:
            buf[(*len)++] = 0x72;
            break;
        case WEB49_OPCODE_I32_XOR:
            buf[(*len)++] = 0x73;
            break;
        case WEB49_OPCODE_I32_SHL:
            buf[(*len)++] = 0x74;
            break;
        case WEB49_OPCODE_I32_SHR_S:
            buf[(*len)++] = 0x75;
            break;
        case WEB49_OPCODE_I32_SHR_U:
            buf[(*len)++] = 0x76;
            break;
        case WEB49_OPCODE_I32_ROTL:
            buf[(*len)++] = 0x77;
            break;
        case WEB49_OPCODE_I32_ROTR:
            buf[(*len)++] = 0x78;
            break;
        case WEB49_OPCODE_I64_CLZ:
            buf[(*len)++] = 0x79;
            break;
        case WEB49_OPCODE_I64_CTZ:
            buf[(*len)++] = 0x7A;
            break;
        case WEB49_OPCODE_I64_POPCNT:
            buf[(*len)++] = 0x7B;
            break;
        case WEB49_OPCODE_I64_ADD:
            buf[(*len)++] = 0x7C;
            break;
        case WEB49_OPCODE_I64_SUB:
            buf[(*len)++] = 0x7D;
            break;
        case WEB49_OPCODE_I64_MUL:
            buf[(*len)++] = 0x7E;
            break;
        case WEB49_OPCODE_I64_DIV_S:
            buf[(*len)++] = 0x7F;
            break;
        case WEB49_OPCODE_I64_DIV_U:
            buf[(*len)++] = 0x80;
            break;
        case WEB49_OPCODE_I64_REM_S:
            buf[(*len)++] = 0x81;
            break;
        case WEB49_OPCODE_I64_REM_U:
            buf[(*len)++] = 0x82;
            break;
        case WEB49_OPCODE_I64_AND:
            buf[(*len)++] = 0x83;
            break;
        case WEB49_OPCODE_I64_OR:
            buf[(*len)++] = 0x84;
            break;
        case WEB49_OPCODE_I64_XOR:
            buf[(*len)++] = 0x85;
            break;
        case WEB49_OPCODE_I64_SHL:
            buf[(*len)++] = 0x86;
            break;
        case WEB49_OPCODE_I64_SHR_S:
            buf[(*len)++] = 0x87;
            break;
        case WEB49_OPCODE_I64_SHR_U:
            buf[(*len)++] = 0x88;
            break;
        case WEB49_OPCODE_I64_ROTL:
            buf[(*len)++] = 0x89;
            break;
        case WEB49_OPCODE_I64_ROTR:
            buf[(*len)++] = 0x8A;
            break;
        case WEB49_OPCODE_F32_ABS:
            buf[(*len)++] = 0x8B;
            break;
        case WEB49_OPCODE_F32_NEG:
            buf[(*len)++] = 0x8C;
            break;
        case WEB49_OPCODE_F32_CEIL:
            buf[(*len)++] = 0x8D;
            break;
        case WEB49_OPCODE_F32_FLOOR:
            buf[(*len)++] = 0x8E;
            break;
        case WEB49_OPCODE_F32_TRUNC:
            buf[(*len)++] = 0x8F;
            break;
        case WEB49_OPCODE_F32_NEAREST:
            buf[(*len)++] = 0x90;
            break;
        case WEB49_OPCODE_F32_SQRT:
            buf[(*len)++] = 0x91;
            break;
        case WEB49_OPCODE_F32_ADD:
            buf[(*len)++] = 0x92;
            break;
        case WEB49_OPCODE_F32_SUB:
            buf[(*len)++] = 0x93;
            break;
        case WEB49_OPCODE_F32_MUL:
            buf[(*len)++] = 0x94;
            break;
        case WEB49_OPCODE_F32_DIV:
            buf[(*len)++] = 0x95;
            break;
        case WEB49_OPCODE_F32_MIN:
            buf[(*len)++] = 0x96;
            break;
        case WEB49_OPCODE_F32_MAX:
            buf[(*len)++] = 0x97;
            break;
        case WEB49_OPCODE_F32_COPYSIGN:
            buf[(*len)++] = 0x98;
            break;
        case WEB49_OPCODE_F64_ABS:
            buf[(*len)++] = 0x99;
            break;
        case WEB49_OPCODE_F64_NEG:
            buf[(*len)++] = 0x9A;
            break;
        case WEB49_OPCODE_F64_CEIL:
            buf[(*len)++] = 0x9B;
            break;
        case WEB49_OPCODE_F64_FLOOR:
            buf[(*len)++] = 0x9C;
            break;
        case WEB49_OPCODE_F64_TRUNC:
            buf[(*len)++] = 0x9D;
            break;
        case WEB49_OPCODE_F64_NEAREST:
            buf[(*len)++] = 0x9E;
            break;
        case WEB49_OPCODE_F64_SQRT:
            buf[(*len)++] = 0x9F;
            break;
        case WEB49_OPCODE_F64_ADD:
            buf[(*len)++] = 0xA0;
            break;
        case WEB49_OPCODE_F64_SUB:
            buf[(*len)++] = 0xA1;
            break;
        case WEB49_OPCODE_F64_MUL:
            buf[(*len)++] = 0xA2;
            break;
        case WEB49_OPCODE_F64_DIV:
            buf[(*len)++] = 0xA3;
            break;
        case WEB49_OPCODE_F64_MIN:
            buf[(*len)++] = 0xA4;
            break;
        case WEB49_OPCODE_F64_MAX:
            buf[(*len)++] = 0xA5;
            break;
        case WEB49_OPCODE_F64_COPYSIGN:
            buf[(*len)++] = 0xA6;
            break;
        case WEB49_OPCODE_I32_WRAP_I64:
            buf[(*len)++] = 0xA7;
            break;
        case WEB49_OPCODE_I32_TRUNC_S_F32:
            buf[(*len)++] = 0xA8;
            break;
        case WEB49_OPCODE_I32_TRUNC_U_F32:
            buf[(*len)++] = 0xA9;
            break;
        case WEB49_OPCODE_I32_TRUNC_S_F64:
            buf[(*len)++] = 0xAA;
            break;
        case WEB49_OPCODE_I32_TRUNC_U_F64:
            buf[(*len)++] = 0xAB;
            break;
        case WEB49_OPCODE_I64_EXTEND_S_I32:
            buf[(*len)++] = 0xAC;
            break;
        case WEB49_OPCODE_I64_EXTEND_U_I32:
            buf[(*len)++] = 0xAD;
            break;
        case WEB49_OPCODE_I64_TRUNC_S_F32:
            buf[(*len)++] = 0xAE;
            break;
        case WEB49_OPCODE_I64_TRUNC_U_F32:
            buf[(*len)++] = 0xAF;
            break;
        case WEB49_OPCODE_I64_TRUNC_S_F64:
            buf[(*len)++] = 0xB0;
            break;
        case WEB49_OPCODE_I64_TRUNC_U_F64:
            buf[(*len)++] = 0xB1;
            break;
        case WEB49_OPCODE_F32_CONVERT_S_I32:
            buf[(*len)++] = 0xB2;
            break;
        case WEB49_OPCODE_F32_CONVERT_U_I32:
            buf[(*len)++] = 0xB3;
            break;
        case WEB49_OPCODE_F32_CONVERT_S_I64:
            buf[(*len)++] = 0xB4;
            break;
        case WEB49_OPCODE_F32_CONVERT_U_I64:
            buf[(*len)++] = 0xB5;
            break;
        case WEB49_OPCODE_F32_DEMOTE_F64:
            buf[(*len)++] = 0xB6;
            break;
        case WEB49_OPCODE_F64_CONVERT_S_I32:
            buf[(*len)++] = 0xB7;
            break;
        case WEB49_OPCODE_F64_CONVERT_U_I32:
            buf[(*len)++] = 0xB8;
            break;
        case WEB49_OPCODE_F64_CONVERT_S_I64:
            buf[(*len)++] = 0xB9;
            break;
        case WEB49_OPCODE_F64_CONVERT_U_I64:
            buf[(*len)++] = 0xBA;
            break;
        case WEB49_OPCODE_F64_PROMOTE_F32:
            buf[(*len)++] = 0xBB;
            break;
        case WEB49_OPCODE_I32_REINTERPRET_F32:
            buf[(*len)++] = 0xBC;
            break;
        case WEB49_OPCODE_I64_REINTERPRET_F64:
            buf[(*len)++] = 0xBD;
            break;
        case WEB49_OPCODE_F32_REINTERPRET_I32:
            buf[(*len)++] = 0xBE;
            break;
        case WEB49_OPCODE_F64_REINTERPRET_I64:
            buf[(*len)++] = 0xBF;
            break;
        case WEB49_OPCODE_I32_EXTEND8_S:
            buf[(*len)++] = 0xC0;
            break;
        case WEB49_OPCODE_I32_EXTEND16_S:
            buf[(*len)++] = 0xC1;
            break;
        case WEB49_OPCODE_I64_EXTEND8_S:
            buf[(*len)++] = 0xC2;
            break;
        case WEB49_OPCODE_I64_EXTEND16_S:
            buf[(*len)++] = 0xC3;
            break;
        case WEB49_OPCODE_I64_EXTEND32_S:
            buf[(*len)++] = 0xC4;
            break;
        case WEB49_OPCODE_I32_TRUNC_SAT_F32_S:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x00;
            break;
        case WEB49_OPCODE_I32_TRUNC_SAT_F32_U:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x01;
            break;
        case WEB49_OPCODE_I32_TRUNC_SAT_F64_S:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x02;
            break;
        case WEB49_OPCODE_I32_TRUNC_SAT_F64_U:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x03;
            break;
        case WEB49_OPCODE_I64_TRUNC_SAT_F32_S:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x04;
            break;
        case WEB49_OPCODE_I64_TRUNC_SAT_F32_U:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x05;
            break;
        case WEB49_OPCODE_I64_TRUNC_SAT_F64_S:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x06;
            break;
        case WEB49_OPCODE_I64_TRUNC_SAT_F64_U:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x07;
            break;
        case WEB49_OPCODE_MEMORY_INIT:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x08;
            break;
        case WEB49_OPCODE_DATA_DROP:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x09;
            break;
        case WEB49_OPCODE_MEMORY_COPY:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x0A;
            break;
        case WEB49_OPCODE_MEMORY_FILL:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x0B;
            break;
        case WEB49_OPCODE_TABLE_INIT:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x0C;
            break;
        case WEB49_OPCODE_ELEM_DROP:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x0D;
            break;
        case WEB49_OPCODE_TABLE_COPY:
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x0E;
            break;

        case WEB49_OPCODE_V128_LOAD: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x00;
            break;
        }
        case WEB49_OPCODE_V128_LOAD8X8_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_V128_LOAD8X8_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x02;
            break;
        }
        case WEB49_OPCODE_V128_LOAD16X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x03;
            break;
        }
        case WEB49_OPCODE_V128_LOAD16X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x04;
            break;
        }
        case WEB49_OPCODE_V128_LOAD32X2_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x05;
            break;
        }
        case WEB49_OPCODE_V128_LOAD32X2_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x06;
            break;
        }
        case WEB49_OPCODE_V128_LOAD8_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x07;
            break;
        }
        case WEB49_OPCODE_V128_LOAD16_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x08;
            break;
        }
        case WEB49_OPCODE_V128_LOAD32_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x09;
            break;
        }
        case WEB49_OPCODE_V128_LOAD64_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x0A;
            break;
        }
        case WEB49_OPCODE_V128_STORE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x0B;
            break;
        }
        case WEB49_OPCODE_V128_CONST: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x0C;
            break;
        }
        case WEB49_OPCODE_I8X16_SHUFFLE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x0D;
            break;
        }
        case WEB49_OPCODE_I8X16_SWIZZLE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x0E;
            break;
        }
        case WEB49_OPCODE_I8X16_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x0F;
            break;
        }
        case WEB49_OPCODE_I16X8_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x10;
            break;
        }
        case WEB49_OPCODE_I32X4_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x11;
            break;
        }
        case WEB49_OPCODE_I64X2_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x12;
            break;
        }
        case WEB49_OPCODE_F32X4_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x13;
            break;
        }
        case WEB49_OPCODE_F64X2_SPLAT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x14;
            break;
        }
        case WEB49_OPCODE_I8X16_EXTRACT_LANE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x15;
            break;
        }
        case WEB49_OPCODE_I8X16_EXTRACT_LANE_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x16;
            break;
        }
        case WEB49_OPCODE_I8X16_REPLACE_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x17;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTRACT_LANE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x18;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTRACT_LANE_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x19;
            break;
        }
        case WEB49_OPCODE_I16X8_REPLACE_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x1A;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTRACT_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x1B;
            break;
        }
        case WEB49_OPCODE_I32X4_REPLACE_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x1C;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTRACT_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x1D;
            break;
        }
        case WEB49_OPCODE_I64X2_REPLACE_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x1E;
            break;
        }
        case WEB49_OPCODE_F32X4_EXTRACT_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x1F;
            break;
        }
        case WEB49_OPCODE_F32X4_REPLACE_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x20;
            break;
        }
        case WEB49_OPCODE_F64X2_EXTRACT_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x21;
            break;
        }
        case WEB49_OPCODE_F64X2_REPLACE_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x22;
            break;
        }
        case WEB49_OPCODE_I8X16_EQ: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x23;
            break;
        }
        case WEB49_OPCODE_I8X16_NE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x24;
            break;
        }
        case WEB49_OPCODE_I8X16_LT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x25;
            break;
        }
        case WEB49_OPCODE_I8X16_LT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x26;
            break;
        }
        case WEB49_OPCODE_I8X16_GT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x27;
            break;
        }
        case WEB49_OPCODE_I8X16_GT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x28;
            break;
        }
        case WEB49_OPCODE_I8X16_LE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x29;
            break;
        }
        case WEB49_OPCODE_I8X16_LE_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x2A;
            break;
        }
        case WEB49_OPCODE_I8X16_GE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x2B;
            break;
        }
        case WEB49_OPCODE_I8X16_GE_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x2C;
            break;
        }
        case WEB49_OPCODE_I16X8_EQ: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x2D;
            break;
        }
        case WEB49_OPCODE_I16X8_NE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x2E;
            break;
        }
        case WEB49_OPCODE_I16X8_LT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x2F;
            break;
        }
        case WEB49_OPCODE_I16X8_LT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x30;
            break;
        }
        case WEB49_OPCODE_I16X8_GT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x31;
            break;
        }
        case WEB49_OPCODE_I16X8_GT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x32;
            break;
        }
        case WEB49_OPCODE_I16X8_LE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x33;
            break;
        }
        case WEB49_OPCODE_I16X8_LE_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x34;
            break;
        }
        case WEB49_OPCODE_I16X8_GE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x35;
            break;
        }
        case WEB49_OPCODE_I16X8_GE_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x36;
            break;
        }
        case WEB49_OPCODE_I32X4_EQ: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x37;
            break;
        }
        case WEB49_OPCODE_I32X4_NE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x38;
            break;
        }
        case WEB49_OPCODE_I32X4_LT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x39;
            break;
        }
        case WEB49_OPCODE_I32X4_LT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x3A;
            break;
        }
        case WEB49_OPCODE_I32X4_GT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x3B;
            break;
        }
        case WEB49_OPCODE_I32X4_GT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x3C;
            break;
        }
        case WEB49_OPCODE_I32X4_LE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x3D;
            break;
        }
        case WEB49_OPCODE_I32X4_LE_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x3E;
            break;
        }
        case WEB49_OPCODE_I32X4_GE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x3F;
            break;
        }
        case WEB49_OPCODE_I32X4_GE_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x40;
            break;
        }
        case WEB49_OPCODE_F32X4_EQ: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x41;
            break;
        }
        case WEB49_OPCODE_F32X4_NE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x42;
            break;
        }
        case WEB49_OPCODE_F32X4_LT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x43;
            break;
        }
        case WEB49_OPCODE_F32X4_GT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x44;
            break;
        }
        case WEB49_OPCODE_F32X4_LE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x45;
            break;
        }
        case WEB49_OPCODE_F32X4_GE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x46;
            break;
        }
        case WEB49_OPCODE_F64X2_EQ: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x47;
            break;
        }
        case WEB49_OPCODE_F64X2_NE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x48;
            break;
        }
        case WEB49_OPCODE_F64X2_LT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x49;
            break;
        }
        case WEB49_OPCODE_F64X2_GT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x4A;
            break;
        }
        case WEB49_OPCODE_F64X2_LE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x4B;
            break;
        }
        case WEB49_OPCODE_F64X2_GE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x4C;
            break;
        }
        case WEB49_OPCODE_V128_NOT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x4D;
            break;
        }
        case WEB49_OPCODE_V128_AND: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x4E;
            break;
        }
        case WEB49_OPCODE_V128_ANDNOT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x4F;
            break;
        }
        case WEB49_OPCODE_V128_OR: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x50;
            break;
        }
        case WEB49_OPCODE_V128_XOR: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x51;
            break;
        }
        case WEB49_OPCODE_V128_BITSELECT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x52;
            break;
        }
        case WEB49_OPCODE_V128_ANY_TRUE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x53;
            break;
        }
        case WEB49_OPCODE_V128_LOAD8_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x54;
            break;
        }
        case WEB49_OPCODE_V128_LOAD16_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x55;
            break;
        }
        case WEB49_OPCODE_V128_LOAD32_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x56;
            break;
        }
        case WEB49_OPCODE_V128_LOAD64_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x57;
            break;
        }
        case WEB49_OPCODE_V128_STORE8_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x58;
            break;
        }
        case WEB49_OPCODE_V128_STORE16_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x59;
            break;
        }
        case WEB49_OPCODE_V128_STORE32_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x5A;
            break;
        }
        case WEB49_OPCODE_V128_STORE64_LANE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x5B;
            break;
        }
        case WEB49_OPCODE_V128_LOAD32_ZERO: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x5C;
            break;
        }
        case WEB49_OPCODE_V128_LOAD64_ZERO: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x5D;
            break;
        }
        case WEB49_OPCODE_F32X4_DEMOTE_F64X2_ZERO: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x5E;
            break;
        }
        case WEB49_OPCODE_F64X2_PROMOTE_LOW_F32X4: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x5F;
            break;
        }
        case WEB49_OPCODE_I8X16_ABS: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x60;
            break;
        }
        case WEB49_OPCODE_I8X16_NEG: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x61;
            break;
        }
        case WEB49_OPCODE_I8X16_POPCNT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x62;
            break;
        }
        case WEB49_OPCODE_I8X16_ALL_TRUE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x63;
            break;
        }
        case WEB49_OPCODE_I8X16_BITMASK: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x64;
            break;
        }
        case WEB49_OPCODE_I8X16_NARROW_I16X8_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x65;
            break;
        }
        case WEB49_OPCODE_I8X16_NARROW_I16X8_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x66;
            break;
        }
        case WEB49_OPCODE_F32X4_CEIL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x67;
            break;
        }
        case WEB49_OPCODE_F32X4_FLOOR: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x68;
            break;
        }
        case WEB49_OPCODE_F32X4_TRUNC: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x69;
            break;
        }
        case WEB49_OPCODE_F32X4_NEAREST: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x6A;
            break;
        }
        case WEB49_OPCODE_I8X16_SHL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x6B;
            break;
        }
        case WEB49_OPCODE_I8X16_SHR_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x6C;
            break;
        }
        case WEB49_OPCODE_I8X16_SHR_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x6D;
            break;
        }
        case WEB49_OPCODE_I8X16_ADD: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x6E;
            break;
        }
        case WEB49_OPCODE_I8X16_ADD_SAT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x6F;
            break;
        }
        case WEB49_OPCODE_I8X16_ADD_SAT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x70;
            break;
        }
        case WEB49_OPCODE_I8X16_SUB: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x71;
            break;
        }
        case WEB49_OPCODE_I8X16_SUB_SAT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x72;
            break;
        }
        case WEB49_OPCODE_I8X16_SUB_SAT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x73;
            break;
        }
        case WEB49_OPCODE_F64X2_CEIL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x74;
            break;
        }
        case WEB49_OPCODE_F64X2_FLOOR: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x75;
            break;
        }
        case WEB49_OPCODE_I8X16_MIN_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x76;
            break;
        }
        case WEB49_OPCODE_I8X16_MIN_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x77;
            break;
        }
        case WEB49_OPCODE_I8X16_MAX_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x78;
            break;
        }
        case WEB49_OPCODE_I8X16_MAX_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x79;
            break;
        }
        case WEB49_OPCODE_F64X2_TRUNC: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x7A;
            break;
        }
        case WEB49_OPCODE_I8X16_AVGR_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x7B;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTADD_PAIRWISE_I8X16_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x7C;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTADD_PAIRWISE_I8X16_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x7D;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTADD_PAIRWISE_I16X8_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x7E;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTADD_PAIRWISE_I16X8_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x7F;
            break;
        }
        case WEB49_OPCODE_I16X8_ABS: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x80;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_NEG: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x81;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_Q15MULR_SAT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x82;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_ALL_TRUE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x83;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_BITMASK: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x84;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_NARROW_I32X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x85;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_NARROW_I32X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x86;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTEND_LOW_I8X16_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x87;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTEND_HIGH_I8X16_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x88;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTEND_LOW_I8X16_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x89;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTEND_HIGH_I8X16_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x8A;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_SHL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x8B;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_SHR_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x8C;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_SHR_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x8D;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_ADD: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x8E;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_ADD_SAT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x8F;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_ADD_SAT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x90;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_SUB: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x91;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_SUB_SAT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x92;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_SUB_SAT_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x93;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_NEAREST: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x94;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_MUL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x95;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_MIN_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x96;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_MIN_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x97;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_MAX_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x98;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_MAX_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x99;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_AVGR_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x9B;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTMUL_LOW_I8X16_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x9C;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTMUL_HIGH_I8X16_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x9D;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTMUL_LOW_I8X16_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x9E;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I16X8_EXTMUL_HIGH_I8X16_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x9F;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_ABS: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xA0;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_NEG: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xA1;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_ALL_TRUE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xA3;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_BITMASK: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xA4;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTEND_LOW_I16X8_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xA7;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTEND_HIGH_I16X8_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xA8;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTEND_LOW_I16X8_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xA9;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTEND_HIGH_I16X8_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xAA;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_SHL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xAB;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_SHR_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xAC;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_SHR_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xAD;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_ADD: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xAE;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_SUB: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xB1;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_MUL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xB5;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_MIN_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xB6;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_MIN_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xB7;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_MAX_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xB8;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_MAX_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xB9;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_DOT_I16X8_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xBA;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTMUL_LOW_I16X8_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xBC;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTMUL_HIGH_I16X8_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xBD;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTMUL_LOW_I16X8_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xBE;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_EXTMUL_HIGH_I16X8_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xBF;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_ABS: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xC0;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_NEG: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xC1;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_ALL_TRUE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xC3;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_BITMASK: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xC4;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTEND_LOW_I32X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xC7;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTEND_HIGH_I32X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xC8;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTEND_LOW_I32X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xC9;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTEND_HIGH_I32X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xCA;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_SHL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xCB;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_SHR_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xCC;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_SHR_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xCD;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_ADD: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xCE;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_SUB: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xD1;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_MUL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xD5;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EQ: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xD6;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_NE: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xD7;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_LT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xD8;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_GT_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xD9;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_LE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xDA;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_GE_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xDB;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTMUL_LOW_I32X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xDC;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTMUL_HIGH_I32X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xDD;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTMUL_LOW_I32X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xDE;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I64X2_EXTMUL_HIGH_I32X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xDF;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_ABS: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE0;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_NEG: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE1;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_SQRT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE3;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_ADD: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE4;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_SUB: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE5;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_MUL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE6;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_DIV: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE7;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_MIN: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE8;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_MAX: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xE9;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_PMIN: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xEA;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_PMAX: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xEB;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_ABS: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xEC;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_NEG: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xED;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_SQRT: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xEF;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_ADD: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF0;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_SUB: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF1;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_MUL: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF2;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_DIV: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF3;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_MIN: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF4;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_MAX: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF5;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_PMIN: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF6;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_PMAX: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF7;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_TRUNC_SAT_F32X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF8;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_TRUNC_SAT_F32X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xF9;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_CONVERT_I32X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xFA;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F32X4_CONVERT_I32X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xFB;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_TRUNC_SAT_F64X2_S_ZERO: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xFC;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_I32X4_TRUNC_SAT_F64X2_U_ZERO: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_CONVERT_LOW_I32X4_S: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xFE;
            buf[(*len)++] = 0x01;
            break;
        }
        case WEB49_OPCODE_F64X2_CONVERT_LOW_I32X4_U: {
            buf[(*len)++] = 0xFD;
            buf[(*len)++] = 0xFF;
            buf[(*len)++] = 0x01;
            break;
        }
        default:
            web49_error("unknown opcode: %zu\n", (size_t)opcode);
    }
}

uint8_t web49_opcode_skip(web49_opcode_t opcode) {
    if (opcode == WEB49_OPCODE_MEMORY_COPY) {
        return 2;
    }
    if (opcode == WEB49_OPCODE_MEMORY_FILL) {
        return 1;
    }
    return 0;
}

web49_opcode_t web49_name_to_opcode(const char *name) {
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
    if (!strcmp(name, "then")) {
        return WEB49_OPCODE_THEN;
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
    if (!strcmp(name, "i32.extend8_s")) {
        return WEB49_OPCODE_I32_EXTEND8_S;
    }
    if (!strcmp(name, "i32.extend16_s")) {
        return WEB49_OPCODE_I32_EXTEND16_S;
    }
    if (!strcmp(name, "i64.extend8_s")) {
        return WEB49_OPCODE_I64_EXTEND8_S;
    }
    if (!strcmp(name, "i64.extend16_s")) {
        return WEB49_OPCODE_I64_EXTEND16_S;
    }
    if (!strcmp(name, "i64.extend32_s")) {
        return WEB49_OPCODE_I64_EXTEND32_S;
    }
    if (!strcmp(name, "memory.init")) {
        return WEB49_OPCODE_MEMORY_INIT;
    }
    if (!strcmp(name, "data.drop")) {
        return WEB49_OPCODE_DATA_DROP;
    }
    if (!strcmp(name, "ref.null")) {
        return WEB49_OPCODE_REF_NULL;
    }
    if (!strcmp(name, "ref.is_null")) {
        return WEB49_OPCODE_REF_IS_NULL;
    }
    if (!strcmp(name, "ref.func")) {
        return WEB49_OPCODE_REF_FUNC;
    }
    if (!strcmp(name, "table.get")) {
        return WEB49_OPCODE_TABLE_GET;
    }
    if (!strcmp(name, "table.set")) {
        return WEB49_OPCODE_TABLE_SET;
    }
    if (!strcmp(name, "table.size")) {
        return WEB49_OPCODE_TABLE_SIZE;
    }
    if (!strcmp(name, "table.grow")) {
        return WEB49_OPCODE_TABLE_GROW;
    }
    if (!strcmp(name, "table.fill")) {
        return WEB49_OPCODE_TABLE_FILL;
    }
    if (!strcmp(name, "table.copy")) {
        return WEB49_OPCODE_TABLE_COPY;
    }
    if (!strcmp(name, "table.init")) {
        return WEB49_OPCODE_TABLE_INIT;
    }
    if (!strcmp(name, "elem.drop")) {
        return WEB49_OPCODE_ELEM_DROP;
    }
    if (!strcmp(name, "v128.load")) {
        return WEB49_OPCODE_V128_LOAD;
    }
    if (!strcmp(name, "v128.load8x8_s")) {
        return WEB49_OPCODE_V128_LOAD8X8_S;
    }
    if (!strcmp(name, "v128.load8x8_u")) {
        return WEB49_OPCODE_V128_LOAD8X8_U;
    }
    if (!strcmp(name, "v128.load16x4_s")) {
        return WEB49_OPCODE_V128_LOAD16X4_S;
    }
    if (!strcmp(name, "v128.load16x4_u")) {
        return WEB49_OPCODE_V128_LOAD16X4_U;
    }
    if (!strcmp(name, "v128.load32x2_s")) {
        return WEB49_OPCODE_V128_LOAD32X2_S;
    }
    if (!strcmp(name, "v128.load32x2_u")) {
        return WEB49_OPCODE_V128_LOAD32X2_U;
    }
    if (!strcmp(name, "v128.load8_splat")) {
        return WEB49_OPCODE_V128_LOAD8_SPLAT;
    }
    if (!strcmp(name, "v128.load16_splat")) {
        return WEB49_OPCODE_V128_LOAD16_SPLAT;
    }
    if (!strcmp(name, "v128.load32_splat")) {
        return WEB49_OPCODE_V128_LOAD32_SPLAT;
    }
    if (!strcmp(name, "v128.load64_splat")) {
        return WEB49_OPCODE_V128_LOAD64_SPLAT;
    }
    if (!strcmp(name, "v128.store")) {
        return WEB49_OPCODE_V128_STORE;
    }
    if (!strcmp(name, "v128.const")) {
        return WEB49_OPCODE_V128_CONST;
    }
    if (!strcmp(name, "i8x16.shuffle")) {
        return WEB49_OPCODE_I8X16_SHUFFLE;
    }
    if (!strcmp(name, "i8x16.swizzle")) {
        return WEB49_OPCODE_I8X16_SWIZZLE;
    }
    if (!strcmp(name, "i8x16.splat")) {
        return WEB49_OPCODE_I8X16_SPLAT;
    }
    if (!strcmp(name, "i16x8.splat")) {
        return WEB49_OPCODE_I16X8_SPLAT;
    }
    if (!strcmp(name, "i32x4.splat")) {
        return WEB49_OPCODE_I32X4_SPLAT;
    }
    if (!strcmp(name, "i64x2.splat")) {
        return WEB49_OPCODE_I64X2_SPLAT;
    }
    if (!strcmp(name, "f32x4.splat")) {
        return WEB49_OPCODE_F32X4_SPLAT;
    }
    if (!strcmp(name, "f64x2.splat")) {
        return WEB49_OPCODE_F64X2_SPLAT;
    }
    if (!strcmp(name, "i8x16.extract_lane_s")) {
        return WEB49_OPCODE_I8X16_EXTRACT_LANE_S;
    }
    if (!strcmp(name, "i8x16.extract_lane_u")) {
        return WEB49_OPCODE_I8X16_EXTRACT_LANE_U;
    }
    if (!strcmp(name, "i8x16.replace_lane")) {
        return WEB49_OPCODE_I8X16_REPLACE_LANE;
    }
    if (!strcmp(name, "i16x8.extract_lane_s")) {
        return WEB49_OPCODE_I16X8_EXTRACT_LANE_S;
    }
    if (!strcmp(name, "i16x8.extract_lane_u")) {
        return WEB49_OPCODE_I16X8_EXTRACT_LANE_U;
    }
    if (!strcmp(name, "i16x8.replace_lane")) {
        return WEB49_OPCODE_I16X8_REPLACE_LANE;
    }
    if (!strcmp(name, "i32x4.extract_lane")) {
        return WEB49_OPCODE_I32X4_EXTRACT_LANE;
    }
    if (!strcmp(name, "i32x4.replace_lane")) {
        return WEB49_OPCODE_I32X4_REPLACE_LANE;
    }
    if (!strcmp(name, "i64x2.extract_lane")) {
        return WEB49_OPCODE_I64X2_EXTRACT_LANE;
    }
    if (!strcmp(name, "i64x2.replace_lane")) {
        return WEB49_OPCODE_I64X2_REPLACE_LANE;
    }
    if (!strcmp(name, "f32x4.extract_lane")) {
        return WEB49_OPCODE_F32X4_EXTRACT_LANE;
    }
    if (!strcmp(name, "f32x4.replace_lane")) {
        return WEB49_OPCODE_F32X4_REPLACE_LANE;
    }
    if (!strcmp(name, "f64x2.extract_lane")) {
        return WEB49_OPCODE_F64X2_EXTRACT_LANE;
    }
    if (!strcmp(name, "f64x2.replace_lan")) {
        return WEB49_OPCODE_F64X2_REPLACE_LANE;
    }
    if (!strcmp(name, "i8x16.eq")) {
        return WEB49_OPCODE_I8X16_EQ;
    }
    if (!strcmp(name, "i8x16.ne")) {
        return WEB49_OPCODE_I8X16_NE;
    }
    if (!strcmp(name, "i8x16.lt_s")) {
        return WEB49_OPCODE_I8X16_LT_S;
    }
    if (!strcmp(name, "i8x16.lt_u")) {
        return WEB49_OPCODE_I8X16_LT_U;
    }
    if (!strcmp(name, "i8x16.gt_s")) {
        return WEB49_OPCODE_I8X16_GT_S;
    }
    if (!strcmp(name, "i8x16.gt_u")) {
        return WEB49_OPCODE_I8X16_GT_U;
    }
    if (!strcmp(name, "i8x16.le_s")) {
        return WEB49_OPCODE_I8X16_LE_S;
    }
    if (!strcmp(name, "i8x16.le_u")) {
        return WEB49_OPCODE_I8X16_LE_U;
    }
    if (!strcmp(name, "i8x16.ge_s")) {
        return WEB49_OPCODE_I8X16_GE_S;
    }
    if (!strcmp(name, "i8x16.ge_u")) {
        return WEB49_OPCODE_I8X16_GE_U;
    }
    if (!strcmp(name, "i16x8.eq")) {
        return WEB49_OPCODE_I16X8_EQ;
    }
    if (!strcmp(name, "i16x8.ne")) {
        return WEB49_OPCODE_I16X8_NE;
    }
    if (!strcmp(name, "i16x8.lt_s")) {
        return WEB49_OPCODE_I16X8_LT_S;
    }
    if (!strcmp(name, "i16x8.lt_u")) {
        return WEB49_OPCODE_I16X8_LT_U;
    }
    if (!strcmp(name, "i16x8.gt_s")) {
        return WEB49_OPCODE_I16X8_GT_S;
    }
    if (!strcmp(name, "i16x8.gt_u")) {
        return WEB49_OPCODE_I16X8_GT_U;
    }
    if (!strcmp(name, "i16x8.le_s")) {
        return WEB49_OPCODE_I16X8_LE_S;
    }
    if (!strcmp(name, "i16x8.le_u")) {
        return WEB49_OPCODE_I16X8_LE_U;
    }
    if (!strcmp(name, "i16x8.ge_s")) {
        return WEB49_OPCODE_I16X8_GE_S;
    }
    if (!strcmp(name, "i16x8.ge_u")) {
        return WEB49_OPCODE_I16X8_GE_U;
    }
    if (!strcmp(name, "i32x4.eq")) {
        return WEB49_OPCODE_I32X4_EQ;
    }
    if (!strcmp(name, "i32x4.ne")) {
        return WEB49_OPCODE_I32X4_NE;
    }
    if (!strcmp(name, "i32x4.lt_s")) {
        return WEB49_OPCODE_I32X4_LT_S;
    }
    if (!strcmp(name, "i32x4.lt_u")) {
        return WEB49_OPCODE_I32X4_LT_U;
    }
    if (!strcmp(name, "i32x4.gt_s")) {
        return WEB49_OPCODE_I32X4_GT_S;
    }
    if (!strcmp(name, "i32x4.gt_u")) {
        return WEB49_OPCODE_I32X4_GT_U;
    }
    if (!strcmp(name, "i32x4.le_s")) {
        return WEB49_OPCODE_I32X4_LE_S;
    }
    if (!strcmp(name, "i32x4.le_u")) {
        return WEB49_OPCODE_I32X4_LE_U;
    }
    if (!strcmp(name, "i32x4.ge_s")) {
        return WEB49_OPCODE_I32X4_GE_S;
    }
    if (!strcmp(name, "i32x4.ge_u")) {
        return WEB49_OPCODE_I32X4_GE_U;
    }
    if (!strcmp(name, "f32x4.eq")) {
        return WEB49_OPCODE_F32X4_EQ;
    }
    if (!strcmp(name, "f32x4.ne")) {
        return WEB49_OPCODE_F32X4_NE;
    }
    if (!strcmp(name, "f32x4.lt")) {
        return WEB49_OPCODE_F32X4_LT;
    }
    if (!strcmp(name, "f32x4.gt")) {
        return WEB49_OPCODE_F32X4_GT;
    }
    if (!strcmp(name, "f32x4.le")) {
        return WEB49_OPCODE_F32X4_LE;
    }
    if (!strcmp(name, "f32x4.ge")) {
        return WEB49_OPCODE_F32X4_GE;
    }
    if (!strcmp(name, "f64x2.eq")) {
        return WEB49_OPCODE_F64X2_EQ;
    }
    if (!strcmp(name, "f64x2.ne")) {
        return WEB49_OPCODE_F64X2_NE;
    }
    if (!strcmp(name, "f64x2.lt")) {
        return WEB49_OPCODE_F64X2_LT;
    }
    if (!strcmp(name, "f64x2.gt")) {
        return WEB49_OPCODE_F64X2_GT;
    }
    if (!strcmp(name, "f64x2.le")) {
        return WEB49_OPCODE_F64X2_LE;
    }
    if (!strcmp(name, "f64x2.ge")) {
        return WEB49_OPCODE_F64X2_GE;
    }
    if (!strcmp(name, "v128.not")) {
        return WEB49_OPCODE_V128_NOT;
    }
    if (!strcmp(name, "v128.and")) {
        return WEB49_OPCODE_V128_AND;
    }
    if (!strcmp(name, "v128.andnot")) {
        return WEB49_OPCODE_V128_ANDNOT;
    }
    if (!strcmp(name, "v128.or")) {
        return WEB49_OPCODE_V128_OR;
    }
    if (!strcmp(name, "v128.xor")) {
        return WEB49_OPCODE_V128_XOR;
    }
    if (!strcmp(name, "v128.bitselect")) {
        return WEB49_OPCODE_V128_BITSELECT;
    }
    if (!strcmp(name, "v128.any_true")) {
        return WEB49_OPCODE_V128_ANY_TRUE;
    }
    if (!strcmp(name, "v128.load8_lane")) {
        return WEB49_OPCODE_V128_LOAD8_LANE;
    }
    if (!strcmp(name, "v128.load16_lane")) {
        return WEB49_OPCODE_V128_LOAD16_LANE;
    }
    if (!strcmp(name, "v128.load32_lane")) {
        return WEB49_OPCODE_V128_LOAD32_LANE;
    }
    if (!strcmp(name, "v128.load64_lane")) {
        return WEB49_OPCODE_V128_LOAD64_LANE;
    }
    if (!strcmp(name, "v128.store8_lane")) {
        return WEB49_OPCODE_V128_STORE8_LANE;
    }
    if (!strcmp(name, "v128.store16_lane")) {
        return WEB49_OPCODE_V128_STORE16_LANE;
    }
    if (!strcmp(name, "v128.store32_lane")) {
        return WEB49_OPCODE_V128_STORE32_LANE;
    }
    if (!strcmp(name, "v128.store64_lane")) {
        return WEB49_OPCODE_V128_STORE64_LANE;
    }
    if (!strcmp(name, "v128.load32_zero")) {
        return WEB49_OPCODE_V128_LOAD32_ZERO;
    }
    if (!strcmp(name, "v128.load64_zero")) {
        return WEB49_OPCODE_V128_LOAD64_ZERO;
    }
    if (!strcmp(name, "f32x4.demote_f64x2_zero")) {
        return WEB49_OPCODE_F32X4_DEMOTE_F64X2_ZERO;
    }
    if (!strcmp(name, "f64x2.promote_low_f32x4")) {
        return WEB49_OPCODE_F64X2_PROMOTE_LOW_F32X4;
    }
    if (!strcmp(name, "i8x16.abs")) {
        return WEB49_OPCODE_I8X16_ABS;
    }
    if (!strcmp(name, "i8x16.neg")) {
        return WEB49_OPCODE_I8X16_NEG;
    }
    if (!strcmp(name, "i8x16.popcnt")) {
        return WEB49_OPCODE_I8X16_POPCNT;
    }
    if (!strcmp(name, "i8x16.all_true")) {
        return WEB49_OPCODE_I8X16_ALL_TRUE;
    }
    if (!strcmp(name, "i8x16.bitmask")) {
        return WEB49_OPCODE_I8X16_BITMASK;
    }
    if (!strcmp(name, "i8x16.narrow_i16x8_s")) {
        return WEB49_OPCODE_I8X16_NARROW_I16X8_S;
    }
    if (!strcmp(name, "i8x16.narrow_i16x8_u")) {
        return WEB49_OPCODE_I8X16_NARROW_I16X8_U;
    }
    if (!strcmp(name, "f32x4.ceil")) {
        return WEB49_OPCODE_F32X4_CEIL;
    }
    if (!strcmp(name, "f32x4.floor")) {
        return WEB49_OPCODE_F32X4_FLOOR;
    }
    if (!strcmp(name, "f32x4.trunc")) {
        return WEB49_OPCODE_F32X4_TRUNC;
    }
    if (!strcmp(name, "f32x4.nearest")) {
        return WEB49_OPCODE_F32X4_NEAREST;
    }
    if (!strcmp(name, "i8x16.shl")) {
        return WEB49_OPCODE_I8X16_SHL;
    }
    if (!strcmp(name, "i8x16.shr_s")) {
        return WEB49_OPCODE_I8X16_SHR_S;
    }
    if (!strcmp(name, "i8x16.shr_u")) {
        return WEB49_OPCODE_I8X16_SHR_U;
    }
    if (!strcmp(name, "i8x16.add")) {
        return WEB49_OPCODE_I8X16_ADD;
    }
    if (!strcmp(name, "i8x16.add_sat_s")) {
        return WEB49_OPCODE_I8X16_ADD_SAT_S;
    }
    if (!strcmp(name, "i8x16.add_sat_u")) {
        return WEB49_OPCODE_I8X16_ADD_SAT_U;
    }
    if (!strcmp(name, "i8x16.sub")) {
        return WEB49_OPCODE_I8X16_SUB;
    }
    if (!strcmp(name, "i8x16.sub_sat_s")) {
        return WEB49_OPCODE_I8X16_SUB_SAT_S;
    }
    if (!strcmp(name, "i8x16.sub_sat_u")) {
        return WEB49_OPCODE_I8X16_SUB_SAT_U;
    }
    if (!strcmp(name, "f64x2.ceil")) {
        return WEB49_OPCODE_F64X2_CEIL;
    }
    if (!strcmp(name, "f64x2.floor")) {
        return WEB49_OPCODE_F64X2_FLOOR;
    }
    if (!strcmp(name, "i8x16.min_s")) {
        return WEB49_OPCODE_I8X16_MIN_S;
    }
    if (!strcmp(name, "i8x16.min_u")) {
        return WEB49_OPCODE_I8X16_MIN_U;
    }
    if (!strcmp(name, "i8x16.max_s")) {
        return WEB49_OPCODE_I8X16_MAX_S;
    }
    if (!strcmp(name, "i8x16.max_u")) {
        return WEB49_OPCODE_I8X16_MAX_U;
    }
    if (!strcmp(name, "f64x2.trunc")) {
        return WEB49_OPCODE_F64X2_TRUNC;
    }
    if (!strcmp(name, "i8x16.avgr_u")) {
        return WEB49_OPCODE_I8X16_AVGR_U;
    }
    if (!strcmp(name, "i16x8.extadd_pairwise_i8x16_s")) {
        return WEB49_OPCODE_I16X8_EXTADD_PAIRWISE_I8X16_S;
    }
    if (!strcmp(name, "i16x8.extadd_pairwise_i8x16_u")) {
        return WEB49_OPCODE_I16X8_EXTADD_PAIRWISE_I8X16_U;
    }
    if (!strcmp(name, "i32x4.extadd_pairwise_i16x8_s")) {
        return WEB49_OPCODE_I32X4_EXTADD_PAIRWISE_I16X8_S;
    }
    if (!strcmp(name, "i32x4.extadd_pairwise_i16x8_u")) {
        return WEB49_OPCODE_I32X4_EXTADD_PAIRWISE_I16X8_U;
    }
    if (!strcmp(name, "i16x8.abs")) {
        return WEB49_OPCODE_I16X8_ABS;
    }
    if (!strcmp(name, "i16x8.neg")) {
        return WEB49_OPCODE_I16X8_NEG;
    }
    if (!strcmp(name, "i16x8.q15mulr_sat_s")) {
        return WEB49_OPCODE_I16X8_Q15MULR_SAT_S;
    }
    if (!strcmp(name, "i16x8.all_true")) {
        return WEB49_OPCODE_I16X8_ALL_TRUE;
    }
    if (!strcmp(name, "i16x8.bitmask")) {
        return WEB49_OPCODE_I16X8_BITMASK;
    }
    if (!strcmp(name, "i16x8.narrow_i32x4_s")) {
        return WEB49_OPCODE_I16X8_NARROW_I32X4_S;
    }
    if (!strcmp(name, "i16x8.narrow_i32x4_u")) {
        return WEB49_OPCODE_I16X8_NARROW_I32X4_U;
    }
    if (!strcmp(name, "i16x8.extend_low_i8x16_s")) {
        return WEB49_OPCODE_I16X8_EXTEND_LOW_I8X16_S;
    }
    if (!strcmp(name, "i16x8.extend_high_i8x16_s")) {
        return WEB49_OPCODE_I16X8_EXTEND_HIGH_I8X16_S;
    }
    if (!strcmp(name, "i16x8.extend_low_i8x16_u")) {
        return WEB49_OPCODE_I16X8_EXTEND_LOW_I8X16_U;
    }
    if (!strcmp(name, "i16x8.extend_high_i8x16_u")) {
        return WEB49_OPCODE_I16X8_EXTEND_HIGH_I8X16_U;
    }
    if (!strcmp(name, "i16x8.shl")) {
        return WEB49_OPCODE_I16X8_SHL;
    }
    if (!strcmp(name, "i16x8.shr_s")) {
        return WEB49_OPCODE_I16X8_SHR_S;
    }
    if (!strcmp(name, "i16x8.shr_u")) {
        return WEB49_OPCODE_I16X8_SHR_U;
    }
    if (!strcmp(name, "i16x8.add")) {
        return WEB49_OPCODE_I16X8_ADD;
    }
    if (!strcmp(name, "i16x8.add_sat_s")) {
        return WEB49_OPCODE_I16X8_ADD_SAT_S;
    }
    if (!strcmp(name, "i16x8.add_sat_u")) {
        return WEB49_OPCODE_I16X8_ADD_SAT_U;
    }
    if (!strcmp(name, "i16x8.sub")) {
        return WEB49_OPCODE_I16X8_SUB;
    }
    if (!strcmp(name, "i16x8.sub_sat_s")) {
        return WEB49_OPCODE_I16X8_SUB_SAT_S;
    }
    if (!strcmp(name, "i16x8.sub_sat_u")) {
        return WEB49_OPCODE_I16X8_SUB_SAT_U;
    }
    if (!strcmp(name, "f64x2.nearest")) {
        return WEB49_OPCODE_F64X2_NEAREST;
    }
    if (!strcmp(name, "i16x8.mul")) {
        return WEB49_OPCODE_I16X8_MUL;
    }
    if (!strcmp(name, "i16x8.min_s")) {
        return WEB49_OPCODE_I16X8_MIN_S;
    }
    if (!strcmp(name, "i16x8.min_u")) {
        return WEB49_OPCODE_I16X8_MIN_U;
    }
    if (!strcmp(name, "i16x8.max_s")) {
        return WEB49_OPCODE_I16X8_MAX_S;
    }
    if (!strcmp(name, "i16x8.max_u")) {
        return WEB49_OPCODE_I16X8_MAX_U;
    }
    if (!strcmp(name, "i16x8.avgr_u")) {
        return WEB49_OPCODE_I16X8_AVGR_U;
    }
    if (!strcmp(name, "i16x8.extmul_low_i8x16_s")) {
        return WEB49_OPCODE_I16X8_EXTMUL_LOW_I8X16_S;
    }
    if (!strcmp(name, "i16x8.extmul_high_i8x16_s")) {
        return WEB49_OPCODE_I16X8_EXTMUL_HIGH_I8X16_S;
    }
    if (!strcmp(name, "i16x8.extmul_low_i8x16_u")) {
        return WEB49_OPCODE_I16X8_EXTMUL_LOW_I8X16_U;
    }
    if (!strcmp(name, "i16x8.extmul_high_i8x16_u")) {
        return WEB49_OPCODE_I16X8_EXTMUL_HIGH_I8X16_U;
    }
    if (!strcmp(name, "i32x4.abs")) {
        return WEB49_OPCODE_I32X4_ABS;
    }
    if (!strcmp(name, "i32x4.neg")) {
        return WEB49_OPCODE_I32X4_NEG;
    }
    if (!strcmp(name, "i32x4.all_true")) {
        return WEB49_OPCODE_I32X4_ALL_TRUE;
    }
    if (!strcmp(name, "i32x4.bitmask")) {
        return WEB49_OPCODE_I32X4_BITMASK;
    }
    if (!strcmp(name, "i32x4.extend_low_i16x8_s")) {
        return WEB49_OPCODE_I32X4_EXTEND_LOW_I16X8_S;
    }
    if (!strcmp(name, "i32x4.extend_high_i16x8_s")) {
        return WEB49_OPCODE_I32X4_EXTEND_HIGH_I16X8_S;
    }
    if (!strcmp(name, "i32x4.extend_low_i16x8_u")) {
        return WEB49_OPCODE_I32X4_EXTEND_LOW_I16X8_U;
    }
    if (!strcmp(name, "i32x4.extend_high_i16x8_u")) {
        return WEB49_OPCODE_I32X4_EXTEND_HIGH_I16X8_U;
    }
    if (!strcmp(name, "i32x4.shl")) {
        return WEB49_OPCODE_I32X4_SHL;
    }
    if (!strcmp(name, "i32x4.shr_s")) {
        return WEB49_OPCODE_I32X4_SHR_S;
    }
    if (!strcmp(name, "i32x4.shr_u")) {
        return WEB49_OPCODE_I32X4_SHR_U;
    }
    if (!strcmp(name, "i32x4.add")) {
        return WEB49_OPCODE_I32X4_ADD;
    }
    if (!strcmp(name, "i32x4.sub")) {
        return WEB49_OPCODE_I32X4_SUB;
    }
    if (!strcmp(name, "i32x4.mul")) {
        return WEB49_OPCODE_I32X4_MUL;
    }
    if (!strcmp(name, "i32x4.min_s")) {
        return WEB49_OPCODE_I32X4_MIN_S;
    }
    if (!strcmp(name, "i32x4.min_u")) {
        return WEB49_OPCODE_I32X4_MIN_U;
    }
    if (!strcmp(name, "i32x4.max_s")) {
        return WEB49_OPCODE_I32X4_MAX_S;
    }
    if (!strcmp(name, "i32x4.max_u")) {
        return WEB49_OPCODE_I32X4_MAX_U;
    }
    if (!strcmp(name, "i32x4.dot_i16x8_s")) {
        return WEB49_OPCODE_I32X4_DOT_I16X8_S;
    }
    if (!strcmp(name, "i32x4.extmul_low_i16x8_s")) {
        return WEB49_OPCODE_I32X4_EXTMUL_LOW_I16X8_S;
    }
    if (!strcmp(name, "i32x4.extmul_high_i16x8_s")) {
        return WEB49_OPCODE_I32X4_EXTMUL_HIGH_I16X8_S;
    }
    if (!strcmp(name, "i32x4.extmul_low_i16x8_u")) {
        return WEB49_OPCODE_I32X4_EXTMUL_LOW_I16X8_U;
    }
    if (!strcmp(name, "i32x4.extmul_high_i16x8_u")) {
        return WEB49_OPCODE_I32X4_EXTMUL_HIGH_I16X8_U;
    }
    if (!strcmp(name, "i64x2.abs")) {
        return WEB49_OPCODE_I64X2_ABS;
    }
    if (!strcmp(name, "i64x2.neg")) {
        return WEB49_OPCODE_I64X2_NEG;
    }
    if (!strcmp(name, "i64x2.all_true")) {
        return WEB49_OPCODE_I64X2_ALL_TRUE;
    }
    if (!strcmp(name, "i64x2.bitmask")) {
        return WEB49_OPCODE_I64X2_BITMASK;
    }
    if (!strcmp(name, "i64x2.extend_low_i32x4_s")) {
        return WEB49_OPCODE_I64X2_EXTEND_LOW_I32X4_S;
    }
    if (!strcmp(name, "i64x2.extend_high_i32x4_s")) {
        return WEB49_OPCODE_I64X2_EXTEND_HIGH_I32X4_S;
    }
    if (!strcmp(name, "i64x2.extend_low_i32x4_u")) {
        return WEB49_OPCODE_I64X2_EXTEND_LOW_I32X4_U;
    }
    if (!strcmp(name, "i64x2.extend_high_i32x4_u")) {
        return WEB49_OPCODE_I64X2_EXTEND_HIGH_I32X4_U;
    }
    if (!strcmp(name, "i64x2.shl")) {
        return WEB49_OPCODE_I64X2_SHL;
    }
    if (!strcmp(name, "i64x2.shr_s")) {
        return WEB49_OPCODE_I64X2_SHR_S;
    }
    if (!strcmp(name, "i64x2.shr_u")) {
        return WEB49_OPCODE_I64X2_SHR_U;
    }
    if (!strcmp(name, "i64x2.add")) {
        return WEB49_OPCODE_I64X2_ADD;
    }
    if (!strcmp(name, "i64x2.sub")) {
        return WEB49_OPCODE_I64X2_SUB;
    }
    if (!strcmp(name, "i64x2.mul")) {
        return WEB49_OPCODE_I64X2_MUL;
    }
    if (!strcmp(name, "i64x2.eq")) {
        return WEB49_OPCODE_I64X2_EQ;
    }
    if (!strcmp(name, "i64x2.ne")) {
        return WEB49_OPCODE_I64X2_NE;
    }
    if (!strcmp(name, "i64x2.lt_s")) {
        return WEB49_OPCODE_I64X2_LT_S;
    }
    if (!strcmp(name, "i64x2.gt_s")) {
        return WEB49_OPCODE_I64X2_GT_S;
    }
    if (!strcmp(name, "i64x2.le_s")) {
        return WEB49_OPCODE_I64X2_LE_S;
    }
    if (!strcmp(name, "i64x2.ge_s")) {
        return WEB49_OPCODE_I64X2_GE_S;
    }
    if (!strcmp(name, "i64x2.extmul_low_i32x4_s")) {
        return WEB49_OPCODE_I64X2_EXTMUL_LOW_I32X4_S;
    }
    if (!strcmp(name, "i64x2.extmul_high_i32x4_s")) {
        return WEB49_OPCODE_I64X2_EXTMUL_HIGH_I32X4_S;
    }
    if (!strcmp(name, "i64x2.extmul_low_i32x4_u")) {
        return WEB49_OPCODE_I64X2_EXTMUL_LOW_I32X4_U;
    }
    if (!strcmp(name, "i64x2.extmul_high_i32x4_u")) {
        return WEB49_OPCODE_I64X2_EXTMUL_HIGH_I32X4_U;
    }
    if (!strcmp(name, "f32x4.abs")) {
        return WEB49_OPCODE_F32X4_ABS;
    }
    if (!strcmp(name, "f32x4.neg")) {
        return WEB49_OPCODE_F32X4_NEG;
    }
    if (!strcmp(name, "f32x4.sqrt")) {
        return WEB49_OPCODE_F32X4_SQRT;
    }
    if (!strcmp(name, "f32x4.add")) {
        return WEB49_OPCODE_F32X4_ADD;
    }
    if (!strcmp(name, "f32x4.sub")) {
        return WEB49_OPCODE_F32X4_SUB;
    }
    if (!strcmp(name, "f32x4.mul")) {
        return WEB49_OPCODE_F32X4_MUL;
    }
    if (!strcmp(name, "f32x4.div")) {
        return WEB49_OPCODE_F32X4_DIV;
    }
    if (!strcmp(name, "f32x4.min")) {
        return WEB49_OPCODE_F32X4_MIN;
    }
    if (!strcmp(name, "f32x4.max")) {
        return WEB49_OPCODE_F32X4_MAX;
    }
    if (!strcmp(name, "f32x4.pmin")) {
        return WEB49_OPCODE_F32X4_PMIN;
    }
    if (!strcmp(name, "f32x4.pmax")) {
        return WEB49_OPCODE_F32X4_PMAX;
    }
    if (!strcmp(name, "f64x2.abs")) {
        return WEB49_OPCODE_F64X2_ABS;
    }
    if (!strcmp(name, "f64x2.neg")) {
        return WEB49_OPCODE_F64X2_NEG;
    }
    if (!strcmp(name, "f64x2.sqrt")) {
        return WEB49_OPCODE_F64X2_SQRT;
    }
    if (!strcmp(name, "f64x2.add")) {
        return WEB49_OPCODE_F64X2_ADD;
    }
    if (!strcmp(name, "f64x2.sub")) {
        return WEB49_OPCODE_F64X2_SUB;
    }
    if (!strcmp(name, "f64x2.mul")) {
        return WEB49_OPCODE_F64X2_MUL;
    }
    if (!strcmp(name, "f64x2.div")) {
        return WEB49_OPCODE_F64X2_DIV;
    }
    if (!strcmp(name, "f64x2.min")) {
        return WEB49_OPCODE_F64X2_MIN;
    }
    if (!strcmp(name, "f64x2.max")) {
        return WEB49_OPCODE_F64X2_MAX;
    }
    if (!strcmp(name, "f64x2.pmin")) {
        return WEB49_OPCODE_F64X2_PMIN;
    }
    if (!strcmp(name, "f64x2.pmax")) {
        return WEB49_OPCODE_F64X2_PMAX;
    }
    if (!strcmp(name, "i32x4.trunc_sat_f32x4_s")) {
        return WEB49_OPCODE_I32X4_TRUNC_SAT_F32X4_S;
    }
    if (!strcmp(name, "i32x4.trunc_sat_f32x4_u")) {
        return WEB49_OPCODE_I32X4_TRUNC_SAT_F32X4_U;
    }
    if (!strcmp(name, "f32x4.convert_i32x4_s")) {
        return WEB49_OPCODE_F32X4_CONVERT_I32X4_S;
    }
    if (!strcmp(name, "f32x4.convert_i32x4_u")) {
        return WEB49_OPCODE_F32X4_CONVERT_I32X4_U;
    }
    if (!strcmp(name, "i32x4.trunc_sat_f64x2_s_zero")) {
        return WEB49_OPCODE_I32X4_TRUNC_SAT_F64X2_S_ZERO;
    }
    if (!strcmp(name, "i32x4.trunc_sat_f64x2_u_zero")) {
        return WEB49_OPCODE_I32X4_TRUNC_SAT_F64X2_U_ZERO;
    }
    if (!strcmp(name, "f64x2.convert_low_i32x4_s")) {
        return WEB49_OPCODE_F64X2_CONVERT_LOW_I32X4_S;
    }
    if (!strcmp(name, "f64x2.convert_low_i32x4_u")) {
        return WEB49_OPCODE_F64X2_CONVERT_LOW_I32X4_U;
    }
    return WEB49_MAX_OPCODE_NUM;
}

const char *web49_opcode_to_name(web49_opcode_t opcode) {
    switch (opcode) {
        case WEB49_OPCODE_UNREACHABLE:
            return "unreachable";
        case WEB49_OPCODE_NOP:
            return "nop";
        case WEB49_OPCODE_BLOCK:
            return "block";
        case WEB49_OPCODE_LOOP:
            return "loop";
        case WEB49_OPCODE_IF:
            return "if";
        case WEB49_OPCODE_THEN:
            return "then";
        case WEB49_OPCODE_ELSE:
            return "else";
        case WEB49_OPCODE_END:
            return "end";
        case WEB49_OPCODE_BR:
            return "br";
        case WEB49_OPCODE_BR_IF:
            return "br_if";
        case WEB49_OPCODE_BR_TABLE:
            return "br_table";
        case WEB49_OPCODE_RETURN:
            return "return";
        case WEB49_OPCODE_CALL:
            return "call";
        case WEB49_OPCODE_CALL_INDIRECT:
            return "call_indirect";
        case WEB49_OPCODE_DROP:
            return "drop";
        case WEB49_OPCODE_SELECT:
            return "select";
        case WEB49_OPCODE_GET_LOCAL:
            return "local.get";
        case WEB49_OPCODE_SET_LOCAL:
            return "local.set";
        case WEB49_OPCODE_TEE_LOCAL:
            return "local.tee";
        case WEB49_OPCODE_GET_GLOBAL:
            return "global.get";
        case WEB49_OPCODE_SET_GLOBAL:
            return "global.set";
        case WEB49_OPCODE_I32_LOAD:
            return "i32.load";
        case WEB49_OPCODE_I64_LOAD:
            return "i64.load";
        case WEB49_OPCODE_F32_LOAD:
            return "f32.load";
        case WEB49_OPCODE_F64_LOAD:
            return "f64.load";
        case WEB49_OPCODE_I32_LOAD8_S:
            return "i32.load8_s";
        case WEB49_OPCODE_I32_LOAD8_U:
            return "i32.load8_u";
        case WEB49_OPCODE_I32_LOAD16_S:
            return "i32.load16_s";
        case WEB49_OPCODE_I32_LOAD16_U:
            return "i32.load16_u";
        case WEB49_OPCODE_I64_LOAD8_S:
            return "i64.load8_s";
        case WEB49_OPCODE_I64_LOAD8_U:
            return "i64.load8_u";
        case WEB49_OPCODE_I64_LOAD16_S:
            return "i64.load16_s";
        case WEB49_OPCODE_I64_LOAD16_U:
            return "i64.load16_u";
        case WEB49_OPCODE_I64_LOAD32_S:
            return "i64.load32_s";
        case WEB49_OPCODE_I64_LOAD32_U:
            return "i64.load32_u";
        case WEB49_OPCODE_I32_STORE:
            return "i32.store";
        case WEB49_OPCODE_I64_STORE:
            return "i64.store";
        case WEB49_OPCODE_F32_STORE:
            return "f32.store";
        case WEB49_OPCODE_F64_STORE:
            return "f64.store";
        case WEB49_OPCODE_I32_STORE8:
            return "i32.store8";
        case WEB49_OPCODE_I32_STORE16:
            return "i32.store16";
        case WEB49_OPCODE_I64_STORE8:
            return "i64.store8";
        case WEB49_OPCODE_I64_STORE16:
            return "i64.store16";
        case WEB49_OPCODE_I64_STORE32:
            return "i64.store32";
        case WEB49_OPCODE_MEMORY_SIZE:
            return "memory.size";
        case WEB49_OPCODE_MEMORY_GROW:
            return "memory.grow";
        case WEB49_OPCODE_I32_CONST:
            return "i32.const";
        case WEB49_OPCODE_I64_CONST:
            return "i64.const";
        case WEB49_OPCODE_F32_CONST:
            return "f32.const";
        case WEB49_OPCODE_F64_CONST:
            return "f64.const";
        case WEB49_OPCODE_I32_EQZ:
            return "i32.eqz";
        case WEB49_OPCODE_I32_EQ:
            return "i32.eq";
        case WEB49_OPCODE_I32_NE:
            return "i32.ne";
        case WEB49_OPCODE_I32_LT_S:
            return "i32.lt_s";
        case WEB49_OPCODE_I32_LT_U:
            return "i32.lt_u";
        case WEB49_OPCODE_I32_GT_S:
            return "i32.gt_s";
        case WEB49_OPCODE_I32_GT_U:
            return "i32.gt_u";
        case WEB49_OPCODE_I32_LE_S:
            return "i32.le_s";
        case WEB49_OPCODE_I32_LE_U:
            return "i32.le_u";
        case WEB49_OPCODE_I32_GE_S:
            return "i32.ge_s";
        case WEB49_OPCODE_I32_GE_U:
            return "i32.ge_u";
        case WEB49_OPCODE_I64_EQZ:
            return "i64.eqz";
        case WEB49_OPCODE_I64_EQ:
            return "i64.eq";
        case WEB49_OPCODE_I64_NE:
            return "i64.ne";
        case WEB49_OPCODE_I64_LT_S:
            return "i64.lt_s";
        case WEB49_OPCODE_I64_LT_U:
            return "i64.lt_u";
        case WEB49_OPCODE_I64_GT_S:
            return "i64.gt_s";
        case WEB49_OPCODE_I64_GT_U:
            return "i64.gt_u";
        case WEB49_OPCODE_I64_LE_S:
            return "i64.le_s";
        case WEB49_OPCODE_I64_LE_U:
            return "i64.le_u";
        case WEB49_OPCODE_I64_GE_S:
            return "i64.ge_s";
        case WEB49_OPCODE_I64_GE_U:
            return "i64.ge_u";
        case WEB49_OPCODE_F32_EQ:
            return "f32.eq";
        case WEB49_OPCODE_F32_NE:
            return "f32.ne";
        case WEB49_OPCODE_F32_LT:
            return "f32.lt";
        case WEB49_OPCODE_F32_GT:
            return "f32.gt";
        case WEB49_OPCODE_F32_LE:
            return "f32.le";
        case WEB49_OPCODE_F32_GE:
            return "f32.ge";
        case WEB49_OPCODE_F64_EQ:
            return "f64.eq";
        case WEB49_OPCODE_F64_NE:
            return "f64.ne";
        case WEB49_OPCODE_F64_LT:
            return "f64.lt";
        case WEB49_OPCODE_F64_GT:
            return "f64.gt";
        case WEB49_OPCODE_F64_LE:
            return "f64.le";
        case WEB49_OPCODE_F64_GE:
            return "f64.ge";
        case WEB49_OPCODE_I32_CLZ:
            return "i32.clz";
        case WEB49_OPCODE_I32_CTZ:
            return "i32.ctz";
        case WEB49_OPCODE_I32_POPCNT:
            return "i32.popcnt";
        case WEB49_OPCODE_I32_ADD:
            return "i32.add";
        case WEB49_OPCODE_I32_SUB:
            return "i32.sub";
        case WEB49_OPCODE_I32_MUL:
            return "i32.mul";
        case WEB49_OPCODE_I32_DIV_S:
            return "i32.div_s";
        case WEB49_OPCODE_I32_DIV_U:
            return "i32.div_u";
        case WEB49_OPCODE_I32_REM_S:
            return "i32.rem_s";
        case WEB49_OPCODE_I32_REM_U:
            return "i32.rem_u";
        case WEB49_OPCODE_I32_AND:
            return "i32.and";
        case WEB49_OPCODE_I32_OR:
            return "i32.or";
        case WEB49_OPCODE_I32_XOR:
            return "i32.xor";
        case WEB49_OPCODE_I32_SHL:
            return "i32.shl";
        case WEB49_OPCODE_I32_SHR_S:
            return "i32.shr_s";
        case WEB49_OPCODE_I32_SHR_U:
            return "i32.shr_u";
        case WEB49_OPCODE_I32_ROTL:
            return "i32.rotl";
        case WEB49_OPCODE_I32_ROTR:
            return "i32.rotr";
        case WEB49_OPCODE_I64_CLZ:
            return "i64.clz";
        case WEB49_OPCODE_I64_CTZ:
            return "i64.ctz";
        case WEB49_OPCODE_I64_POPCNT:
            return "i64.popcnt";
        case WEB49_OPCODE_I64_ADD:
            return "i64.add";
        case WEB49_OPCODE_I64_SUB:
            return "i64.sub";
        case WEB49_OPCODE_I64_MUL:
            return "i64.mul";
        case WEB49_OPCODE_I64_DIV_S:
            return "i64.div_s";
        case WEB49_OPCODE_I64_DIV_U:
            return "i64.div_u";
        case WEB49_OPCODE_I64_REM_S:
            return "i64.rem_s";
        case WEB49_OPCODE_I64_REM_U:
            return "i64.rem_u";
        case WEB49_OPCODE_I64_AND:
            return "i64.and";
        case WEB49_OPCODE_I64_OR:
            return "i64.or";
        case WEB49_OPCODE_I64_XOR:
            return "i64.xor";
        case WEB49_OPCODE_I64_SHL:
            return "i64.shl";
        case WEB49_OPCODE_I64_SHR_S:
            return "i64.shr_s";
        case WEB49_OPCODE_I64_SHR_U:
            return "i64.shr_u";
        case WEB49_OPCODE_I64_ROTL:
            return "i64.rotl";
        case WEB49_OPCODE_I64_ROTR:
            return "i64.rotr";
        case WEB49_OPCODE_F32_ABS:
            return "f32.abs";
        case WEB49_OPCODE_F32_NEG:
            return "f32.neg";
        case WEB49_OPCODE_F32_CEIL:
            return "f32.ceil";
        case WEB49_OPCODE_F32_FLOOR:
            return "f32.floor";
        case WEB49_OPCODE_F32_TRUNC:
            return "f32.trunc";
        case WEB49_OPCODE_F32_NEAREST:
            return "f32.nearest";
        case WEB49_OPCODE_F32_SQRT:
            return "f32.sqrt";
        case WEB49_OPCODE_F32_ADD:
            return "f32.add";
        case WEB49_OPCODE_F32_SUB:
            return "f32.sub";
        case WEB49_OPCODE_F32_MUL:
            return "f32.mul";
        case WEB49_OPCODE_F32_DIV:
            return "f32.div";
        case WEB49_OPCODE_F32_MIN:
            return "f32.min";
        case WEB49_OPCODE_F32_MAX:
            return "f32.max";
        case WEB49_OPCODE_F32_COPYSIGN:
            return "f32.copysign";
        case WEB49_OPCODE_F64_ABS:
            return "f64.abs";
        case WEB49_OPCODE_F64_NEG:
            return "f64.neg";
        case WEB49_OPCODE_F64_CEIL:
            return "f64.ceil";
        case WEB49_OPCODE_F64_FLOOR:
            return "f64.floor";
        case WEB49_OPCODE_F64_TRUNC:
            return "f64.trunc";
        case WEB49_OPCODE_F64_NEAREST:
            return "f64.nearest";
        case WEB49_OPCODE_F64_SQRT:
            return "f64.sqrt";
        case WEB49_OPCODE_F64_ADD:
            return "f64.add";
        case WEB49_OPCODE_F64_SUB:
            return "f64.sub";
        case WEB49_OPCODE_F64_MUL:
            return "f64.mul";
        case WEB49_OPCODE_F64_DIV:
            return "f64.div";
        case WEB49_OPCODE_F64_MIN:
            return "f64.min";
        case WEB49_OPCODE_F64_MAX:
            return "f64.max";
        case WEB49_OPCODE_F64_COPYSIGN:
            return "f64.copysign";
        case WEB49_OPCODE_I32_WRAP_I64:
            return "i32.wrap_i64";
        case WEB49_OPCODE_I32_TRUNC_S_F32:
            return "i32.trunc_f32_s";
        case WEB49_OPCODE_I32_TRUNC_U_F32:
            return "i32.trunc_f32_u";
        case WEB49_OPCODE_I32_TRUNC_S_F64:
            return "i32.trunc_f64_s";
        case WEB49_OPCODE_I32_TRUNC_U_F64:
            return "i32.trunc_f64_u";
        case WEB49_OPCODE_I64_EXTEND_S_I32:
            return "i64.extend_i32_s";
        case WEB49_OPCODE_I64_EXTEND_U_I32:
            return "i64.extend_i32_u";
        case WEB49_OPCODE_I64_TRUNC_S_F32:
            return "i64.trunc_f32_s";
        case WEB49_OPCODE_I64_TRUNC_U_F32:
            return "i64.trunc_f32_u";
        case WEB49_OPCODE_I64_TRUNC_S_F64:
            return "i64.trunc_f64_s";
        case WEB49_OPCODE_I64_TRUNC_U_F64:
            return "i64.trunc_f64_u";
        case WEB49_OPCODE_F32_CONVERT_S_I32:
            return "f32.convert_i32_s";
        case WEB49_OPCODE_F32_CONVERT_U_I32:
            return "f32.convert_i32_u";
        case WEB49_OPCODE_F32_CONVERT_S_I64:
            return "f32.convert_i64_s";
        case WEB49_OPCODE_F32_CONVERT_U_I64:
            return "f32.convert_i64_u";
        case WEB49_OPCODE_F32_DEMOTE_F64:
            return "f32.demote_f64";
        case WEB49_OPCODE_F64_CONVERT_S_I32:
            return "f64.convert_i32_s";
        case WEB49_OPCODE_F64_CONVERT_U_I32:
            return "f64.convert_i32_u";
        case WEB49_OPCODE_F64_CONVERT_S_I64:
            return "f64.convert_i64_s";
        case WEB49_OPCODE_F64_CONVERT_U_I64:
            return "f64.convert_i64_u";
        case WEB49_OPCODE_F64_PROMOTE_F32:
            return "f64.promote_f32";
        case WEB49_OPCODE_I32_REINTERPRET_F32:
            return "i32.reinterpret_f32";
        case WEB49_OPCODE_I64_REINTERPRET_F64:
            return "i64.reinterpret_f64";
        case WEB49_OPCODE_F32_REINTERPRET_I32:
            return "f32.reinterpret_i32";
        case WEB49_OPCODE_F64_REINTERPRET_I64:
            return "f64.reinterpret_i64";
        case WEB49_OPCODE_I32_EXTEND8_S:
            return "i32.extend8_s";
        case WEB49_OPCODE_I32_EXTEND16_S:
            return "i32.extend16_s";
        case WEB49_OPCODE_I64_EXTEND8_S:
            return "i64.extend8_s";
        case WEB49_OPCODE_I64_EXTEND16_S:
            return "i64.extend16_s";
        case WEB49_OPCODE_I64_EXTEND32_S:
            return "i64.extend32_s";
        case WEB49_OPCODE_MEMORY_INIT:
            return "memory.init";
        case WEB49_OPCODE_MEMORY_COPY:
            return "memory.copy";
        case WEB49_OPCODE_MEMORY_FILL:
            return "memory.fill";
        case WEB49_OPCODE_DATA_DROP:
            return "data.drop";
        case WEB49_OPCODE_REF_NULL:
            return "ref.null";
        case WEB49_OPCODE_REF_IS_NULL:
            return "ref.is_null";
        case WEB49_OPCODE_REF_FUNC:
            return "ref.func";
        case WEB49_OPCODE_TABLE_GET:
            return "table.get";
        case WEB49_OPCODE_TABLE_SET:
            return "table.set";
        case WEB49_OPCODE_TABLE_SIZE:
            return "table.size";
        case WEB49_OPCODE_TABLE_GROW:
            return "table.grow";
        case WEB49_OPCODE_TABLE_FILL:
            return "table.fill";
        case WEB49_OPCODE_TABLE_COPY:
            return "table.copy";
        case WEB49_OPCODE_TABLE_INIT:
            return "table.init";
        case WEB49_OPCODE_ELEM_DROP:
            return "elem.drop";
        case WEB49_OPCODE_BEGIN0:
            return "web49.begin0";
        case WEB49_OPCODE_YIELD_PUSH:
            return "web49.yield_push";
        case WEB49_OPCODE_YIELD_POP:
            return "web49.yield_pop";
        case WEB49_OPCODE_RETURN0:
            return "web49.return0";
        case WEB49_OPCODE_RETURN1:
            return "web49.return1";
        case WEB49_OPCODE_CALL0:
            return "web49.call0";
        case WEB49_OPCODE_CALL1:
            return "web49.call1";
        case WEB49_OPCODE_CALL_INDIRECT0:
            return "web49.call_indirect0";
        case WEB49_OPCODE_CALL_INDIRECT1:
            return "web49.call_indirect1";
        case WEB49_OPCODE_V128_LOAD:
            return "v128.load";
        case WEB49_OPCODE_V128_LOAD8X8_S:
            return "v128.load8x8_s";
        case WEB49_OPCODE_V128_LOAD8X8_U:
            return "v128.load8x8_u";
        case WEB49_OPCODE_V128_LOAD16X4_S:
            return "v128.load16x4_s";
        case WEB49_OPCODE_V128_LOAD16X4_U:
            return "v128.load16x4_u";
        case WEB49_OPCODE_V128_LOAD32X2_S:
            return "v128.load32x2_s";
        case WEB49_OPCODE_V128_LOAD32X2_U:
            return "v128.load32x2_u";
        case WEB49_OPCODE_V128_LOAD8_SPLAT:
            return "v128.load8_splat";
        case WEB49_OPCODE_V128_LOAD16_SPLAT:
            return "v128.load16_splat";
        case WEB49_OPCODE_V128_LOAD32_SPLAT:
            return "v128.load32_splat";
        case WEB49_OPCODE_V128_LOAD64_SPLAT:
            return "v128.load64_splat";
        case WEB49_OPCODE_V128_STORE:
            return "v128.store";
        case WEB49_OPCODE_V128_CONST:
            return "v128.const";
        case WEB49_OPCODE_I8X16_SHUFFLE:
            return "i8x16.shuffle";
        case WEB49_OPCODE_I8X16_SWIZZLE:
            return "i8x16.swizzle";
        case WEB49_OPCODE_I8X16_SPLAT:
            return "i8x16.splat";
        case WEB49_OPCODE_I16X8_SPLAT:
            return "i16x8.splat";
        case WEB49_OPCODE_I32X4_SPLAT:
            return "i32x4.splat";
        case WEB49_OPCODE_I64X2_SPLAT:
            return "i64x2.splat";
        case WEB49_OPCODE_F32X4_SPLAT:
            return "f32x4.splat";
        case WEB49_OPCODE_F64X2_SPLAT:
            return "f64x2.splat";
        case WEB49_OPCODE_I8X16_EXTRACT_LANE_S:
            return "i8x16.extract_lane_s";
        case WEB49_OPCODE_I8X16_EXTRACT_LANE_U:
            return "i8x16.extract_lane_u";
        case WEB49_OPCODE_I8X16_REPLACE_LANE:
            return "i8x16.replace_lane";
        case WEB49_OPCODE_I16X8_EXTRACT_LANE_S:
            return "i16x8.extract_lane_s";
        case WEB49_OPCODE_I16X8_EXTRACT_LANE_U:
            return "i16x8.extract_lane_u";
        case WEB49_OPCODE_I16X8_REPLACE_LANE:
            return "i16x8.replace_lane";
        case WEB49_OPCODE_I32X4_EXTRACT_LANE:
            return "i32x4.extract_lane";
        case WEB49_OPCODE_I32X4_REPLACE_LANE:
            return "i32x4.replace_lane";
        case WEB49_OPCODE_I64X2_EXTRACT_LANE:
            return "i64x2.extract_lane";
        case WEB49_OPCODE_I64X2_REPLACE_LANE:
            return "i64x2.replace_lane";
        case WEB49_OPCODE_F32X4_EXTRACT_LANE:
            return "f32x4.extract_lane";
        case WEB49_OPCODE_F32X4_REPLACE_LANE:
            return "f32x4.replace_lane";
        case WEB49_OPCODE_F64X2_EXTRACT_LANE:
            return "f64x2.extract_lane";
        case WEB49_OPCODE_F64X2_REPLACE_LANE:
            return "f64x2.replace_lane";
        case WEB49_OPCODE_I8X16_EQ:
            return "i8x16.eq";
        case WEB49_OPCODE_I8X16_NE:
            return "i8x16.ne";
        case WEB49_OPCODE_I8X16_LT_S:
            return "i8x16.lt_s";
        case WEB49_OPCODE_I8X16_LT_U:
            return "i8x16.lt_u";
        case WEB49_OPCODE_I8X16_GT_S:
            return "i8x16.gt_s";
        case WEB49_OPCODE_I8X16_GT_U:
            return "i8x16.gt_u";
        case WEB49_OPCODE_I8X16_LE_S:
            return "i8x16.le_s";
        case WEB49_OPCODE_I8X16_LE_U:
            return "i8x16.le_u";
        case WEB49_OPCODE_I8X16_GE_S:
            return "i8x16.ge_s";
        case WEB49_OPCODE_I8X16_GE_U:
            return "i8x16.ge_u";
        case WEB49_OPCODE_I16X8_EQ:
            return "i16x8.eq";
        case WEB49_OPCODE_I16X8_NE:
            return "i16x8.ne";
        case WEB49_OPCODE_I16X8_LT_S:
            return "i16x8.lt_s";
        case WEB49_OPCODE_I16X8_LT_U:
            return "i16x8.lt_u";
        case WEB49_OPCODE_I16X8_GT_S:
            return "i16x8.gt_s";
        case WEB49_OPCODE_I16X8_GT_U:
            return "i16x8.gt_u";
        case WEB49_OPCODE_I16X8_LE_S:
            return "i16x8.le_s";
        case WEB49_OPCODE_I16X8_LE_U:
            return "i16x8.le_u";
        case WEB49_OPCODE_I16X8_GE_S:
            return "i16x8.ge_s";
        case WEB49_OPCODE_I16X8_GE_U:
            return "i16x8.ge_u";
        case WEB49_OPCODE_I32X4_EQ:
            return "i32x4.eq";
        case WEB49_OPCODE_I32X4_NE:
            return "i32x4.ne";
        case WEB49_OPCODE_I32X4_LT_S:
            return "i32x4.lt_s";
        case WEB49_OPCODE_I32X4_LT_U:
            return "i32x4.lt_u";
        case WEB49_OPCODE_I32X4_GT_S:
            return "i32x4.gt_s";
        case WEB49_OPCODE_I32X4_GT_U:
            return "i32x4.gt_u";
        case WEB49_OPCODE_I32X4_LE_S:
            return "i32x4.le_s";
        case WEB49_OPCODE_I32X4_LE_U:
            return "i32x4.le_u";
        case WEB49_OPCODE_I32X4_GE_S:
            return "i32x4.ge_s";
        case WEB49_OPCODE_I32X4_GE_U:
            return "i32x4.ge_u";
        case WEB49_OPCODE_F32X4_EQ:
            return "f32x4.eq";
        case WEB49_OPCODE_F32X4_NE:
            return "f32x4.ne";
        case WEB49_OPCODE_F32X4_LT:
            return "f32x4.lt";
        case WEB49_OPCODE_F32X4_GT:
            return "f32x4.gt";
        case WEB49_OPCODE_F32X4_LE:
            return "f32x4.le";
        case WEB49_OPCODE_F32X4_GE:
            return "f32x4.ge";
        case WEB49_OPCODE_F64X2_EQ:
            return "f64x2.eq";
        case WEB49_OPCODE_F64X2_NE:
            return "f64x2.ne";
        case WEB49_OPCODE_F64X2_LT:
            return "f64x2.lt";
        case WEB49_OPCODE_F64X2_GT:
            return "f64x2.gt";
        case WEB49_OPCODE_F64X2_LE:
            return "f64x2.le";
        case WEB49_OPCODE_F64X2_GE:
            return "f64x2.ge";
        case WEB49_OPCODE_V128_NOT:
            return "v128.not";
        case WEB49_OPCODE_V128_AND:
            return "v128.and";
        case WEB49_OPCODE_V128_ANDNOT:
            return "v128.andnot";
        case WEB49_OPCODE_V128_OR:
            return "v128.or";
        case WEB49_OPCODE_V128_XOR:
            return "v128.xor";
        case WEB49_OPCODE_V128_BITSELECT:
            return "v128.bitselect";
        case WEB49_OPCODE_V128_ANY_TRUE:
            return "v128.any_true";
        case WEB49_OPCODE_V128_LOAD8_LANE:
            return "v128.load8_lane";
        case WEB49_OPCODE_V128_LOAD16_LANE:
            return "v128.load16_lane";
        case WEB49_OPCODE_V128_LOAD32_LANE:
            return "v128.load32_lane";
        case WEB49_OPCODE_V128_LOAD64_LANE:
            return "v128.load64_lane";
        case WEB49_OPCODE_V128_STORE8_LANE:
            return "v128.store8_lane";
        case WEB49_OPCODE_V128_STORE16_LANE:
            return "v128.store16_lane";
        case WEB49_OPCODE_V128_STORE32_LANE:
            return "v128.store32_lane";
        case WEB49_OPCODE_V128_STORE64_LANE:
            return "v128.store64_lane";
        case WEB49_OPCODE_V128_LOAD32_ZERO:
            return "v128.load32_zero";
        case WEB49_OPCODE_V128_LOAD64_ZERO:
            return "v128.load64_zero";
        case WEB49_OPCODE_F32X4_DEMOTE_F64X2_ZERO:
            return "f32x4.demote_f64x2_zero";
        case WEB49_OPCODE_F64X2_PROMOTE_LOW_F32X4:
            return "f64x2.promote_low_f32x4";
        case WEB49_OPCODE_I8X16_ABS:
            return "i8x16.abs";
        case WEB49_OPCODE_I8X16_NEG:
            return "i8x16.neg";
        case WEB49_OPCODE_I8X16_POPCNT:
            return "i8x16.popcnt";
        case WEB49_OPCODE_I8X16_ALL_TRUE:
            return "i8x16.all_true";
        case WEB49_OPCODE_I8X16_BITMASK:
            return "i8x16.bitmask";
        case WEB49_OPCODE_I8X16_NARROW_I16X8_S:
            return "i8x16.narrow_i16x8_s";
        case WEB49_OPCODE_I8X16_NARROW_I16X8_U:
            return "i8x16.narrow_i16x8_u";
        case WEB49_OPCODE_F32X4_CEIL:
            return "f32x4.ceil";
        case WEB49_OPCODE_F32X4_FLOOR:
            return "f32x4.floor";
        case WEB49_OPCODE_F32X4_TRUNC:
            return "f32x4.trunc";
        case WEB49_OPCODE_F32X4_NEAREST:
            return "f32x4.nearest";
        case WEB49_OPCODE_I8X16_SHL:
            return "i8x16.shl";
        case WEB49_OPCODE_I8X16_SHR_S:
            return "i8x16.shr_s";
        case WEB49_OPCODE_I8X16_SHR_U:
            return "i8x16.shr_u";
        case WEB49_OPCODE_I8X16_ADD:
            return "i8x16.add";
        case WEB49_OPCODE_I8X16_ADD_SAT_S:
            return "i8x16.add_sat_s";
        case WEB49_OPCODE_I8X16_ADD_SAT_U:
            return "i8x16.add_sat_u";
        case WEB49_OPCODE_I8X16_SUB:
            return "i8x16.sub";
        case WEB49_OPCODE_I8X16_SUB_SAT_S:
            return "i8x16.sub_sat_s";
        case WEB49_OPCODE_I8X16_SUB_SAT_U:
            return "i8x16.sub_sat_u";
        case WEB49_OPCODE_F64X2_CEIL:
            return "f64x2.ceil";
        case WEB49_OPCODE_F64X2_FLOOR:
            return "f64x2.floor";
        case WEB49_OPCODE_I8X16_MIN_S:
            return "i8x16.min_s";
        case WEB49_OPCODE_I8X16_MIN_U:
            return "i8x16.min_u";
        case WEB49_OPCODE_I8X16_MAX_S:
            return "i8x16.max_s";
        case WEB49_OPCODE_I8X16_MAX_U:
            return "i8x16.max_u";
        case WEB49_OPCODE_F64X2_TRUNC:
            return "f64x2.trunc";
        case WEB49_OPCODE_I8X16_AVGR_U:
            return "i8x16.avgr_u";
        case WEB49_OPCODE_I16X8_EXTADD_PAIRWISE_I8X16_S:
            return "i16x8.extadd_pairwise_i8x16_s";
        case WEB49_OPCODE_I16X8_EXTADD_PAIRWISE_I8X16_U:
            return "i16x8.extadd_pairwise_i8x16_u";
        case WEB49_OPCODE_I32X4_EXTADD_PAIRWISE_I16X8_S:
            return "i32x4.extadd_pairwise_i16x8_s";
        case WEB49_OPCODE_I32X4_EXTADD_PAIRWISE_I16X8_U:
            return "i32x4.extadd_pairwise_i16x8_u";
        case WEB49_OPCODE_I16X8_ABS:
            return "i16x8.abs";
        case WEB49_OPCODE_I16X8_NEG:
            return "i16x8.neg";
        case WEB49_OPCODE_I16X8_Q15MULR_SAT_S:
            return "i16x8.q15mulr_sat_s";
        case WEB49_OPCODE_I16X8_ALL_TRUE:
            return "i16x8.all_true";
        case WEB49_OPCODE_I16X8_BITMASK:
            return "i16x8.bitmask";
        case WEB49_OPCODE_I16X8_NARROW_I32X4_S:
            return "i16x8.narrow_i32x4_s";
        case WEB49_OPCODE_I16X8_NARROW_I32X4_U:
            return "i16x8.narrow_i32x4_u";
        case WEB49_OPCODE_I16X8_EXTEND_LOW_I8X16_S:
            return "i16x8.extend_low_i8x16_s";
        case WEB49_OPCODE_I16X8_EXTEND_HIGH_I8X16_S:
            return "i16x8.extend_high_i8x16_s";
        case WEB49_OPCODE_I16X8_EXTEND_LOW_I8X16_U:
            return "i16x8.extend_low_i8x16_u";
        case WEB49_OPCODE_I16X8_EXTEND_HIGH_I8X16_U:
            return "i16x8.extend_high_i8x16_u";
        case WEB49_OPCODE_I16X8_SHL:
            return "i16x8.shl";
        case WEB49_OPCODE_I16X8_SHR_S:
            return "i16x8.shr_s";
        case WEB49_OPCODE_I16X8_SHR_U:
            return "i16x8.shr_u";
        case WEB49_OPCODE_I16X8_ADD:
            return "i16x8.add";
        case WEB49_OPCODE_I16X8_ADD_SAT_S:
            return "i16x8.add_sat_s";
        case WEB49_OPCODE_I16X8_ADD_SAT_U:
            return "i16x8.add_sat_u";
        case WEB49_OPCODE_I16X8_SUB:
            return "i16x8.sub";
        case WEB49_OPCODE_I16X8_SUB_SAT_S:
            return "i16x8.sub_sat_s";
        case WEB49_OPCODE_I16X8_SUB_SAT_U:
            return "i16x8.sub_sat_u";
        case WEB49_OPCODE_F64X2_NEAREST:
            return "f64x2.nearest";
        case WEB49_OPCODE_I16X8_MUL:
            return "i16x8.mul";
        case WEB49_OPCODE_I16X8_MIN_S:
            return "i16x8.min_s";
        case WEB49_OPCODE_I16X8_MIN_U:
            return "i16x8.min_u";
        case WEB49_OPCODE_I16X8_MAX_S:
            return "i16x8.max_s";
        case WEB49_OPCODE_I16X8_MAX_U:
            return "i16x8.max_u";
        case WEB49_OPCODE_I16X8_AVGR_U:
            return "i16x8.avgr_u";
        case WEB49_OPCODE_I16X8_EXTMUL_LOW_I8X16_S:
            return "i16x8.extmul_low_i8x16_s";
        case WEB49_OPCODE_I16X8_EXTMUL_HIGH_I8X16_S:
            return "i16x8.extmul_high_i8x16_s";
        case WEB49_OPCODE_I16X8_EXTMUL_LOW_I8X16_U:
            return "i16x8.extmul_low_i8x16_u";
        case WEB49_OPCODE_I16X8_EXTMUL_HIGH_I8X16_U:
            return "i16x8.extmul_high_i8x16_u";
        case WEB49_OPCODE_I32X4_ABS:
            return "i32x4.abs";
        case WEB49_OPCODE_I32X4_NEG:
            return "i32x4.neg";
        case WEB49_OPCODE_I32X4_ALL_TRUE:
            return "i32x4.all_true";
        case WEB49_OPCODE_I32X4_BITMASK:
            return "i32x4.bitmask";
        case WEB49_OPCODE_I32X4_EXTEND_LOW_I16X8_S:
            return "i32x4.extend_low_i16x8_s";
        case WEB49_OPCODE_I32X4_EXTEND_HIGH_I16X8_S:
            return "i32x4.extend_high_i16x8_s";
        case WEB49_OPCODE_I32X4_EXTEND_LOW_I16X8_U:
            return "i32x4.extend_low_i16x8_u";
        case WEB49_OPCODE_I32X4_EXTEND_HIGH_I16X8_U:
            return "i32x4.extend_high_i16x8_u";
        case WEB49_OPCODE_I32X4_SHL:
            return "i32x4.shl";
        case WEB49_OPCODE_I32X4_SHR_S:
            return "i32x4.shr_s";
        case WEB49_OPCODE_I32X4_SHR_U:
            return "i32x4.shr_u";
        case WEB49_OPCODE_I32X4_ADD:
            return "i32x4.add";
        case WEB49_OPCODE_I32X4_SUB:
            return "i32x4.sub";
        case WEB49_OPCODE_I32X4_MUL:
            return "i32x4.mul";
        case WEB49_OPCODE_I32X4_MIN_S:
            return "i32x4.min_s";
        case WEB49_OPCODE_I32X4_MIN_U:
            return "i32x4.min_u";
        case WEB49_OPCODE_I32X4_MAX_S:
            return "i32x4.max_s";
        case WEB49_OPCODE_I32X4_MAX_U:
            return "i32x4.max_u";
        case WEB49_OPCODE_I32X4_DOT_I16X8_S:
            return "i32x4.dot_i16x8_s";
        case WEB49_OPCODE_I32X4_EXTMUL_LOW_I16X8_S:
            return "i32x4.extmul_low_i16x8_s";
        case WEB49_OPCODE_I32X4_EXTMUL_HIGH_I16X8_S:
            return "i32x4.extmul_high_i16x8_s";
        case WEB49_OPCODE_I32X4_EXTMUL_LOW_I16X8_U:
            return "i32x4.extmul_low_i16x8_u";
        case WEB49_OPCODE_I32X4_EXTMUL_HIGH_I16X8_U:
            return "i32x4.extmul_high_i16x8_u";
        case WEB49_OPCODE_I64X2_ABS:
            return "i64x2.abs";
        case WEB49_OPCODE_I64X2_NEG:
            return "i64x2.neg";
        case WEB49_OPCODE_I64X2_ALL_TRUE:
            return "i64x2.all_true";
        case WEB49_OPCODE_I64X2_BITMASK:
            return "i64x2.bitmask";
        case WEB49_OPCODE_I64X2_EXTEND_LOW_I32X4_S:
            return "i64x2.extend_low_i32x4_s";
        case WEB49_OPCODE_I64X2_EXTEND_HIGH_I32X4_S:
            return "i64x2.extend_high_i32x4_s";
        case WEB49_OPCODE_I64X2_EXTEND_LOW_I32X4_U:
            return "i64x2.extend_low_i32x4_u";
        case WEB49_OPCODE_I64X2_EXTEND_HIGH_I32X4_U:
            return "i64x2.extend_high_i32x4_u";
        case WEB49_OPCODE_I64X2_SHL:
            return "i64x2.shl";
        case WEB49_OPCODE_I64X2_SHR_S:
            return "i64x2.shr_s";
        case WEB49_OPCODE_I64X2_SHR_U:
            return "i64x2.shr_u";
        case WEB49_OPCODE_I64X2_ADD:
            return "i64x2.add";
        case WEB49_OPCODE_I64X2_SUB:
            return "i64x2.sub";
        case WEB49_OPCODE_I64X2_MUL:
            return "i64x2.mul";
        case WEB49_OPCODE_I64X2_EQ:
            return "i64x2.eq";
        case WEB49_OPCODE_I64X2_NE:
            return "i64x2.ne";
        case WEB49_OPCODE_I64X2_LT_S:
            return "i64x2.lt_s";
        case WEB49_OPCODE_I64X2_GT_S:
            return "i64x2.gt_s";
        case WEB49_OPCODE_I64X2_LE_S:
            return "i64x2.le_s";
        case WEB49_OPCODE_I64X2_GE_S:
            return "i64x2.ge_s";
        case WEB49_OPCODE_I64X2_EXTMUL_LOW_I32X4_S:
            return "i64x2.extmul_low_i32x4_s";
        case WEB49_OPCODE_I64X2_EXTMUL_HIGH_I32X4_S:
            return "i64x2.extmul_high_i32x4_s";
        case WEB49_OPCODE_I64X2_EXTMUL_LOW_I32X4_U:
            return "i64x2.extmul_low_i32x4_u";
        case WEB49_OPCODE_I64X2_EXTMUL_HIGH_I32X4_U:
            return "i64x2.extmul_high_i32x4_u";
        case WEB49_OPCODE_F32X4_ABS:
            return "f32x4.abs";
        case WEB49_OPCODE_F32X4_NEG:
            return "f32x4.neg";
        case WEB49_OPCODE_F32X4_SQRT:
            return "f32x4.sqrt";
        case WEB49_OPCODE_F32X4_ADD:
            return "f32x4.add";
        case WEB49_OPCODE_F32X4_SUB:
            return "f32x4.sub";
        case WEB49_OPCODE_F32X4_MUL:
            return "f32x4.mul";
        case WEB49_OPCODE_F32X4_DIV:
            return "f32x4.div";
        case WEB49_OPCODE_F32X4_MIN:
            return "f32x4.min";
        case WEB49_OPCODE_F32X4_MAX:
            return "f32x4.max";
        case WEB49_OPCODE_F32X4_PMIN:
            return "f32x4.pmin";
        case WEB49_OPCODE_F32X4_PMAX:
            return "f32x4.pmax";
        case WEB49_OPCODE_F64X2_ABS:
            return "f64x2.abs";
        case WEB49_OPCODE_F64X2_NEG:
            return "f64x2.neg";
        case WEB49_OPCODE_F64X2_SQRT:
            return "f64x2.sqrt";
        case WEB49_OPCODE_F64X2_ADD:
            return "f64x2.add";
        case WEB49_OPCODE_F64X2_SUB:
            return "f64x2.sub";
        case WEB49_OPCODE_F64X2_MUL:
            return "f64x2.mul";
        case WEB49_OPCODE_F64X2_DIV:
            return "f64x2.div";
        case WEB49_OPCODE_F64X2_MIN:
            return "f64x2.min";
        case WEB49_OPCODE_F64X2_MAX:
            return "f64x2.max";
        case WEB49_OPCODE_F64X2_PMIN:
            return "f64x2.pmin";
        case WEB49_OPCODE_F64X2_PMAX:
            return "f64x2.pmax";
        case WEB49_OPCODE_I32X4_TRUNC_SAT_F32X4_S:
            return "i32x4.trunc_sat_f32x4_s";
        case WEB49_OPCODE_I32X4_TRUNC_SAT_F32X4_U:
            return "i32x4.trunc_sat_f32x4_u";
        case WEB49_OPCODE_F32X4_CONVERT_I32X4_S:
            return "f32x4.convert_i32x4_s";
        case WEB49_OPCODE_F32X4_CONVERT_I32X4_U:
            return "f32x4.convert_i32x4_u";
        case WEB49_OPCODE_I32X4_TRUNC_SAT_F64X2_S_ZERO:
            return "i32x4.trunc_sat_f64x2_s_zero";
        case WEB49_OPCODE_I32X4_TRUNC_SAT_F64X2_U_ZERO:
            return "i32x4.trunc_sat_f64x2_u_zero";
        case WEB49_OPCODE_F64X2_CONVERT_LOW_I32X4_S:
            return "f64x2.convert_low_i32x4_s";
        case WEB49_OPCODE_F64X2_CONVERT_LOW_I32X4_U:
            return "f64x2.convert_low_i32x4_u";
        default:
            web49_error("unknown opcode: %zu\ng", (size_t)opcode);
    }
}
