
LABEL(WEB49_OPCODE_MEMORY_INIT) {
    fprintf(stderr, "memory init? you wish\n");
    __builtin_trap();
    NEXT();
}
LABEL(WEB49_OPCODE_DATA_DROP) {
    NEXT();
}
LABEL(WEB49_OPCODE_TABLE_INIT) {
    fprintf(stderr, "table init? you wish!\n");
    __builtin_trap();
    NEXT();
}
LABEL(WEB49_OPCODE_ELEM_DROP) {
    fprintf(stderr, "elem drop? you wish!\n");
    __builtin_trap();
    NEXT();
}
LABEL(WEB49_OPCODE_TABLE_COPY) {
    fprintf(stderr, "table copy? you wish!\n");
    __builtin_trap();
    NEXT();
}
LABEL(WEB49_OPCODE_FFI_CALL1) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth -= 1;
#endif
    interp.locals = locals;
    web49_env_t *func = head[0].func;
    locals[0] = func->func(func->state, interp);
    head = *--returns;
    locals = *--stacks;
    NEXT();
}
LABEL(WEB49_OPCODE_FFI_CALL0) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth -= 1;
#endif
    interp.locals = locals;
    web49_env_t *func = head[0].func;
    func->func(func->state, interp);
    head = *--returns;
    locals = *--stacks;
    NEXT();
}
NAME(WEB49_OPCODE_YIELD_POP) {
    locals[head[0].data.i32_u] = *--yield_ptr;
    head += 1;
    NEXT();
}
NAME(WEB49_OPCODE_RETURN0) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth -= 1;
#endif
    head = *--returns;
    locals = *--stacks;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE0) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE1) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    locals[head[1].data.i32_u + 0].i64_u = 0;
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE2) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    locals[head[1].data.i32_u + 0].i64_u = 0;
    locals[head[1].data.i32_u + 1].i64_u = 0;
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE4) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 4);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE8) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 8);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE16) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 16);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE32) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 32);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE64) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 64);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE128) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 128);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE256) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 256);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE512) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 512);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE1024) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + head[1].data.i32_u, 0, sizeof(web49_interp_data_t) * 1024);
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_CALL) {
#if defined(WEB49_PRINT_INSTR_DEPTH)
    depth += 1;
#endif
    web49_interp_block_t *fblock = head[0].block;
    web49_interp_block_run_comp(fblock, ptrs, interp);
    *returns++ = head + 3;
    *stacks++ = locals;
    locals += head[2].data.i32_u;
    memset(locals + fblock->nparams, 0, sizeof(web49_interp_data_t) * fblock->nlocals);
    if (fblock->nlocals == 0) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE0);
    } else if (fblock->nlocals <= 1) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE1);
    } else if (fblock->nlocals <= 2) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE2);
    } else if (fblock->nlocals <= 4) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE4);
    } else if (fblock->nlocals <= 8) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE8);
    } else if (fblock->nlocals <= 16) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE16);
    } else if (fblock->nlocals <= 32) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE32);
    } else if (fblock->nlocals <= 64) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE64);
    } else if (fblock->nlocals <= 128) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE128);
    } else if (fblock->nlocals <= 256) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE256);
    } else if (fblock->nlocals <= 512) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE512);
    } else if (fblock->nlocals <= 1024) {
        head[-1].opcode = OPCODE(WEB49_OPCODE_CALL_DONE1024);
    } else {
        fprintf(stderr, "too many locals: %zu\n", (size_t)fblock->nlocals);
        __builtin_trap();
    }
    head[0].opcodes = fblock->code;
    head[1].data.i32_u = fblock->nparams;
    head = fblock->code;
    NEXT();
}
NAME(WEB49_OPCODE_BR) {
    head = head[0].opcodes;
    NEXT();
}
NAME(WEB49_OPCODE_GET_LOCAL) {
    locals[head[0].data.i32_u] = locals[head[1].data.i32_u];
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_GET_GLOBAL) {
    locals[head[0].data.i32_u] = interp.globals[head[1].data.i32_u];
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_MEMORY_SIZE) {
    locals[head[0].data.i32_u].i32_u = interp.memsize / 65536;
    head += 1;
    NEXT();
}
NAME(WEB49_OPCODE_I32_CONST) {
    locals[head[0].data.i32_u] = head[1].data;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_I64_CONST) {
    locals[head[0].data.i32_u] = head[1].data;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F32_CONST) {
    locals[head[0].data.i32_u] = head[1].data;
    head += 2;
    NEXT();
}
NAME(WEB49_OPCODE_F64_CONST) {
    locals[head[0].data.i32_u] = head[1].data;
    head += 2;
    NEXT();
}
