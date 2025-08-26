#include <bits/stdc++.h>
using i64 = long long;

template<typename T>
struct Matrix {
    Matrix() : n(0), m(0) {};
    Matrix(int _n, int _m) : n(_n), m(_m), mt(n, std::vector<T>(m)){}
    Matrix(const std::vector<std::vector<T>> &v) : Matrix(v.size(), v[0].size()) {
        for(int i = 0; i < n; ++i) {
            assert(v[i].size() == m);
            for(int j = 0; j < m; ++j) {
                mt[i][j] = v[i][j]; 
            }
        }
    }
    Matrix<T> operator*(const Matrix<T> &o) {
        assert(m == o.n);
        Matrix<T> res(n, o.m);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < o.m; ++j) {
                for(int k = 0; k < m; ++k) {
                    res.mt[i][j] = res.mt[i][j] + mt[i][k] * o.mt[k][j];
                }
            }
        }
        return res;
    }
    Matrix<T> operator*=(const Matrix<T> &o) {
        return *this = *this * o; 
    }
    Matrix<T> operator+(const Matrix<T> &o) {
        assert(n == o.n && m == o.m);
        Matrix<T> res(n, m);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                res.mt[i][j] = mt[i][j] + o.mt[i][j];
            }
        }
        return res;
    }
    Matrix<T> operator-(const Matrix<T> &o) {
        assert(n == o.n && m == o.m);
        Matrix<T> res(n, m);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                res.mt[i][j] = mt[i][j] - o.mt[i][j];
            }
        }
        return res;
    }
    static Matrix<T> eye(int n) {
        Matrix<T> res(n, n);
        for(int i = 0; i < n; ++i) {
            res.mt[i][i] = 1;
        }
        return res;
    }
    static Matrix<T> qpow(Matrix<T> a, i64 b) {
        Matrix<T> res(Matrix::eye(a.n));
        while(b != 0) {
            if(b & 1) {
                res = res * a;
            }
            a = a * a;
            b >>= 1;
        }
        return res;
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& o) {
        for(int i = 0; i < o.n; ++i) {
            for(int j = 0; j < o.m; ++j) {
                os << o.mt[i][j] << " \n"[j + 1 == o.m];
            }
        }
        return os;
    }
    int n, m;
    std::vector<std::vector<T>> mt;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Matrix<int> res({{1, 2}, {2, 3}});
    Matrix<int> b(res);
    std::cout << Matrix<int>::qpow(res, 3);
    return 0;
}