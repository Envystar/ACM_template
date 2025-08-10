constexpr i64 P = 998244353;
constexpr i64 MAXN = 3000;

struct Comb {
    Comb(int n) : _fac(n + 1, 1), _inv(n + 1, 1), _finv(n + 1, 1) {
        for(int i = 2; i <= n; ++i) {
            _fac[i] = _fac[i - 1] * i % P;
            _inv[i] = (P - P / i) * _inv[P % i] % P;
            _finv[i] = _inv[i] * _finv[i - 1] % P;
        }
    }
    i64 fac(int x) { return _fac[x]; }
    i64 finv(int x) { return _finv[x]; }
    i64 inv(int x) { return _inv[x]; }
    i64 C(int n, int m) {
        if(n < m || n < 0 || m < 0) return 0;
        return _fac[n] * _finv[m] % P * _finv[n - m] % P;
    }
    i64 A(int n, int m) {
        if(n < m || n < 0 || m < 0) return 0;
        return _fac[n] * _finv[n - m] % P;
    }
    std::vector<i64> _fac, _inv, _finv; //阶乘，i的逆元，阶乘的逆元
} comb(MAXN);
