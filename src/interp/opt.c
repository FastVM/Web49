#include "interp.h"

web49_instr_t web49_interp_opt(web49_instr_t cur) {
    for (uint64_t i = 0; i < cur.nargs; i++) {
        cur.args[i] = web49_interp_opt(cur.args[i]);
    }
    web49_instr_t next = cur;
    if (cur.nargs != 0 && cur.args[cur.nargs - 1].opcode == WEB49_OPCODE_I32_CONST) {
        if (cur.opcode == WEB49_OPCODE_I32_EQ) {
            next.opcode = WEB49_OPCODE_I32_EQ_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_NE) {
            next.opcode = WEB49_OPCODE_I32_NE_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LT_S) {
            next.opcode = WEB49_OPCODE_I32_LT_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LT_U) {
            next.opcode = WEB49_OPCODE_I32_LT_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GT_S) {
            next.opcode = WEB49_OPCODE_I32_GT_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GT_U) {
            next.opcode = WEB49_OPCODE_I32_GT_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LE_S) {
            next.opcode = WEB49_OPCODE_I32_LE_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LE_U) {
            next.opcode = WEB49_OPCODE_I32_LE_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GE_S) {
            next.opcode = WEB49_OPCODE_I32_GE_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GE_U) {
            next.opcode = WEB49_OPCODE_I32_GE_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ADD) {
            next.opcode = WEB49_OPCODE_I32_ADD_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SUB) {
            next.opcode = WEB49_OPCODE_I32_SUB_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_MUL) {
            next.opcode = WEB49_OPCODE_I32_MUL_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_DIV_S) {
            next.opcode = WEB49_OPCODE_I32_DIV_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_DIV_U) {
            next.opcode = WEB49_OPCODE_I32_DIV_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_REM_S) {
            next.opcode = WEB49_OPCODE_I32_REM_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_REM_U) {
            next.opcode = WEB49_OPCODE_I32_REM_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_AND) {
            next.opcode = WEB49_OPCODE_I32_AND_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_OR) {
            next.opcode = WEB49_OPCODE_I32_OR_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_XOR) {
            next.opcode = WEB49_OPCODE_I32_XOR_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHL) {
            next.opcode = WEB49_OPCODE_I32_SHL_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHR_S) {
            next.opcode = WEB49_OPCODE_I32_SHR_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHR_U) {
            next.opcode = WEB49_OPCODE_I32_SHR_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ROTL) {
            next.opcode = WEB49_OPCODE_I32_ROTL_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ROTR) {
            next.opcode = WEB49_OPCODE_I32_ROTR_TOP_CONST;
            next.nargs -= 1;
        }
    }
    if (cur.nargs != 0 && cur.args[cur.nargs - 1].opcode == WEB49_OPCODE_GET_LOCAL) {
        if (cur.opcode == WEB49_OPCODE_I32_EQ_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_EQ_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_NE_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_NE_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LT_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_LT_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LT_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_LT_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GT_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_GT_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GT_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_GT_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LE_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_LE_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LE_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_LE_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GE_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_GE_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GE_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_GE_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ADD_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_ADD_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SUB_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_SUB_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_MUL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_MUL_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_DIV_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_DIV_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_DIV_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_DIV_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_REM_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_REM_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_REM_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_REM_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_AND_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_AND_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_OR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_OR_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_XOR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_XOR_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_SHL_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHR_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_SHR_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHR_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_SHR_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ROTL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_ROTL_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ROTR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_ROTR_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
    }
    if (cur.opcode == WEB49_OPCODE_SET_LOCAL && cur.nargs == 1) {
        if (cur.args[0].opcode == WEB49_OPCODE_I32_EQ) {
            next.opcode = WEB49_OPCODE_I32_EQ_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_NE) {
            next.opcode = WEB49_OPCODE_I32_NE_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_S) {
            next.opcode = WEB49_OPCODE_I32_LT_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_U) {
            next.opcode = WEB49_OPCODE_I32_LT_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_S) {
            next.opcode = WEB49_OPCODE_I32_GT_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_U) {
            next.opcode = WEB49_OPCODE_I32_GT_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_S) {
            next.opcode = WEB49_OPCODE_I32_LE_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_U) {
            next.opcode = WEB49_OPCODE_I32_LE_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_S) {
            next.opcode = WEB49_OPCODE_I32_GE_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_U) {
            next.opcode = WEB49_OPCODE_I32_GE_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ADD) {
            next.opcode = WEB49_OPCODE_I32_ADD_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SUB) {
            next.opcode = WEB49_OPCODE_I32_SUB_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_MUL) {
            next.opcode = WEB49_OPCODE_I32_MUL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_S) {
            next.opcode = WEB49_OPCODE_I32_DIV_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_U) {
            next.opcode = WEB49_OPCODE_I32_DIV_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_S) {
            next.opcode = WEB49_OPCODE_I32_REM_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_U) {
            next.opcode = WEB49_OPCODE_I32_REM_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_AND) {
            next.opcode = WEB49_OPCODE_I32_AND_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_OR) {
            next.opcode = WEB49_OPCODE_I32_OR_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_XOR) {
            next.opcode = WEB49_OPCODE_I32_XOR_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHL) {
            next.opcode = WEB49_OPCODE_I32_SHL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_S) {
            next.opcode = WEB49_OPCODE_I32_SHR_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_U) {
            next.opcode = WEB49_OPCODE_I32_SHR_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTL) {
            next.opcode = WEB49_OPCODE_I32_ROTL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTR) {
            next.opcode = WEB49_OPCODE_I32_ROTR_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_EQ_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_EQ_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_NE_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_NE_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_LT_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_LT_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_GT_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_GT_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_LE_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_LE_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_GE_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_GE_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ADD_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_ADD_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SUB_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_SUB_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_MUL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_MUL_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_DIV_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_DIV_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_REM_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_REM_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_AND_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_AND_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_OR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_OR_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_XOR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_XOR_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_SHL_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_SHR_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_SHR_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_ROTL_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I32_ROTR_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_EQ_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_EQ_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_NE_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_NE_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_LT_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_LT_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_GT_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_GT_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_LE_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_LE_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_GE_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_GE_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ADD_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_ADD_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SUB_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_SUB_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_MUL_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_MUL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_DIV_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_DIV_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_REM_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_REM_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_AND_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_AND_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_OR_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_OR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_XOR_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_XOR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHL_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_SHL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_SHR_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_SHR_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTL_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_ROTL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTR_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I32_ROTR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
    }
    // i64
    if (cur.nargs != 0 && cur.args[cur.nargs - 1].opcode == WEB49_OPCODE_I64_CONST) {
        if (cur.opcode == WEB49_OPCODE_I64_EQ) {
            next.opcode = WEB49_OPCODE_I64_EQ_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_NE) {
            next.opcode = WEB49_OPCODE_I64_NE_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_LT_S) {
            next.opcode = WEB49_OPCODE_I64_LT_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_LT_U) {
            next.opcode = WEB49_OPCODE_I64_LT_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_GT_S) {
            next.opcode = WEB49_OPCODE_I64_GT_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_GT_U) {
            next.opcode = WEB49_OPCODE_I64_GT_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_LE_S) {
            next.opcode = WEB49_OPCODE_I64_LE_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_LE_U) {
            next.opcode = WEB49_OPCODE_I64_LE_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_GE_S) {
            next.opcode = WEB49_OPCODE_I64_GE_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_GE_U) {
            next.opcode = WEB49_OPCODE_I64_GE_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_ADD) {
            next.opcode = WEB49_OPCODE_I64_ADD_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_SUB) {
            next.opcode = WEB49_OPCODE_I64_SUB_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_MUL) {
            next.opcode = WEB49_OPCODE_I64_MUL_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_DIV_S) {
            next.opcode = WEB49_OPCODE_I64_DIV_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_DIV_U) {
            next.opcode = WEB49_OPCODE_I64_DIV_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_REM_S) {
            next.opcode = WEB49_OPCODE_I64_REM_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_REM_U) {
            next.opcode = WEB49_OPCODE_I64_REM_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_AND) {
            next.opcode = WEB49_OPCODE_I64_AND_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_OR) {
            next.opcode = WEB49_OPCODE_I64_OR_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_XOR) {
            next.opcode = WEB49_OPCODE_I64_XOR_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_SHL) {
            next.opcode = WEB49_OPCODE_I64_SHL_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_SHR_S) {
            next.opcode = WEB49_OPCODE_I64_SHR_S_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_SHR_U) {
            next.opcode = WEB49_OPCODE_I64_SHR_U_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_ROTL) {
            next.opcode = WEB49_OPCODE_I64_ROTL_TOP_CONST;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_ROTR) {
            next.opcode = WEB49_OPCODE_I64_ROTR_TOP_CONST;
            next.nargs -= 1;
        }
    }
    if (cur.nargs != 0 && cur.args[cur.nargs - 1].opcode == WEB49_OPCODE_GET_LOCAL) {
        if (cur.opcode == WEB49_OPCODE_I64_EQ_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_EQ_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_NE_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_NE_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_LT_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_LT_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_LT_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_LT_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_GT_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_GT_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_GT_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_GT_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_LE_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_LE_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_LE_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_LE_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_GE_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_GE_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_GE_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_GE_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_ADD_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_ADD_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_SUB_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_SUB_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_MUL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_MUL_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_DIV_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_DIV_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_DIV_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_DIV_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_REM_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_REM_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_REM_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_REM_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_AND_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_AND_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_OR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_OR_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_XOR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_XOR_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_SHL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_SHL_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_SHR_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_SHR_S_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_SHR_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_SHR_U_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_ROTL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_ROTL_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I64_ROTR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_ROTR_TOP_CONST_NEXT_LOCAL;
            next.nargs -= 1;
        }
    }
    if (cur.opcode == WEB49_OPCODE_SET_LOCAL && cur.nargs == 1) {
        if (cur.args[0].opcode == WEB49_OPCODE_I64_EQ) {
            next.opcode = WEB49_OPCODE_I64_EQ_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_NE) {
            next.opcode = WEB49_OPCODE_I64_NE_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LT_S) {
            next.opcode = WEB49_OPCODE_I64_LT_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LT_U) {
            next.opcode = WEB49_OPCODE_I64_LT_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GT_S) {
            next.opcode = WEB49_OPCODE_I64_GT_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GT_U) {
            next.opcode = WEB49_OPCODE_I64_GT_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LE_S) {
            next.opcode = WEB49_OPCODE_I64_LE_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LE_U) {
            next.opcode = WEB49_OPCODE_I64_LE_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GE_S) {
            next.opcode = WEB49_OPCODE_I64_GE_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GE_U) {
            next.opcode = WEB49_OPCODE_I64_GE_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ADD) {
            next.opcode = WEB49_OPCODE_I64_ADD_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SUB) {
            next.opcode = WEB49_OPCODE_I64_SUB_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_MUL) {
            next.opcode = WEB49_OPCODE_I64_MUL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_DIV_S) {
            next.opcode = WEB49_OPCODE_I64_DIV_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_DIV_U) {
            next.opcode = WEB49_OPCODE_I64_DIV_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_REM_S) {
            next.opcode = WEB49_OPCODE_I64_REM_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_REM_U) {
            next.opcode = WEB49_OPCODE_I64_REM_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_AND) {
            next.opcode = WEB49_OPCODE_I64_AND_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_OR) {
            next.opcode = WEB49_OPCODE_I64_OR_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_XOR) {
            next.opcode = WEB49_OPCODE_I64_XOR_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHL) {
            next.opcode = WEB49_OPCODE_I64_SHL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHR_S) {
            next.opcode = WEB49_OPCODE_I64_SHR_S_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHR_U) {
            next.opcode = WEB49_OPCODE_I64_SHR_U_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ROTL) {
            next.opcode = WEB49_OPCODE_I64_ROTL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ROTR) {
            next.opcode = WEB49_OPCODE_I64_ROTR_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_EQ_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_EQ_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_NE_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_NE_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LT_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_LT_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LT_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_LT_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GT_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_GT_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GT_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_GT_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LE_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_LE_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LE_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_LE_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GE_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_GE_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GE_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_GE_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ADD_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_ADD_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SUB_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_SUB_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_MUL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_MUL_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_DIV_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_DIV_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_DIV_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_DIV_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_REM_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_REM_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_REM_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_REM_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_AND_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_AND_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_OR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_OR_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_XOR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_XOR_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_SHL_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHR_S_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_SHR_S_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHR_U_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_SHR_U_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ROTL_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_ROTL_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ROTR_TOP_CONST) {
            next.opcode = WEB49_OPCODE_I64_ROTR_TOP_CONST_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_EQ_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_EQ_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_NE_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_NE_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LT_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_LT_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LT_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_LT_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GT_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_GT_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GT_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_GT_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LE_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_LE_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_LE_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_LE_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GE_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_GE_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_GE_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_GE_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ADD_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_ADD_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SUB_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_SUB_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_MUL_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_MUL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_DIV_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_DIV_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_DIV_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_DIV_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_REM_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_REM_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_REM_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_REM_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_AND_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_AND_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_OR_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_OR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_XOR_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_XOR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHL_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_SHL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHR_S_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_SHR_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_SHR_U_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_SHR_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ROTL_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_ROTL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I64_ROTR_TOP_CONST_NEXT_LOCAL) {
            next.opcode = WEB49_OPCODE_I64_ROTR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            next.nargs = cur.args[0].nargs;
            next.args = cur.args[0].args;
        }
    }
    return next;
}
