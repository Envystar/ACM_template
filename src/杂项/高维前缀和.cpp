#include <bits/stdc++.h>
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> v(1 << n);
    for(int i = 0; i < (1 << n); ++i) {
        std::cin >> v[i].first;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1 << n); ++j) {
            if(j >> i & 1) { //条件取反 !(j >> i & 1) 即为高维后缀和
                //f[j] = f[j] + f[j ^ (1 << i)]; 一般情况：求真子集和
                if(v[j ^ (1 << i)].first > v[j].first) {
                    v[j].second = v[j].first;
                    v[j].first = v[j ^ (1 << i)].first;
                } else if(v[j ^ (1 << i)].first > v[j].second) {
                    v[j].second = v[j ^ (1 << i)].first;
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1; i < (1 << n); ++i) {
        ans = std::max(ans, v[i].first + v[i].second);
        std::cout << ans << '\n';
    }
    return 0;
}