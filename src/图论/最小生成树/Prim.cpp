#include <bits/stdc++.h>

//prim算法最小生成树(稠密图)
//https://www.luogu.com.cn/problem/P3366
struct node {
    int id, w;
    bool operator<(const node& o) const {
        return w > o.w;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> v(n + 1);
    std::vector<int> vis(n + 1);
    for(int i = 0; i < m; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        v[x].push_back({y, w});
        v[y].push_back({x, w});
    }
    std::priority_queue<node> pq; //利用优先队列不断加入最小边
    int ans = 0;
    pq.push({1, 0});
    while(!pq.empty()) {
        auto [id, w] = pq.top();
        pq.pop();
        if(!vis[id]) {
            vis[id] = 1;
            ans += w;   
            for(auto [nxt, w] : v[id]) {
                if(!vis[nxt]) {
                    pq.push({nxt, w});
                }
            }
        } 
    }
    if(!*std::min_element(vis.begin() + 1, vis.end())) {
        std::cout << "orz" << '\n'; //图不连通
    } else {
        std::cout << ans << '\n';
    }
    return 0;
}