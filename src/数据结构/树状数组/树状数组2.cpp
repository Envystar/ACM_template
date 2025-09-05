#include <bits/stdc++.h>
using i64 = long long;

template<typename T>
struct Fenwick {
    Fenwick(int n) : vec(n + 1), add(n + 1) {}
    void rangeUpdate(int l, int r, T dx) {
        updatedx(l, dx);
        updatedx(r + 1, -dx);
    }
    void update(int pos, T dx) {
        rangeUpdate(pos, pos, dx);
    }
    T rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
    T query(int pos) {
        T res{};
        for(int i = pos; i >= 1; i -= (i & -i)) {
            res += pos * vec[i] - add[i];
        }
        return res;
    }
    void updatedx(int pos, T dx) {
        for(int i = pos; i < vec.size(); i += (i & -i)) {
            vec[i] += dx;
            add[i] += (pos - 1) * dx;
        }
    }
    std::vector<T> vec, add;
};

//树状数组，区间修改，区间查询
//https://www.luogu.com.cn/problem/P3372
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    Fenwick<i64> tr(n);
    for(int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        tr.rangeUpdate(i, i, x);
    }
    for(int i = 1; i <= m; ++i) {
        int opt;
        std::cin >> opt;
        if(opt == 1) {
            int l, r, dx;
            std::cin >> l >> r >> dx;
            tr.rangeUpdate(l, r, dx);
        } else if(opt == 2) {
            int l, r;
            std::cin >> l >> r;
            std::cout << tr.rangeQuery(l, r) << '\n';
        }
    }
    return 0;
}