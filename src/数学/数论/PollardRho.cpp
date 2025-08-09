#include <bits/stdc++.h>
using i64 = long long;

i64 qpow(i64 a, i64 b, i64 p) {
    i64 res = 1;
    while(b) {
        if(b & 1) {
            res = (__int128)res * a % p;
        }
        a = (__int128)a * a % p;
        b >>= 1; 
    }
    return res;
}

//Miller_rabin判断质数
bool Miller(i64 n) {
    if(n <= 1 || n % 2 == 0) return (n == 2);
    i64 u = n - 1, k = 0;
    while(u % 2 == 0) u /= 2, ++k;
    static std::vector<i64> base = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for(auto x : base) {
        i64 res = qpow(x, u, n);
        if(res == 0 || res == 1 || res == n - 1) continue;
        for(int i = 1; i <= k; ++i) {
            res = (__int128)res * res % n;
            if(res == n - 1) break;
            if(i == k) return false;
        }
    }
    return true;
}

//Pollard_rho找因子
i64 Pollard_rho(i64 n) {
    assert(n >= 2);
    if (!(n & 1)) return 2;
    auto f = [&](i64 x) {
        return (__int128)x * x % n + 5;
    };
    i64 x = 0, y = 0, prod = 1;
    for (int i = 30, z = 0; i % 64 || std::gcd(prod, n) == 1; ++i) {
        if (x == y) {
            x = ++z;
            y = f(x);
        }
        i64 q = (__int128)prod * (x + n - y) % n;
        if (q) prod = q;
        x = f(x), y = f(f(y));
    }
    return std::gcd(prod, n);
}

std::vector<i64> factorize(i64 x) {
    std::vector<i64> res;
    auto f = [&](auto f, i64 x) ->void {
        if (x == 1) return;
        if (Miller(x)) {
            res.push_back(x);
            return;
        }
        i64 y = Pollard_rho(x);
        f(f, y), f(f, x / y);
    };
    f(f, x);
    std::ranges::sort(res);
    return res;
}

void solve() {
    i64 x;
    std::cin >> x;
    auto res = factorize(x);
    std::cout << res.size() << " \n"[res.empty()];
    for(int i = 0; i < res.size(); ++i) {
        std::cout << res[i] << " \n"[i + 1 == res.size()];
    }
}

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

