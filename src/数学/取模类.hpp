constexpr i64 P = 998244353;
template<typename T>
T qpow(T a, i64 b) {
    T res = 1;
    while(b) {
        if(b & 1) {
            res = res * a;
        }
        b >>= 1;
        a = a * a;
    }
    return res;
}

struct M64 {
    M64() = default;
    M64(const i64 a) : x((a % P + P) % P) {}
    i64 val() const { return x; }
    M64 inv() const { return qpow(*this, P - 2); }
#define OP(op, EXPR) \
    friend M64& operator op##= (M64 &A, const M64 &B) { \
        return A = M64(EXPR); \
    } \
    friend M64 operator op (M64 A, const M64 &B) { \
        return A op##= B; \
    }
    OP(+, A.val() + B.val())
    OP(-, A.val() - B.val())
    OP(*, A.val() * B.val())
    OP(/, A.val() * B.inv().val())
    OP(&, A.val() & B.val())
    OP(|, A.val() | B.val())
    OP(^, A.val() ^ B.val())
#undef OP
    friend M64& operator++(M64 &a) {
        a += 1;
        return a;
    }
    friend M64 operator++(M64 &a, int) {
        M64 t = a;
        a += 1;
        return t;
    }
    friend std::ostream& operator<<(std::ostream &os, const M64 &m) {
        return os << m.x;
    }
    friend std::istream& operator>>(std::istream &is, M64 &m) {
        i64 tmp;
        is >> tmp;
        m = M64(tmp);
        return is;
    }
    i64 x{};
};