#include <bits/stdc++.h>
using i64 = long long;
constexpr int MAXN = 20;
unsigned int s;
unsigned int get(unsigned int x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return s = x; 
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q >> s;
    std::vector<std::vector<int>> v(n + 1), up(n + 1), down(n + 1), fa(MAXN + 1, std::vector<int>(n + 1));
    std::vector<int> son(n + 1), len(n + 1), dep(n + 1), top(n + 1), lg(n + 1); //dep从0开始
    int root = 0;
    for(int i = 1; i <= n; ++i) {
        if(i >= 2) {
            lg[i] = lg[i >> 1] + 1;
        }
        std::cin >> fa[0][i]; //i号节点的直接祖先
        if(fa[0][i] == 0) {
            root = i;
        } else {
            v[fa[0][i]].push_back(i);
        }
    }
    auto dfs1 = [&](auto self, int id) -> void {
        for(int i = 0; i < MAXN; ++i) {
            fa[i + 1][id] = fa[i][fa[i][id]];
        }
        len[id] = 1;
        dep[id] = dep[fa[0][id]] + 1;
        for(auto nxt : v[id]) {
            if(nxt == fa[0][id]) continue;
            self(self, nxt);
            if(len[nxt] + 1 > len[id]) {
                len[id] = len[nxt] + 1;
                son[id] = nxt;
            }
        }
    };
    auto dfs2 = [&](auto self, int id, int t) -> void {
        top[id] = t;
        if(son[id] == 0) return;
        self(self, son[id], t);
        for(auto nxt : v[id]) {
            if(nxt == fa[0][id] || nxt == son[id]) continue;
            self(self, nxt, nxt);
        }
    };
    dfs1(dfs1, root);
    dfs2(dfs2, root, root);
    for(int i = 2; i <= n; ++i) {
        lg[i] = lg[i >> 1] + 1;
    }
    for(int i = 1; i <= n; ++i) {
        if(top[i] != i) continue;
        for(int j = 1, now = i; j <= len[i] && now; ++j, now = fa[0][now]) {
            up[i].push_back(now);
        }
        for(int j = 1, now = i; j <= len[i] && now; ++j, now = son[now]) {
            down[i].push_back(now);
        }
    }
    auto find = [&](int id, int k) ->int {
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
    };
    i64 res = 0;
    std::vector<int> ans(q + 1);
    for(int i = 1; i <= q; ++i) {
        int x = ((get(s) ^ ans[i - 1]) % n) + 1, k = (get(s) ^ ans[i - 1]) % dep[x];
        ans[i] = find(x, k);
        res ^= (1LL * i * ans[i]);
    }
    std::cout << res << '\n';
    return 0;
}