#include <bits/stdc++.h>
using i64 = long long;

struct BipartiteGraph {
    BipartiteGraph(int n, int m)
    : n(n), m(m), g(n + 1), vis(m + 1), mch(m + 1) {};
    void add(int x, int y) {
        g[x].push_back(y);
    }
    bool dfs(int id) {
        for(auto nxt : g[id]) {
            if(!vis[nxt]) {
                vis[nxt] = 1;
                if(!mch[nxt] || dfs(mch[nxt])) {
                    mch[nxt] = id;
                    return true;
                }
            }
        }
        return false;
    }
    int solve() { //求最大匹配
        int res = 0;
        for(int i = 1; i <= n; ++i) {
            std::fill(vis.begin(), vis.end(), false);
            res += dfs(i);
        }
        return res;
    }
    int n, m;
    std::vector<std::vector<int>> g; //存图
    std::vector<bool> vis;  //标记是否搜索过
    std::vector<int> mch;   //mch[i]表示i号点匹配的编号
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, k;
    std::cin >> n >> m >> k;
    BipartiteGraph bg(n + 1, m + 1);
    for(int i = 1; i <= k; ++i) {
        int x, y;
        std::cin >> x >> y;
        bg.add(x, y);
    }
    std::cout << bg.solve() << '\n';
    return 0;
}