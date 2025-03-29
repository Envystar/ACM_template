#include <bits/stdc++.h>
using i64 = long long;

struct LDL {
    LDL(const int &_n) : n(_n) {
        son = len = dep = top = in = out = lg = std::vector<int>(n + 1);
        v = up = down = std::vector<std::vector<int>>(n + 1);
        m = std::bit_width(std::bit_ceil((unsigned)n));
        fa = std::vector(m + 1, std::vector<int>(n + 1));
        for(int i = 2; i <= n; ++i) {
            lg[i] = lg[i >> 1] + 1;
        }
    }

    void addEdge(const int &x, const int &y) {
        v[x].push_back(y);
        v[y].push_back(x);
    }

    void dfs1(int id, int &t) {
        for(int i = 0; i < m; ++i) {
            fa[i + 1][id] = fa[i][fa[i][id]];
        }
        in[id] = t;
        len[id] = 1;
        for(const auto &nxt : v[id]) {
            if(nxt == fa[0][id]) continue;
            fa[0][nxt] = id; 
            dep[nxt] = dep[id] + 1;
            dfs1(nxt, ++t);
            if(len[nxt] + 1 > len[id]) {
                len[id] = len[nxt] + 1;
                son[id] = nxt;
            }
        }
        out[id] = t;
    }

    void dfs2(int id, int t) {
        top[id] = t;
        if(son[id] == 0) return;
        dfs2(son[id], t);
        for(const auto &nxt : v[id]) {
            if(nxt == fa[0][id] || nxt == son[id]) continue;
            dfs2(nxt, nxt);
        }
    }

    void work(int root = 1) {
        int dfsn = 1;
        dfs1(root, dfsn);
        dfs2(root, root);
        for(int i = 1; i <= n; ++i) {
            if(top[i] != i) continue;
            for(int j = 1, now = i; j <= len[i] && now; ++j, now = fa[0][now]) {
                up[i].push_back(now);
            }
            for(int j = 1, now = i; j <= len[i] && now; ++j, now = son[now]) {
                down[i].push_back(now);
            }
        }
    }
    
    bool isAncestor(int x, int y) { //x是y的祖先
        return in[x] <= in[y] && out[x] >= out[y];
    }

    int lca(int x, int y) {
        while(top[x] != top[y]) { 
            if(dep[top[x]] < dep[top[y]]) {
                std::swap(x, y);
            }
            x = fa[0][top[x]];
        }
        return (dep[x] < dep[y] ? x : y);
    }

    int dis(int x, int y) {
        int a = lca(x, y);
        return dep[x] - dep[a] + dep[y] - dep[a];
    }

    int kth(int id, int k) {
        if(k == 0) return id;
        int t = lg[k];
        k -= (1 << t);
        id = fa[t][id];
        int p = top[id];
        if(dep[id] - dep[p] >= k) {
            id = down[p][(dep[id] - dep[p]) - k];
        } else {
            id = up[p][k - (dep[id] - dep[p])];
        }
        return id;
    }

    std::vector<std::vector<int>> v, up, down, fa;
    std::vector<int> son, len, dep, top, in, out, lg;
    int n, m;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, s;
    std::cin >> n >> m >> s;
    LDL tree(n);
    for(int i = 1; i <= n - 1; ++i) {
        int x, y;
        std::cin >> x >> y;
        tree.addEdge(x, y);
    }
    tree.work(s);
    for(int i = 1; i <= m; ++i) {
        int x, y;
        std::cin >> x >> y;
        std::cout << tree.lca(x, y) << '\n';
    }
    return 0;
}