#include <bits/stdc++.h>
using i64 = long long;

template <typename T, typename Func = std::function<T(const T&, const T&)>>
struct ST {
    ST(const std::vector<T> &v, Func func = [](const T& a, const T& b) {  
        return std::max(a, b);  
    }) : func(std::move(func)) {
        int k = std::__lg(v.size());
        st = std::vector<std::vector<T>>(k + 1, std::vector<T>(v.size()));
        st[0] = v;
        for(int i = 0; i < k; ++i) {
            for(int j = 0; j + (1 << (i + 1)) - 1 < v.size(); ++j) {
                st[i + 1][j] = this->func(st[i][j], st[i][j + (1 << i)]);
            }
        }
    }
    T range(int l, int r) {
        int t = std::__lg(r - l + 1);
        return func(st[t][l], st[t][r + 1 - (1 << t)]);
    }
    std::vector<std::vector<T>> st;
    Func func;
};

//ST表(sparseTable)
//https://www.luogu.com.cn/problem/P3865
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> v(n + 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> v[i];
    }
    ST<int> st(v);
    while(q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << st.range(l, r) << '\n';
    }
    return 0;
}
