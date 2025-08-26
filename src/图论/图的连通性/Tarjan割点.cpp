#include <bits/stdc++.h>
using i64 = long long;

//tarjan求割点
//https://www.luogu.com.cn/problem/P3388
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
    std::vector<int> dfn(n + 1), low(n + 1), cutPoint(n + 1);
    int cnt = 0, root = 0;
    auto dfs = [&](auto self, int id, int lst) ->void {
        dfn[id] = low[id] = ++cnt;
        int sz = 0; //儿子个数
        for(auto nxt : v[id]) {
            if(!dfn[nxt]) {
                sz++;
                self(self, nxt, id);
                low[id] = std::min(low[id], low[nxt]);
                if(low[nxt] >= dfn[id]) {
                    cutPoint[id] = 1;
                }
            } else if(nxt != lst) {
                low[id] = std::min(low[id], dfn[nxt]);
            }
        }
        if(sz <= 1 && id == root) {
            cutPoint[id] = 0;
        }
    };
    for(int i = 1; i <= n; ++i) {
        if(!dfn[i]) {
            root = i;
            dfs(dfs, i, 0);
        }
    }
    std::cout << std::count(cutPoint.begin() + 1, cutPoint.end(), 1) << '\n';
    for(int i = 1; i <= n; ++i) {
        if(cutPoint[i] == 1) {
            std::cout << i << ' ';
        }
    }
    return 0;
}