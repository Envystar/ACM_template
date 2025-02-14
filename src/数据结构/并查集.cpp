#include <bits/stdc++.h>

//并查集(disjoint set union)
//https://www.luogu.com.cn/problem/P3367
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
            std::cout << (dsu.query(x, y) ? 'Y' : 'N') << '\n';
        }
    }
    return 0;
} 