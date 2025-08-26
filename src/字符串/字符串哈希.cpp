#include <bits/stdc++.h>
using i64 = long long;

struct H64 {
    H64() = default;
    H64(i64 v) : v(v) {}
    H64 operator+(const H64 &o) const {
        return (v + o.v >= MOD ? v + o.v - MOD : v + o.v);
    }
    H64 operator-(const H64 &o) const {
        return (o.v > v ? v + MOD - o.v : v - o.v);
    }
    H64 operator*(const H64 &o) const {
        __int128 r = (__int128)v * o.v;
        return H64((r >> 61) + (r & MOD));
    }
    auto operator<=>(const H64& o) const = default;
    i64 v = 0;
    constexpr static i64 MOD = (1LL << 61) - 1;
};

struct Hash {
    Hash() = default;
    Hash(const Hash &hs) : h(hs.h), n(1) {}
    Hash(const int &val) : h(H64(val)), n(1) {}
    Hash(const std::string &s) : n(s.size()) {
        for(int i = 0; i < (int)s.size(); ++i) {
            h = h + H64(s[i]) * fac(s.size() - i - 1);;
        }
    }
    Hash(const H64 &h, const int &n) : h(h), n(n) {}
    auto operator<=>(const Hash& o) const = default;
    Hash operator+(const Hash &o) {
        return {h * fac(o.n) + o.h, n + o.n};
    }
    Hash operator-(const Hash &o) {
        return {h - o.h * fac(n - o.n), n - o.n};
    }
    Hash operator+=(const Hash &o) {
        return *this = (*this + o);
    }
    Hash operator-=(const Hash &o) {
        return *this = (*this - o);
    }
    static H64 fac(int x) {
        if(x >= f.size()) {
            int l = f.size();
            f.resize(x + 1);
            for(int i = l; i < f.size(); ++i) {
                f[i] = f[i - 1] * BASE;
            }
        }
        return f[x];
    }
    int n{};
    H64 h{};
    constexpr static i64 BASE = 114514;
    inline static std::vector<H64> f{H64(1)};
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::set<Hash> st;
    for(int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        st.insert(Hash(s));
    }
    std::cout << st.size() << '\n';
    return 0;
}