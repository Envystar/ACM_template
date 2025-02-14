#include <bits/stdc++.h>
using i64 = long long;
constexpr i64 P = 998244353;

template<typename T>
class Fenwick {
public:
    Fenwick(int n) : v(std::vector<T>(n + 1)) {};
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
private:
    std::vector<T> v;
};

//康托展开(求排列的排名)
//https://www.luogu.com.cn/problem/P5367
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    Fenwick<int> tr(n);
    std::vector<int> p(n + 1);
    std::vector<i64> fac(n + 1, 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> p[i];
        tr.update(p[i], 1);
        fac[i] = fac[i - 1] * i % P;
    }
    i64 ans = 1;
    for(int i = 1; i <= n; ++i) {
        ans = (ans + fac[n - i] * tr.query(p[i] - 1)) % P;
        tr.update(p[i], -1);
    }
    std::cout << ans << '\n';
    return 0;
}