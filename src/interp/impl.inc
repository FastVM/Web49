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
    (OUT)->i32_u = (uint32_t)(lhs == rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_NE) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (uint32_t)(lhs != rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_LT_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    (OUT)->i32_u = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_LT_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_GT_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    (OUT)->i32_u = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_GT_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_LE_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    (OUT)->i32_u = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_LE_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_GE_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    (OUT)->i32_u = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_GE_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_ADD) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs + rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_SUB) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs - rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_MUL) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs * rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_DIV_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    (OUT)->i32_s = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_DIV_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_REM_S) {
    int32_t rhs = (RHS)->i32_s;
    int32_t lhs = (LHS)->i32_s;
    (OUT)->i32_s = (lhs % rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_REM_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs % rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_AND) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = lhs & rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_OR) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = lhs | rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_XOR) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = lhs ^ rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_SHL) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs << rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_SHR_S) {
    uint32_t rhs = (RHS)->i32_u;
    int32_t lhs = (LHS)->i32_s;
    (OUT)->i32_s = (lhs >> rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_SHR_U) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs >> rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_ROTL) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs >> rhs) | (lhs << (32 - rhs));
    NEXT();
}
BLOCK(WEB49_OPCODE_I32_ROTR) {
    uint32_t rhs = (RHS)->i32_u;
    uint32_t lhs = (LHS)->i32_u;
    (OUT)->i32_u = (lhs << rhs) | (lhs >> (32 - rhs));
    NEXT();
}

BLOCK(WEB49_OPCODE_I64_EQ) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i32_u = (uint32_t)(lhs == rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_NE) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i32_u = (uint32_t)(lhs != rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_LT_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    (OUT)->i32_u = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_LT_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i32_u = (uint32_t)(lhs < rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_GT_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    (OUT)->i32_u = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_GT_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i32_u = (uint32_t)(lhs > rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_LE_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    (OUT)->i32_u = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_LE_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i32_u = (uint32_t)(lhs <= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_GE_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    (OUT)->i32_u = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_GE_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i32_u = (uint32_t)(lhs >= rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_ADD) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs + rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_SUB) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs - rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_MUL) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs * rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_DIV_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    (OUT)->i64_s = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_DIV_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs / rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_REM_S) {
    int64_t rhs = (RHS)->i64_s;
    int64_t lhs = (LHS)->i64_s;
    (OUT)->i64_s = (lhs % rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_REM_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs % rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_AND) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = lhs & rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_OR) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = lhs | rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_XOR) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = lhs ^ rhs;
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_SHL) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs << rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_SHR_S) {
    uint64_t rhs = (RHS)->i64_u;
    int64_t lhs = (LHS)->i64_s;
    (OUT)->i64_s = (lhs >> rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_SHR_U) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs >> rhs);
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_ROTL) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs >> rhs) | (lhs << (64 - rhs));
    NEXT();
}
BLOCK(WEB49_OPCODE_I64_ROTR) {
    uint64_t rhs = (RHS)->i64_u;
    uint64_t lhs = (LHS)->i64_u;
    (OUT)->i64_u = (lhs << rhs) | (lhs >> (64 - rhs));
    NEXT();
}

#undef LHS
#undef RHS
#undef OUT
#undef BLOCK
