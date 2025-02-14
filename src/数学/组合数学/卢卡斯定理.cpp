#include <bits/stdc++.h>
using i64 = long long;

i64 qpow(i64 a, i64 b, i64 p) {
    i64 res = 1;
    while(b) {
        if(b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n, m, p;
    std::cin >> n >> m >> p;
    std::vector<i64> fac(p + 1, 1);
    for(int i = 2; i <= p; ++i) {
        fac[i] = fac[i - 1] * i % p;
    }
    auto comb = [&fac, &p](i64 n, i64 m) ->i64 {
        return fac[n] * qpow(fac[m], p - 2, p) % p * qpow(fac[n - m], p - 2, p) % p;
    };
    auto lucas = [&fac, &p, &comb](auto self, i64 n, i64 m) ->i64 {
        if(m == 0) return 1;
        return self(self, n / p, m / p) * comb(n % p, m % p) % p;
    };
    std::cout << lucas(lucas, n + m, m) << '\n';
}

//lucas定理，求大数组合数
//https://www.luogu.com.cn/problem/P3807
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    std::cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}