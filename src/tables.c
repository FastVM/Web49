
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
        .in[0] = WEB49_TABLE_STACK_EFFECT_ANY,
        .branch = true,
    },
    [WEB49_OPCODE_CALL] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_ARGS,
        .out[0] = WEB49_TABLE_STACK_EFFECT_RET,
    },
    [WEB49_OPCODE_CALL_INDIRECT] = (web49_table_stack_effect_t){
        .in[0] = WEB49_TABLE_STACK_EFFECT_I32,
        .in[1] = WEB49_TABLE_STACK_EFFECT_ARGS_INDIRECT,
        .out[0] = WEB49_TABLE_STACK_EFFECT_RET_INDIRECT,
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
    [WEB49_OPCODE_DATA_DROP] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_INIT] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_ELEM_DROP] = (web49_table_stack_effect_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_COPY] = (web49_table_stack_effect_t){
        .fail = true,
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
};

bool web49_opcode_is_multibyte(uint8_t first_byte) {
    return first_byte == 0xFB || first_byte == 0xFC || first_byte == 0xFD || first_byte == 0xFE;
}

#define web49_error(...)          \
    fprintf(stderr, __VA_ARGS__); \
    __builtin_trap();

web49_opcode_t web49_bytes_to_opcode(uint8_t *bytes) {
    switch (bytes[0]) {
        case 0x0: {
            return WEB49_OPCODE_UNREACHABLE;
        }
        case 0x1: {
            web49_error("unknown opcode 0x1\n");
            break;
        }
        case 0x2: {
            web49_error("unknown opcode 0x2\n");
            break;
        }
        case 0x3: {
            web49_error("unknown opcode 0x3\n");
            break;
        }
        case 0x4: {
            web49_error("unknown opcode 0x4\n");
            break;
        }
        case 0x5: {
            web49_error("unknown opcode 0x5\n");
            break;
        }
        case 0x6: {
            web49_error("unknown opcode 0x6\n");
            break;
        }
        case 0x7: {
            web49_error("unknown opcode 0x7\n");
            break;
        }
        case 0x8: {
            web49_error("unknown opcode 0x8\n");
            break;
        }
        case 0x9: {
            web49_error("unknown opcode 0x9\n");
            break;
        }
        case 0xa: {
            web49_error("unknown opcode 0xa\n");
            break;
        }
        case 0xb: {
            web49_error("unknown opcode 0xb\n");
            break;
        }
        case 0xc: {
            web49_error("unknown opcode 0xc\n");
            break;
        }
        case 0xd: {
            web49_error("unknown opcode 0xd\n");
            break;
        }
        case 0xe: {
            web49_error("unknown opcode 0xe\n");
            break;
        }
        case 0xf: {
            web49_error("unknown opcode 0xf\n");
            break;
        }
        case 0x10: {
            web49_error("unknown opcode 0x10\n");
            break;
        }
        case 0x11: {
            web49_error("unknown opcode 0x11\n");
            break;
        }
        case 0x12: {
            web49_error("unknown opcode 0x12\n");
            break;
        }
        case 0x13: {
            web49_error("unknown opcode 0x13\n");
            break;
        }
        case 0x14: {
            web49_error("unknown opcode 0x14\n");
            break;
        }
        case 0x15: {
            web49_error("unknown opcode 0x15\n");
            break;
        }
        case 0x16: {
            web49_error("unknown opcode 0x16\n");
            break;
        }
        case 0x17: {
            web49_error("unknown opcode 0x17\n");
            break;
        }
        case 0x18: {
            web49_error("unknown opcode 0x18\n");
            break;
        }
        case 0x19: {
            web49_error("unknown opcode 0x19\n");
            break;
        }
        case 0x1a: {
            web49_error("unknown opcode 0x1a\n");
            break;
        }
        case 0x1b: {
            web49_error("unknown opcode 0x1b\n");
            break;
        }
        case 0x1c: {
            web49_error("unknown opcode 0x1c\n");
            break;
        }
        case 0x1d: {
            web49_error("unknown opcode 0x1d\n");
            break;
        }
        case 0x1e: {
            web49_error("unknown opcode 0x1e\n");
            break;
        }
        case 0x1f: {
            web49_error("unknown opcode 0x1f\n");
            break;
        }
        case 0x20: {
            web49_error("unknown opcode 0x20\n");
            break;
        }
        case 0x21: {
            web49_error("unknown opcode 0x21\n");
            break;
        }
        case 0x22: {
            web49_error("unknown opcode 0x22\n");
            break;
        }
        case 0x23: {
            web49_error("unknown opcode 0x23\n");
            break;
        }
        case 0x24: {
            web49_error("unknown opcode 0x24\n");
            break;
        }
        case 0x25: {
            web49_error("unknown opcode 0x25\n");
            break;
        }
        case 0x26: {
            web49_error("unknown opcode 0x26\n");
            break;
        }
        case 0x27: {
            web49_error("unknown opcode 0x27\n");
            break;
        }
        case 0x28: {
            web49_error("unknown opcode 0x28\n");
            break;
        }
        case 0x29: {
            web49_error("unknown opcode 0x29\n");
            break;
        }
        case 0x2a: {
            web49_error("unknown opcode 0x2a\n");
            break;
        }
        case 0x2b: {
            web49_error("unknown opcode 0x2b\n");
            break;
        }
        case 0x2c: {
            web49_error("unknown opcode 0x2c\n");
            break;
        }
        case 0x2d: {
            web49_error("unknown opcode 0x2d\n");
            break;
        }
        case 0x2e: {
            web49_error("unknown opcode 0x2e\n");
            break;
        }
        case 0x2f: {
            web49_error("unknown opcode 0x2f\n");
            break;
        }
        case 0x30: {
            web49_error("unknown opcode 0x30\n");
            break;
        }
        case 0x31: {
            web49_error("unknown opcode 0x31\n");
            break;
        }
        case 0x32: {
            web49_error("unknown opcode 0x32\n");
            break;
        }
        case 0x33: {
            web49_error("unknown opcode 0x33\n");
            break;
        }
        case 0x34: {
            web49_error("unknown opcode 0x34\n");
            break;
        }
        case 0x35: {
            web49_error("unknown opcode 0x35\n");
            break;
        }
        case 0x36: {
            web49_error("unknown opcode 0x36\n");
            break;
        }
        case 0x37: {
            web49_error("unknown opcode 0x37\n");
            break;
        }
        case 0x38: {
            web49_error("unknown opcode 0x38\n");
            break;
        }
        case 0x39: {
            web49_error("unknown opcode 0x39\n");
            break;
        }
        case 0x3a: {
            web49_error("unknown opcode 0x3a\n");
            break;
        }
        case 0x3b: {
            web49_error("unknown opcode 0x3b\n");
            break;
        }
        case 0x3c: {
            web49_error("unknown opcode 0x3c\n");
            break;
        }
        case 0x3d: {
            web49_error("unknown opcode 0x3d\n");
            break;
        }
        case 0x3e: {
            web49_error("unknown opcode 0x3e\n");
            break;
        }
        case 0x3f: {
            web49_error("unknown opcode 0x3f\n");
            break;
        }
        case 0x40: {
            web49_error("unknown opcode 0x40\n");
            break;
        }
        case 0x41: {
            web49_error("unknown opcode 0x41\n");
            break;
        }
        case 0x42: {
            web49_error("unknown opcode 0x42\n");
            break;
        }
        case 0x43: {
            web49_error("unknown opcode 0x43\n");
            break;
        }
        case 0x44: {
            web49_error("unknown opcode 0x44\n");
            break;
        }
        case 0x45: {
            web49_error("unknown opcode 0x45\n");
            break;
        }
        case 0x46: {
            web49_error("unknown opcode 0x46\n");
            break;
        }
        case 0x47: {
            web49_error("unknown opcode 0x47\n");
            break;
        }
        case 0x48: {
            web49_error("unknown opcode 0x48\n");
            break;
        }
        case 0x49: {
            web49_error("unknown opcode 0x49\n");
            break;
        }
        case 0x4a: {
            web49_error("unknown opcode 0x4a\n");
            break;
        }
        case 0x4b: {
            web49_error("unknown opcode 0x4b\n");
            break;
        }
        case 0x4c: {
            web49_error("unknown opcode 0x4c\n");
            break;
        }
        case 0x4d: {
            web49_error("unknown opcode 0x4d\n");
            break;
        }
        case 0x4e: {
            web49_error("unknown opcode 0x4e\n");
            break;
        }
        case 0x4f: {
            web49_error("unknown opcode 0x4f\n");
            break;
        }
        case 0x50: {
            web49_error("unknown opcode 0x50\n");
            break;
        }
        case 0x51: {
            web49_error("unknown opcode 0x51\n");
            break;
        }
        case 0x52: {
            web49_error("unknown opcode 0x52\n");
            break;
        }
        case 0x53: {
            web49_error("unknown opcode 0x53\n");
            break;
        }
        case 0x54: {
            web49_error("unknown opcode 0x54\n");
            break;
        }
        case 0x55: {
            web49_error("unknown opcode 0x55\n");
            break;
        }
        case 0x56: {
            web49_error("unknown opcode 0x56\n");
            break;
        }
        case 0x57: {
            web49_error("unknown opcode 0x57\n");
            break;
        }
        case 0x58: {
            web49_error("unknown opcode 0x58\n");
            break;
        }
        case 0x59: {
            web49_error("unknown opcode 0x59\n");
            break;
        }
        case 0x5a: {
            web49_error("unknown opcode 0x5a\n");
            break;
        }
        case 0x5b: {
            web49_error("unknown opcode 0x5b\n");
            break;
        }
        case 0x5c: {
            web49_error("unknown opcode 0x5c\n");
            break;
        }
        case 0x5d: {
            web49_error("unknown opcode 0x5d\n");
            break;
        }
        case 0x5e: {
            web49_error("unknown opcode 0x5e\n");
            break;
        }
        case 0x5f: {
            web49_error("unknown opcode 0x5f\n");
            break;
        }
        case 0x60: {
            web49_error("unknown opcode 0x60\n");
            break;
        }
        case 0x61: {
            web49_error("unknown opcode 0x61\n");
            break;
        }
        case 0x62: {
            web49_error("unknown opcode 0x62\n");
            break;
        }
        case 0x63: {
            web49_error("unknown opcode 0x63\n");
            break;
        }
        case 0x64: {
            web49_error("unknown opcode 0x64\n");
            break;
        }
        case 0x65: {
            web49_error("unknown opcode 0x65\n");
            break;
        }
        case 0x66: {
            web49_error("unknown opcode 0x66\n");
            break;
        }
        case 0x67: {
            web49_error("unknown opcode 0x67\n");
            break;
        }
        case 0x68: {
            web49_error("unknown opcode 0x68\n");
            break;
        }
        case 0x69: {
            web49_error("unknown opcode 0x69\n");
            break;
        }
        case 0x6a: {
            web49_error("unknown opcode 0x6a\n");
            break;
        }
        case 0x6b: {
            web49_error("unknown opcode 0x6b\n");
            break;
        }
        case 0x6c: {
            web49_error("unknown opcode 0x6c\n");
            break;
        }
        case 0x6d: {
            web49_error("unknown opcode 0x6d\n");
            break;
        }
        case 0x6e: {
            web49_error("unknown opcode 0x6e\n");
            break;
        }
        case 0x6f: {
            web49_error("unknown opcode 0x6f\n");
            break;
        }
        case 0x70: {
            web49_error("unknown opcode 0x70\n");
            break;
        }
        case 0x71: {
            web49_error("unknown opcode 0x71\n");
            break;
        }
        case 0x72: {
            web49_error("unknown opcode 0x72\n");
            break;
        }
        case 0x73: {
            web49_error("unknown opcode 0x73\n");
            break;
        }
        case 0x74: {
            web49_error("unknown opcode 0x74\n");
            break;
        }
        case 0x75: {
            web49_error("unknown opcode 0x75\n");
            break;
        }
        case 0x76: {
            web49_error("unknown opcode 0x76\n");
            break;
        }
        case 0x77: {
            web49_error("unknown opcode 0x77\n");
            break;
        }
        case 0x78: {
            web49_error("unknown opcode 0x78\n");
            break;
        }
        case 0x79: {
            web49_error("unknown opcode 0x79\n");
            break;
        }
        case 0x7a: {
            web49_error("unknown opcode 0x7a\n");
            break;
        }
        case 0x7b: {
            web49_error("unknown opcode 0x7b\n");
            break;
        }
        case 0x7c: {
            web49_error("unknown opcode 0x7c\n");
            break;
        }
        case 0x7d: {
            web49_error("unknown opcode 0x7d\n");
            break;
        }
        case 0x7e: {
            web49_error("unknown opcode 0x7e\n");
            break;
        }
        case 0x7f: {
            web49_error("unknown opcode 0x7f\n");
            break;
        }
        case 0x80: {
            web49_error("unknown opcode 0x80\n");
            break;
        }
        case 0x81: {
            web49_error("unknown opcode 0x81\n");
            break;
        }
        case 0x82: {
            web49_error("unknown opcode 0x82\n");
            break;
        }
        case 0x83: {
            web49_error("unknown opcode 0x83\n");
            break;
        }
        case 0x84: {
            web49_error("unknown opcode 0x84\n");
            break;
        }
        case 0x85: {
            web49_error("unknown opcode 0x85\n");
            break;
        }
        case 0x86: {
            web49_error("unknown opcode 0x86\n");
            break;
        }
        case 0x87: {
            web49_error("unknown opcode 0x87\n");
            break;
        }
        case 0x88: {
            web49_error("unknown opcode 0x88\n");
            break;
        }
        case 0x89: {
            web49_error("unknown opcode 0x89\n");
            break;
        }
        case 0x8a: {
            web49_error("unknown opcode 0x8a\n");
            break;
        }
        case 0x8b: {
            web49_error("unknown opcode 0x8b\n");
            break;
        }
        case 0x8c: {
            web49_error("unknown opcode 0x8c\n");
            break;
        }
        case 0x8d: {
            web49_error("unknown opcode 0x8d\n");
            break;
        }
        case 0x8e: {
            web49_error("unknown opcode 0x8e\n");
            break;
        }
        case 0x8f: {
            web49_error("unknown opcode 0x8f\n");
            break;
        }
        case 0x90: {
            web49_error("unknown opcode 0x90\n");
            break;
        }
        case 0x91: {
            web49_error("unknown opcode 0x91\n");
            break;
        }
        case 0x92: {
            web49_error("unknown opcode 0x92\n");
            break;
        }
        case 0x93: {
            web49_error("unknown opcode 0x93\n");
            break;
        }
        case 0x94: {
            web49_error("unknown opcode 0x94\n");
            break;
        }
        case 0x95: {
            web49_error("unknown opcode 0x95\n");
            break;
        }
        case 0x96: {
            web49_error("unknown opcode 0x96\n");
            break;
        }
        case 0x97: {
            web49_error("unknown opcode 0x97\n");
            break;
        }
        case 0x98: {
            web49_error("unknown opcode 0x98\n");
            break;
        }
        case 0x99: {
            web49_error("unknown opcode 0x99\n");
            break;
        }
        case 0x9a: {
            web49_error("unknown opcode 0x9a\n");
            break;
        }
        case 0x9b: {
            web49_error("unknown opcode 0x9b\n");
            break;
        }
        case 0x9c: {
            web49_error("unknown opcode 0x9c\n");
            break;
        }
        case 0x9d: {
            web49_error("unknown opcode 0x9d\n");
            break;
        }
        case 0x9e: {
            web49_error("unknown opcode 0x9e\n");
            break;
        }
        case 0x9f: {
            web49_error("unknown opcode 0x9f\n");
            break;
        }
        case 0xa0: {
            web49_error("unknown opcode 0xa0\n");
            break;
        }
        case 0xa1: {
            web49_error("unknown opcode 0xa1\n");
            break;
        }
        case 0xa2: {
            web49_error("unknown opcode 0xa2\n");
            break;
        }
        case 0xa3: {
            web49_error("unknown opcode 0xa3\n");
            break;
        }
        case 0xa4: {
            web49_error("unknown opcode 0xa4\n");
            break;
        }
        case 0xa5: {
            web49_error("unknown opcode 0xa5\n");
            break;
        }
        case 0xa6: {
            web49_error("unknown opcode 0xa6\n");
            break;
        }
        case 0xa7: {
            web49_error("unknown opcode 0xa7\n");
            break;
        }
        case 0xa8: {
            web49_error("unknown opcode 0xa8\n");
            break;
        }
        case 0xa9: {
            web49_error("unknown opcode 0xa9\n");
            break;
        }
        case 0xaa: {
            web49_error("unknown opcode 0xaa\n");
            break;
        }
        case 0xab: {
            web49_error("unknown opcode 0xab\n");
            break;
        }
        case 0xac: {
            web49_error("unknown opcode 0xac\n");
            break;
        }
        case 0xad: {
            web49_error("unknown opcode 0xad\n");
            break;
        }
        case 0xae: {
            web49_error("unknown opcode 0xae\n");
            break;
        }
        case 0xaf: {
            web49_error("unknown opcode 0xaf\n");
            break;
        }
        case 0xb0: {
            web49_error("unknown opcode 0xb0\n");
            break;
        }
        case 0xb1: {
            web49_error("unknown opcode 0xb1\n");
            break;
        }
        case 0xb2: {
            web49_error("unknown opcode 0xb2\n");
            break;
        }
        case 0xb3: {
            web49_error("unknown opcode 0xb3\n");
            break;
        }
        case 0xb4: {
            web49_error("unknown opcode 0xb4\n");
            break;
        }
        case 0xb5: {
            web49_error("unknown opcode 0xb5\n");
            break;
        }
        case 0xb6: {
            web49_error("unknown opcode 0xb6\n");
            break;
        }
        case 0xb7: {
            web49_error("unknown opcode 0xb7\n");
            break;
        }
        case 0xb8: {
            web49_error("unknown opcode 0xb8\n");
            break;
        }
        case 0xb9: {
            web49_error("unknown opcode 0xb9\n");
            break;
        }
        case 0xba: {
            web49_error("unknown opcode 0xba\n");
            break;
        }
        case 0xbb: {
            web49_error("unknown opcode 0xbb\n");
            break;
        }
        case 0xbc: {
            web49_error("unknown opcode 0xbc\n");
            break;
        }
        case 0xbd: {
            web49_error("unknown opcode 0xbd\n");
            break;
        }
        case 0xbe: {
            web49_error("unknown opcode 0xbe\n");
            break;
        }
        case 0xbf: {
            web49_error("unknown opcode 0xbf\n");
            break;
        }
        case 0xc0: {
            web49_error("unknown opcode 0xc0\n");
            break;
        }
        case 0xc1: {
            web49_error("unknown opcode 0xc1\n");
            break;
        }
        case 0xc2: {
            web49_error("unknown opcode 0xc2\n");
            break;
        }
        case 0xc3: {
            web49_error("unknown opcode 0xc3\n");
            break;
        }
        case 0xc4: {
            web49_error("unknown opcode 0xc4\n");
            break;
        }
        case 0xc5: {
            web49_error("unknown opcode 0xc5\n");
            break;
        }
        case 0xc6: {
            web49_error("unknown opcode 0xc6\n");
            break;
        }
        case 0xc7: {
            web49_error("unknown opcode 0xc7\n");
            break;
        }
        case 0xc8: {
            web49_error("unknown opcode 0xc8\n");
            break;
        }
        case 0xc9: {
            web49_error("unknown opcode 0xc9\n");
            break;
        }
        case 0xca: {
            web49_error("unknown opcode 0xca\n");
            break;
        }
        case 0xcb: {
            web49_error("unknown opcode 0xcb\n");
            break;
        }
        case 0xcc: {
            web49_error("unknown opcode 0xcc\n");
            break;
        }
        case 0xcd: {
            web49_error("unknown opcode 0xcd\n");
            break;
        }
        case 0xce: {
            web49_error("unknown opcode 0xce\n");
            break;
        }
        case 0xcf: {
            web49_error("unknown opcode 0xcf\n");
            break;
        }
        case 0xd0: {
            web49_error("unknown opcode 0xd0\n");
            break;
        }
        case 0xd1: {
            web49_error("unknown opcode 0xd1\n");
            break;
        }
        case 0xd2: {
            web49_error("unknown opcode 0xd2\n");
            break;
        }
        case 0xd3: {
            web49_error("unknown opcode 0xd3\n");
            break;
        }
        case 0xd4: {
            web49_error("unknown opcode 0xd4\n");
            break;
        }
        case 0xd5: {
            web49_error("unknown opcode 0xd5\n");
            break;
        }
        case 0xd6: {
            web49_error("unknown opcode 0xd6\n");
            break;
        }
        case 0xd7: {
            web49_error("unknown opcode 0xd7\n");
            break;
        }
        case 0xd8: {
            web49_error("unknown opcode 0xd8\n");
            break;
        }
        case 0xd9: {
            web49_error("unknown opcode 0xd9\n");
            break;
        }
        case 0xda: {
            web49_error("unknown opcode 0xda\n");
            break;
        }
        case 0xdb: {
            web49_error("unknown opcode 0xdb\n");
            break;
        }
        case 0xdc: {
            web49_error("unknown opcode 0xdc\n");
            break;
        }
        case 0xdd: {
            web49_error("unknown opcode 0xdd\n");
            break;
        }
        case 0xde: {
            web49_error("unknown opcode 0xde\n");
            break;
        }
        case 0xdf: {
            web49_error("unknown opcode 0xdf\n");
            break;
        }
        case 0xe0: {
            web49_error("unknown opcode 0xe0\n");
            break;
        }
        case 0xe1: {
            web49_error("unknown opcode 0xe1\n");
            break;
        }
        case 0xe2: {
            web49_error("unknown opcode 0xe2\n");
            break;
        }
        case 0xe3: {
            web49_error("unknown opcode 0xe3\n");
            break;
        }
        case 0xe4: {
            web49_error("unknown opcode 0xe4\n");
            break;
        }
        case 0xe5: {
            web49_error("unknown opcode 0xe5\n");
            break;
        }
        case 0xe6: {
            web49_error("unknown opcode 0xe6\n");
            break;
        }
        case 0xe7: {
            web49_error("unknown opcode 0xe7\n");
            break;
        }
        case 0xe8: {
            web49_error("unknown opcode 0xe8\n");
            break;
        }
        case 0xe9: {
            web49_error("unknown opcode 0xe9\n");
            break;
        }
        case 0xea: {
            web49_error("unknown opcode 0xea\n");
            break;
        }
        case 0xeb: {
            web49_error("unknown opcode 0xeb\n");
            break;
        }
        case 0xec: {
            web49_error("unknown opcode 0xec\n");
            break;
        }
        case 0xed: {
            web49_error("unknown opcode 0xed\n");
            break;
        }
        case 0xee: {
            web49_error("unknown opcode 0xee\n");
            break;
        }
        case 0xef: {
            web49_error("unknown opcode 0xef\n");
            break;
        }
        case 0xf0: {
            web49_error("unknown opcode 0xf0\n");
            break;
        }
        case 0xf1: {
            web49_error("unknown opcode 0xf1\n");
            break;
        }
        case 0xf2: {
            web49_error("unknown opcode 0xf2\n");
            break;
        }
        case 0xf3: {
            web49_error("unknown opcode 0xf3\n");
            break;
        }
        case 0xf4: {
            web49_error("unknown opcode 0xf4\n");
            break;
        }
        case 0xf5: {
            web49_error("unknown opcode 0xf5\n");
            break;
        }
        case 0xf6: {
            web49_error("unknown opcode 0xf6\n");
            break;
        }
        case 0xf7: {
            web49_error("unknown opcode 0xf7\n");
            break;
        }
        case 0xf8: {
            web49_error("unknown opcode 0xf8\n");
            break;
        }
        case 0xf9: {
            web49_error("unknown opcode 0xf9\n");
            break;
        }
        case 0xfa: {
            web49_error("unknown opcode 0xfa\n");
            break;
        }
        case 0xfb: {
            web49_error("unknown opcode 0xfb\n");
            break;
        }
        case 0xfc: {
            web49_error("unknown opcode 0xfc\n");
            break;
        }
        case 0xfd: {
            web49_error("unknown opcode 0xfd\n");
            break;
        }
        case 0xfe: {
            web49_error("unknown opcode 0xfe\n");
            break;
        }
        case 0xff: {
            web49_error("unknown opcode 0xff\n");
            break;
        }
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
        case WEB49_OPCODE_BEGIN0:
            return "begin0";
        case WEB49_OPCODE_MEMORY_INIT:
            return "memory.init";
        case WEB49_OPCODE_MEMORY_COPY:
            return "memory.copy";
        case WEB49_OPCODE_MEMORY_FILL:
            return "memory.fill";
        case WEB49_OPCODE_DATA_DROP:
            return "data.drop";
        case WEB49_OPCODE_TABLE_INIT:
            return "table.init";
        case WEB49_OPCODE_ELEM_DROP:
            return "elem.drop";
        case WEB49_OPCODE_TABLE_COPY:
            return "table.copy";
        default:
            return NULL;
    }
}
