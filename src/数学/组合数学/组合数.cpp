constexpr i64 P = 998244353;
constexpr i64 MAXN = 3000;

struct Comb {
    Comb(int n) : _fac(n + 1, 1), _inv(n + 1, 1), _invfac(n + 1, 1) {
        for(int i = 2; i <= n; ++i) {
            _fac[i] = _fac[i - 1] * i % P;
            _inv[i] = (P - P / i) * _inv[P % i] % P;
            _invfac[i] = _inv[i] * _invfac[i - 1] % P;
        }
    }
    i64 fac(int x) { return _fac[x]; }
    i64 invfac(int x) { return _invfac[x]; }
    i64 inv(int x) { return _inv[x]; }
    i64 C(int n, int m) {
        if(n < m || n < 0 || m < 0) return 0;
        return _fac[n] * _invfac[m] % P * _invfac[n - m] % P;
    }
    i64 A(int n, int m) {
        if(n < m || n < 0 || m < 0) return 0;
        return _fac[n] * _invfac[n - m] % P;
    }
    std::vector<i64> _fac, _inv, _invfac; //阶乘，i的逆元，阶乘的逆元
} comb(MAXN);
