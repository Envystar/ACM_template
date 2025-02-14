#include <bits/stdc++.h>

//kruskal算法最小生成树(稀疏图)
//https://www.luogu.com.cn/problem/P3366
struct DSU {
    DSU(int n) { //初始构造
        v.resize(n + 1);
        std::iota(v.begin(), v.end(), 0);
    }
    int find(int x) { //找根
        return (v[x] == x ? x : (v[x] = find(v[x])));
    }
    void merge(int x, int y) { //合并集合
        v[find(x)] = find(y);
    }
    bool query(int x, int y) { //是否在同一集合
        return find(x) == find(y);
    }
    std::vector<int> v;
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
        if(!dsu.query(x, y)) {
            dsu.uniset(x, y);
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