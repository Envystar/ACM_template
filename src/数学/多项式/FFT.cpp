#include <bits/stdc++.h>
using i64 = long long;

constexpr double PI = std::numbers::pi_v<double>;

void FFT(std::vector<std::complex<double>> &A, int opt = 1) {
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
        std::complex<double> w1 = {cos(2 * PI / len), sin(2 * PI / len) * opt};
        for(int i = 0; i < n; i += len) {
            std::complex<double> wk = {1, 0};
            for(int j = 0; j < len / 2; ++j) {
                std::complex<double> x = A[i + j];
                std::complex<double> y = A[i + j + len / 2] * wk;
                A[i + j] = x + y;
                A[i + j + len / 2] = x - y;
                wk *= w1;
            }
        }
    }
}

template<typename T>
std::vector<T> convolution(const std::vector<T> &A, const std::vector<T> &B) {
    int n = 1 << (int)ceil(log2(A.size() + B.size() - 1));
    assert(n != (A.size() + B.size() - 1) * 2);
    std::vector<std::complex<double>> va(A.begin(), A.end());
    std::vector<std::complex<double>> vb(B.begin(), B.end());
    va.resize(n), vb.resize(n);
    FFT(va), FFT(vb);
    for(int i = 0; i < n; ++i) {
        va[i] *= vb[i];
    }
    FFT(va, -1);
    std::vector<T> res(A.size() + B.size() - 1);
    for(int i = 0; i < res.size(); ++i) {
        res[i] = (T)(va[i].real() / n + 0.5);
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1), b(m + 1);
    for(int i = 0; i <= n; ++i) {
        std::cin >> a[i];
    }
    for(int i = 0; i <= m; ++i) {
        std::cin >> b[i];
    }
    auto c = convolution(a, b);
    for(int i = 0; i < c.size(); ++i) {
        std::cout << c[i] << " \n"[i + 1 == c.size()];
    }
    return 0;
}
