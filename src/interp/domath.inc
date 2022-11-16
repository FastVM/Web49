#if !defined(LHS)
#error define LHS to get the left hand side
#endif

#if !defined(RHS)
#error define RHS to get the right hand side
#endif

#if !defined(OUT)
#error define OUT to store the output
#endif

#if !defined(BLOCK)
#error define BLOCK to label the block
#endif

BLOCK(WEB49_OPCODE_I32_EQ) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (uint32_t)(lhs == rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_NE) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (uint32_t)(lhs != rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_LT_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    OUT(i32_u) = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_LT_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_GT_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    OUT(i32_u) = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_GT_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_LE_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    OUT(i32_u) = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_LE_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_GE_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    OUT(i32_u) = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_GE_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_ADD) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs + rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_SUB) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs - rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_MUL) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs * rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_DIV_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    OUT(i32_s) = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_DIV_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_REM_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    OUT(i32_s) = (lhs % rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_REM_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs % rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_AND) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = lhs & rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_OR) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = lhs | rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_XOR) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = lhs ^ rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_SHL) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs << rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_SHR_S) {
    uint32_t rhs = (RHS)->i32_u;
    int32_t lhs = (LHS)->i32_s;
    OUT(i32_s) = (lhs >> rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_SHR_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs >> rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_ROTL) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs >> rhs) | (lhs << (32 - rhs));
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_ROTR) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    OUT(i32_u) = (lhs << rhs) | (lhs >> (32 - rhs));
    NEXT();
}

BLOCK(WEB49_OPCODE_I64_EQ) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i32_u) = (uint32_t)(lhs == rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_NE) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i32_u) = (uint32_t)(lhs != rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_LT_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    OUT(i32_u) = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_LT_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i32_u) = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_GT_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    OUT(i32_u) = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_GT_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i32_u) = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_LE_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    OUT(i32_u) = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_LE_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i32_u) = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_GE_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    OUT(i32_u) = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_GE_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i32_u) = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_ADD) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs + rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_SUB) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs - rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_MUL) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs * rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_DIV_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    OUT(i64_s) = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_DIV_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_REM_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    OUT(i64_s) = (lhs % rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_REM_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs % rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_AND) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = lhs & rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_OR) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = lhs | rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_XOR) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = lhs ^ rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_SHL) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs << rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_SHR_S) {
    uint64_t rhs = (RHS)->i64_u;
    int64_t lhs = (LHS)->i64_s;
    OUT(i64_s) = (lhs >> rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_SHR_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs >> rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_ROTL) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs >> rhs) | (lhs << (64 - rhs));
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_ROTR) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    OUT(i64_u) = (lhs << rhs) | (lhs >> (64 - rhs));
    NEXT();
}

BLOCK(WEB49_OPCODE_F32_EQ) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(i32_u) = (uint32_t)(lhs == rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_NE) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(i32_u) = (uint32_t)(lhs != rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_LT) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(i32_u) = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_GT) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(i32_u) = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_LE) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(i32_u) = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_GE) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(i32_u) = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_ADD) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(f32) = (lhs + rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_SUB) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(f32) = (lhs - rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_MUL) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(f32) = (lhs * rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_DIV) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(f32) = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_MIN) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(f32) = fminf(lhs, rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_MAX) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(f32) = fmaxf(lhs, rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F32_COPYSIGN) {
    float rhs = (RHS)->f32;
    float lhs = (LHS)->f32;
    OUT(f32) = copysignf(lhs, rhs);
    NEXT();
}


BLOCK(WEB49_OPCODE_F64_EQ) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(i32_u) = (uint32_t)(lhs == rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_NE) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(i32_u) = (uint32_t)(lhs != rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_LT) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(i32_u) = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_GT) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(i32_u) = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_LE) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(i32_u) = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_GE) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(i32_u) = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_ADD) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(f64) = (lhs + rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_SUB) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(f64) = (lhs - rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_MUL) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(f64) = (lhs * rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_DIV) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(f64) = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_MIN) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(f64) = fmin(lhs, rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_MAX) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(f64) = fmax(lhs, rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_F64_COPYSIGN) {
    double rhs = (RHS)->f64;
    double lhs = (LHS)->f64;
    OUT(f64) = copysign(lhs, rhs);
    NEXT();
}

#undef LHS
#undef RHS
#undef OUT
#undef BLOCK
