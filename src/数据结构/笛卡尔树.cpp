#include <bits/stdc++.h>
using i64 = long long;

template<typename T, typename _Compare = std::less<T>>
struct Cartesian {
    Cartesian() = default;
    Cartesian(const std::vector<T> &v, _Compare cmp = _Compare())
        : ls(v.size(), -1), rs(v.size(), -1), cmp(std::move(cmp)) {
        std::stack<int> stk;
        for(int i = 0; i < v.size(); ++i) {
            while(!stk.empty() && cmp(v[stk.top()], v[i])) {
                stk.pop();
            }
            if(stk.empty()) {
                ls[i] = root;
                root = i;
            } else {
                ls[i] = rs[stk.top()];
                rs[stk.top()] = i;
            }
            stk.push(i);
        }
    }
    _Compare cmp;
    int root = -1;
    std::vector<int> ls, rs;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    Cartesian<int, std::greater<>> tree(v);
    i64 lans = 0, rans = 0;
    for(int i = 0; i < n; ++i) {
        lans ^= 1LL * (i + 1) * (tree.ls[i] + 2);
    }
    for(int i = 0; i < n; ++i) {
        rans ^= 1LL * (i + 1) * (tree.rs[i] + 2);
    }
    std::cout << lans << ' ' << rans << '\n';
    return 0;
}