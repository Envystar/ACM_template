#include <bits/stdc++.h>
using i64 = long long;

//tarjan求割边
//https://www.luogu.com.cn/problem/P1656
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> v(n + 1);
    for(int i = 1; i <= m; ++i) {
        int x, y;
        std::cin >> x >> y;
        v[x].push_back({y, i});//记录边id(从1开始)，防止重边
        v[y].push_back({x, i});
    }
    std::vector<int> dfn(n + 1), low(n + 1);
    std::vector<std::pair<int, int>> bridge;
    int cnt = 0;
    auto dfs = [&](auto self, int id, int lid) ->void {
        dfn[id] = low[id] = ++cnt;
        for(auto [nxt, eid] : v[id]) {
            if(!dfn[nxt]) {
                self(self, nxt, eid);
                low[id] = std::min(low[id], low[nxt]);
                if(low[nxt] == dfn[nxt]) { //是割边
                    bridge.push_back({id, nxt});
                }
            } else if(eid != lid) {
                low[id] = std::min(low[id], dfn[nxt]);
            }
        }
    };
    for(int i = 1; i <= n; ++i) {
        if(!dfn[i]) {
            dfs(dfs, i, 0);
        }
    }
    std::sort(bridge.begin(), bridge.end());
    for(auto [x, y] : bridge) {
        std::cout << x << ' ' << y << '\n';
    }
    return 0;
}