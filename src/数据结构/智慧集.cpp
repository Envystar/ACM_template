#include <bits/stdc++.h>
using i64 = long long;

template<typename T>
struct SmartSet {
    std::multiset<T> small, large;
    T smallSum, largeSum;
    SmartSet() : small(), large(), smallSum(), largeSum() {}
    void insert(T val) {
        if(small.empty() || val > *small.rbegin()) {
            large.insert(val);
            largeSum += val;
        } else {
            small.insert(val);
            smallSum += val;
        }
    }
    void erase(T val) {
        if(small.contains(val)) {
            smallSum -= val;
            small.extract(val);
        } else if(large.contains(val)) {
            largeSum -= val;
            large.extract(val);
        }
    }
    void balance(int k) {
        k = std::max(0, std::min(k, size()));
        while(small.size() > k) {
            T val = *small.rbegin();
            smallSum -= val;
            largeSum += val;
            large.insert(val);
            small.extract(val);
        }
        while(small.size() < k) {
            T val = *large.begin();
            smallSum += val;
            largeSum -= val;
            small.insert(val);
            large.extract(val);
        }
    }
    int size() {
        return small.size() + large.size();
    }
    int smallSize(int k) {
        balance(k);
        return small.size();
    }
    int largeSize(int k) {
        balance(k);
        return large.size();
    }
    T kth(int k) {
        balance(k);
        return *small.rbegin();
    }
    T getSmallSum(int k) {
        balance(k);
        return smallSum;
    }
    T getLargeSum(int k) {
        balance(k);
        return largeSum;
    }
};

void solve() {
    i64 n, k;
    std::cin >> n >> k;
    std::vector<i64> v(n + 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> v[i];
        v[i] = v[i] - i + n;
    }
    SmartSet<i64> sst;
    int ans = 1;
    for(int i = 1, j = 1; j <= n; ++j)  {
        sst.insert(v[j]);
        while(true) {
            int len = (j - i + 1);
            int mid = (len + 1) / 2;
            i64 target = sst.kth(mid);
            i64 res = 1LL * target * (sst.smallSize(mid) - sst.largeSize(mid)) + sst.getLargeSum(mid) - sst.getSmallSum(mid) ;
            if(res > k) {
                sst.erase(v[i]);
                ++i;
            } else {
                ans = std::max(ans, j - i + 1);
                break;
            }

        }
    }
    std::cout << ans << '\n';
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    std::cin >> T;
    while(T--) {
        solve();
    }
}