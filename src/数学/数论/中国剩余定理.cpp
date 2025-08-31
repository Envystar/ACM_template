#include <bits/stdc++.h>
using i64 = long long;

std::array<i64, 3> exgcd(i64 a, i64 b) {
    if(b == 0) {
        return {a, 1, 0};
    }
    auto [gd, x, y] = exgcd(b, a % b);
    return {gd, y, x - a / b * y};
}

i64 CRT(std::vector<std::pair<i64, i64>> &v) {
    i64 M = 1;
    for(const auto &[m, r] : v) {
        M *= m;
    }
    i64 ans = 0;
    for(const auto &[m, r] : v) {
        i64 Mi = M / m;
        auto [gd, x, y] = exgcd(Mi, m);
        ans += (__int128)r * Mi % M * x % M;
    }
    return (ans % M + M) % M;
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
    std::cout << CRT(v) << '\n';
    return 0;
}