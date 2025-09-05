#include <bits/stdc++.h>
using i64 = long long;

template<typename T>
struct Matrix {
    Matrix() : Matrix(0, 0) {};
    Matrix(int _n, int _m, T val = T{}) : n(_n), m(_m), mt(n * m, val){}
    Matrix(const std::initializer_list<std::initializer_list<T>> &v) : Matrix(v.size(), v.begin()->size()) {
        int i = 0;
        for(auto &row : v) {
            assert(row.size() == m);
            for(auto &x : row) {
                mt[i++] = x;
            }
        }
    }
    std::span<T> operator[](int idx) {
        return std::span<T>(mt.data() + idx * m, m);
    }
    std::span<const T> operator[](int idx) const {
        return std::span<const T>(mt.data() + idx * m, m);
    }
    friend Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B) {
        assert(A.m == B.n);
        Matrix<T> MT(A.n, B.m);
        for(int i = 0; i < MT.n; ++i) {
            for(int j = 0; j < MT.m; ++j) {
                for(int k = 0; k < A.m; ++k) {
                    MT[i][j] = MT[i][j] + A[i][k] * B[k][j];
                }
            }
        }
        return MT;
    }
    friend Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B) {
        assert(A.n == B.n && A.m == B.m);
        Matrix<T> MT(A.n, B.m);
        for(int i = 0; i < MT.n; ++i) {
            for(int j = 0; j < MT.m; ++j) {
                MT[i][j] = A[i][j] + B[i][j];
            }
        }
        return MT;
    }
    friend Matrix<T> operator-(const Matrix<T>& A, const Matrix<T>& B) {
        assert(A.n == B.n && A.m == B.m);
        Matrix<T> MT(A.n, B.m);
        for(int i = 0; i < MT.n; ++i) {
            for(int j = 0; j < MT.m; ++j) {
                MT[i][j] = A[i][j] - B[i][j];
            }
        }
        return MT;
    }
    static Matrix<T> eye(int n) {
        Matrix<T> MT(n, n);
        for(int i = 0; i < n; ++i) {
            MT[i][i] = 1;
        }
        return MT;
    }
    static Matrix<T> qpow(Matrix<T> a, i64 b) {
        Matrix<T> res(Matrix<T>::eye(a.n));
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
                os << o[i][j] << " \n"[j + 1 == o.m];
            }
        }
        return os;
    }
    int n, m;
    std::vector<T> mt;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    return 0;
}