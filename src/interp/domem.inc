
#if !defined(LOAD) && !defined(STORE)
#error to use this inc file, define LOAD, define STORE, or define both
#endif

#if defined(LOAD)
LOAD(WEB49_OPCODE_I32_LOAD) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i32_u) = *(uint32_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I64_LOAD) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i64_u) = *(uint64_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_F32_LOAD) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(f32) = *(float *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_F64_LOAD) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(f64) = *(double *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I32_LOAD8_S) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i32_s) = (int32_t) * (int8_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I32_LOAD8_U) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i32_u) = (uint32_t) * (uint8_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I32_LOAD16_S) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i32_s) = (int32_t) * (int16_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I32_LOAD16_U) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i32_u) = (uint32_t) * (uint16_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I64_LOAD8_S) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i64_s) = (int64_t) * (int8_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I64_LOAD8_U) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i64_u) = (uint64_t) * (uint8_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I64_LOAD16_S) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i64_s) = (int64_t) * (int16_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I64_LOAD16_U) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i64_u) = (uint64_t) * (uint16_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I64_LOAD32_S) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i64_s) = (int64_t) * (int32_t *)&interp.memory[ptr + off];
    NEXT();
}
LOAD(WEB49_OPCODE_I64_LOAD32_U) {
    uint32_t ptr = (LOAD_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    LOAD_TO(i64_u) = (uint64_t) * (uint32_t *)&interp.memory[ptr + off];
    NEXT();
}
#endif

#if defined(STORE)
STORE(WEB49_OPCODE_I32_STORE) {
    uint32_t val = (STORE_VAL)->i32_u;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(uint32_t *)&interp.memory[ptr + off] = (uint32_t)val;
    NEXT();
}
STORE(WEB49_OPCODE_I64_STORE) {
    uint64_t val = (STORE_VAL)->i64_u;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(uint64_t *)&interp.memory[ptr + off] = (uint64_t)val;
    NEXT();
}
STORE(WEB49_OPCODE_F32_STORE) {
    float val = (STORE_VAL)->f32;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(float *)&interp.memory[ptr + off] = (float)val;
    NEXT();
}
STORE(WEB49_OPCODE_F64_STORE) {
    double val = (STORE_VAL)->f64;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(double *)&interp.memory[ptr + off] = (double)val;
    NEXT();
}
STORE(WEB49_OPCODE_I32_STORE8) {
    uint32_t val = (STORE_VAL)->i32_u;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(uint8_t *)&interp.memory[ptr + off] = (uint8_t)val;
    NEXT();
}
STORE(WEB49_OPCODE_I32_STORE16) {
    uint32_t val = (STORE_VAL)->i32_u;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(uint16_t *)&interp.memory[ptr + off] = (uint16_t)val;
    NEXT();
}
STORE(WEB49_OPCODE_I64_STORE8) {
    uint64_t val = (STORE_VAL)->i64_u;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(uint8_t *)&interp.memory[ptr + off] = (uint8_t)val;
    NEXT();
}
STORE(WEB49_OPCODE_I64_STORE16) {
    uint64_t val = (STORE_VAL)->i64_u;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(uint16_t *)&interp.memory[ptr + off] = (uint16_t)val;
    NEXT();
}
STORE(WEB49_OPCODE_I64_STORE32) {
    uint64_t val = (STORE_VAL)->i64_u;
    uint32_t ptr = (STORE_PTR)->i32_u;
    uint32_t off = head++->data.i32_u;
    *(uint32_t *)&interp.memory[ptr + off] = (uint32_t)val;
    NEXT();
}
#endif