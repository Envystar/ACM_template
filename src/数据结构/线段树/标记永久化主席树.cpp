#include <bits/stdc++.h>
using i64 = long long;

template<typename Info, typename Tag>
struct PersistentTree {
    struct Node {
        int l = 0, r = 0;
        Info info;
        Tag tag;
    };
#define ls(x) (node[id].l)
#define rs(x) (node[id].r)
    PersistentTree(int n) : n(n) {}
    PersistentTree(const std::vector<Info> &init) : PersistentTree((int)init.size() - 1) {
        node.reserve(n << 3);
        auto build = [&](auto self, int l, int r) ->int {
            node.push_back(Node());
            int id = node.size() - 1;
            if(l == r) {
                node[id].info = init[l];
            } else {
                int mid = (l + r) / 2;
                ls(id) = self(self, l, mid);
                rs(id) = self(self, mid + 1, r);
                node[id].info = node[ls(id)].info + node[rs(id)].info;
            }
            return id;
        };
        root.push_back(build(build, 1, n));
    };
    int update(int version, int t, const Tag &dx) {
        return rangeUpdate(version, t, t, dx);
    }
    Info query(int version, int t) {
        return rangeQuery(version, t, t);
    }
    int rangeUpdate(int version, int l, int r, const Tag &dx) {
        root.push_back(rangeUpdate(root[version], 1, n, l, r, dx));
        return root.size() - 1;
    }
    Info rangeQuery(int version, int l, int r) {
        return rangeQuery(root[version], 1, n, l, r);
    }
    int rangeUpdate(int lst, int l, int r, const int &x, const int &y, const Tag &dx) {
        node.push_back(node[lst]);
        int id = node.size() - 1;
        node[id].info.apply(std::min(r, y) - std::max(l, x) + 1, dx);
        if(x <= l && r <= y) {
            node[id].tag.apply(dx);
        } else {
            int mid = (l + r) / 2;
            if(x <= mid) {
                ls(id) = rangeUpdate(ls(lst), l, mid, x, y, dx);
            }
            if(y > mid) {
                rs(id) = rangeUpdate(rs(lst), mid + 1, r, x, y, dx);
            }
        }
        return id;
    }
    Info rangeQuery(int id, int l, int r, const int &x, const int &y) {
        if(x <= l && r <= y) {
            return node[id].info;
        }
        int mid = (l + r) / 2;
        Info res;
        if(x <= mid) {
            res = res + rangeQuery(ls(id), l, mid, x, y);
        }
        if(y > mid) {
            res = res + rangeQuery(rs(id), mid + 1, r, x, y);
        }
        res.apply(std::min(r, y) - std::max(l, x) + 1, node[id].tag);
        return res;
    }
#undef ls
#undef rs
    const int n;
    std::vector<Node> node;
    std::vector<int> root;
};

struct Tag {
    Tag(int dx = 0) : add(dx) {}
    int add = 0;
    void apply(const Tag &dx) {
        add += dx.add;
    }
};

struct Info {
    int sum = 0;
    void apply(int len, const Tag &dx) {
        sum += 1LL * len * dx.add;
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    return res;
}

//可持久化线段树(区间修改，区间历史查询)
//https://www.luogu.com.cn/problem/P3919
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<Info> v(n + 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> v[i].sum;
    }
    PersistentTree<Info, Tag> tr(v);
    std::vector<int> version(q + 1);
    for(int i = 1; i <= q; ++i) {
        int ver, opt, pos;
        std::cin >> ver >> opt >> pos;
        if(opt == 1) {
            int x;
            std::cin >> x;
            int lst = tr.query(version[ver], pos).sum;
            version[i] = tr.update(version[ver], pos, Tag(x - lst));
        } else if(opt == 2) {
            std::cout << tr.query(version[ver], pos).sum << '\n';
            version[i] = version[ver];
        }
    }
    return 0;
}