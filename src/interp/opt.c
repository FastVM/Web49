#include "interp.h"

web49_instr_t web49_interp_opt(web49_instr_t cur) {
    for (uint64_t i = 0; i < cur.nargs; i++) {
        cur.args[i] = web49_interp_opt(cur.args[i]);
    }
    if (cur.nargs != 0 && cur.args[cur.nargs - 1].opcode == WEB49_OPCODE_I32_CONST) {
        if (cur.opcode == WEB49_OPCODE_I32_EQ) {
            cur.opcode = WEB49_OPCODE_I32_EQ_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_NE) {
            cur.opcode = WEB49_OPCODE_I32_NE_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LT_S) {
            cur.opcode = WEB49_OPCODE_I32_LT_S_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LT_U) {
            cur.opcode = WEB49_OPCODE_I32_LT_U_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GT_S) {
            cur.opcode = WEB49_OPCODE_I32_GT_S_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GT_U) {
            cur.opcode = WEB49_OPCODE_I32_GT_U_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LE_S) {
            cur.opcode = WEB49_OPCODE_I32_LE_S_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LE_U) {
            cur.opcode = WEB49_OPCODE_I32_LE_U_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GE_S) {
            cur.opcode = WEB49_OPCODE_I32_GE_S_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GE_U) {
            cur.opcode = WEB49_OPCODE_I32_GE_U_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ADD) {
            cur.opcode = WEB49_OPCODE_I32_ADD_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SUB) {
            cur.opcode = WEB49_OPCODE_I32_SUB_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_MUL) {
            cur.opcode = WEB49_OPCODE_I32_MUL_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_DIV_S) {
            cur.opcode = WEB49_OPCODE_I32_DIV_S_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_DIV_U) {
            cur.opcode = WEB49_OPCODE_I32_DIV_U_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_REM_S) {
            cur.opcode = WEB49_OPCODE_I32_REM_S_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_REM_U) {
            cur.opcode = WEB49_OPCODE_I32_REM_U_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_AND) {
            cur.opcode = WEB49_OPCODE_I32_AND_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_OR) {
            cur.opcode = WEB49_OPCODE_I32_OR_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_XOR) {
            cur.opcode = WEB49_OPCODE_I32_XOR_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHL) {
            cur.opcode = WEB49_OPCODE_I32_SHL_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHR_S) {
            cur.opcode = WEB49_OPCODE_I32_SHR_S_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHR_U) {
            cur.opcode = WEB49_OPCODE_I32_SHR_U_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ROTL) {
            cur.opcode = WEB49_OPCODE_I32_ROTL_TOP_CONST;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ROTR) {
            cur.opcode = WEB49_OPCODE_I32_ROTR_TOP_CONST;
            cur.nargs -= 1;
        }
    }
    if (cur.nargs != 0 && cur.args[cur.nargs - 1].opcode == WEB49_OPCODE_GET_LOCAL) {
        if (cur.opcode == WEB49_OPCODE_I32_EQ_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_EQ_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_NE_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_NE_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LT_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_LT_S_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LT_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_LT_U_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GT_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_GT_S_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GT_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_GT_U_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LE_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_LE_S_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_LE_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_LE_U_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GE_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_GE_S_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_GE_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_GE_U_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ADD_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_ADD_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SUB_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_SUB_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_MUL_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_MUL_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_DIV_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_DIV_S_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_DIV_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_DIV_U_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_REM_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_REM_S_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_REM_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_REM_U_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_AND_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_AND_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_OR_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_OR_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_XOR_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_XOR_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHL_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_SHL_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHR_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_SHR_S_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_SHR_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_SHR_U_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ROTL_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_ROTL_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
        if (cur.opcode == WEB49_OPCODE_I32_ROTR_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_ROTR_TOP_CONST_NEXT_LOCAL;
            cur.nargs -= 1;
        }
    }
    if (cur.opcode == WEB49_OPCODE_SET_LOCAL && cur.nargs == 1) {
        if (cur.args[0].opcode == WEB49_OPCODE_I32_EQ) {
            cur.opcode =  WEB49_OPCODE_I32_EQ_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_NE) {
            cur.opcode =  WEB49_OPCODE_I32_NE_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_S) {
            cur.opcode =  WEB49_OPCODE_I32_LT_S_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_U) {
            cur.opcode =  WEB49_OPCODE_I32_LT_U_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_S) {
            cur.opcode =  WEB49_OPCODE_I32_GT_S_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_U) {
            cur.opcode =  WEB49_OPCODE_I32_GT_U_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_S) {
            cur.opcode =  WEB49_OPCODE_I32_LE_S_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_U) {
            cur.opcode =  WEB49_OPCODE_I32_LE_U_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_S) {
            cur.opcode =  WEB49_OPCODE_I32_GE_S_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_U) {
            cur.opcode =  WEB49_OPCODE_I32_GE_U_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ADD) {
            cur.opcode =  WEB49_OPCODE_I32_ADD_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SUB) {
            cur.opcode =  WEB49_OPCODE_I32_SUB_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_MUL) {
            cur.opcode =  WEB49_OPCODE_I32_MUL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_S) {
            cur.opcode =  WEB49_OPCODE_I32_DIV_S_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_U) {
            cur.opcode =  WEB49_OPCODE_I32_DIV_U_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_S) {
            cur.opcode =  WEB49_OPCODE_I32_REM_S_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_U) {
            cur.opcode =  WEB49_OPCODE_I32_REM_U_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_AND) {
            cur.opcode =  WEB49_OPCODE_I32_AND_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_OR) {
            cur.opcode =  WEB49_OPCODE_I32_OR_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_XOR) {
            cur.opcode =  WEB49_OPCODE_I32_XOR_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHL) {
            cur.opcode =  WEB49_OPCODE_I32_SHL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_S) {
            cur.opcode =  WEB49_OPCODE_I32_SHR_S_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_U) {
            cur.opcode =  WEB49_OPCODE_I32_SHR_U_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTL) {
            cur.opcode =  WEB49_OPCODE_I32_ROTL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTR) {
            cur.opcode =  WEB49_OPCODE_I32_ROTR_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_EQ_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_EQ_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_NE_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_NE_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_LT_S_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_LT_U_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_GT_S_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_GT_U_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_LE_S_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_LE_U_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_GE_S_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_GE_U_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ADD_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_ADD_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SUB_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_SUB_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_MUL_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_MUL_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_DIV_S_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_DIV_U_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_REM_S_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_REM_U_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_AND_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_AND_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_OR_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_OR_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_XOR_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_XOR_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHL_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_SHL_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_S_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_SHR_S_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_U_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_SHR_U_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTL_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_ROTL_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTR_TOP_CONST) {
            cur.opcode = WEB49_OPCODE_I32_ROTR_TOP_CONST_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_EQ_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_EQ_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_NE_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_NE_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_S_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_LT_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LT_U_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_LT_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_S_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_GT_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GT_U_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_GT_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_S_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_LE_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_LE_U_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_LE_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_S_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_GE_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_GE_U_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_GE_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ADD_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_ADD_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SUB_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_SUB_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_MUL_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_MUL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_S_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_DIV_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_DIV_U_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_DIV_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_S_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_REM_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_REM_U_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_REM_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_AND_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_AND_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_OR_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_OR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_XOR_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_XOR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHL_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_SHL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_S_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_SHR_S_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_SHR_U_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_SHR_U_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTL_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_ROTL_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
        if (cur.args[0].opcode == WEB49_OPCODE_I32_ROTR_TOP_CONST_NEXT_LOCAL) {
            cur.opcode = WEB49_OPCODE_I32_ROTR_TOP_CONST_NEXT_LOCAL_TO_LOCAL;
            cur.immediate = cur.immediate;
            cur.nargs = cur.args[0].nargs;
            cur.args = cur.args[0].args;
        }
    }
    return cur;
}
