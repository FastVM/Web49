NAME(WEB49_OPCODE_CALL_INDIRECT) {
    web49_interp_block_t *block = interp.extra->table[LOCAL0.i32_u];
    *returns++ = head;
    *stacks++ = interp.locals;
    interp.locals += head[1].data.i32_u;
    memset(interp.locals + block->nparams, 0, sizeof(web49_interp_data_t) * block->nlocals);
    web49_interp_block_run_comp(block, ptrs, interp);
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
NAME(WEB49_OPCODE_BR_IF) {
    if (LOCAL0.i32_u != 0) {
        head = head[1].ptr;
        NEXT();
    } else {
        head += 2;
        NEXT();
    }
}
NAME(WEB49_OPCODE_BR_TABLE) {
    uint32_t brvalue = LOCAL0.i32_u;
    uint32_t maxvalue = head[1].data.i32_u;
    head += 2;
    if (brvalue < maxvalue) {
        head = head[brvalue].ptr;
        NEXT();
    } else {
        head = head[maxvalue].ptr;
        NEXT();
    }
}
NAME(WEB49_OPCODE_RETURN) {
    web49_interp_data_t ret = LOCAL0;
    head = *--returns;
    interp.locals = *--stacks;
    interp.locals[head[2].data.i32_u] = ret;
    head += 4;
    NEXT();
}
NAME(WEB49_OPCODE_TEE_LOCAL) {
    web49_interp_data_t got = LOCAL0;
    interp.locals[head[1].data.i32_u] = got;
    interp.locals[head[2].data.i32_u] = got;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_SET_LOCAL) {
    interp.locals[head[1].data.i32_u] = LOCAL0;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_GET_GLOBAL) {
    interp.locals[head[0].data.i32_u] = interp.extra->globals[head[1].data.i32_u];
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_SET_GLOBAL) {
    interp.extra->globals[head[1].data.i32_u] = LOCAL0;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD) {
    interp.locals[head[1].data.i32_u].i32_u = *(uint32_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD) {
    interp.locals[head[1].data.i32_u].i64_u = *(uint64_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_LOAD) {
    interp.locals[head[1].data.i32_u].f32 = *(float *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_LOAD) {
    interp.locals[head[1].data.i32_u].f64 = *(double *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD8_S) {
    interp.locals[head[1].data.i32_u].i32_s = (int32_t) * (int8_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD8_U) {
    interp.locals[head[1].data.i32_u].i32_u = (uint32_t) * (uint8_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD16_S) {
    interp.locals[head[1].data.i32_u].i32_s = (int32_t) * (int16_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LOAD16_U) {
    interp.locals[head[1].data.i32_u].i32_u = (uint32_t) * (uint16_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD8_S) {
    interp.locals[head[1].data.i32_u].i64_s = (int64_t) * (int8_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD8_U) {
    interp.locals[head[1].data.i32_u].i64_u = (uint64_t) * (uint8_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD16_S) {
    interp.locals[head[1].data.i32_u].i64_s = (int64_t) * (int16_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD16_U) {
    interp.locals[head[1].data.i32_u].i64_u = (uint64_t) * (uint16_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD32_S) {
    interp.locals[head[1].data.i32_u].i64_s = (int64_t) * (int32_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LOAD32_U) {
    interp.locals[head[1].data.i32_u].i64_u = (uint64_t) * (uint32_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u];
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_MEMORY_SIZE) {
    interp.locals[head[0].data.i32_u].i32_u = interp.extra->memsize / 65536;
    head += 1;
    NEXT();
}
NAME(WEB49_OPCODE_MEMORY_GROW) {
    fprintf(stderr, "unimplemented: memory_grow\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I32_CONST) {
    interp.locals[head[0].data.i32_u] = head[1].data;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_CONST) {
    interp.locals[head[0].data.i32_u] = head[1].data;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONST) {
    interp.locals[head[0].data.i32_u] = head[1].data;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONST) {
    interp.locals[head[0].data.i32_u] = head[1].data;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_EQZ) {
    interp.locals[head[1].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u == 0);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EQZ) {
    interp.locals[head[1].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u == 0);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_EQZ) {
    if (LOCAL0.i32_u == 0) { head = head[1].ptr; } else { head = head[2].ptr; }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_EQZ) {
    if (LOCAL0.i64_u == 0) { head = head[1].ptr; } else { head = head[2].ptr; }
    NEXT();
}
NAME(WEB49_OPCODE_I32_CLZ) {
    interp.locals[head[1].data.i32_u].i32_u = __builtin_clz(LOCAL0.i32_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_CTZ) {
    interp.locals[head[1].data.i32_u].i32_u = __builtin_ctz(LOCAL0.i32_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_POPCNT) {
    interp.locals[head[1].data.i32_u].i32_u = __builtin_popcount(LOCAL0.i32_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_CLZ) {
    interp.locals[head[1].data.i32_u].i64_u = __builtin_clz(LOCAL0.i64_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_CTZ) {
    interp.locals[head[1].data.i32_u].i64_u = __builtin_ctz(LOCAL0.i64_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_POPCNT) {
    interp.locals[head[1].data.i32_u].i64_u = __builtin_popcount(LOCAL0.i64_u);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_ABS) {
    interp.locals[head[1].data.i32_u].f32 = fabsf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_NEG) {
    interp.locals[head[1].data.i32_u].f32 = -LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CEIL) {
    interp.locals[head[1].data.i32_u].f32 = ceilf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_FLOOR) {
    interp.locals[head[1].data.i32_u].f32 = floorf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_TRUNC) {
    interp.locals[head[1].data.i32_u].f32 = truncf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_NEAREST) {
    interp.locals[head[1].data.i32_u].f32 = nearbyintf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_SQRT) {
    interp.locals[head[1].data.i32_u].f32 = sqrtf(LOCAL0.f32);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_ABS) {
    interp.locals[head[1].data.i32_u].f64 = fabs(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_NEG) {
    interp.locals[head[1].data.i32_u].f64 = -LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CEIL) {
    interp.locals[head[1].data.i32_u].f64 = ceil(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_FLOOR) {
    interp.locals[head[1].data.i32_u].f64 = floor(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_TRUNC) {
    interp.locals[head[1].data.i32_u].f64 = trunc(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_NEAREST) {
    interp.locals[head[1].data.i32_u].f64 = nearbyint(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_SQRT) {
    interp.locals[head[1].data.i32_u].f64 = sqrt(LOCAL0.f64);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_WRAP_I64) {
    interp.locals[head[1].data.i32_u].i32_u = (uint32_t)LOCAL0.i64_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_TRUNC_S_F32) {
    interp.locals[head[1].data.i32_u].i32_s = (int32_t)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_TRUNC_U_F32) {
    interp.locals[head[1].data.i32_u].i32_u = (uint32_t)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_TRUNC_S_F64) {
    interp.locals[head[1].data.i32_u].i32_s = (int32_t)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I32_TRUNC_U_F64) {
    interp.locals[head[1].data.i32_u].i32_u = (uint32_t)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EXTEND_S_I32) {
    interp.locals[head[1].data.i32_u].i64_s = (int64_t)LOCAL0.i32_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EXTEND_U_I32) {
    interp.locals[head[1].data.i32_u].i64_u = (uint64_t)LOCAL0.i32_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_TRUNC_S_F32) {
    interp.locals[head[1].data.i32_u].i64_s = (int64_t)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_TRUNC_U_F32) {
    interp.locals[head[1].data.i32_u].i64_u = (uint64_t)LOCAL0.f32;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_TRUNC_S_F64) {
    interp.locals[head[1].data.i32_u].i64_s = (int64_t)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_TRUNC_U_F64) {
    interp.locals[head[1].data.i32_u].i64_u = (uint64_t)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONVERT_S_I32) {
    interp.locals[head[1].data.i32_u].f32 = (float)LOCAL0.i32_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONVERT_U_I32) {
    interp.locals[head[1].data.i32_u].f32 = (float)LOCAL0.i32_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONVERT_S_I64) {
    interp.locals[head[1].data.i32_u].f32 = (float)LOCAL0.i64_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONVERT_U_I64) {
    interp.locals[head[1].data.i32_u].f32 = (float)LOCAL0.i64_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_DEMOTE_F64) {
    interp.locals[head[1].data.i32_u].f32 = (float)LOCAL0.f64;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONVERT_S_I32) {
    interp.locals[head[1].data.i32_u].f64 = (double)LOCAL0.i32_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONVERT_U_I32) {
    interp.locals[head[1].data.i32_u].f64 = (double)LOCAL0.i32_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONVERT_S_I64) {
    interp.locals[head[1].data.i32_u].f64 = (double)LOCAL0.i64_s;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONVERT_U_I64) {
    interp.locals[head[1].data.i32_u].f64 = (double)LOCAL0.i64_u;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_PROMOTE_F32) {
    interp.locals[head[1].data.i32_u].f64 = (double)LOCAL0.f32;
    head += 2;
    NEXT();
}
