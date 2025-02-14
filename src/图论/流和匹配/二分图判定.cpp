#include <bits/stdc++.h>
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> v(n + 1);
    for(int i = 1; i <= m; ++i) {
        int x, y;
        std::cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    std::vector<int> col(n + 1), vis(n + 1); //染色值1/2，是否标记
    auto dfs = [&](auto self, int id, int val) ->bool { //判定是否是二分图
        col[id] = val;
        vis[id] = 1;
        for(auto nxt : v[id]) {
            if(!col[nxt]) {
                if(!self(self, nxt, val ^ 3)) {
                    return false;
                }
            } else if(col[nxt] == val) {
                return false;
            }
        }
        return true;
    };
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) {
            col = std::vector<int>(n + 1);
            if(!dfs(dfs, i, 1)) {
                std::cout << "Impossible\n";
                exit(0);
            }
            int A = std::count(col.begin(), col.end(), 1);
            int B = std::count(col.begin(), col.end(), 2);
            ans += std::min(A, B);
        }
    }
    std::cout << ans << '\n';
    return 0;
}