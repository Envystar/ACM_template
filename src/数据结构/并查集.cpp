#include <bits/stdc++.h>

//并查集(disjoint set union)
//https://www.luogu.com.cn/problem/P3367
struct DSU {
    DSU() = default;
    DSU(int n) : p(n), sz(n, 1) { 
        std::iota(p.begin(), p.end(), 0);
    }
    int find(int x) { 
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int merge(int x, int y) {
        if (same(x, y)) return 0;
        x = find(x), y = find(y);
        if (sz[x] < sz[y]) std::swap(x, y);
        sz[x] += sz[y];
        p[y] = x;
        return x;
    }
    int& size(int x) {
        return sz[find(x)];
    }
    std::vector<int> p, sz;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    DSU dsu(n);
    for(int i = 0; i < m; ++i) {
        int z, x, y;
        std::cin >> z >> x >> y;
        if(z == 1) {
            dsu.merge(x, y);
        } else if(z == 2) {
            std::cout << (dsu.same(x, y) ? 'Y' : 'N') << '\n';
        }
    }
    return 0;
} 