#include "table.h"

const web49_interp_table_t web49_interp_opcode_stack_effect[WEB49_MAX_OPCODE_INTERP_NUM] = {
    [WEB49_OPCODE_UNREACHABLE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_NOP] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_BLOCK] = (web49_interp_table_t){
        .branch = true,
    },
    [WEB49_OPCODE_LOOP] = (web49_interp_table_t){
        .branch = true,
    },
    [WEB49_OPCODE_IF] = (web49_interp_table_t){
        .branch = true,
    },
    [WEB49_OPCODE_ELSE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_END] = (web49_interp_table_t){
        .branch = true,
    },
    [WEB49_OPCODE_BR] = (web49_interp_table_t){
        .branch = true,
    },
    [WEB49_OPCODE_BR_IF] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .branch = true,
    },
    [WEB49_OPCODE_BR_TABLE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .branch = true,
    },
    [WEB49_OPCODE_RETURN] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_ANY,
        .branch = true,
    },
    [WEB49_OPCODE_CALL0] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_ARGS,
    },
    [WEB49_OPCODE_CALL1] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_ARGS,
        .out[0] = WEB49_INTERP_TABLE_ANY,
    },
    [WEB49_OPCODE_CALL_INDIRECT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_ARGS,
        .out[0] = WEB49_INTERP_TABLE_RET,
    },
    [WEB49_OPCODE_DROP] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_ANY,
    },
    [WEB49_OPCODE_SELECT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_ANY,
        .in[2] = WEB49_INTERP_TABLE_ANY,
        .out[0] = WEB49_INTERP_TABLE_ANY,
    },
    [WEB49_OPCODE_GET_LOCAL] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_ANY,
    },
    [WEB49_OPCODE_SET_LOCAL] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_ANY,
    },
    [WEB49_OPCODE_TEE_LOCAL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_ANY,
        .out[0] = WEB49_INTERP_TABLE_ANY,
    },
    [WEB49_OPCODE_GET_GLOBAL] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_ANY,
    },
    [WEB49_OPCODE_SET_GLOBAL] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_ANY,
    },
    [WEB49_OPCODE_I32_LOAD] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_LOAD] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_F32_LOAD] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F64_LOAD] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_I32_LOAD8_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_LOAD8_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_LOAD16_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_LOAD16_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_LOAD8_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_LOAD8_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_LOAD16_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_LOAD16_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_LOAD32_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_LOAD32_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I32_STORE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_STORE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F32_STORE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F64_STORE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_STORE8] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_STORE16] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_STORE8] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_STORE16] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_STORE32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_MEMORY_SIZE] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_MEMORY_GROW] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_CONST] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_CONST] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_F32_CONST] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F64_CONST] = (web49_interp_table_t){
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_I32_EQZ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_EQ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_NE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_LT_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_LT_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_GT_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_GT_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_LE_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_LE_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_GE_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_GE_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_EQZ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_EQ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_NE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_LT_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_LT_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_GT_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_GT_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_LE_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_LE_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_GE_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_GE_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F32_EQ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F32_NE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F32_LT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F32_GT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F32_LE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F32_GE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F64_EQ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F64_NE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F64_LT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F64_GT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F64_LE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_F64_GE] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_CLZ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_CTZ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_POPCNT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_ADD] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_SUB] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_MUL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_DIV_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_DIV_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_REM_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_REM_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_AND] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_OR] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_XOR] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_SHL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_SHR_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_SHR_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_ROTL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_ROTR] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .in[1] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_CLZ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_CTZ] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_POPCNT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_ADD] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_SUB] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_MUL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_DIV_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_DIV_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_REM_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_REM_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_AND] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_OR] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_XOR] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_SHL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_SHR_S] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_SHR_U] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_ROTL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_ROTR] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .in[1] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_F32_ABS] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_NEG] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_CEIL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_FLOOR] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_TRUNC] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_NEAREST] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_SQRT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_ADD] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_SUB] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_MUL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_DIV] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_MIN] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_MAX] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_COPYSIGN] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .in[1] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F64_ABS] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_NEG] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_CEIL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_FLOOR] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_TRUNC] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_NEAREST] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_SQRT] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_ADD] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_SUB] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_MUL] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_DIV] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_MIN] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_MAX] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .in[1] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_COPYSIGN] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_I32_WRAP_I64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_S_F32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_U_F32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_S_F64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I32_TRUNC_U_F64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_EXTEND_S_I32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_EXTEND_U_I32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_S_F32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_U_F32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_S_F64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_I64_TRUNC_U_F64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_F32_CONVERT_S_I32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_CONVERT_U_I32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_CONVERT_S_I64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_CONVERT_U_I64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F32_DEMOTE_F64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F64_CONVERT_S_I32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_CONVERT_U_I32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_CONVERT_S_I64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_CONVERT_U_I64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_F64_PROMOTE_F32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_I32_REINTERPRET_F32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F32,
        .out[0] = WEB49_INTERP_TABLE_I32,
    },
    [WEB49_OPCODE_I64_REINTERPRET_F64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_F64,
        .out[0] = WEB49_INTERP_TABLE_I64,
    },
    [WEB49_OPCODE_F32_REINTERPRET_I32] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I32,
        .out[0] = WEB49_INTERP_TABLE_F32,
    },
    [WEB49_OPCODE_F64_REINTERPRET_I64] = (web49_interp_table_t){
        .in[0] = WEB49_INTERP_TABLE_I64,
        .out[0] = WEB49_INTERP_TABLE_F64,
    },
    [WEB49_OPCODE_MEMORY_INIT] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_MEMORY_COPY] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_MEMORY_FILL] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_DATA_DROP] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_INIT] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_ELEM_DROP] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_TABLE_COPY] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_SEEK] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_FILESTAT_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_FILESTAT_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_ARGS_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_ARGS_SIZES_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_CLOCK_RES_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_CLOCK_TIME_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_ENVIRON_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_ENVIRON_SIZES_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_ADVISE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_ALLOCATE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_CLOSE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_DATASYNC] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_FDSTAT_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_FDSTAT_SET_FLAGS] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_FDSTAT_SET_RIGHTS] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_FILESTAT_SET_SIZE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_FILESTAT_SET_TIMES] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_PREAD] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_PRESTAT_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_PRESTAT_DIR_NAME] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_PWRITE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_READ] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_READDIR] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_RENUMBER] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_SYNC] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_TELL] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_FD_WRITE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_CREATE_DIRECTORY] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_FILESTAT_SET_TIMES] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_LINK] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_OPEN] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_READLINK] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_REMOVE_DIRECTORY] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_RENAME] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_SYMLINK] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PATH_UNLINK_FILE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_POLL_ONEOFF] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PROC_EXIT] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_PROC_RAISE] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_RANDOM_GET] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_SCHED_YIELD] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_SOCK_RECV] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_SOCK_SEND] = (web49_interp_table_t){
        .fail = true,
    },
    [WEB49_OPCODE_WASI_SOCK_SHUTDOWN] = (web49_interp_table_t){
        .fail = true,
    },
};
