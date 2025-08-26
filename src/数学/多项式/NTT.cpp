#include <bits/stdc++.h>
using i64 = long long;

constexpr i64 P = 998244353;
constexpr i64 G = 3;
constexpr i64 INVG = 332748118;

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

void NTT(std::vector<i64> &A, int opt = 1) {
    int n = A.size();
    std::vector<int> p(n);
    for(int i = 0; i < n; ++i) {
        p[i] = p[i / 2] / 2 + (n / 2) * (i & 1);
    }
    for(int i = 0; i < n; ++i) {
        if(i < p[i]) {
            std::swap(A[i], A[p[i]]);
        }
    }
    for(int len = 2; len <= n; len <<= 1) {
        i64 g1 = qpow(opt == 1 ? G : INVG, (P - 1) / len);
        for(int i = 0; i < n; i += len) {
            i64 gk = 1;
            for(int j = 0; j < len / 2; ++j) {
                i64 x = A[i + j];
                i64 y = A[i + j + len / 2] * gk % P;
                A[i + j] = (x + y) % P;
                A[i + j + len / 2] = (x - y + P) % P;
                gk = (gk * g1) % P;
            }
        }
    }
}

std::vector<i64> multiply(std::vector<i64> A, std::vector<i64> B) {
    auto k = A.size() + B.size() - 1;
    int n = std::bit_ceil(k);
    A.resize(n), B.resize(n);
    NTT(A), NTT(B);
    for (int i = 0; i < n; ++i) {
        A[i] = A[i] * B[i] % P;
    }
    NTT(A, -1);
    i64 invn = qpow(n, P - 2);
    A.resize(k);
    for (auto &x : A) {
        x = x * invn % P;
    }
    return A;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<i64> a(n + 1), b(m + 1);
    for(int i = 0; i <= n; ++i) {
        std::cin >> a[i];
    }
    for(int i = 0; i <= m; ++i) {
        std::cin >> b[i];
    }
    auto c = multiply(a, b);
    for(int i = 0; i < c.size(); ++i) {
        std::cout << c[i] << " \n"[i + 1 == c.size()];
    }
    return 0;
}