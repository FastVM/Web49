#include "./write_wat.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

size_t web49_wat_instr_mem_size[WEB49_MAX_OPCODE_NUM] = {
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

void web49_wat_print_lang_type(FILE *out, web49_lang_type_t ltype) {
    switch (ltype) {
        case WEB49_TYPE_I32: {
            fprintf(out, "i32");
            break;
        }
        case WEB49_TYPE_I64: {
            fprintf(out, "i64");
            break;
        }
        case WEB49_TYPE_F32: {
            fprintf(out, "f32");
            break;
        }
        case WEB49_TYPE_F64: {
            fprintf(out, "f64");
            break;
        }
        case WEB49_TYPE_ANYFUNC: {
            fprintf(out, "anyfunc");
            break;
        }
        case WEB49_TYPE_FUNC: {
            fprintf(out, "func");
            break;
        }
        case WEB49_TYPE_BLOCK_TYPE: {
            fprintf(out, "block_type");
            break;
        }
        default: {
            fprintf(stderr, "unsupported: type tag 0x%02zX", (size_t)ltype);
            exit(1);
        }
    }
}

void web49_wat_print_instr(FILE *out, web49_instr_t instr) {
    web49_wat_print_instr_depth(out, instr, 0);
}

void web49_wat_print_instr_depth(FILE *out, web49_instr_t instr, uint64_t indent) {
    for (uint64_t i = 0; i < indent; i++) {
        fprintf(out, "  ");
    }
    switch (instr.opcode) {
        case WEB49_OPCODE_UNREACHABLE:
            fprintf(out, "unreachable");
            break;
        case WEB49_OPCODE_NOP:
            fprintf(out, "nop");
            break;
        case WEB49_OPCODE_BLOCK:
            fprintf(out, "block");
            break;
        case WEB49_OPCODE_LOOP:
            fprintf(out, "loop");
            break;
        case WEB49_OPCODE_IF:
            fprintf(out, "if");
            break;
        case WEB49_OPCODE_ELSE:
            fprintf(out, "else");
            break;
        case WEB49_OPCODE_END:
            fprintf(out, "end");
            break;
        case WEB49_OPCODE_BR:
            fprintf(out, "br");
            break;
        case WEB49_OPCODE_BR_IF:
            fprintf(out, "br_if");
            break;
        case WEB49_OPCODE_BR_TABLE:
            fprintf(out, "br_table");
            break;
        case WEB49_OPCODE_RETURN:
            fprintf(out, "return");
            break;
        case WEB49_OPCODE_CALL:
            fprintf(out, "call");
            break;
        case WEB49_OPCODE_CALL_INDIRECT:
            fprintf(out, "call_indirect");
            break;
        case WEB49_OPCODE_DROP:
            fprintf(out, "drop");
            break;
        case WEB49_OPCODE_SELECT:
            fprintf(out, "select");
            break;
        case WEB49_OPCODE_GET_LOCAL:
            fprintf(out, "local.get");
            break;
        case WEB49_OPCODE_SET_LOCAL:
            fprintf(out, "local.set");
            break;
        case WEB49_OPCODE_TEE_LOCAL:
            fprintf(out, "local.tee");
            break;
        case WEB49_OPCODE_GET_GLOBAL:
            fprintf(out, "global.get");
            break;
        case WEB49_OPCODE_SET_GLOBAL:
            fprintf(out, "global.set");
            break;
        case WEB49_OPCODE_I32_LOAD:
            fprintf(out, "i32.load");
            break;
        case WEB49_OPCODE_I64_LOAD:
            fprintf(out, "i64.load");
            break;
        case WEB49_OPCODE_F32_LOAD:
            fprintf(out, "f32.load");
            break;
        case WEB49_OPCODE_F64_LOAD:
            fprintf(out, "f64.load");
            break;
        case WEB49_OPCODE_I32_LOAD8_S:
            fprintf(out, "i32.load8_s");
            break;
        case WEB49_OPCODE_I32_LOAD8_U:
            fprintf(out, "i32.load8_u");
            break;
        case WEB49_OPCODE_I32_LOAD16_S:
            fprintf(out, "i32.load16_s");
            break;
        case WEB49_OPCODE_I32_LOAD16_U:
            fprintf(out, "i32.load16_u");
            break;
        case WEB49_OPCODE_I64_LOAD8_S:
            fprintf(out, "i64.load8_s");
            break;
        case WEB49_OPCODE_I64_LOAD8_U:
            fprintf(out, "i64.load8_u");
            break;
        case WEB49_OPCODE_I64_LOAD16_S:
            fprintf(out, "i64.load16_s");
            break;
        case WEB49_OPCODE_I64_LOAD16_U:
            fprintf(out, "i64.load16_u");
            break;
        case WEB49_OPCODE_I64_LOAD32_S:
            fprintf(out, "i64.load32_s");
            break;
        case WEB49_OPCODE_I64_LOAD32_U:
            fprintf(out, "i64.load32_u");
            break;
        case WEB49_OPCODE_I32_STORE:
            fprintf(out, "i32.store");
            break;
        case WEB49_OPCODE_I64_STORE:
            fprintf(out, "i64.store");
            break;
        case WEB49_OPCODE_F32_STORE:
            fprintf(out, "f32.store");
            break;
        case WEB49_OPCODE_F64_STORE:
            fprintf(out, "f64.store");
            break;
        case WEB49_OPCODE_I32_STORE8:
            fprintf(out, "i32.store8");
            break;
        case WEB49_OPCODE_I32_STORE16:
            fprintf(out, "i32.store16");
            break;
        case WEB49_OPCODE_I64_STORE8:
            fprintf(out, "i64.store8");
            break;
        case WEB49_OPCODE_I64_STORE16:
            fprintf(out, "i64.store16");
            break;
        case WEB49_OPCODE_I64_STORE32:
            fprintf(out, "i64.store32");
            break;
        case WEB49_OPCODE_MEMORY_SIZE:
            fprintf(out, "memory.size");
            break;
        case WEB49_OPCODE_MEMORY_GROW:
            fprintf(out, "memory.grow");
            break;
        case WEB49_OPCODE_I32_CONST:
            fprintf(out, "i32.const");
            break;
        case WEB49_OPCODE_I64_CONST:
            fprintf(out, "i64.const");
            break;
        case WEB49_OPCODE_F32_CONST:
            fprintf(out, "f32.const");
            break;
        case WEB49_OPCODE_F64_CONST:
            fprintf(out, "f64.const");
            break;
        case WEB49_OPCODE_I32_EQZ:
            fprintf(out, "i32.eqz");
            break;
        case WEB49_OPCODE_I32_EQ:
            fprintf(out, "i32.eq");
            break;
        case WEB49_OPCODE_I32_NE:
            fprintf(out, "i32.ne");
            break;
        case WEB49_OPCODE_I32_LT_S:
            fprintf(out, "i32.lt_s");
            break;
        case WEB49_OPCODE_I32_LT_U:
            fprintf(out, "i32.lt_u");
            break;
        case WEB49_OPCODE_I32_GT_S:
            fprintf(out, "i32.gt_s");
            break;
        case WEB49_OPCODE_I32_GT_U:
            fprintf(out, "i32.gt_u");
            break;
        case WEB49_OPCODE_I32_LE_S:
            fprintf(out, "i32.le_s");
            break;
        case WEB49_OPCODE_I32_LE_U:
            fprintf(out, "i32.le_u");
            break;
        case WEB49_OPCODE_I32_GE_S:
            fprintf(out, "i32.ge_s");
            break;
        case WEB49_OPCODE_I32_GE_U:
            fprintf(out, "i32.ge_u");
            break;
        case WEB49_OPCODE_I64_EQZ:
            fprintf(out, "i64.eqz");
            break;
        case WEB49_OPCODE_I64_EQ:
            fprintf(out, "i64.eq");
            break;
        case WEB49_OPCODE_I64_NE:
            fprintf(out, "i64.ne");
            break;
        case WEB49_OPCODE_I64_LT_S:
            fprintf(out, "i64.lt_s");
            break;
        case WEB49_OPCODE_I64_LT_U:
            fprintf(out, "i64.lt_u");
            break;
        case WEB49_OPCODE_I64_GT_S:
            fprintf(out, "i64.gt_s");
            break;
        case WEB49_OPCODE_I64_GT_U:
            fprintf(out, "i64.gt_u");
            break;
        case WEB49_OPCODE_I64_LE_S:
            fprintf(out, "i64.le_s");
            break;
        case WEB49_OPCODE_I64_LE_U:
            fprintf(out, "i64.le_u");
            break;
        case WEB49_OPCODE_I64_GE_S:
            fprintf(out, "i64.ge_s");
            break;
        case WEB49_OPCODE_I64_GE_U:
            fprintf(out, "i64.ge_u");
            break;
        case WEB49_OPCODE_F32_EQ:
            fprintf(out, "f32.eq");
            break;
        case WEB49_OPCODE_F32_NE:
            fprintf(out, "f32.ne");
            break;
        case WEB49_OPCODE_F32_LT:
            fprintf(out, "f32.lt");
            break;
        case WEB49_OPCODE_F32_GT:
            fprintf(out, "f32.gt");
            break;
        case WEB49_OPCODE_F32_LE:
            fprintf(out, "f32.le");
            break;
        case WEB49_OPCODE_F32_GE:
            fprintf(out, "f32.ge");
            break;
        case WEB49_OPCODE_F64_EQ:
            fprintf(out, "f64.eq");
            break;
        case WEB49_OPCODE_F64_NE:
            fprintf(out, "f64.ne");
            break;
        case WEB49_OPCODE_F64_LT:
            fprintf(out, "f64.lt");
            break;
        case WEB49_OPCODE_F64_GT:
            fprintf(out, "f64.gt");
            break;
        case WEB49_OPCODE_F64_LE:
            fprintf(out, "f64.le");
            break;
        case WEB49_OPCODE_F64_GE:
            fprintf(out, "f64.ge");
            break;
        case WEB49_OPCODE_I32_CLZ:
            fprintf(out, "i32.clz");
            break;
        case WEB49_OPCODE_I32_CTZ:
            fprintf(out, "i32.ctz");
            break;
        case WEB49_OPCODE_I32_POPCNT:
            fprintf(out, "i32.popcnt");
            break;
        case WEB49_OPCODE_I32_ADD:
            fprintf(out, "i32.add");
            break;
        case WEB49_OPCODE_I32_SUB:
            fprintf(out, "i32.sub");
            break;
        case WEB49_OPCODE_I32_MUL:
            fprintf(out, "i32.mul");
            break;
        case WEB49_OPCODE_I32_DIV_S:
            fprintf(out, "i32.div_s");
            break;
        case WEB49_OPCODE_I32_DIV_U:
            fprintf(out, "i32.div_u");
            break;
        case WEB49_OPCODE_I32_REM_S:
            fprintf(out, "i32.rem_s");
            break;
        case WEB49_OPCODE_I32_REM_U:
            fprintf(out, "i32.rem_u");
            break;
        case WEB49_OPCODE_I32_AND:
            fprintf(out, "i32.and");
            break;
        case WEB49_OPCODE_I32_OR:
            fprintf(out, "i32.or");
            break;
        case WEB49_OPCODE_I32_XOR:
            fprintf(out, "i32.xor");
            break;
        case WEB49_OPCODE_I32_SHL:
            fprintf(out, "i32.shl");
            break;
        case WEB49_OPCODE_I32_SHR_S:
            fprintf(out, "i32.shr_s");
            break;
        case WEB49_OPCODE_I32_SHR_U:
            fprintf(out, "i32.shr_u");
            break;
        case WEB49_OPCODE_I32_ROTL:
            fprintf(out, "i32.rotl");
            break;
        case WEB49_OPCODE_I32_ROTR:
            fprintf(out, "i32.rotr");
            break;
        case WEB49_OPCODE_I64_CLZ:
            fprintf(out, "i64.clz");
            break;
        case WEB49_OPCODE_I64_CTZ:
            fprintf(out, "i64.ctz");
            break;
        case WEB49_OPCODE_I64_POPCNT:
            fprintf(out, "i64.popcnt");
            break;
        case WEB49_OPCODE_I64_ADD:
            fprintf(out, "i64.add");
            break;
        case WEB49_OPCODE_I64_SUB:
            fprintf(out, "i64.sub");
            break;
        case WEB49_OPCODE_I64_MUL:
            fprintf(out, "i64.mul");
            break;
        case WEB49_OPCODE_I64_DIV_S:
            fprintf(out, "i64.div_s");
            break;
        case WEB49_OPCODE_I64_DIV_U:
            fprintf(out, "i64.div_u");
            break;
        case WEB49_OPCODE_I64_REM_S:
            fprintf(out, "i64.rem_s");
            break;
        case WEB49_OPCODE_I64_REM_U:
            fprintf(out, "i64.rem_u");
            break;
        case WEB49_OPCODE_I64_AND:
            fprintf(out, "i64.and");
            break;
        case WEB49_OPCODE_I64_OR:
            fprintf(out, "i64.or");
            break;
        case WEB49_OPCODE_I64_XOR:
            fprintf(out, "i64.xor");
            break;
        case WEB49_OPCODE_I64_SHL:
            fprintf(out, "i64.shl");
            break;
        case WEB49_OPCODE_I64_SHR_S:
            fprintf(out, "i64.shr_s");
            break;
        case WEB49_OPCODE_I64_SHR_U:
            fprintf(out, "i64.shr_u");
            break;
        case WEB49_OPCODE_I64_ROTL:
            fprintf(out, "i64.rotl");
            break;
        case WEB49_OPCODE_I64_ROTR:
            fprintf(out, "i64.rotr");
            break;
        case WEB49_OPCODE_F32_ABS:
            fprintf(out, "f32.abs");
            break;
        case WEB49_OPCODE_F32_NEG:
            fprintf(out, "f32.neg");
            break;
        case WEB49_OPCODE_F32_CEIL:
            fprintf(out, "f32.ceil");
            break;
        case WEB49_OPCODE_F32_FLOOR:
            fprintf(out, "f32.floor");
            break;
        case WEB49_OPCODE_F32_TRUNC:
            fprintf(out, "f32.trunc");
            break;
        case WEB49_OPCODE_F32_NEAREST:
            fprintf(out, "f32.nearest");
            break;
        case WEB49_OPCODE_F32_SQRT:
            fprintf(out, "f32.sqrt");
            break;
        case WEB49_OPCODE_F32_ADD:
            fprintf(out, "f32.add");
            break;
        case WEB49_OPCODE_F32_SUB:
            fprintf(out, "f32.sub");
            break;
        case WEB49_OPCODE_F32_MUL:
            fprintf(out, "f32.mul");
            break;
        case WEB49_OPCODE_F32_DIV:
            fprintf(out, "f32.div");
            break;
        case WEB49_OPCODE_F32_MIN:
            fprintf(out, "f32.min");
            break;
        case WEB49_OPCODE_F32_MAX:
            fprintf(out, "f32.max");
            break;
        case WEB49_OPCODE_F32_COPYSIGN:
            fprintf(out, "f32.copysign");
            break;
        case WEB49_OPCODE_F64_ABS:
            fprintf(out, "f64.abs");
            break;
        case WEB49_OPCODE_F64_NEG:
            fprintf(out, "f64.neg");
            break;
        case WEB49_OPCODE_F64_CEIL:
            fprintf(out, "f64.ceil");
            break;
        case WEB49_OPCODE_F64_FLOOR:
            fprintf(out, "f64.floor");
            break;
        case WEB49_OPCODE_F64_TRUNC:
            fprintf(out, "f64.trunc");
            break;
        case WEB49_OPCODE_F64_NEAREST:
            fprintf(out, "f64.nearest");
            break;
        case WEB49_OPCODE_F64_SQRT:
            fprintf(out, "f64.sqrt");
            break;
        case WEB49_OPCODE_F64_ADD:
            fprintf(out, "f64.add");
            break;
        case WEB49_OPCODE_F64_SUB:
            fprintf(out, "f64.sub");
            break;
        case WEB49_OPCODE_F64_MUL:
            fprintf(out, "f64.mul");
            break;
        case WEB49_OPCODE_F64_DIV:
            fprintf(out, "f64.div");
            break;
        case WEB49_OPCODE_F64_MIN:
            fprintf(out, "f64.min");
            break;
        case WEB49_OPCODE_F64_MAX:
            fprintf(out, "f64.max");
            break;
        case WEB49_OPCODE_F64_COPYSIGN:
            fprintf(out, "f64.copysign");
            break;
        case WEB49_OPCODE_I32_WRAP_I64:
            fprintf(out, "i32.wrap_i64");
            break;
        case WEB49_OPCODE_I32_TRUNC_S_F32:
            fprintf(out, "i32.trunc_f32_s");
            break;
        case WEB49_OPCODE_I32_TRUNC_U_F32:
            fprintf(out, "i32.trunc_f32_u");
            break;
        case WEB49_OPCODE_I32_TRUNC_S_F64:
            fprintf(out, "i32.trunc_f64_s");
            break;
        case WEB49_OPCODE_I32_TRUNC_U_F64:
            fprintf(out, "i32.trunc_f64_u");
            break;
        case WEB49_OPCODE_I64_EXTEND_S_I32:
            fprintf(out, "i64.extend_i32_s");
            break;
        case WEB49_OPCODE_I64_EXTEND_U_I32:
            fprintf(out, "i64.extend_i32_u");
            break;
        case WEB49_OPCODE_I64_TRUNC_S_F32:
            fprintf(out, "i64.trunc_f32_s");
            break;
        case WEB49_OPCODE_I64_TRUNC_U_F32:
            fprintf(out, "i64.trunc_f32_u");
            break;
        case WEB49_OPCODE_I64_TRUNC_S_F64:
            fprintf(out, "i64.trunc_f64_s");
            break;
        case WEB49_OPCODE_I64_TRUNC_U_F64:
            fprintf(out, "i64.trunc_f64_u");
            break;
        case WEB49_OPCODE_F32_CONVERT_S_I32:
            fprintf(out, "f32.convert_i32_s");
            break;
        case WEB49_OPCODE_F32_CONVERT_U_I32:
            fprintf(out, "f32.convert_i32_u");
            break;
        case WEB49_OPCODE_F32_CONVERT_S_I64:
            fprintf(out, "f32.convert_i64_s");
            break;
        case WEB49_OPCODE_F32_CONVERT_U_I64:
            fprintf(out, "f32.convert_i64_u");
            break;
        case WEB49_OPCODE_F32_DEMOTE_F64:
            fprintf(out, "f32.demote_f64");
            break;
        case WEB49_OPCODE_F64_CONVERT_S_I32:
            fprintf(out, "f64.convert_i32_s");
            break;
        case WEB49_OPCODE_F64_CONVERT_U_I32:
            fprintf(out, "f64.convert_i32_u");
            break;
        case WEB49_OPCODE_F64_CONVERT_S_I64:
            fprintf(out, "f64.convert_i64_s");
            break;
        case WEB49_OPCODE_F64_CONVERT_U_I64:
            fprintf(out, "f64.convert_i64_u");
            break;
        case WEB49_OPCODE_F64_PROMOTE_F32:
            fprintf(out, "f64.promote_f32");
            break;
        case WEB49_OPCODE_I32_REINTERPRET_F32:
            fprintf(out, "i32.reinterpret_f32");
            break;
        case WEB49_OPCODE_I64_REINTERPRET_F64:
            fprintf(out, "i64.reinterpret_f64");
            break;
        case WEB49_OPCODE_F32_REINTERPRET_I32:
            fprintf(out, "f32.reinterpret_i32");
            break;
        case WEB49_OPCODE_F64_REINTERPRET_I64:
            fprintf(out, "f64.reinterpret_i64");
            break;
        case WEB49_OPCODE_MEMORY_INIT:
            fprintf(out, "memory.init");
            break;
        case WEB49_OPCODE_MEMORY_COPY:
            fprintf(out, "memory.copy");
            break;
        case WEB49_OPCODE_MEMORY_FILL:
            fprintf(out, "memory.fill");
            break;
        case WEB49_OPCODE_DATA_DROP:
            fprintf(out, "data.drop");
            break;
        case WEB49_OPCODE_TABLE_INIT:
            fprintf(out, "table.init");
            break;
        case WEB49_OPCODE_ELEM_DROP:
            fprintf(out, "elem.drop");
            break;
        case WEB49_OPCODE_TABLE_COPY:
            fprintf(out, "table.copy");
            break;
        default:
            fprintf(out, "op%zu\n", (size_t)instr.opcode);
            break;
    }
    switch (instr.immediate.id) {
        case WEB49_IMMEDIATE_NONE:
            break;
        case WEB49_IMMEDIATE_BLOCK_TYPE:
            if (instr.immediate.block_type != WEB49_TYPE_BLOCK_TYPE) {
                fprintf(out, " (result ");
                web49_wat_print_lang_type(out, instr.immediate.block_type);
                fprintf(out, ")");
            }
            break;
        case WEB49_IMMEDIATE_VARUINT1:
            if (instr.opcode != WEB49_OPCODE_MEMORY_GROW) {
                fprintf(out, " %zu", (size_t) (instr.immediate.varuint1 ? 1 : 0));
            }
            break;
        case WEB49_IMMEDIATE_VARUINT32:
            fprintf(out, " %"PRIu32, instr.immediate.varuint32);
            if (instr.opcode == WEB49_OPCODE_BR_IF || instr.opcode == WEB49_OPCODE_BR) {
                fprintf(out, " (;@%zu;)", (size_t)(indent - instr.immediate.varuint32));
            }
            break;
        case WEB49_IMMEDIATE_VARUINT64:
            fprintf(out, " %"PRIu64, instr.immediate.varuint64);
            break;
        case WEB49_IMMEDIATE_VARINT32:
            fprintf(out, " %"PRIi32, instr.immediate.varint32);
            break;
        case WEB49_IMMEDIATE_VARINT64:
            fprintf(out, " %"PRIi64, instr.immediate.varint64);
            break;
        case WEB49_IMMEDIATE_UINT32:
            fprintf(out, " %"PRIu32, instr.immediate.uint32);
            break;
        case WEB49_IMMEDIATE_UINT64:
            fprintf(out, " %"PRIu64, instr.immediate.uint64);
            break;
        case WEB49_IMMEDIATE_BR_TABLE:
            for (uint64_t i = 0; i < instr.immediate.br_table.num_targets; i++) {
                fprintf(out, " %"PRIu64" (;@%zu;)", instr.immediate.br_table.targets[i], (size_t)(indent - instr.immediate.br_table.targets[i]));
            }
            fprintf(out, " %"PRIu64" (;@%zu;)", instr.immediate.br_table.default_target, (size_t)(indent - instr.immediate.br_table.default_target));
            break;
        case WEB49_IMMEDIATE_CALL_INDIRECT:
            fprintf(out, " (type %"PRIu64")", instr.immediate.call_indirect.index);
            break;
        case WEB49_IMMEDIATE_MEMORY_IMMEDIATE:
            if (instr.immediate.memory_immediate.offset != 0) {
                fprintf(out, " offset=%"PRIu64, instr.immediate.memory_immediate.offset);
            }
            size_t nat_size = web49_wat_instr_mem_size[instr.opcode];
            size_t size = (size_t)1 << instr.immediate.memory_immediate.align;
            if (size != nat_size) {
                fprintf(out, " align=%zu", size);
            }
            break;
    }
}

void web49_wat_print_section_custom(FILE *out, web49_module_t mod, web49_section_custom_t scustom) {
    // fprintf(stderr, "unsupported: custom section type\n");
}

void web49_wat_print_section_type(FILE *out, web49_module_t mod, web49_section_type_t stype) {
    for (uint64_t i = 0; i < stype.num_entries; i++) {
        fprintf(out, "\n  (type");
        fprintf(out, " ");
        web49_section_type_entry_t entry = stype.entries[i];
        fprintf(out, "(;%"PRIi64";) ", i);
        if (entry.type == WEB49_TYPE_FUNC) {
            fprintf(out, "(func");
            if (entry.num_params != 0) {
                fprintf(out, " (param");
                for (uint64_t j = 0; j < entry.num_params; j++) {
                    fprintf(out, " ");
                    web49_wat_print_lang_type(out, entry.params[j]);
                }
                fprintf(out, ")");
            }
            if (entry.has_return_type) {
                fprintf(out, " (result ");
                web49_wat_print_lang_type(out, entry.return_type);
                fprintf(out, ")");
            }
            fprintf(out, ")");
        } else {
            web49_wat_print_lang_type(out, entry.type);
        }
        fprintf(out, ")");
    }
}

void web49_wat_print_section_import(FILE *out, web49_module_t mod, web49_section_import_t simport) {
    size_t num_funcs = 0;
    for (uint64_t i = 0; i < simport.num_entries; i++) {
        web49_section_import_entry_t import = simport.entries[i];
        fprintf(out, "\n  (import \"%s\" \"%s\" ", import.module_str, import.field_str);
        switch (import.kind) {
            case WEB49_EXTERNAL_KIND_FUNCTION:
                fprintf(out, "(func (;%zu;) (type %zu))", (size_t)num_funcs++, (size_t)import.func_type.data);
                break;
            case WEB49_EXTERNAL_KIND_TABLE:
                fprintf(out, "(table ");
                web49_wat_print_lang_type(out, import.table_type.element_type);
                fprintf(out, ")");
                break;
            case WEB49_EXTERNAL_KIND_MEMORY:
                fprintf(out, "(memory %"PRIu64")", import.memory_type.initial);
                break;
            case WEB49_EXTERNAL_KIND_GLOBAL:
                fprintf(out, "(global ");
                if (import.global_type.is_mutable) {
                    fprintf(out, "(mut ");
                    web49_wat_print_lang_type(out, import.global_type.content_type);
                    fprintf(out, ")");
                } else {
                    web49_wat_print_lang_type(out, import.global_type.content_type);
                }
                fprintf(out, ")");
                break;
        }
        fprintf(out, ")");
    }
}

void web49_wat_print_section_function(FILE *out, web49_module_t mod, web49_section_function_t sfunction) {
    size_t num_funcs = 0;
    web49_section_code_t code_section;
    web49_section_type_t type_section;
    for (uint64_t i = 0; i < mod.num_sections; i++) {
        if (mod.sections[i].header.id == WEB49_SECTION_ID_CODE) {
            code_section = mod.sections[i].code_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_TYPE) {
            type_section = mod.sections[i].type_section;
        }
        if (mod.sections[i].header.id == WEB49_SECTION_ID_IMPORT) {
            for (uint64_t j = 0; j < mod.sections[i].import_section.num_entries; j++) {
                if (mod.sections[i].import_section.entries[j].kind == WEB49_EXTERNAL_KIND_FUNCTION) {
                    num_funcs++;
                }
            }
        }
    }
    for (uint64_t i = 0; i < code_section.num_entries; i++) {
        web49_section_type_entry_t type = type_section.entries[sfunction.entries[i]];
        web49_section_code_entry_t code = code_section.entries[i];
        fprintf(out, "\n  (func (;%zu;) (type %zu)", (size_t)num_funcs++, (size_t)sfunction.entries[i]);
        if (type.num_params != 0) {
            fprintf(out, " (param");
            for (uint64_t j = 0; j < type.num_params; j++) {
                fprintf(out, " ");
                web49_wat_print_lang_type(out, type.params[j]);
            }
            fprintf(out, ")");
        }
        if (type.has_return_type) {
            fprintf(out, " (result ");
            web49_wat_print_lang_type(out, type.return_type);
            fprintf(out, ")");
        }
        if (code.num_locals != 0) {
            fprintf(out, "\n    (local");
            for (uint64_t j = 0; j < code.num_locals; j++) {
                for (uint64_t k = 0; k < code.locals[j].count; k++) {
                    fprintf(out, " ");
                    web49_wat_print_lang_type(out, code.locals[j].type);
                }
            }
            fprintf(out, ")");
        }
        uint64_t depth = 0;
        for (uint64_t j = 0; j < code.num_instrs; j++) {
            web49_opcode_t op = code.instrs[j].opcode;
            if (j + 1 == code.num_instrs && op == WEB49_OPCODE_END) {
                break;
            }
            if (depth != 0 && (op == WEB49_OPCODE_END || op == WEB49_OPCODE_ELSE)) {
                depth -= 1;
            }
            fprintf(out, "\n    ");
            fflush(out);
            web49_wat_print_instr_depth(out, code.instrs[j], depth);
            if (op == WEB49_OPCODE_ELSE || op == WEB49_OPCODE_BLOCK || op == WEB49_OPCODE_IF || op == WEB49_OPCODE_LOOP) {
                depth += 1;
            }
            if (op == WEB49_OPCODE_BLOCK || op == WEB49_OPCODE_LOOP || op == WEB49_OPCODE_IF) {
                fprintf(out, "  ;; label = @%zu", (size_t)depth);
            }
        }
        fprintf(out, ")");
    }
}

void web49_wat_print_section_table(FILE *out, web49_module_t mod, web49_section_table_t stable) {
    for (uint64_t i = 0; i < stable.num_entries; i++) {
        web49_type_table_t table = stable.entries[i];
        fprintf(out, "\n  (table (;%zu;) %"PRIu64, (size_t)i, table.limits.initial);
        if (table.limits.maximum != UINT64_MAX) {
            fprintf(out, " %zu", (size_t)table.limits.maximum);
        }
        fprintf(out, " ");
        if (table.element_type == WEB49_TYPE_ANYFUNC) {
            fprintf(out, "funcref");
        } else {
            web49_wat_print_lang_type(out, table.element_type);
        }
        fprintf(out, ")");
    }
}

void web49_wat_print_section_memory(FILE *out, web49_module_t mod, web49_section_memory_t smemory) {
    for (uint64_t i = 0; i < smemory.num_entries; i++) {
        web49_type_memory_t mem = smemory.entries[i];
        if (mem.maximum != UINT64_MAX) {
            fprintf(out, "\n  (memory (;%zu;) %zu %zu)", (size_t)i, (size_t)mem.initial, (size_t)mem.maximum);
        } else {
            fprintf(out, "\n  (memory (;%zu;) %zu)", (size_t)i, (size_t)mem.initial);
        }
    }
}

void web49_wat_print_section_global(FILE *out, web49_module_t mod, web49_section_global_t sglobal) {
    for (uint64_t i = 0; i < sglobal.num_entries; i++) {
        web49_section_global_entry_t global = sglobal.entries[i];
        fprintf(out, "\n  (global (;%zu;) ", (size_t)i);
        if (global.global.is_mutable) {
            fprintf(out, "(mut ");
            web49_wat_print_lang_type(out, global.global.content_type);
            fprintf(out, ")");
        } else {
            web49_wat_print_lang_type(out, global.global.content_type);
        }
        fprintf(out, " (");
        web49_wat_print_instr(out, global.init_expr);
        fprintf(out, ")");
        fprintf(out, ")");
    }
}

void web49_wat_print_section_export(FILE *out, web49_module_t mod, web49_section_export_t sexport) {
    for (uint64_t i = 0; i < sexport.num_entries; i++) {
        web49_section_export_entry_t export = sexport.entries[i];
        fprintf(out, "\n  (export \"%s\" ", export.field_str);
        switch (export.kind) {
            case WEB49_EXTERNAL_KIND_FUNCTION:
                fprintf(out, "(func %zu)", (size_t) export.index);
                break;
            case WEB49_EXTERNAL_KIND_TABLE:
                fprintf(out, "(table %zu)", (size_t) export.index);
                break;
            case WEB49_EXTERNAL_KIND_MEMORY:
                fprintf(out, "(memory %zu)", (size_t) export.index);
                break;
            case WEB49_EXTERNAL_KIND_GLOBAL:
                fprintf(out, "(global %zu)", (size_t) export.index);
                break;
        }
        fprintf(out, ")");
    }
}

void web49_wat_print_section_start(FILE *out, web49_module_t mod, web49_section_start_t sstart) {
    // fprintf(stderr, "unsupported: start section\n");
}

void web49_wat_print_section_element(FILE *out, web49_module_t mod, web49_section_element_t selement) {
    for (uint64_t i = 0; i < selement.num_entries; i++) {
        web49_section_element_entry_t element = selement.entries[i];
        fprintf(out, "\n  (elem (;%"PRIu64";) (", i);
        web49_wat_print_instr(out, element.offset);
        fprintf(out, ") func");
        for (uint64_t j = 0; j < element.num_elems; j++) {
            fprintf(out, " %zu", (size_t)element.elems[j]);
        }
        fprintf(out, ")");
    }
}

void web49_wat_print_section_code(FILE *out, web49_module_t mod, web49_section_code_t scode) {
}

void web49_wat_print_section_data(FILE *out, web49_module_t mod, web49_section_data_t sdata) {
    // fprintf(stderr, "unsupported: data section\n");
    web49_section_type_t type_section;
    for (uint64_t i = 0; i < mod.num_sections; i++) {
        if (mod.sections[i].header.id == WEB49_SECTION_ID_TYPE) {
            type_section = mod.sections[i].type_section;
        }
    }
    for (uint64_t i = 0; i < sdata.num_entries; i++) {
        web49_section_data_entry_t data = sdata.entries[i];
        web49_section_type_entry_t type = type_section.entries[data.index];
        fprintf(out, "\n  (data (;%"PRIu64";) (", i);
        web49_wat_print_instr(out, data.offset);
        fprintf(out, ") \"");
        for (uint64_t j = 0; j < data.size; j++) {
            uint8_t arg = data.data[j];
            if (arg == '\\') {
                fprintf(out, "\\%02zx", (size_t)'\\');
            } else if (arg == '\t') {
                fprintf(out, "\\%02zx", (size_t)'\t');
            } else if (arg == '\r') {
                fprintf(out, "\\%02zx", (size_t)'\r');
            } else if (arg == '\n') {
                fprintf(out, "\\%02zx", (size_t)'\n');
            } else if (arg == '\'') {
                fprintf(out, "\\%02zx", (size_t)'\'');
            } else if (arg == '\"') {
                fprintf(out, "\\%02zx", (size_t)'\"');
            } else if (isprint(arg)) {
                fprintf(out, "%c", (char)arg);
            } else {
                fprintf(out, "\\%02zx", (size_t)arg);
            }
        }
        fprintf(out, "\")");
    }
}

void web49_wat_print_section(FILE *out, web49_module_t mod, web49_section_t section) {
    switch (section.header.id) {
        case WEB49_SECTION_ID_CUSTOM: {
            web49_wat_print_section_custom(out, mod, section.custom_section);
            break;
        }
        case WEB49_SECTION_ID_TYPE: {
            web49_wat_print_section_type(out, mod, section.type_section);
            break;
        }
        case WEB49_SECTION_ID_IMPORT: {
            web49_wat_print_section_import(out, mod, section.import_section);
            break;
        }
        case WEB49_SECTION_ID_FUNCTION: {
            web49_wat_print_section_function(out, mod, section.function_section);
            break;
        }
        case WEB49_SECTION_ID_TABLE: {
            web49_wat_print_section_table(out, mod, section.table_section);
            break;
        }
        case WEB49_SECTION_ID_MEMORY: {
            web49_wat_print_section_memory(out, mod, section.memory_section);
            break;
        }
        case WEB49_SECTION_ID_GLOBAL: {
            web49_wat_print_section_global(out, mod, section.global_section);
            break;
        }
        case WEB49_SECTION_ID_EXPORT: {
            web49_wat_print_section_export(out, mod, section.export_section);
            break;
        }
        case WEB49_SECTION_ID_START: {
            web49_wat_print_section_start(out, mod, section.start_section);
            break;
        }
        case WEB49_SECTION_ID_ELEMENT: {
            web49_wat_print_section_element(out, mod, section.element_section);
            break;
        }
        case WEB49_SECTION_ID_CODE: {
            web49_wat_print_section_code(out, mod, section.code_section);
            break;
        }
        case WEB49_SECTION_ID_DATA: {
            web49_wat_print_section_data(out, mod, section.data_section);
            break;
        }
    }
}

void web49_wat_print_module(FILE *out, web49_module_t mod) {
    fprintf(out, "(module");
    for (uint64_t i = 0; i < mod.num_sections; i++) {
        web49_wat_print_section(out, mod, mod.sections[i]);
    }
    fprintf(out, ")\n");
}
