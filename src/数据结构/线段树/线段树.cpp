#include <bits/stdc++.h>
using i64 = long long;

//线段树，区间修改，区间查询
//https://www.luogu.com.cn/problem/P3372
template<typename Info, typename Tag>
struct SegmentTree {
#define ls (id<<1)
#define rs (id<<1|1)
    SegmentTree(int n) : n(n), info(n << 2), tag(n << 2) {} //最值操作不可用此初始化
    SegmentTree(const std::vector<Info> &init) : SegmentTree((int)init.size() - 1) {
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
        build(build, 1, 1, n);
    }
    void apply(int id, const Tag &dx) {
        info[id].apply(dx);
        tag[id].apply(dx);
    }
    void pushup(int id) {
        info[id] = info[ls] + info[rs];
    }
    void pushdown(int id) {
        apply(ls, tag[id]);
        apply(rs, tag[id]);
        tag[id] = Tag();
    }
    void rangeUpdate(int l, int r, const Tag &dx) {
        rangeUpdate(1, 1, n, l, r, dx);
    }
    void update(int t, const Tag &dx) {
        rangeUpdate(t, t, dx);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }
    Info query(int t) {
        return rangeQuery(t, t);
    }
    void rangeUpdate(int id, int l, int r, int x, int y, const Tag &dx) {
        if(x <= l && r <= y) {
            apply(id, dx);
            return;
        }
        int mid = (l + r) / 2;
        pushdown(id);
        if(x <= mid) {
            rangeUpdate(ls, l, mid, x, y, dx);
        }
        if(y > mid) {
            rangeUpdate(rs, mid + 1, r, x, y, dx);
        }
        pushup(id);
    }
    Info rangeQuery(int id, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return info[id];
        }
        int mid = (l + r) / 2;
        pushdown(id);
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
    const int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
};

constexpr i64 INF = 1E18;

struct Tag {
    i64 add = 0;
    void apply(const Tag &dx) {
        add += dx.add;
    }
};

struct Info {
    i64 mn = INF;
    i64 mx = -INF;
    i64 sum = 0;
    i64 len = 1;
    void apply(const Tag &dx) {
        mn += dx.add;
        mx += dx.add;
        sum += len * dx.add;
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.mn = std::min(x.mn, y.mn);
    res.mx = std::max(x.mx, y.mx);
    res.sum = x.sum + y.sum;
    res.len = x.len + y.len;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<Info> v(n + 1);
    for(int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        v[i] = {x, x, x, 1};
    }
    SegmentTree<Info, Tag> tr(v);
    // SegmentTree<Info, Tag> tr(n);
    // for(int i = 1; i <= n; ++i) {
    //     int x;
    //     std::cin >> x;
    //     tr.update(i, Tag(x));
    // }
    while(m--) {
        int opt, x, y;
        std::cin >> opt >> x >> y;
        if(opt == 1) {
            int k;
            std::cin >> k;
            tr.rangeUpdate(x, y, Tag(k));
        } else if(opt == 2) {
            std::cout << tr.rangeQuery(x, y).sum << '\n';
        }
    }
    return 0;
}