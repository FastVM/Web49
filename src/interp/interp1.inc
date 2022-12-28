NAME(WEB49_OPCODE_CALL_INDIRECT) {
    web49_interp_block_t *block = interp.table[LOCAL0.i32_u];
    web49_interp_block_run_comp(block, ptrs, interp);
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + block->nparams, 0, sizeof(web49_interp_data_t) * block->nlocals);
    head = block->code;
    NEXT();
}
NAME(WEB49_OPCODE_IF) {
    if (LOCAL0.i32_u != 0) {
        head = head[1].ptr;
        NEXT();
    } else {
        head = head[2].ptr;
        NEXT();
    }
}
NAME(WEB49_OPCODE_BR_TABLE) {
    uint32_t brvalue = LOCAL0.i32_u;
    uint32_t maxvalue = head[1].data.i32_u;
    head += 2;
    if (brvalue >= maxvalue) {
        brvalue = maxvalue;
    }
    head = head[brvalue].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_RETURN) {
#if defined(WEB49_PRINT_INSTR)
    depth -= 1;
#endif
    web49_interp_data_t ret = LOCAL0;
    head = *--returns;
    locals = *--stacks;
    locals[head[2].data.i32_u] = ret;
    head += 4;
    NEXT();
}
NAME(WEB49_OPCODE_TEE_LOCAL) {
    web49_interp_data_t got = LOCAL0;
    locals[head[1].data.i32_u] = got;
    locals[head[2].data.i32_u] = got;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_SET_LOCAL) {
    locals[head[1].data.i32_u] = LOCAL0;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_SET_GLOBAL) {
    interp.globals[head[1].data.i32_u] = LOCAL0;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD) {
    locals[head[1].data.i32_u].i32_u = WEB49_INTERP_READ(uint32_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD) {
    locals[head[1].data.i32_u].i64_u = WEB49_INTERP_READ(uint64_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_LOAD) {
    locals[head[1].data.i32_u].f32 = WEB49_INTERP_READ(float, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_LOAD) {
    locals[head[1].data.i32_u].f64 = WEB49_INTERP_READ(double, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD8_S) {
    locals[head[1].data.i32_u].i32_s = (int32_t) WEB49_INTERP_READ(int8_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD8_U) {
    locals[head[1].data.i32_u].i32_u = (uint32_t) WEB49_INTERP_READ(uint8_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD16_S) {
    locals[head[1].data.i32_u].i32_s = (int32_t) WEB49_INTERP_READ(int16_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD16_U) {
    locals[head[1].data.i32_u].i32_u = (uint32_t) WEB49_INTERP_READ(uint16_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD8_S) {
    locals[head[1].data.i32_u].i64_s = (int64_t) WEB49_INTERP_READ(int8_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD8_U) {
    locals[head[1].data.i32_u].i64_u = (uint64_t) WEB49_INTERP_READ(uint8_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD16_S) {
    locals[head[1].data.i32_u].i64_s = (int64_t) WEB49_INTERP_READ(int16_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD16_U) {
    locals[head[1].data.i32_u].i64_u = (uint64_t) WEB49_INTERP_READ(uint16_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD32_S) {
    locals[head[1].data.i32_u].i64_s = (int64_t) WEB49_INTERP_READ(int32_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD32_U) {
    locals[head[1].data.i32_u].i64_u = (uint64_t) WEB49_INTERP_READ(uint32_t, interp, LOCAL0.i32_u + head[2].data.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_MEMORY_GROW) {
    uint32_t last = interp.memsize;
    interp.memsize += LOCAL0.i32_u * 65536;
    interp.memory = web49_realloc(interp.memory, interp.memsize);
    // printf("grow (from: 0x%zx) (by: 0x%zx)\n", (size_t) last, (size_t) (LOCAL0.i32_u * 65536));
    memset(&interp.memory[last], 0, LOCAL0.i32_u * 65536);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_EQZ) {
    locals[head[1].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u == 0);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EQZ) {
    locals[head[1].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u == 0);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_CLZ) {
    locals[head[1].data.i32_u].i32_u = LOCAL0.i32_s == 0 ? 32 : __builtin_clz(LOCAL0.i32_s);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_CTZ) {
    locals[head[1].data.i32_u].i32_u = __builtin_ctz(LOCAL0.i32_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_POPCNT) {
    locals[head[1].data.i32_u].i32_u = __builtin_popcount(LOCAL0.i32_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_CLZ) {
    locals[head[1].data.i32_u].i64_u = LOCAL0.i64_s == 0 ? 64 : __builtin_clz(LOCAL0.i64_s);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_CTZ) {
    locals[head[1].data.i32_u].i64_u = __builtin_ctz(LOCAL0.i64_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_POPCNT) {
    locals[head[1].data.i32_u].i64_u = __builtin_popcount(LOCAL0.i64_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_ABS) {
    locals[head[1].data.i32_u].f32 = fabsf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_NEG) {
    locals[head[1].data.i32_u].f32 = -LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CEIL) {
    locals[head[1].data.i32_u].f32 = ceilf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_FLOOR) {
    locals[head[1].data.i32_u].f32 = floorf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_TRUNC) {
    locals[head[1].data.i32_u].f32 = truncf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_NEAREST) {
    locals[head[1].data.i32_u].f32 = nearbyintf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_SQRT) {
    locals[head[1].data.i32_u].f32 = sqrtf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_ABS) {
    locals[head[1].data.i32_u].f64 = fabs(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_NEG) {
    locals[head[1].data.i32_u].f64 = -LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CEIL) {
    locals[head[1].data.i32_u].f64 = ceil(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_FLOOR) {
    locals[head[1].data.i32_u].f64 = floor(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_TRUNC) {
    locals[head[1].data.i32_u].f64 = trunc(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_NEAREST) {
    locals[head[1].data.i32_u].f64 = nearbyint(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_SQRT) {
    locals[head[1].data.i32_u].f64 = sqrt(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_WRAP_I64) {
    locals[head[1].data.i32_u].i32_u = (uint32_t)LOCAL0.i64_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_TRUNC_S_F32) {
    locals[head[1].data.i32_u].i32_s = (int32_t)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_TRUNC_U_F32) {
    locals[head[1].data.i32_u].i32_u = (uint32_t)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_TRUNC_S_F64) {
    locals[head[1].data.i32_u].i32_s = (int32_t)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_TRUNC_U_F64) {
    locals[head[1].data.i32_u].i32_u = (uint32_t)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EXTEND_S_I32) {
    locals[head[1].data.i32_u].i64_s = (int64_t)LOCAL0.i32_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EXTEND_U_I32) {
    locals[head[1].data.i32_u].i64_u = (uint64_t)LOCAL0.i32_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_TRUNC_S_F32) {
    locals[head[1].data.i32_u].i64_s = (int64_t)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_TRUNC_U_F32) {
    locals[head[1].data.i32_u].i64_u = (uint64_t)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_TRUNC_S_F64) {
    locals[head[1].data.i32_u].i64_s = (int64_t)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_TRUNC_U_F64) {
    locals[head[1].data.i32_u].i64_u = (uint64_t)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONVERT_S_I32) {
    locals[head[1].data.i32_u].f32 = (float)LOCAL0.i32_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONVERT_U_I32) {
    locals[head[1].data.i32_u].f32 = (float)LOCAL0.i32_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONVERT_S_I64) {
    locals[head[1].data.i32_u].f32 = (float)LOCAL0.i64_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONVERT_U_I64) {
    locals[head[1].data.i32_u].f32 = (float)LOCAL0.i64_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_DEMOTE_F64) {
    locals[head[1].data.i32_u].f32 = (float)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONVERT_S_I32) {
    locals[head[1].data.i32_u].f64 = (double)LOCAL0.i32_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONVERT_U_I32) {
    locals[head[1].data.i32_u].f64 = (double)LOCAL0.i32_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONVERT_S_I64) {
    locals[head[1].data.i32_u].f64 = (double)LOCAL0.i64_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONVERT_U_I64) {
    locals[head[1].data.i32_u].f64 = (double)LOCAL0.i64_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_PROMOTE_F32) {
    locals[head[1].data.i32_u].f64 = (double)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_EXTEND8_S) {
    locals[head[1].data.i32_u].i32_s = (int32_t)(int8_t)LOCAL0.i32_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_EXTEND16_S) {
    locals[head[1].data.i32_u].i32_s = (int32_t)(int16_t)LOCAL0.i32_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EXTEND8_S) {
    locals[head[1].data.i32_u].i64_s = (int64_t)(int8_t)LOCAL0.i64_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EXTEND16_S) {
    locals[head[1].data.i32_u].i64_s = (int64_t)(int16_t)LOCAL0.i64_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EXTEND32_S) {
    locals[head[1].data.i32_u].i64_s = (int64_t)(int32_t)LOCAL0.i64_s;
    head += 2;
    NEXT();
}
