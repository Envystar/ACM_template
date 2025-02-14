#include <bits/stdc++.h>
using i64 = long long;

//tarjan求点双连通分量
//https://www.luogu.com.cn/problem/P8435
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
    std::vector<std::vector<int>> vcc(n + 1);
    std::vector<int> dfn(n + 1), low(n + 1);
    std::stack<int> stk;
    int cnt = 0, tot = 0;
    auto dfs = [&](auto self, int id, int lst) ->void {
        dfn[id] = low[id] = ++cnt;
        stk.push(id);
        int num = 0;
        for(auto nxt : v[id]) {
            if(!dfn[nxt]) {
                num++;
                self(self, nxt, id);
                low[id] = std::min(low[id], low[nxt]);
                if(low[nxt] >= dfn[id]) {
                    ++tot;
                    while(true) {
                        int num = stk.top();
                        stk.pop();
                        vcc[tot].push_back(num);
                        if(num == nxt) break;
                    }
                    vcc[tot].push_back(id);
                }
            } else if(nxt != lst) {
                low[id] = std::min(low[id], dfn[nxt]);
            }
        }
        if(lst == 0 && num == 0) {
            ++tot;
            vcc[tot].push_back(id);
        }
    };
    for(int i = 1; i <= n; ++i) {
        if(!dfn[i]) {
            dfs(dfs, i, 0);
        }
    }
    std::cout << tot << '\n';
    for(int i = 1; i <= tot; ++i) {
        std::cout << vcc[i].size() << ' ';
        for(int j = 0; j < vcc[i].size(); ++j) {
            std::cout << vcc[i][j] << " \n"[j == vcc[i].size() - 1];
        }
    }
    return 0;
}