NAME(WEB49_OPCODE_RETURN0) {
#if defined(WEB49_PRINT_INSTR)
    depth -= 1;
#endif
    head = *--returns;
    locals = *--stacks;
    head += 4;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE0) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE1) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 1);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE2) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 2);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE4) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 4);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE8) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 8);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE16) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 16);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE32) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 32);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE64) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 64);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE128) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 128);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE256) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 256);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE512) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 512);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL_DONE1024) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + head[3].data.i32_u, 0, sizeof(web49_interp_data_t) * 1024);
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_CALL) {
#if defined(WEB49_PRINT_INSTR)
    depth += 1;
#endif
    web49_interp_block_t *block = head[0].ptr;
    web49_interp_block_run_comp(block, ptrs, interp);
    *returns++ = head;
    *stacks++ = locals;
    locals += head[1].data.i32_u;
    memset(locals + block->nparams, 0, sizeof(web49_interp_data_t) * block->nlocals);
    if (block->nlocals == 0) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE0;
    } else if (block->nlocals <= 1) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE1;
    } else if (block->nlocals <= 2) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE2;
    } else if (block->nlocals <= 4) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE4;
    } else if (block->nlocals <= 8) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE8;
    } else if (block->nlocals <= 16) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE16;
    } else if (block->nlocals <= 32) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE32;
    } else if (block->nlocals <= 64) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE64;
    } else if (block->nlocals <= 128) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE128;
    } else if (block->nlocals <= 256) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE256;
    } else if (block->nlocals <= 512) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE512;
    } else if (block->nlocals <= 1024) {
        head[-1].ptr = &&DO_WEB49_OPCODE_CALL_DONE1024;
    } else {
        fprintf(stderr, "too many locals: %zu\n", (size_t)block->nlocals);
        __builtin_trap();
    }
    head[0].ptr = block->code;
    head = block->code;
    NEXT();
}
NAME(WEB49_OPCODE_LOAD_REG) {
    locals[head[0].data.i32_u] = reg;
    head += 1;
    NEXT();
}
NAME(WEB49_OPCODE_STORE_REG) {
    reg = locals[head[0].data.i32_u];
    head += 1;
    NEXT();
}
NAME(WEB49_OPCODE_BR) {
    head = head[0].ptr;
    NEXT();
}
NAME(WEB49_OPCODE_GET_LOCAL) {
    // printf("local.get %"PRIu32" -> %" -PRIu32"\n", head[1].data.i32_u, head[0].data.i32_u);
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