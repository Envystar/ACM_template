#include <bits/stdc++.h>
using i64 = long long;

constexpr int MAXN = 1E8;
struct Sieve {
    Sieve(int n) : n(n), mnp(n + 1) {
        for(int i = 2; i <= n; ++i) {
            if(mnp[i] == 0) {
                mnp[i] = i;
                prime.push_back(i);
            }
            for(int j = 0; i * prime[j] <= n; ++j) {
                mnp[i * prime[j]] = prime[j];
                if(mnp[i] == prime[j]) break;
            }
        }
    }
    bool isPrime(int x) { 
        return mnp[x] == x; 
    }
    int minp(int x) { 
        return mnp[x]; 
    }
    int phi(int x) {
        static auto _phi = build([&](auto &f, int i, int p, int j) {
            f[i] = f[j] * (p == mnp[j] ? p : p - 1);
        });
        return _phi[x];
    }
    int mu(int x) {
        static auto _mu = build([&](auto &f, int i, int p, int j) {
            f[i] = (p == mnp[j] ? 0 : -f[j]);
        });
        return _mu[x];
    }
    int d(int x) {
        static auto _d = build([&](auto &f, int i, int p, int j) {
            static std::vector<int> a(n + 1);
            a[i] = (p == mnp[j] ? a[j] + 1 : 1);
            f[i] = (p == mnp[j] ? f[j] / (a[j] + 1) * (a[i] + 1) : f[j] * 2);
        });
        return _d[x];
    }
    int sigma(int x) {
        static auto _sigma = build([&](auto &f, int i, int p, int j) {
            static std::vector<i64> s(n + 1);
            s[i] = (p == mnp[j] ? s[j] * p : p);
            f[i] = f[j] + s[i] * (p == mnp[j] ? f[j / s[j]] : f[j]);
        });
        return _sigma[x];
    }
    template<typename T = int, typename Func>
    std::vector<T> build(Func&& foo) {
        std::vector<T> f(n + 1);
        f[1] = 1;
        for(int i = 2; i <= n; ++i) {
            foo(f, i, mnp[i], i / mnp[i]);
        }
        return f;
    }
    int n;
    std::vector<int> mnp, prime;
} sieve(MAXN);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    return 0;
}