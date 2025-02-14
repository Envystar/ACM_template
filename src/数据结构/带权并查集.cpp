#include <bits/stdc++.h>
using i64 = long long;

struct DSUT {
    DSUT(int n) : fa(n + 1), f(n + 1), sz(n + 1, 1) { 
        std::iota(fa.begin(), fa.end(), 0);
    }
    int find(int id) {
        if(id == fa[id]) return id;
        int root = find(fa[id]);
        f[id] += f[fa[id]];
        return fa[id] = root;
    }
    void merge(int x, int y) { //要依据题意修改
        int fx = find(x), fy = find(y);
        fa[fx] = fy;
        f[fx] += sz[fy];
        sz[fy] += sz[fx];
    }
    bool query(int x, int y) {
        return find(x) == find(y);
    }
    void set(int pos, int val) {
        f[pos] = val;
    }
    int get(int pos) {
        return f[pos];
    }
    std::vector<int> fa, f, sz;//父节点，到父节点的权值，集合大小
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    DSUT dsut(n);
    for(int i = 1; i <= n; ++i) {
        char opt;
        int x, y;
        std::cin >> opt >> x >> y;
        if(opt == 'M') {
            dsut.merge(x, y);
        } else if(opt == 'C') {
            if(!dsut.query(x, y)) {
                std::cout << -1 << '\n';
            } else {
                std::cout << std::abs(dsut.get(x) - dsut.get(y)) - 1 << '\n';
            }
        }
    }
    return 0;
}