#include <bits/stdc++.h>
using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> v(n + 1);
    for(int i = 1; i <= n - 1; ++i) {
        int x, y;
        std::cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    std::vector<int> sz(n + 1), weight(n + 1);
    int ans = n;
    auto dfs = [&](auto self, int id, int lst) ->void {
        sz[id] = 1;
        for(auto nxt : v[id]) {
            if(nxt == lst) continue;    
            self(self, nxt, id);
            weight[id] = std::max(weight[id], sz[nxt]);
            sz[id] += sz[nxt];
        }
        weight[id] = std::max(weight[id], n - sz[id]);
        ans = std::min(ans, weight[id]);
    };
    dfs(dfs, 1, 0);
    for(int i = 1; i <= n; ++i) {
        if(weight[i] == ans) {
            std::cout << i << ' ';
            break;
        }
    }
    std::cout << ans << '\n';
}
//树的重心（重心最多有两个）
//http://bailian.openjudge.cn/practice/1655/
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    std::cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}