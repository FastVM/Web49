
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
NAME(WEB49_OPCODE_BR) {
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_GET_LOCAL) {
    interp.locals[head[0].data.i32_u] = interp.locals[head[1].data.i32_u];
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_GET_GLOBAL) {
    interp.locals[head[0].data.i32_u] = interp.extra->globals[head[1].data.i32_u];
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_MEMORY_SIZE) {
    interp.locals[head[0].data.i32_u].i32_u = interp.extra->memsize / 65536;
    head += 1;
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