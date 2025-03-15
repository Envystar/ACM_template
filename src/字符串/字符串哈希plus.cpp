#include <bits/stdc++.h>
using i64 = long long;
using i128 = __int128;

struct StringHash {
    struct Hash {
        i64 hash;
        int n;
        Hash() = default;
        Hash(const i64 &hash, const int &n) : hash(hash), n(n) {}
        Hash operator+(const Hash &rhs) {
            return Hash(StringHash::add(rhs.hash, StringHash::mul(hash, StringHash::p[rhs.n])), n + rhs.n);
        }
        friend constexpr std::strong_ordering operator<=>(const Hash &lhs, const Hash &rhs) {
            return lhs.hash == rhs.hash ? lhs.n <=> rhs.n : lhs.hash <=> rhs.hash;
        }
    };
    constexpr static i64 base = 114514;
    constexpr static i64 mod = (1ll << 61) - 1;
    inline static std::vector<i64> p{1};
    inline static int n = 0;
    std::vector<i64> h;
    StringHash() = default;
    StringHash(const std::string &s) {
        int n = s.size();
        h.resize(n + 1);
        init(2 * n);
        for (int i = 1; i <= n; i++) {
            h[i] = add(s[i - 1], mul(h[i - 1], base));
        }
    }
    Hash getHash(const int &l, const int &r) {
        return Hash(sub(h[r + 1], mul(h[l], p[r - l + 1])), r - l + 1);
    }
private:
    void init(const int &m) {
        if (n > m) return;
        p.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            p[i] = mul(p[i - 1], base);
        }
        n = m;
    }
    inline static i64 mul(const i64 &a, const i64 &b) {
        i128 c = (i128)a * b;
        return add(c >> 61, c & mod);
    }
    inline static i64 add(const i64 &a, const i64 &b) {
        return (a + b >= mod ? a + b - mod : a + b);
    }
    inline static i64 sub(const i64 &a, const i64 &b) {
        return (a - b < 0 ? a - b + mod : a - b);
    }
};

int main() {
    
    return 0;
}