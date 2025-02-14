#include <bits/stdc++.h>
using i64 = long long;

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

//逆康托展开
//https://acm.hdu.edu.cn/showproblem.php?pid=1027
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    while(std::cin >> n >> m) {
        Fenwick<int> tr(n);
        std::vector<i64> fac(n + 1, 1);
        for(int i = 1; i <= n; ++i) {
            if(fac[i - 1] > m) {
                fac[i] = fac[i - 1];
            } else {
                fac[i] = fac[i - 1] * i;
            }
            tr.update(i, 1);
        }
        m--;
        for(int i = 1; i <= n; ++i) {
            int k = m / fac[n - i];
            int l = k + 1, r = n, res = 1;
            while(l <= r) {
                int mid = (l + r) / 2;
                if(tr.query(mid - 1) <= k) {
                    res = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            tr.update(res, -1);
            m = m % fac[n - i];
            std::cout << res << " \n"[i == n];
        }
    }
    return 0;
}