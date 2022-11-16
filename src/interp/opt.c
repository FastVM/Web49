#include "interp.h"

web49_instr_t web49_interp_opt(web49_instr_t cur) {
    for (uint64_t i = 0; i < cur.nargs; i++) {
        cur.args[i] = web49_interp_opt(cur.args[i]);
    }
    web49_instr_t next = cur;
#define NAME(n) if (next.opcode == n) { next.opcode = n##_TO_STACK; }
#include "math.inc"
    if (next.nargs != 0 && next.args[next.nargs - 1].opcode == WEB49_OPCODE_I32_CONST) {
#define NAME(n) if (next.opcode == n##_TO_STACK) { next.opcode = n##_TOP_CONST_TO_STACK; next.nargs -= 1; }
#include "math.inc"
    }
    if (next.nargs != 0 && next.args[next.nargs - 1].opcode == WEB49_OPCODE_GET_LOCAL) {
#define NAME(n) if (next.opcode == n##_TO_STACK) { next.opcode = n##_TOP_LOCAL_TO_STACK; next.nargs -= 1; }
#include "math.inc"
    }
    if (next.nargs != 0 && next.args[next.nargs - 1].opcode == WEB49_OPCODE_GET_LOCAL) {
#define NAME(n) if (next.opcode == n##_TOP_CONST_TO_STACK) { next.opcode = n##_TOP_CONST_NEXT_LOCAL_TO_STACK; next.nargs -= 1; }
#include "math.inc"
#define NAME(n) if (next.opcode == n##_TOP_LOCAL_TO_STACK) { next.opcode = n##_TOP_LOCAL_NEXT_LOCAL_TO_STACK; next.nargs -= 1; }
#include "math.inc"
    }
    if (next.opcode == WEB49_OPCODE_SET_LOCAL && cur.nargs == 1) {
#define NAME(n) if (cur.args[0].opcode == n##_TO_STACK) { next.opcode = n##_TO_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_CONST_TO_STACK) { next.opcode = n##_TOP_CONST_TO_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_LOCAL_TO_STACK) { next.opcode = n##_TOP_LOCAL_TO_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_CONST_NEXT_LOCAL_TO_STACK) { next.opcode = n##_TOP_CONST_NEXT_LOCAL_TO_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_LOCAL_TO_STACK) { next.opcode = n##_TOP_LOCAL_TO_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_LOCAL_NEXT_LOCAL_TO_STACK) { next.opcode = n##_TOP_LOCAL_NEXT_LOCAL_TO_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
    }
    if (next.opcode == WEB49_OPCODE_TEE_LOCAL && cur.nargs == 1) {
#define NAME(n) if (cur.args[0].opcode == n##_TO_STACK) { next.opcode = n##_TO_STACK_AND_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_CONST_TO_STACK) { next.opcode = n##_TOP_CONST_TO_STACK_AND_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_LOCAL_TO_STACK) { next.opcode = n##_TOP_LOCAL_TO_STACK_AND_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_CONST_NEXT_LOCAL_TO_STACK) { next.opcode = n##_TOP_CONST_NEXT_LOCAL_TO_STACK_AND_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_LOCAL_TO_STACK) { next.opcode = n##_TOP_LOCAL_TO_STACK_AND_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
#define NAME(n) if (cur.args[0].opcode == n##_TOP_LOCAL_NEXT_LOCAL_TO_STACK) { next.opcode = n##_TOP_LOCAL_NEXT_LOCAL_TO_STACK_AND_LOCAL; next.nargs = cur.args[0].nargs, next.args = cur.args[0].args; }
#include "math.inc"
    }
    return next;
}
