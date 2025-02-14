#include <bits/stdc++.h>
using i64 = long long;

template<typename T>
struct MaxFolw {
    struct Edge {
        Edge() = default;
        Edge(int _nxt, T _cap, int _enxt) : nxt(_nxt), cap(_cap), enxt(_enxt) {}
        int nxt, enxt;
        T cap;
    };
    MaxFolw(int n) : head(n, -1), pre(n), mf(n) {}
    void addEdge(int x, int y, T cap) {
        edge.push_back(Edge(y, cap, head[x]));
        head[x] = edge.size() - 1;
        edge.push_back(Edge(x, 0, head[y]));
        head[y] = edge.size() - 1;
    }
    bool bfs(int s, int t) {
        std::fill(mf.begin(), mf.end(), 0);
        mf[s] = INF;
        std::queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int id = q.front();
            q.pop();
            for(int eid = head[id]; ~eid; eid = edge[eid].enxt) {
                auto &[nxt, _, cap] = edge[eid];
                if(mf[nxt] == 0 && cap > 0) {
                    mf[nxt] = std::min(mf[id], cap);
                    pre[nxt] = eid;
                    if(nxt == t) return true;
                    q.push(nxt);
                }
            }
        }
        return false;
    };
    T flow(int s, int t) {
        T flow = 0;
        while(bfs(s, t)) { //找到增广路
            for(int id = t; id != s; id = edge[pre[id] ^ 1].nxt) {
                edge[pre[id]].cap -= mf[t];
                edge[pre[id] ^ 1].cap += mf[t];
            }
            flow += mf[t]; 
        }
        return flow;
    }
    std::vector<Edge> edge;
    std::vector<int> head, pre; // pre: id的前驱边
    std::vector<T> mf; //每S~v的流量上限, 
    const T INF = INT_MAX;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, S, T;
    std::cin >> n >> m >> S >> T;
    MaxFolw<i64> mf(n + 1);
    for(int i = 0; i < m; ++i) {
        int x, y, cap;
        std::cin >> x >> y >> cap;
        mf.addEdge(x, y, cap);
    }
    std::cout << mf.flow(S, T) << '\n';
    return 0;
}