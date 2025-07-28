#include <bits/stdc++.h>
using i64 = long long;

template<typename Info>
struct SegmentTree {
#define ls (id<<1)
#define rs (id<<1|1)
    SegmentTree() = default;
    SegmentTree(int n) : n(n), info(n << 2) {}
    SegmentTree(const SegmentTree<Info> &o) : n(o.n), info(o.info) {}
    SegmentTree(const std::vector<Info> &init) : SegmentTree((int)init.size()) {
        auto build = [&](auto self, int id, int l, int r) ->void {
            if(l == r) {
                info[id] = init[l];
                return;
            }
            int mid = (l + r) / 2;
            self(self, ls, l, mid);
            self(self, rs, mid + 1, r);
            pushup(id);
        };
        build(build, 1, 0, n - 1);
    }
    void pushup(int id) {
        info[id] = info[ls] + info[rs];
    }
    void update(int pos, const Info &val) {
        update(1, 0, n - 1, pos, val);
    }
    Info query(int pos) {
        return rangeQuery(pos, pos);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
    void update(int id, int l, int r, int pos, const Info &val) {
        if(l == r) {
            info[id] = val;
            return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid) {
            update(ls, l, mid, pos, val);
        } else {
            update(rs, mid + 1, r, pos, val);
        }
        pushup(id);
    }
    Info rangeQuery(int id, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return info[id];
        }
        int mid = (l + r) / 2;
        Info res;
        if(x <= mid) {
            res = res + rangeQuery(ls, l, mid, x, y);
        }
        if(y > mid) {
            res = res + rangeQuery(rs, mid + 1, r, x, y);
        }
        return res;
    }
#undef ls
#undef rs
    int n;
    std::vector<Info> info;
};

constexpr int INF = 2E9;

struct Info {
    Info() = default;
    Info(int x, int idx) {
        lmn = rmx = x - idx;
        lmx = rmn = x + idx;
    }
    int lmn = INF;
    int rmn = -INF;
    int lmx = INF;
    int rmx = -INF;
    int ans = 0;
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.lmx = std::max(x.lmx, y.lmx);
    res.rmx = std::max(x.rmx, y.rmx);
    res.lmn = std::min(x.lmn, y.lmn);
    res.rmn = std::min(x.rmn, y.rmn);
    res.ans = std::max({x.ans, y.ans, x.lmx - y.rmn, y.rmx - x.lmn});
    return res;
}

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<Info> v(n + 1);
    for(int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        v[i] = Info(x, i);
    }
    SegmentTree<Info> tr(v);
    std::cout << tr.rangeQuery(1, n).ans << '\n';
    for(int i = 1; i <= q; ++i) {
        int idx, x;
        std::cin >> idx >> x;
        tr.update(idx, Info(x, idx));
        std::cout << tr.rangeQuery(1, n).ans << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    std::cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}
