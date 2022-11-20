
NAME(WEB49_OPCODE_IF) {
    if (LOCAL0.i32_u != 0) {
        head = head[1].ptr;
        NEXT();
    } else {
        head = head[2].ptr;
        NEXT();
    }
}
NAME(WEB49_OPCODE_BR) {
    head = head[0].ptr;
    NEXT();
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
    return LOCAL0;
}
NAME(WEB49_OPCODE_CALL0) {
    web49_interp_block_t *block = head[0].ptr;
    web49_interp_data_t *next = interp.locals + head[1].data.i32_u;
    web49_interp_t interp2 = (web49_interp_t){
        .locals = next,
        .extra = interp.extra,
    };
    memset(next + block->nparams, 0, sizeof(web49_interp_data_t) * block->nlocals);
    web49_interp_block_run(interp2, block);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_CALL1) {
    // fprintf(stderr, "OUT %p\n", &interp.locals[head[2].data.i32_u]);
    web49_interp_block_t *block = head[0].ptr;
    web49_interp_data_t *next = interp.locals + head[1].data.i32_u;
    web49_interp_t interp2 = (web49_interp_t){
        .locals = next,
        .extra = interp.extra,
    };
    memset(next + block->nparams, 0, sizeof(web49_interp_data_t) * block->nlocals);
    web49_interp_data_t res = web49_interp_block_run(interp2, block);
    interp.locals[head[2].data.i32_u] = res;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_INDIRECT) {
    web49_interp_block_t *block = interp.extra->table[head[0].data.i32_u];
    web49_interp_data_t *next = interp.locals + head[1].data.i32_u;
    web49_interp_t interp2 = (web49_interp_t){
        .locals = next,
        .extra = interp.extra,
    };
    memset(next + block->nparams, 0, sizeof(web49_interp_data_t) * block->nlocals);
    web49_interp_data_t res = web49_interp_block_run(interp2, block);
    interp.locals[head[2].data.i32_u] = res;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_SELECT) {
    if (interp.locals[head[2].data.i32_u].i32_u != 0) {
        interp.locals[head[3].data.i32_u] = LOCAL0;
    } else {
        interp.locals[head[3].data.i32_u] = LOCAL1;
    }
    head += 4;
    NEXT();
}
NAME(WEB49_OPCODE_GET_LOCAL) {
    interp.locals[head[0].data.i32_u] = LOCAL1;
    // fprintf(stderr,"local.get %"PRIu32" (%p)\n", head[1].data.i32_u, &interp.locals[head[1].data.i32_u]);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_SET_LOCAL) {
    interp.locals[head[1].data.i32_u] = LOCAL0;
    // fprintf(stderr,"local.set %"PRIu32" (%p)\n", head[1].data.i32_u, &interp.locals[head[1].data.i32_u]);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_TEE_LOCAL) {
    web49_interp_data_t got = LOCAL0;
    interp.locals[head[1].data.i32_u] = got;
    interp.locals[head[2].data.i32_u] = got;
    // fprintf(stderr,"local.tee %"PRIu32" (%p)\n", head[2].data.i32_u, &interp.locals[head[2].data.i32_u]);
    // fprintf(stderr,"local.tee %"PRIu32" (%p) & %"PRIu32" (%p)\n", head[1].data.i32_u, &interp.locals[head[1].data.i32_u], head[2].data.i32_u, &interp.locals[head[2].data.i32_u]);
    head += 3;
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
NAME(WEB49_OPCODE_I32_STORE) {
    *(uint32_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE) {
    *(uint64_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_STORE) {
    *(float *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_STORE) {
    *(double *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_STORE8) {
    *(uint8_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint8_t)LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_STORE16) {
    *(uint16_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint16_t)LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE8) {
    *(uint8_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint8_t)LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE16) {
    *(uint16_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint16_t)LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE32) {
    *(uint32_t *)&interp.extra->memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint32_t)LOCAL1.i64_u;
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
NAME(WEB49_OPCODE_I32_EQ) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u == LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_NE) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u != LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LT_S) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_s < LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LT_U) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u < LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_GT_S) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_s > LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_GT_U) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u > LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LE_S) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_s <= LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LE_U) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u <= LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_GE_S) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_s >= LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_GE_U) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u >= LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EQZ) {
    interp.locals[head[1].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u == 0);
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EQ) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u == LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_NE) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u != LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LT_S) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_s < LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LT_U) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u < LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_GT_S) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_s > LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_GT_U) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u > LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LE_S) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_s <= LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LE_U) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u <= LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_GE_S) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_s >= LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_GE_U) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u >= LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_EQ) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 == LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_NE) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 != LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_LT) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 < LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_GT) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 > LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_LE) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 <= LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_GE) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 >= LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_EQ) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 == LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_NE) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 != LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_LT) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 < LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_GT) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 > LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_LE) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 <= LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_GE) {
    interp.locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 >= LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_CLZ) {
    fprintf(stderr, "unimplemented: i32_clz\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I32_CTZ) {
    fprintf(stderr, "unimplemented: i32_ctz\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I32_POPCNT) {
    fprintf(stderr, "unimplemented: i32_popcnt\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I32_ADD) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u + LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_SUB) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u - LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_MUL) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u * LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_DIV_S) {
    interp.locals[head[2].data.i32_u].i32_s = LOCAL0.i32_s / LOCAL1.i32_s;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_DIV_U) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u / LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_REM_S) {
    interp.locals[head[2].data.i32_u].i32_s = LOCAL0.i32_s % LOCAL1.i32_s;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_REM_U) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u % LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_AND) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u & LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_OR) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u | LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_XOR) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u ^ LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_SHL) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u << LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_SHR_S) {
    interp.locals[head[2].data.i32_u].i32_s = LOCAL0.i32_s >> LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_SHR_U) {
    interp.locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u >> LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_ROTL) {
    fprintf(stderr, "unimplemented: i32_rotl\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I32_ROTR) {
    fprintf(stderr, "unimplemented: i32_rotr\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I64_CLZ) {
    fprintf(stderr, "unimplemented: i64_clz\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I64_CTZ) {
    fprintf(stderr, "unimplemented: i64_ctz\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I64_POPCNT) {
    fprintf(stderr, "unimplemented: i64_popcnt\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I64_ADD) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u + LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_SUB) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u - LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_MUL) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u * LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_DIV_S) {
    interp.locals[head[2].data.i32_u].i64_s = LOCAL0.i64_s / LOCAL1.i64_s;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_DIV_U) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u / LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_REM_S) {
    interp.locals[head[2].data.i32_u].i64_s = LOCAL0.i64_s % LOCAL1.i64_s;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_REM_U) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u % LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_AND) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u & LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_OR) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u | LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_XOR) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u ^ LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_SHL) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u << LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_SHR_S) {
    interp.locals[head[2].data.i32_u].i64_s = LOCAL0.i64_s >> LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_SHR_U) {
    interp.locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u >> LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_ROTL) {
    fprintf(stderr, "unimplemented: i64_rotl\n");
    __builtin_trap();
    NEXT();
}
NAME(WEB49_OPCODE_I64_ROTR) {
    fprintf(stderr, "unimplemented: i64_rotr\n");
    __builtin_trap();
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
NAME(WEB49_OPCODE_F32_ADD) {
    interp.locals[head[2].data.i32_u].f32 = LOCAL0.f32 + LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_SUB) {
    interp.locals[head[2].data.i32_u].f32 = LOCAL0.f32 - LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_MUL) {
    interp.locals[head[2].data.i32_u].f32 = LOCAL0.f32 * LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_DIV) {
    interp.locals[head[2].data.i32_u].f32 = LOCAL0.f32 / LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_MIN) {
    interp.locals[head[2].data.i32_u].f32 = fminf(LOCAL0.f32, LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_MAX) {
    interp.locals[head[2].data.i32_u].f32 = fmaxf(LOCAL0.f32, LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_COPYSIGN) {
    interp.locals[head[2].data.i32_u].f32 = copysignf(LOCAL0.f32, LOCAL1.f32);
    head += 3;
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
NAME(WEB49_OPCODE_F64_ADD) {
    interp.locals[head[2].data.i32_u].f64 = LOCAL0.f64 + LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_SUB) {
    interp.locals[head[2].data.i32_u].f64 = LOCAL0.f64 - LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_MUL) {
    interp.locals[head[2].data.i32_u].f64 = LOCAL0.f64 * LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_DIV) {
    interp.locals[head[2].data.i32_u].f64 = LOCAL0.f64 / LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_MIN) {
    interp.locals[head[2].data.i32_u].f64 = fmin(LOCAL0.f64, LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_MAX) {
    interp.locals[head[2].data.i32_u].f64 = fmax(LOCAL0.f64, LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_COPYSIGN) {
    interp.locals[head[2].data.i32_u].f64 = copysign(LOCAL0.f64, LOCAL1.f64);
    head += 3;
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