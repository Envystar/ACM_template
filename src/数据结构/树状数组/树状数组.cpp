#include<bits/stdc++.h>

//树状数组(Fenwick)
//https://www.luogu.com.cn/problem/P3374
template<typename T>
struct Fenwick {
    Fenwick(int n) : v(n + 1) {};
    void update(int x, T dx) {
        for(int i = x; i < v.size(); i += (i & -i)) {
            v[i] += dx;
        }
    }
    T query(int x) {
        T res{};
        for(int i = x; i > 0; i -= (i & -i)) {
            res += v[i];
        }
        return res;
    }
    T range(int l, int r) {
        return query(r) - query(l - 1);
    }
    std::vector<T> v;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    Fenwick<int> tr(n);
    for(int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        tr.update(i, x);
    }
    for(int i = 0; i < m; ++i) {
        int o, x, y;
        std::cin >> o >> x >> y;
        if(o == 1) {
            tr.update(x, y);
        } else if (o == 2) {
            std::cout << tr.range(x, y) << '\n';
        }
    }
    return 0;
};
