
NAME(WEB49_OPCODE_SELECT) {
    if (interp.locals[head[2].data.i32_u].i32_u != 0) {
        interp.locals[head[3].data.i32_u] = LOCAL0;
    } else {
        interp.locals[head[3].data.i32_u] = LOCAL1;
    }
    head += 4;
    NEXT();
}
NAME(WEB49_OPCODE_I32_STORE) {
    *(uint32_t *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE) {
    *(uint64_t *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_STORE) {
    *(float *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_STORE) {
    *(double *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_STORE8) {
    *(uint8_t *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint8_t)LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_STORE16) {
    *(uint16_t *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint16_t)LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE8) {
    *(uint8_t *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint8_t)LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE16) {
    *(uint16_t *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint16_t)LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE32) {
    *(uint32_t *)&interp.memory[LOCAL0.i32_u + head[2].data.i32_u] = (uint32_t)LOCAL1.i64_u;
    head += 3;
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
NAME(WEB49_OPCODE_IF_I32_EQ) {
    if (LOCAL0.i32_u == LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_NE) {
    if (LOCAL0.i32_u != LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_LT_S) {
    if (LOCAL0.i32_s < LOCAL1.i32_s) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_LT_U) {
    if (LOCAL0.i32_u < LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_GT_S) {
    if (LOCAL0.i32_s > LOCAL1.i32_s) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_GT_U) {
    if (LOCAL0.i32_u > LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_LE_S) {
    if (LOCAL0.i32_s <= LOCAL1.i32_s) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_LE_U) {
    if (LOCAL0.i32_u <= LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_GE_S) {
    if (LOCAL0.i32_s >= LOCAL1.i32_s) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_GE_U) {
    if (LOCAL0.i32_u >= LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_EQ) {
    if (LOCAL0.i64_u == LOCAL1.i64_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_NE) {
    if (LOCAL0.i64_u != LOCAL1.i64_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_LT_S) {
    if (LOCAL0.i64_s < LOCAL1.i64_s) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_LT_U) {
    if (LOCAL0.i64_u < LOCAL1.i64_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_GT_S) {
    if (LOCAL0.i64_s > LOCAL1.i64_s) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_GT_U) {
    if (LOCAL0.i64_u > LOCAL1.i64_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_LE_S) {
    if (LOCAL0.i64_s <= LOCAL1.i64_s) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_LE_U) {
    if (LOCAL0.i64_u <= LOCAL1.i64_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_GE_S) {
    if (LOCAL0.i64_s >= LOCAL1.i64_s) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I64_GE_U) {
    if (LOCAL0.i64_u >= LOCAL1.i64_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F32_EQ) {
    if (LOCAL0.f32 == LOCAL1.f32) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F32_NE) {
    if (LOCAL0.f32 != LOCAL1.f32) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F32_LT) {
    if (LOCAL0.f32 < LOCAL1.f32) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F32_GT) {
    if (LOCAL0.f32 > LOCAL1.f32) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F32_LE) {
    if (LOCAL0.f32 <= LOCAL1.f32) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F32_GE) {
    if (LOCAL0.f32 >= LOCAL1.f32) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F64_EQ) {
    if (LOCAL0.f64 == LOCAL1.f64) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F64_NE) {
    if (LOCAL0.f64 != LOCAL1.f64) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F64_LT) {
    if (LOCAL0.f64 < LOCAL1.f64) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F64_GT) {
    if (LOCAL0.f64 > LOCAL1.f64) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F64_LE) {
    if (LOCAL0.f64 <= LOCAL1.f64) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_F64_GE) {
    if (LOCAL0.f64 >= LOCAL1.f64) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
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
    interp.locals[head[2].data.i32_u].i32_u = (LOCAL0.i32_u << LOCAL1.i32_u) | (LOCAL0.i32_u >> (32 - LOCAL1.i32_u));
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_ROTR) {
    interp.locals[head[2].data.i32_u].i32_u = (LOCAL0.i32_u >> LOCAL1.i32_u) | (LOCAL0.i32_u << (32 - LOCAL1.i32_u));
    head += 3;
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
    interp.locals[head[2].data.i32_u].i64_u = (LOCAL0.i64_u << LOCAL1.i64_u) | (LOCAL0.i64_u >> (64 - LOCAL1.i64_u));
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_ROTR) {
    interp.locals[head[2].data.i32_u].i64_u = (LOCAL0.i64_u >> LOCAL1.i64_u) | (LOCAL0.i64_u << (64 - LOCAL1.i64_u));
    head += 3;
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
NAME(WEB49_OPCODE_MEMORY_FILL) {
    memset(&interp.memory[LOCAL0.i32_u], LOCAL1.i32_u, interp.locals[head[2].data.i32_u].i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_MEMORY_COPY) {
    memmove(&interp.memory[LOCAL0.i32_u], &interp.memory[LOCAL1.i32_u], interp.locals[head[2].data.i32_u].i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_AND) {
    if (LOCAL0.i32_u & LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_OR) {
    if (LOCAL0.i32_u | LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}
NAME(WEB49_OPCODE_IF_I32_XOR) {
    if (LOCAL0.i32_u ^ LOCAL1.i32_u) {
        head = head[2].ptr;
    } else {
        head = head[3].ptr;
    }
    NEXT();
}