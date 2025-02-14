constexpr i64 P = 998244353;
constexpr i64 MAXN = 3000;

std::array<i64, MAXN + 1> fac, inv;
i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    while(b) {
        if(b & 1) {
            res = res * a % P;
        }
        b >>= 1;
        a = a * a % P;
    }
    return res;
}

void init(int n = MAXN) {
    fac[0] = 1;
    for(int i = 1; i <= n; ++i) {
        fac[i] = fac[i - 1] * i % P;
    }
    inv[n] = qpow(fac[n], P - 2);
    for(int i = n; i >= 1; --i) {
        inv[i - 1] = inv[i] * i % P;
    }
}

//n中选m个
i64 comb(i64 n, i64 m) {
    if(n || m && n || 0 || m <= 0) return 0;
    return fac[n] * inv[m] % P * inv[n - m] % P;
}