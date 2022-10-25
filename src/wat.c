#include "./wat.h"

#include <stdint.h>
#include <stdio.h>

void vm_wat_print_lang_type(FILE *out, vm_wasm_lang_type_t ltype) {
    switch (ltype) {
        case VM_WASM_TYPE_I32: {
            fprintf(out, "i32");
            break;
        }
        case VM_WASM_TYPE_I64: {
            fprintf(out, "i64");
            break;
        }
        case VM_WASM_TYPE_F32: {
            fprintf(out, "f32");
            break;
        }
        case VM_WASM_TYPE_F64: {
            fprintf(out, "f64");
            break;
        }
        case VM_WASM_TYPE_ANYFUNC: {
            fprintf(out, "anyfunc");
            break;
        }
        case VM_WASM_TYPE_FUNC: {
            fprintf(out, "func");
            break;
        }
        case VM_WASM_TYPE_BLOCK_TYPE: {
            fprintf(out, "block_type");
            break;
        }
        default: {
            fprintf(stderr, "unsupported: type tag %x", (int)ltype);
        }
    }
}

void vm_wat_print_instr(FILE *out, vm_wasm_instr_t instr) {
    fprintf(out, "(");
    switch (instr.opcode) {
        case VM_WASM_OPCODE_UNREACHABLE:
            fprintf(out, "unreachable");
            break;
        case VM_WASM_OPCODE_NOP:
            fprintf(out, "nop");
            break;
        case VM_WASM_OPCODE_BLOCK:
            fprintf(out, "block");
            break;
        case VM_WASM_OPCODE_LOOP:
            fprintf(out, "loop");
            break;
        case VM_WASM_OPCODE_IF:
            fprintf(out, "if");
            break;
        case VM_WASM_OPCODE_ELSE:
            fprintf(out, "else");
            break;
        case VM_WASM_OPCODE_END:
            fprintf(out, "end");
            break;
        case VM_WASM_OPCODE_BR:
            fprintf(out, "br");
            break;
        case VM_WASM_OPCODE_BR_IF:
            fprintf(out, "br_if");
            break;
        case VM_WASM_OPCODE_BR_TABLE:
            fprintf(out, "br_table");
            break;
        case VM_WASM_OPCODE_RETURN:
            fprintf(out, "return");
            break;
        case VM_WASM_OPCODE_CALL:
            fprintf(out, "call");
            break;
        case VM_WASM_OPCODE_CALL_INDIRECT:
            fprintf(out, "call_indirect");
            break;
        case VM_WASM_OPCODE_DROP:
            fprintf(out, "drop");
            break;
        case VM_WASM_OPCODE_SELECT:
            fprintf(out, "select");
            break;
        case VM_WASM_OPCODE_GET_LOCAL:
            fprintf(out, "get_local");
            break;
        case VM_WASM_OPCODE_SET_LOCAL:
            fprintf(out, "set_local");
            break;
        case VM_WASM_OPCODE_TEE_LOCAL:
            fprintf(out, "tee_local");
            break;
        case VM_WASM_OPCODE_GET_GLOBAL:
            fprintf(out, "get_global");
            break;
        case VM_WASM_OPCODE_SET_GLOBAL:
            fprintf(out, "set_global");
            break;
        case VM_WASM_OPCODE_I32_LOAD:
            fprintf(out, "i32.load");
            break;
        case VM_WASM_OPCODE_I64_LOAD:
            fprintf(out, "i64.load");
            break;
        case VM_WASM_OPCODE_F32_LOAD:
            fprintf(out, "f32.load");
            break;
        case VM_WASM_OPCODE_F64_LOAD:
            fprintf(out, "f64.load");
            break;
        case VM_WASM_OPCODE_I32_LOAD8_S:
            fprintf(out, "i32.load8_s");
            break;
        case VM_WASM_OPCODE_I32_LOAD8_U:
            fprintf(out, "i32.load8_u");
            break;
        case VM_WASM_OPCODE_I32_LOAD16_S:
            fprintf(out, "i32.load16_s");
            break;
        case VM_WASM_OPCODE_I32_LOAD16_U:
            fprintf(out, "i32.load16_u");
            break;
        case VM_WASM_OPCODE_I64_LOAD8_S:
            fprintf(out, "i64.load8_s");
            break;
        case VM_WASM_OPCODE_I64_LOAD8_U:
            fprintf(out, "i64.load8_u");
            break;
        case VM_WASM_OPCODE_I64_LOAD16_S:
            fprintf(out, "i64.load16_s");
            break;
        case VM_WASM_OPCODE_I64_LOAD16_U:
            fprintf(out, "i64.load16_u");
            break;
        case VM_WASM_OPCODE_I64_LOAD32_S:
            fprintf(out, "i64.load32_s");
            break;
        case VM_WASM_OPCODE_I64_LOAD32_U:
            fprintf(out, "i64.load32_u");
            break;
        case VM_WASM_OPCODE_I32_STORE:
            fprintf(out, "i32.store");
            break;
        case VM_WASM_OPCODE_I64_STORE:
            fprintf(out, "i64.store");
            break;
        case VM_WASM_OPCODE_F32_STORE:
            fprintf(out, "f32.store");
            break;
        case VM_WASM_OPCODE_F64_STORE:
            fprintf(out, "f64.store");
            break;
        case VM_WASM_OPCODE_I32_STORE8:
            fprintf(out, "i32.store8");
            break;
        case VM_WASM_OPCODE_I32_STORE16:
            fprintf(out, "i32.store16");
            break;
        case VM_WASM_OPCODE_I64_STORE8:
            fprintf(out, "i64.store8");
            break;
        case VM_WASM_OPCODE_I64_STORE16:
            fprintf(out, "i64.store16");
            break;
        case VM_WASM_OPCODE_I64_STORE32:
            fprintf(out, "i64.store32");
            break;
        case VM_WASM_OPCODE_CURRENT_MEMORY:
            fprintf(out, "current_memory");
            break;
        case VM_WASM_OPCODE_GROW_MEMORY:
            fprintf(out, "grow_memory");
            break;
        case VM_WASM_OPCODE_I32_CONST:
            fprintf(out, "i32.const");
            break;
        case VM_WASM_OPCODE_I64_CONST:
            fprintf(out, "i64.const");
            break;
        case VM_WASM_OPCODE_F32_CONST:
            fprintf(out, "f32.const");
            break;
        case VM_WASM_OPCODE_F64_CONST:
            fprintf(out, "f64.const");
            break;
        case VM_WASM_OPCODE_I32_EQZ:
            fprintf(out, "i32.eqz");
            break;
        case VM_WASM_OPCODE_I32_EQ:
            fprintf(out, "i32.eq");
            break;
        case VM_WASM_OPCODE_I32_NE:
            fprintf(out, "i32.ne");
            break;
        case VM_WASM_OPCODE_I32_LT_S:
            fprintf(out, "i32.lt_s");
            break;
        case VM_WASM_OPCODE_I32_LT_U:
            fprintf(out, "i32.lt_u");
            break;
        case VM_WASM_OPCODE_I32_GT_S:
            fprintf(out, "i32.gt_s");
            break;
        case VM_WASM_OPCODE_I32_GT_U:
            fprintf(out, "i32.gt_u");
            break;
        case VM_WASM_OPCODE_I32_LE_S:
            fprintf(out, "i32.le_s");
            break;
        case VM_WASM_OPCODE_I32_LE_U:
            fprintf(out, "i32.le_u");
            break;
        case VM_WASM_OPCODE_I32_GE_S:
            fprintf(out, "i32.ge_s");
            break;
        case VM_WASM_OPCODE_I32_GE_U:
            fprintf(out, "i32.ge_u");
            break;
        case VM_WASM_OPCODE_I64_EQZ:
            fprintf(out, "i64.eqz");
            break;
        case VM_WASM_OPCODE_I64_EQ:
            fprintf(out, "i64.eq");
            break;
        case VM_WASM_OPCODE_I64_NE:
            fprintf(out, "i64.ne");
            break;
        case VM_WASM_OPCODE_I64_LT_S:
            fprintf(out, "i64.lt_s");
            break;
        case VM_WASM_OPCODE_I64_LT_U:
            fprintf(out, "i64.lt_u");
            break;
        case VM_WASM_OPCODE_I64_GT_S:
            fprintf(out, "i64.gt_s");
            break;
        case VM_WASM_OPCODE_I64_GT_U:
            fprintf(out, "i64.gt_u");
            break;
        case VM_WASM_OPCODE_I64_LE_S:
            fprintf(out, "i64.le_s");
            break;
        case VM_WASM_OPCODE_I64_LE_U:
            fprintf(out, "i64.le_u");
            break;
        case VM_WASM_OPCODE_I64_GE_S:
            fprintf(out, "i64.ge_s");
            break;
        case VM_WASM_OPCODE_I64_GE_U:
            fprintf(out, "i64.ge_u");
            break;
        case VM_WASM_OPCODE_F32_EQ:
            fprintf(out, "f32.eq");
            break;
        case VM_WASM_OPCODE_F32_NE:
            fprintf(out, "f32.ne");
            break;
        case VM_WASM_OPCODE_F32_LT:
            fprintf(out, "f32.lt");
            break;
        case VM_WASM_OPCODE_F32_GT:
            fprintf(out, "f32.gt");
            break;
        case VM_WASM_OPCODE_F32_LE:
            fprintf(out, "f32.le");
            break;
        case VM_WASM_OPCODE_F32_GE:
            fprintf(out, "f32.ge");
            break;
        case VM_WASM_OPCODE_F64_EQ:
            fprintf(out, "f64.eq");
            break;
        case VM_WASM_OPCODE_F64_NE:
            fprintf(out, "f64.ne");
            break;
        case VM_WASM_OPCODE_F64_LT:
            fprintf(out, "f64.lt");
            break;
        case VM_WASM_OPCODE_F64_GT:
            fprintf(out, "f64.gt");
            break;
        case VM_WASM_OPCODE_F64_LE:
            fprintf(out, "f64.le");
            break;
        case VM_WASM_OPCODE_F64_GE:
            fprintf(out, "f64.ge");
            break;
        case VM_WASM_OPCODE_I32_CLZ:
            fprintf(out, "i32.clz");
            break;
        case VM_WASM_OPCODE_I32_CTZ:
            fprintf(out, "i32.ctz");
            break;
        case VM_WASM_OPCODE_I32_POPCNT:
            fprintf(out, "i32.popcnt");
            break;
        case VM_WASM_OPCODE_I32_ADD:
            fprintf(out, "i32.add");
            break;
        case VM_WASM_OPCODE_I32_SUB:
            fprintf(out, "i32.sub");
            break;
        case VM_WASM_OPCODE_I32_MUL:
            fprintf(out, "i32.mul");
            break;
        case VM_WASM_OPCODE_I32_DIV_S:
            fprintf(out, "i32.div_s");
            break;
        case VM_WASM_OPCODE_I32_DIV_U:
            fprintf(out, "i32.div_u");
            break;
        case VM_WASM_OPCODE_I32_REM_S:
            fprintf(out, "i32.rem_s");
            break;
        case VM_WASM_OPCODE_I32_REM_U:
            fprintf(out, "i32.rem_u");
            break;
        case VM_WASM_OPCODE_I32_AND:
            fprintf(out, "i32.and");
            break;
        case VM_WASM_OPCODE_I32_OR:
            fprintf(out, "i32.or");
            break;
        case VM_WASM_OPCODE_I32_XOR:
            fprintf(out, "i32.xor");
            break;
        case VM_WASM_OPCODE_I32_SHL:
            fprintf(out, "i32.shl");
            break;
        case VM_WASM_OPCODE_I32_SHR_S:
            fprintf(out, "i32.shr_s");
            break;
        case VM_WASM_OPCODE_I32_SHR_U:
            fprintf(out, "i32.shr_u");
            break;
        case VM_WASM_OPCODE_I32_ROTL:
            fprintf(out, "i32.rotl");
            break;
        case VM_WASM_OPCODE_I32_ROTR:
            fprintf(out, "i32.rotr");
            break;
        case VM_WASM_OPCODE_I64_CLZ:
            fprintf(out, "i64.clz");
            break;
        case VM_WASM_OPCODE_I64_CTZ:
            fprintf(out, "i64.ctz");
            break;
        case VM_WASM_OPCODE_I64_POPCNT:
            fprintf(out, "i64.popcnt");
            break;
        case VM_WASM_OPCODE_I64_ADD:
            fprintf(out, "i64.add");
            break;
        case VM_WASM_OPCODE_I64_SUB:
            fprintf(out, "i64.sub");
            break;
        case VM_WASM_OPCODE_I64_MUL:
            fprintf(out, "i64.mul");
            break;
        case VM_WASM_OPCODE_I64_DIV_S:
            fprintf(out, "i64.div_s");
            break;
        case VM_WASM_OPCODE_I64_DIV_U:
            fprintf(out, "i64.div_u");
            break;
        case VM_WASM_OPCODE_I64_REM_S:
            fprintf(out, "i64.rem_s");
            break;
        case VM_WASM_OPCODE_I64_REM_U:
            fprintf(out, "i64.rem_u");
            break;
        case VM_WASM_OPCODE_I64_AND:
            fprintf(out, "i64.and");
            break;
        case VM_WASM_OPCODE_I64_OR:
            fprintf(out, "i64.or");
            break;
        case VM_WASM_OPCODE_I64_XOR:
            fprintf(out, "i64.xor");
            break;
        case VM_WASM_OPCODE_I64_SHL:
            fprintf(out, "i64.shl");
            break;
        case VM_WASM_OPCODE_I64_SHR_S:
            fprintf(out, "i64.shr_s");
            break;
        case VM_WASM_OPCODE_I64_SHR_U:
            fprintf(out, "i64.shr_u");
            break;
        case VM_WASM_OPCODE_I64_ROTL:
            fprintf(out, "i64.rotl");
            break;
        case VM_WASM_OPCODE_I64_ROTR:
            fprintf(out, "i64.rotr");
            break;
        case VM_WASM_OPCODE_F32_ABS:
            fprintf(out, "f32.abs");
            break;
        case VM_WASM_OPCODE_F32_NEG:
            fprintf(out, "f32.neg");
            break;
        case VM_WASM_OPCODE_F32_CEIL:
            fprintf(out, "f32.ceil");
            break;
        case VM_WASM_OPCODE_F32_FLOOR:
            fprintf(out, "f32.floor");
            break;
        case VM_WASM_OPCODE_F32_TRUNC:
            fprintf(out, "f32.trunc");
            break;
        case VM_WASM_OPCODE_F32_NEAREST:
            fprintf(out, "f32.nearest");
            break;
        case VM_WASM_OPCODE_F32_SQRT:
            fprintf(out, "f32.sqrt");
            break;
        case VM_WASM_OPCODE_F32_ADD:
            fprintf(out, "f32.add");
            break;
        case VM_WASM_OPCODE_F32_SUB:
            fprintf(out, "f32.sub");
            break;
        case VM_WASM_OPCODE_F32_MUL:
            fprintf(out, "f32.mul");
            break;
        case VM_WASM_OPCODE_F32_DIV:
            fprintf(out, "f32.div");
            break;
        case VM_WASM_OPCODE_F32_MIN:
            fprintf(out, "f32.min");
            break;
        case VM_WASM_OPCODE_F32_MAX:
            fprintf(out, "f32.max");
            break;
        case VM_WASM_OPCODE_F32_COPYSIGN:
            fprintf(out, "f32.copysign");
            break;
        case VM_WASM_OPCODE_F64_ABS:
            fprintf(out, "f64.abs");
            break;
        case VM_WASM_OPCODE_F64_NEG:
            fprintf(out, "f64.neg");
            break;
        case VM_WASM_OPCODE_F64_CEIL:
            fprintf(out, "f64.ceil");
            break;
        case VM_WASM_OPCODE_F64_FLOOR:
            fprintf(out, "f64.floor");
            break;
        case VM_WASM_OPCODE_F64_TRUNC:
            fprintf(out, "f64.trunc");
            break;
        case VM_WASM_OPCODE_F64_NEAREST:
            fprintf(out, "f64.nearest");
            break;
        case VM_WASM_OPCODE_F64_SQRT:
            fprintf(out, "f64.sqrt");
            break;
        case VM_WASM_OPCODE_F64_ADD:
            fprintf(out, "f64.add");
            break;
        case VM_WASM_OPCODE_F64_SUB:
            fprintf(out, "f64.sub");
            break;
        case VM_WASM_OPCODE_F64_MUL:
            fprintf(out, "f64.mul");
            break;
        case VM_WASM_OPCODE_F64_DIV:
            fprintf(out, "f64.div");
            break;
        case VM_WASM_OPCODE_F64_MIN:
            fprintf(out, "f64.min");
            break;
        case VM_WASM_OPCODE_F64_MAX:
            fprintf(out, "f64.max");
            break;
        case VM_WASM_OPCODE_F64_COPYSIGN:
            fprintf(out, "f64.copysign");
            break;
        case VM_WASM_OPCODE_I32_WRAP_I64:
            fprintf(out, "i32.wrap/i64");
            break;
        case VM_WASM_OPCODE_I32_TRUNC_S_F32:
            fprintf(out, "i32.trunc_s/f32");
            break;
        case VM_WASM_OPCODE_I32_TRUNC_U_F32:
            fprintf(out, "i32.trunc_u/f32");
            break;
        case VM_WASM_OPCODE_I32_TRUNC_S_F64:
            fprintf(out, "i32.trunc_s/f64");
            break;
        case VM_WASM_OPCODE_I32_TRUNC_U_F64:
            fprintf(out, "i32.trunc_u/f64");
            break;
        case VM_WASM_OPCODE_I64_EXTEND_S_I32:
            fprintf(out, "i64.extend_s/i32");
            break;
        case VM_WASM_OPCODE_I64_EXTEND_U_I32:
            fprintf(out, "i64.extend_u/i32");
            break;
        case VM_WASM_OPCODE_I64_TRUNC_S_F32:
            fprintf(out, "i64.trunc_s/f32");
            break;
        case VM_WASM_OPCODE_I64_TRUNC_U_F32:
            fprintf(out, "i64.trunc_u/f32");
            break;
        case VM_WASM_OPCODE_I64_TRUNC_S_F64:
            fprintf(out, "i64.trunc_s/f64");
            break;
        case VM_WASM_OPCODE_I64_TRUNC_U_F64:
            fprintf(out, "i64.trunc_u/f64");
            break;
        case VM_WASM_OPCODE_F32_CONVERT_S_I32:
            fprintf(out, "f32.convert_s/i32");
            break;
        case VM_WASM_OPCODE_F32_CONVERT_U_I32:
            fprintf(out, "f32.convert_u/i32");
            break;
        case VM_WASM_OPCODE_F32_CONVERT_S_I64:
            fprintf(out, "f32.convert_s/i64");
            break;
        case VM_WASM_OPCODE_F32_CONVERT_U_I64:
            fprintf(out, "f32.convert_u/i64");
            break;
        case VM_WASM_OPCODE_F32_DEMOTE_F64:
            fprintf(out, "f32.demote/f64");
            break;
        case VM_WASM_OPCODE_F64_CONVERT_S_I32:
            fprintf(out, "f64.convert_s/i32");
            break;
        case VM_WASM_OPCODE_F64_CONVERT_U_I32:
            fprintf(out, "f64.convert_u/i32");
            break;
        case VM_WASM_OPCODE_F64_CONVERT_S_I64:
            fprintf(out, "f64.convert_s/i64");
            break;
        case VM_WASM_OPCODE_F64_CONVERT_U_I64:
            fprintf(out, "f64.convert_u/i64");
            break;
        case VM_WASM_OPCODE_F64_PROMOTE_F32:
            fprintf(out, "f64.promote/f32");
            break;
        case VM_WASM_OPCODE_I32_REINTERPRET_F32:
            fprintf(out, "i32.reinterpret/f32");
            break;
        case VM_WASM_OPCODE_I64_REINTERPRET_F64:
            fprintf(out, "i64.reinterpret/f64");
            break;
        case VM_WASM_OPCODE_F32_REINTERPRET_I32:
            fprintf(out, "f32.reinterpret/i32");
            break;
        case VM_WASM_OPCODE_F64_REINTERPRET_I64:
            fprintf(out, "f64.reinterpret/i64");
            break;
    }
    switch (instr.immediate.id) {
        case VM_WASM_IMMEDIATE_NONE:
            break;
        case VM_WASM_IMMEDIATE_BLOCK_TYPE:
            fprintf(out, " <<<BLOCK>>>");
            break;
        case VM_WASM_IMMEDIATE_VARUINT1:
            fprintf(out, " %zu", (size_t) instr.immediate.varuint1);
            break;
        case VM_WASM_IMMEDIATE_VARUINT32:
            fprintf(out, " %zu", (size_t) instr.immediate.varuint32);
            break;
        case VM_WASM_IMMEDIATE_VARUINT64:
            fprintf(out, " %zu", (size_t) instr.immediate.varuint64);
            break;
        case VM_WASM_IMMEDIATE_VARINT32:
            fprintf(out, " %zi", (ptrdiff_t) instr.immediate.varint32);
            break;
        case VM_WASM_IMMEDIATE_VARINT64:
            fprintf(out, " %zi", (ptrdiff_t) instr.immediate.varint64);
            break;
        case VM_WASM_IMMEDIATE_UINT32:
            fprintf(out, " %zu", (size_t) instr.immediate.uint32);
            break;
        case VM_WASM_IMMEDIATE_UINT64:
            fprintf(out, " %zu", (size_t) instr.immediate.uint64);
            break;
        case VM_WASM_IMMEDIATE_BR_TABLE:
            fprintf(out, " ");
            break;
        case VM_WASM_IMMEDIATE_CALL_INDIRECT:
            fprintf(out, " ");
            break;
        case VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE:
            fprintf(out, " ");
            break;
    }
    fprintf(out, ")");
}

void vm_wat_print_section_custom(FILE *out, vm_wasm_section_custom_t scustom) {
    // fprintf(stderr, "unsupported: custom section type\n");
}

void vm_wat_print_section_type(FILE *out, vm_wasm_section_type_t stype) {
    for (uint64_t i = 0; i < stype.num_entries; i++) {
        fprintf(out, "  (type");
        fprintf(out, " ");
        vm_wasm_section_type_entry_t entry = stype.entries[i];
        fprintf(out, "(;%zu;) ", (size_t)i);
        if (entry.type == VM_WASM_TYPE_FUNC) {
            fprintf(out, "(func");
            bool first = true;
            for (uint64_t j = 0; j < entry.num_params; j++) {
                fprintf(out, " ");
                vm_wat_print_lang_type(out, entry.params[j]);
            }
            if (entry.has_return_type) {
                fprintf(out, " ");
                fprintf(out, "(result ");
                vm_wat_print_lang_type(out, entry.return_type);
                fprintf(out, ")");
            }
            fprintf(out, ")");
        } else {
            vm_wat_print_lang_type(out, entry.type);
        }
        fprintf(out, ")\n");
    }
}

void vm_wat_print_section_import(FILE *out, vm_wasm_section_import_t simport) {
    fprintf(stderr, "unsupported: import section\n");
}

void vm_wat_print_section_function(FILE *out, vm_wasm_section_function_t sfunction) {
    for (uint64_t i = 0; i < sfunction.num_entries; i++) {
        fprintf(out, "  (func (;%zu;) %zu)\n", (size_t)i, (size_t)sfunction.entries[i]);
    }
}

void vm_wat_print_section_table(FILE *out, vm_wasm_section_table_t stable) {
    fprintf(stderr, "unsupported: table section\n");
}

void vm_wat_print_section_memory(FILE *out, vm_wasm_section_memory_t smemory) {
    for (uint64_t i = 0; i < smemory.num_entries; i++) {
        vm_wasm_type_memory_t mem = smemory.entries[i];
        if (mem.flags & 1) {
            fprintf(out, "  (memory (;%zu;) %zu %zu)\n", (size_t)i, (size_t)mem.initial, (size_t)mem.maximum);
        } else {
            fprintf(out, "  (memory (;%zu;) %zu)\n", (size_t)i, (size_t)mem.initial);
        }
    }
}

void vm_wat_print_section_global(FILE *out, vm_wasm_section_global_t sglobal) {
    for (uint64_t i = 0; i < sglobal.num_entries; i++) {
        vm_wasm_section_global_entry_t global = sglobal.entries[i];
        fprintf(out, "  (global (;%zu;) ", (size_t)i);
        if (global.global.mutable) {
            fprintf(out, "(mut ");
            vm_wat_print_lang_type(out, global.global.content_type);
            fprintf(out, ")");
        } else {
            vm_wat_print_lang_type(out, global.global.content_type);
        }
        fprintf(out, " ");
        vm_wat_print_instr(out, global.init_expr);
        fprintf(out, ")\n");
    }
}

void vm_wat_print_section_export(FILE *out, vm_wasm_section_export_t sexport) {
    fprintf(stderr, "unsupported: export section\n");
}

void vm_wat_print_section_start(FILE *out, vm_wasm_section_start_t sstart) {
    fprintf(stderr, "unsupported: start section\n");
}

void vm_wat_print_section_element(FILE *out, vm_wasm_section_element_t selement) {
    fprintf(stderr, "unsupported: element section\n");
}

void vm_wat_print_section_code(FILE *out, vm_wasm_section_code_t scode) {
    fprintf(stderr, "unsupported: code section\n");
}

void vm_wat_print_section_data(FILE *out, vm_wasm_section_data_t sdata) {
    fprintf(stderr, "unsupported: data section\n");
}

void vm_wat_print_section(FILE *out, vm_wasm_section_t section) {
    switch (section.id) {
        case VM_WASM_SECTION_ID_CUSTOM: {
            vm_wat_print_section_custom(out, section.custom_section);
            break;
        }
        case VM_WASM_SECTION_ID_TYPE: {
            vm_wat_print_section_type(out, section.type_section);
            break;
        }
        case VM_WASM_SECTION_ID_IMPORT: {
            vm_wat_print_section_import(out, section.import_section);
            break;
        }
        case VM_WASM_SECTION_ID_FUNCTION: {
            vm_wat_print_section_function(out, section.function_section);
            break;
        }
        case VM_WASM_SECTION_ID_TABLE: {
            vm_wat_print_section_table(out, section.table_section);
            break;
        }
        case VM_WASM_SECTION_ID_MEMORY: {
            vm_wat_print_section_memory(out, section.memory_section);
            break;
        }
        case VM_WASM_SECTION_ID_GLOBAL: {
            vm_wat_print_section_global(out, section.global_section);
            break;
        }
        case VM_WASM_SECTION_ID_EXPORT: {
            vm_wat_print_section_export(out, section.export_section);
            break;
        }
        case VM_WASM_SECTION_ID_START: {
            vm_wat_print_section_start(out, section.start_section);
            break;
        }
        case VM_WASM_SECTION_ID_ELEMENT: {
            vm_wat_print_section_element(out, section.element_section);
            break;
        }
        case VM_WASM_SECTION_ID_CODE: {
            vm_wat_print_section_code(out, section.code_section);
            break;
        }
        case VM_WASM_SECTION_ID_DATA: {
            vm_wat_print_section_data(out, section.data_section);
            break;
        }
    }
}

void vm_wat_print_module(FILE *out, vm_wasm_module_t mod) {
    fprintf(out, "(module\n");
    for (uint64_t i = 0; i < mod.num_sections; i++) {
        vm_wat_print_section(out, mod.sections[i]);
    }
    fprintf(out, ")");
}
