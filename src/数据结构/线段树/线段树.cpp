#include <bits/stdc++.h>
using i64 = long long;

//线段树，区间修改，区间查询
//https://www.luogu.com.cn/problem/P3372
template<typename Info, typename Tag>
struct SegmentTree {
#define ls (id<<1)
#define rs (id<<1|1)
    SegmentTree() = default;
    SegmentTree(int n) : SegmentTree(std::vector<Info>(n)) {}
    SegmentTree(int n, const Info &val) : SegmentTree(std::vector<Info>(n, val)) {}
    SegmentTree(const std::vector<Info> &init) : n(init.size()), info(n << 2), tag(n << 2), len(n << 2) {
        auto build = [&](auto self, int id, int l, int r) ->void {
            len[id] = r - l + 1;
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
    void apply(int id, const Tag &dx) {
        info[id].apply(dx, len[id]);
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
        rangeUpdate(1, 0, n - 1, l, r, dx);
    }
    void update(int pos, const Tag &dx) {
        rangeUpdate(pos, pos, dx);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
    Info query(int pos) {
        return rangeQuery(pos, pos);
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
        Info res = Info::unit();
        if(x <= mid) {
            res = res + rangeQuery(ls, l, mid, x, y);
        }
        if(y > mid) {
            res = res + rangeQuery(rs, mid + 1, r, x, y);
        }
        return res;
    }
    int findFirst(int x, int y, auto check) {
        Info pre = Info::unit();
        return findFirst(1, 0, n - 1, x, y, pre, check);
    }
    int findFirst(int id, int l, int r, int x, int y, Info& pre, auto check) {
        if(x <= l && r <= y) {
            if(!check(pre + info[id])) {
                pre = pre + info[id];
                return -1;
            } else if(l == r) {
                return l;
            }
        }
        int mid = (l + r) / 2;
        pushdown(id);
        if(x <= mid) {
            int res = findFirst(ls, l, mid, x, y, pre, check);
            if(res != -1) return res;
        }
        return findFirst(rs, mid + 1, r, x, y, pre, check);
    }
#undef ls
#undef rs
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    std::vector<int> len;
};

constexpr i64 INF = 4E18;
i64 P = 571373;

struct Tag {
    i64 add = 0;
    i64 mul = 1;
    void apply(const Tag &dx) {
        mul = (mul * dx.mul) % P;
        add = (add * dx.mul + dx.add) % P;
    }
};

struct Info {
    Info() = default;
    Info(i64 x) : sum(x % P) {}
    i64 sum = 0;
    void apply(const Tag &dx, const int &len) {
        sum = (sum * dx.mul + dx.add * len) % P;
    }
    static Info unit() {
        return Info();
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.sum = (x.sum + y.sum) % P;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m >> P;
    std::vector<Info> v(n);
    for(int i = 0; i < n; ++i) {
        i64 x;
        std::cin >> x;
        v[i] = x;
    }
    SegmentTree<Info, Tag> tr(v);
    while(m--) {
        i64 opt, x, y;
        std::cin >> opt >> x >> y;
        x--, y--;
        if(opt == 1) {
            i64 k;
            std::cin >> k;
            tr.rangeUpdate(x, y, Tag(0, k));
        } else if(opt == 2) {
            i64 k;
            std::cin >> k;
            tr.rangeUpdate(x, y, Tag(k, 1));
        } else if(opt == 3) {
            std::cout << tr.rangeQuery(x, y).sum << '\n';
        }
    }
    return 0;
}