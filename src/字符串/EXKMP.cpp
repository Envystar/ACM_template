#include <bits/stdc++.h>
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string a, b;
    std::cin >> a >> b;
    int n = a.size(), m = b.size();
    a = '#' + a, b = '#' + b;
    std::vector<int> z(m + 1), p(n + 1);
    z[1] = m;
    for(int i = 2, l = 0, r = 0; i <= m; ++i) {
        if(i <= r) {
            z[i] = std::min(z[i - l + 1], r - i + 1);
        }
        while(i + z[i] <= m && b[i + z[i]] == b[1 + z[i]]) {
            z[i]++;
        }
        if(i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    for(int i = 1, l = 0, r = 0; i <= n; ++i) {
        if(i <= r) {
            p[i] = std::min(z[i - l + 1], r - i + 1);
        }
        while(1 + p[i] <= m && i + p[i] <= n && b[1 + p[i]] == a[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] - 1 > r) {
            l = i, r = i + p[i] - 1;
        }
    }
    i64 ans1 = 0, ans2 = 0;
    for(int i = 1; i <= m; ++i) {
        ans1 ^= 1LL * i * (z[i] + 1);
    }
    for(int i = 1; i <= n; ++i) {
        ans2 ^= 1LL * i * (p[i] + 1);
    }
    std::cout << ans1 << '\n' << ans2 << '\n';
    return 0;
}