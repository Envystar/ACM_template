#include <bits/stdc++.h>
using i64 = long long;

//tarjan求强连通分量(scc)
//https://www.luogu.com.cn/problem/B3609
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> v(n + 1);
    for(int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        v[x].push_back(y);
    }
    std::vector<std::vector<int>> scc(n + 1);
    std::vector<int> dfn(n + 1), low(n + 1), ins(n + 1), bel(n + 1);
    std::stack<int> stk;
    int cnt = 0, tot = 0;
    auto dfs = [&](auto self, int id) ->void {
        dfn[id] = low[id] = ++cnt;
        stk.push(id);
        ins[id] = 1;
        for(auto nxt : v[id]) {
            if(!dfn[nxt]) {
                self(self, nxt);
                low[id] = std::min(low[id], low[nxt]);
            } else if(ins[nxt]) {
                low[id] = std::min(low[id], low[nxt]);
            }
        }
        if(dfn[id] == low[id]) {
            ++tot;
            while(true) {
                int num = stk.top();
                stk.pop();
                ins[num] = 0;
                bel[num] = tot;
                scc[tot].push_back(num);
                if(id == num) break;
            }
        }
    };
    for(int i = 1; i <= n; ++i) {
        if(!dfn[i]) {
            dfs(dfs, i);
        }
    }
    for(int i = 1; i <= tot; ++i) {
        std::sort(scc[i].begin(), scc[i].end());
    }
    std::sort(scc.begin() + 1, scc.begin() + tot + 1);
    std::cout << tot << '\n';
    for(int i = 1; i <= tot; ++i) {
        for(int j = 0; j < scc[i].size(); ++j) {
            std::cout << scc[i][j] << " \n"[j == scc[i].size() - 1];
        }
    }
    return 0;
}