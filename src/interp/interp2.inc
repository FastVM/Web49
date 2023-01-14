
NAME(WEB49_OPCODE_SELECT) {
    if (locals[head[2].data.i32_u].i32_u != 0) {
        locals[head[3].data.i32_u] = LOCAL0;
    } else {
        locals[head[3].data.i32_u] = LOCAL1;
    }
    head += 4;
    NEXT();
}
NAME(WEB49_OPCODE_I32_STORE) {
    WEB49_INTERP_WRITE(uint32_t, interp, LOCAL0.i32_u + head[2].data.i32_u, LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE) {
    WEB49_INTERP_WRITE(uint64_t, interp, LOCAL0.i32_u + head[2].data.i32_u, LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_STORE) {
    WEB49_INTERP_WRITE(float, interp, LOCAL0.i32_u + head[2].data.i32_u, LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_STORE) {
    WEB49_INTERP_WRITE(double, interp, LOCAL0.i32_u + head[2].data.i32_u, LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_STORE8) {
    WEB49_INTERP_WRITE(uint8_t, interp, LOCAL0.i32_u + head[2].data.i32_u, (uint8_t)LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_STORE16) {
    WEB49_INTERP_WRITE(uint16_t, interp, LOCAL0.i32_u + head[2].data.i32_u, (uint16_t)LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE8) {
    WEB49_INTERP_WRITE(uint8_t, interp, LOCAL0.i32_u + head[2].data.i32_u, (uint8_t)LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE16) {
    WEB49_INTERP_WRITE(uint16_t, interp, LOCAL0.i32_u + head[2].data.i32_u, (uint16_t)LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_STORE32) {
    WEB49_INTERP_WRITE(uint32_t, interp, LOCAL0.i32_u + head[2].data.i32_u, (uint32_t)LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_EQ) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u == LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_NE) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u != LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LT_S) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_s < LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LT_U) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u < LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_GT_S) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_s > LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_GT_U) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u > LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LE_S) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_s <= LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_LE_U) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u <= LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_GE_S) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_s >= LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_GE_U) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i32_u >= LOCAL1.i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_EQ) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u == LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_NE) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u != LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LT_S) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_s < LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LT_U) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u < LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_GT_S) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_s > LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_GT_U) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u > LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LE_S) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_s <= LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_LE_U) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u <= LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_GE_S) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_s >= LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_GE_U) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.i64_u >= LOCAL1.i64_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_EQ) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 == LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_NE) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 != LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_LT) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 < LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_GT) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 > LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_LE) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 <= LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_GE) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f32 >= LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_EQ) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 == LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_NE) {
    // printf("%lf != %lf #=> %s\n", LOCAL0.f64, LOCAL1.f64, LOCAL0.f64 != LOCAL1.f64 ? "true" : "false");
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 != LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_LT) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 < LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_GT) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 > LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_LE) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 <= LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_GE) {
    locals[head[2].data.i32_u].i32_u = (uint32_t)(LOCAL0.f64 >= LOCAL1.f64);
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
NAME(WEB49_OPCODE_IF_I64_EQ) {
    if (LOCAL0.i64_u == LOCAL1.i64_u) {
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
NAME(WEB49_OPCODE_I32_ADD) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u + LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_SUB) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u - LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_MUL) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u * LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_DIV_S) {
    locals[head[2].data.i32_u].i32_s = LOCAL0.i32_s / LOCAL1.i32_s;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_DIV_U) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u / LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_REM_S) {
    locals[head[2].data.i32_u].i32_s = (int32_t)((int64_t)LOCAL0.i32_s % (int64_t)LOCAL1.i32_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_REM_U) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u % LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_AND) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u & LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_OR) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u | LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_XOR) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u ^ LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_SHL) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u << LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_SHR_S) {
    locals[head[2].data.i32_u].i32_s = LOCAL0.i32_s >> LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_SHR_U) {
    locals[head[2].data.i32_u].i32_u = LOCAL0.i32_u >> LOCAL1.i32_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_ROTL) {
    locals[head[2].data.i32_u].i32_u = (LOCAL0.i32_u << LOCAL1.i32_u) | (LOCAL0.i32_u >> (32 - LOCAL1.i32_u));
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I32_ROTR) {
    locals[head[2].data.i32_u].i32_u = (LOCAL0.i32_u >> LOCAL1.i32_u) | (LOCAL0.i32_u << (32 - LOCAL1.i32_u));
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_ADD) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u + LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_SUB) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u - LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_MUL) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u * LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_DIV_S) {
    locals[head[2].data.i32_u].i64_s = LOCAL0.i64_s / LOCAL1.i64_s;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_DIV_U) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u / LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_REM_S) {
    locals[head[2].data.i32_u].i64_s = (int64_t)((__int128_t)LOCAL0.i64_s % (__int128_t)LOCAL1.i64_s);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_REM_U) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u % LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_AND) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u & LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_OR) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u | LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_XOR) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u ^ LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_SHL) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u << LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_SHR_S) {
    locals[head[2].data.i32_u].i64_s = LOCAL0.i64_s >> LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_SHR_U) {
    locals[head[2].data.i32_u].i64_u = LOCAL0.i64_u >> LOCAL1.i64_u;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_ROTL) {
    locals[head[2].data.i32_u].i64_u = (LOCAL0.i64_u << LOCAL1.i64_u) | (LOCAL0.i64_u >> (64 - LOCAL1.i64_u));
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_I64_ROTR) {
    locals[head[2].data.i32_u].i64_u = (LOCAL0.i64_u >> LOCAL1.i64_u) | (LOCAL0.i64_u << (64 - LOCAL1.i64_u));
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_ADD) {
    locals[head[2].data.i32_u].f32 = LOCAL0.f32 + LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_SUB) {
    locals[head[2].data.i32_u].f32 = LOCAL0.f32 - LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_MUL) {
    locals[head[2].data.i32_u].f32 = LOCAL0.f32 * LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_DIV) {
    locals[head[2].data.i32_u].f32 = LOCAL0.f32 / LOCAL1.f32;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_MIN) {
    locals[head[2].data.i32_u].f32 = fminf(LOCAL0.f32, LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_MAX) {
    locals[head[2].data.i32_u].f32 = fmaxf(LOCAL0.f32, LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F32_COPYSIGN) {
    locals[head[2].data.i32_u].f32 = copysignf(LOCAL0.f32, LOCAL1.f32);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_ADD) {
    locals[head[2].data.i32_u].f64 = LOCAL0.f64 + LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_SUB) {
    locals[head[2].data.i32_u].f64 = LOCAL0.f64 - LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_MUL) {
    locals[head[2].data.i32_u].f64 = LOCAL0.f64 * LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_DIV) {
    locals[head[2].data.i32_u].f64 = LOCAL0.f64 / LOCAL1.f64;
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_MIN) {
    locals[head[2].data.i32_u].f64 = fmin(LOCAL0.f64, LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_MAX) {
    locals[head[2].data.i32_u].f64 = fmax(LOCAL0.f64, LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_F64_COPYSIGN) {
    locals[head[2].data.i32_u].f64 = copysign(LOCAL0.f64, LOCAL1.f64);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_MEMORY_FILL) {
    memset(WEB49_INTERP_ADDR(void *, interp, LOCAL0.i32_u, LOCAL1.i32_u), LOCAL1.i32_u, locals[head[2].data.i32_u].i32_u);
    head += 3;
    NEXT();
}
NAME(WEB49_OPCODE_MEMORY_COPY) {
    size_t size = (size_t)locals[head[2].data.i32_u].i32_u;
    memmove(WEB49_INTERP_ADDR(void *, interp, LOCAL0.i32_u, size), WEB49_INTERP_ADDR(void *, interp, LOCAL0.i32_u, size), size);
    head += 3;
    NEXT();
}