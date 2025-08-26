#include <bits/stdc++.h>
using i64 = long long;

std::array<i64, 3> exgcd(i64 a, i64 b) {
    if(b == 0) {
        return {a, 1, 0};
    }
    auto [gd, x, y] = exgcd(b, a % b);
    return {gd, y, x - a / b * y};
}

i64 EXCRT(std::vector<std::pair<i64, i64>> &v) {
    i64 M = v[0].first, ans = v[0].second;
    for(int i = 1; i < v.size(); ++i) {
        auto [m, r] = v[i];
        auto [gd, x, y] = exgcd(M, m);
        i64 dx = ((ans - r) % m + m) % m; 
        if(dx % gd != 0) return -1;
        i64 k = m / gd;
        x = __int128(dx / gd) % k * x % k;
        ans -= x * M;
        M *= k;
        ans = (ans % M + M) % M;
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::pair<i64, i64>> v(n);
    for(auto &[m, r] : v) {
        std::cin >> m >> r;
    }
    std::cout << EXCRT(v) << '\n';
    return 0;
}