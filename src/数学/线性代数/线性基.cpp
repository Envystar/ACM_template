#include <bits/stdc++.h>
using i64 = long long;

template<typename T, int N = std::numeric_limits<T>::digits>
struct Basis {
    bool insert(T x) {
        for(int i = N - 1; i >= 0; --i) {
            if(x >> i & 1) {
                if(!base[i]) {
                    base[i] = x;
                    _count++;
                    return true;
                }
                x ^= base[i];
            }
        }
        flag = true;
        return false;
    }
    T kth(T k) {
        k -= flag;
        T res{};
        int len = _count - 1;
        for (int i = N - 1; i >= 0; i--) {
            if(!base[i]) continue;
            if ((k >> len & 1) ^ (res >> i & 1)) {
                res ^= base[i];
            }
            len--;
        }
        return res;
    }
    T querymax() {
        T res{};
        for(int i = N - 1; i >= 0; --i) {
            res = std::max(res ^ base[i], res);
        }
        return res;
    }
    int count() {
        return _count;
    }
    T size() {
        return ((T)1 << count()) - (T)!flag;
    }
    bool flag = false;
    std::array<T, N> base{};
    int _count{};
};

void solve() {
    int n;
    std::cin >> n;
    Basis<i64> basis;
    for(int i = 0; i < n; ++i) {
        i64 x;
        std::cin >> x;
        basis.insert(x);
    }
    std::cout << basis.querymax() << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    // std::cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}