#include <bits/stdc++.h>
using i64 = long long;

struct STOG {
#define ls (id<<1)
#define rs (id<<1|1)
    STOG(int n) : n(n), in(n << 2), out(n << 2), v(n * 7) {
        int tot = n;
        auto build = [&](auto self, int id, int l, int r) ->void {
            if(l == r) {
                in[id] = out[id] = l;
                return;
            }
            int mid = (l + r) / 2;
            self(self, ls, l, mid);
            self(self, rs, mid + 1, r);
            in[id] = ++tot;
            out[id] = ++tot;
            update(in[id], in[ls], 0);
            update(in[id], in[rs], 0);
            update(out[ls], out[id], 0);
            update(out[rs], out[id], 0);
        };
        build(build, 1, 1, n);
    }
    void update(int x, int y, int w) { //连一条从x 到 y的边，边权为w
        v[x].emplace_back(y, w);
    }
    //model == 0 时, 从pos 到 [x, y]连边，边权为w
    //model == 1 时, 从[x, y] 到 pos连边，边权为w
    void rangeUpdate(int pos, int x, int y,int w, int model) {
        rangeUpdate(1, 1, n, pos, x, y, w, model);
    }
    void rangeUpdate(int id, int l, int r, int pos, int x, int y, int w, auto model) {
        if(x <= l && r <= y) {
            if(model == 0) {
                update(pos, in[id], w);
            } else {
                update(out[id], pos, w);
            }
            return;
        }
        int mid = (l + r) / 2;
        if(x <= mid) {
            rangeUpdate(ls, l, mid, pos, x, y, w, model);
        }
        if(y > mid) {
            rangeUpdate(rs, mid + 1, r, pos, x, y, w, model);
        }
    }
#undef ls
#undef rs
    int n;
    std::vector<int> in, out;
    std::vector<std::vector<std::pair<int, int>>> v;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q, s;
    std::cin >> n >> q >> s;
    STOG tr(n);
    for(int i = 1; i <= q; ++i) {
        int opt;
        std::cin >> opt;
        if(opt == 1) {
            int pos, x, w;
            std::cin >> pos >> x >> w;
            tr.update(pos, x, w);
        } else if(opt == 2) {
            int pos, x, y, w;
            std::cin >> pos >> x >> y >> w;
            tr.rangeUpdate(pos, x, y, w, 0);
        } else if(opt == 3) {
            int pos, x, y, w;
            std::cin >> pos >> x >> y >> w;
            tr.rangeUpdate(pos, x, y, w, 1);
        }
    }
    auto &graph = tr.v;
    int m = tr.v.size() - 1;
    std::vector<i64> dp(m + 1, LLONG_MAX);
    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<>> pq;
    pq.emplace(0LL, s);
    while(!pq.empty()) {
        auto [w, id] = pq.top();
        pq.pop();
        if(w >= dp[id]) continue;
        dp[id] = w;
        for(const auto &[nxt, dx] : graph[id]) {
            i64 ww = w + dx;
            if(ww < dp[nxt]) {
                pq.emplace(ww, nxt);
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        std::cout << (dp[i] == LLONG_MAX ? -1 : dp[i]) << " \n"[i == n];
    }
    return 0;
}
