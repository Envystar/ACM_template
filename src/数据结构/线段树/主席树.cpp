#include <bits/stdc++.h>
using i64 = long long;

template<typename Info, typename Tag>
struct PersistentTree {
    struct Node {
        int l = 0, r = 0;
        Info info;
        Tag tag;
    };
#define ls(x) (node[x].l)
#define rs(x) (node[x].r)
    PersistentTree(int n) : PersistentTree(std::vector<Info>(n + 1)) {}
    PersistentTree(const std::vector<Info> &init) : n((int)init.size() - 1) {
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
    int update(int version, int pos, const Info &val) {
        root.push_back(update(root[version], 1, n, pos, val));
        return root.size() - 1;
    }
    int update(int version, int pos, const Tag &dx) {
        root.push_back(update(root[version], 1, n, pos, dx));
        return root.size() - 1;
    }
    Info query(int version, int pos) {
        return rangeQuery(version, pos, pos);
    }
    Info rangeQuery(int version, int l, int r) {
        return rangeQuery(root[version], 1, n, l, r);
    }
    int update(int lst, int l, int r, const int &pos, const Info &val) {
        node.push_back(node[lst]);
        int id = node.size() - 1;
        if(l == r) {
            node[id].info = val;
        } else {
            int mid = (l + r) / 2;
            if(pos <= mid) {
                ls(id) = update(ls(lst), l, mid, pos, val);
            } else if(pos > mid) {
                rs(id) = update(rs(lst), mid + 1, r, pos, val);
            }
            node[id].info = node[ls(id)].info + node[rs(id)].info;
        }
        return id;
    }
    int update(int lst, int l, int r, const int &pos, const Tag &dx) {
        node.push_back(node[lst]);
        int id = node.size() - 1;
        if(l == r) {
            node[id].info.apply(dx);
        } else {
            int mid = (l + r) / 2;
            if(pos <= mid) {
                ls(id) = update(ls(lst), l, mid, pos, dx);
            } else if(pos > mid) {
                rs(id) = update(rs(lst), mid + 1, r, pos, dx);
            }
            node[id].info = node[ls(id)].info + node[rs(id)].info;
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
        return res;
    }
    int kth(int versionl, int versionr, int k) {
        return kth(root[versionl], root[versionr], 1, n, k);
    }
    int kth(int idx, int idy, int l, int r, int k) { //静态区间第k小，不支持修改
        if(l >= r) return l;
        int mid = (l + r) / 2;
        int dx = node[ls(idy)].info.sum - node[ls(idx)].info.sum;
        if(dx >= k) {
            return kth(ls(idx), ls(idy), l, mid, k);
        } else {
            return kth(rs(idx), rs(idy), mid + 1, r, k - dx);
        }
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
    void apply(const Tag &dx) {
        sum += dx.add;
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    return res;
}
//主席树(单点修改，历史版本区间查询, 静态区间第k小)
//https://www.luogu.com.cn/problem/P3834
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> v(n + 1), tmp(n + 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> v[i];
        tmp[i] = v[i];
    }
    std::sort(tmp.begin() + 1, tmp.end());
    tmp.erase(std::unique(tmp.begin() + 1, tmp.end()), tmp.end());
    int m = tmp.size() - 1;
    PersistentTree<Info, Tag> tr(std::vector<Info>(m + 1));
    std::vector<int> version(n + 1);
    version[0] = tr.root.size() - 1;
    for(int i = 1; i <= n; ++i) {
        int pos = std::lower_bound(tmp.begin() + 1, tmp.end(), v[i]) - tmp.begin();
        version[i] = tr.update(version[i - 1], pos, Tag(1));
    }
    for(int i = 1; i <= q; ++i) {
        int l, r, k;
        std::cin >> l >> r >> k;
        int pos = tr.kth(version[l - 1], version[r], k);
        std::cout << tmp[pos] << '\n';
    }
    return 0;
}