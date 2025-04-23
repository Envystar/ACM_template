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
    if(n == 4) return 2;
    static std::mt19937_64 rnd  (std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int64_t> rangeRand(1, n - 1);
    i64 c = rangeRand(rnd);
    auto f = [&](i64 x) {
        return ((__int128)x * x + c) % n;
    };
    i64 x = f(0), y = f(x);
    while(x != y) {
        i64 gd = std::gcd(std::abs(x - y), n);
        if(gd != 1) return gd;
        x = f(x), y = f(f(y));
    }
    return n;
}

void solve() {
    i64 x;
    std::cin >> x;
    i64 res = 0;
    auto max_factor = [&](auto self, i64 x) ->void {
        if(x <= res || x < 2) return;
        if(Miller(x)) {
            res = std::max(res, x);
            return;
        }
        i64 p = x;
        while(p == x) {
            p = Pollard_rho(x);
        }
        while(x % p == 0) {
            x /= p;
        }
        self(self, x), self(self, p);
    };
    max_factor(max_factor, x);
    if(res == x) {
        std::cout << "Prime\n";
    } else {
        std::cout << res << '\n';
    }
}

//Pollard_rho快速求大数因子
//https://www.luogu.com.cn/problem/P4718
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

