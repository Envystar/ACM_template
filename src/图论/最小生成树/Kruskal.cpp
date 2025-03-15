#include <bits/stdc++.h>

//kruskal算法最小生成树(稀疏图)
//https://www.luogu.com.cn/problem/P3366
struct DSU {
    DSU(int n) : p(n + 1), sz(n + 1, 1) { 
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

struct edge { //边
    int x, y, w; //点，点，边权
    bool operator<(const edge& o) const {
        return w < o.w;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<edge> v(m);
    DSU dsu(n);
    for(auto &[x, y, w] : v) {
        std::cin >> x >> y >> w;
    }
    std::sort(v.begin(), v.end()); //对边排序
    int ans = 0, tot = 0;
    for(auto [x, y, w] : v) {
        if(!dsu.same(x, y)) {
            dsu.merge(x, y);
            ans += w;
            tot++;
        }
    }
    if(tot != n - 1) {
        std::cout << "orz" << '\n';
    } else {
        std::cout << ans << '\n';
    }
    return 0;
}