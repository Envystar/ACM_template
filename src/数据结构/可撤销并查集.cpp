#include <bits/stdc++.h>

struct RDSU {
    RDSU() = default;
    RDSU(int n) : p(n), sz(n, 1) {
        std::iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        while(p[x] != x) x = p[x];
        return x;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int merge(int x, int y) {
        if (same(x, y)) return 0;
        x = find(x), y = find(y);
        if (sz[x] < sz[y]) std::swap(x, y);
        hsz.push({sz[x], sz[x]});
        hfa.push({p[y], p[y]});
        sz[x] += sz[y];
        p[y] = x;
        return x;
    }
    int& size(int x) {
        return sz[find(x)];
    }
    size_t now() {
        return hsz.size();
    }
    void version(int ver) {
        rollback(now() - ver);
    }
    void rollback(int t = 1) {
        for(int i = 1; i <= t && !hfa.empty(); ++i) {
            hfa.top().first = hfa.top().second;
            hsz.top().first = hsz.top().second;
            hfa.pop(), hsz.pop();
        }
    }
    std::vector<int> p, sz;
    std::stack<std::pair<int&, int>> hsz, hfa;
};

//https://www.starrycoding.com/problem/9
int main() {
   std::ios::sync_with_stdio(false);
   std::cin.tie(nullptr);
   int n, q;
   std::cin >> n >> q;
   RDSU rdsu(n);
   for(int i = 1; i <= q; ++i) {
       int opt;
       std::cin >> opt;
       if(opt == 1) {
           int x, y;
           std::cin >> x >> y;
           rdsu.merge(x, y);
       } else if(opt == 2) {
           rdsu.rollback();
       } else if(opt == 3) {
           int x, y;
           std::cin >> x >> y;
           std::cout << (rdsu.same(x, y) ? "YES" : "NO") << '\n';
       }
   }
   return 0;
}