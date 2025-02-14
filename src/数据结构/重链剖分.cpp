#include <bits/stdc++.h>

//树链剖分求LCA
//https://www.luogu.com.cn/problem/P3379
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(nullptr);
    int n, m, s;
    std::cin >> n >> m >> s;
    std::vector<std::vector<int>> v(n + 1);
    std::vector<int> fa(n + 1), dep(n + 1), son(n + 1), sz(n + 1), top(n + 1, 0);
    //父节点，深度，重儿子，子树节点数，所在重链的顶点
    for(int i = 0; i < n - 1; ++i) { 
        int x, y;
        std::cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);   
    }
    auto dfs1 = [&](auto self, int id, int lst) ->void {//求fa, dep, son, sz数组
        fa[id] = lst;
        dep[id] = dep[lst] + 1;
        sz[id] = 1;
        for(auto nxt : v[id]) {
            if(nxt == lst) continue;
            self(self, nxt, id);
            sz[id] += sz[nxt];
            if(sz[son[id]] < sz[nxt]) {
                son[id] = nxt;
            }
        }
    };
    auto dfs2 = [&](auto self, int id, int t) ->void { 
        top[id] = t;
        if(son[id] == 0) return;
        self(self, son[id], t);
        for(auto nxt : v[id]) {
            if(nxt != fa[id] && nxt != son[id]) {
                self(self, nxt, nxt);
            }
        }
    };
    auto lca = [&](int x, int y) ->int { 
        while(top[x] != top[y]) { 
            if(dep[top[x]] < dep[top[y]]) {
                std::swap(x, y);
            }
            x = fa[top[x]];
        }
        return (dep[x] < dep[y] ? x : y);
    };
    dfs1(dfs1, s, 0);
    dfs2(dfs2, s, s);
    for(int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        std::cout << lca(x, y) << '\n';
    }
    return 0;
}