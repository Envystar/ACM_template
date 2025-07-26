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
std::vector<T> multiply(const std::vector<T> &A, const std::vector<T> &B) {
    int n = std::bit_ceil(A.size() + B.size() - 1);
    std::vector<std::complex<double>> v(n);
    for(int i = 0; i < A.size(); ++i) {
        v[i].real(A[i]);
    }
    for(int i = 0; i < B.size(); ++i) {
        v[i].imag(B[i]);
    }
    v.resize(n);
    FFT(v);
    for(int i = 0; i < n; ++i) {
        v[i] *= v[i];
    }
    FFT(v, -1);
    std::vector<T> res(A.size() + B.size() - 1);
    for(int i = 0; i < res.size(); ++i) {
        res[i] = (T)round(v[i].imag() / 2 / n);
    }
    return res;
}

template<typename T>
std::vector<T> convolution(const std::vector<T> &A, std::vector<T> kernel) {
    std::reverse(kernel.begin(), kernel.end());
    auto res = multiply(A, kernel);
    return std::vector(res.begin() + kernel.size() - 1, res.begin() + A.size());
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
    auto c = multiply(a, b);
    for(int i = 0; i < c.size(); ++i) {
        std::cout << c[i] << " \n"[i + 1 == c.size()];
    }
    return 0;
}
