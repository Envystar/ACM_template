#include <bits/stdc++.h>
using i64 = long long;
constexpr int MAXN = 2E5;

template<typename Info, typename T = i64>
struct SegmentTree {
    struct Node {
        Node* l = nullptr;
        Node* r = nullptr;
        Info info;
    };
    SegmentTree() = default;
    SegmentTree(T n) : L(0), R(n - 1) {}
    SegmentTree(T L, T R) : L(L), R(R) {}
    void pushup(Node* id) {
        id->info = (id->l == nullptr ? Info() : id->l->info)
                 + (id->r == nullptr ? Info() : id->r->info);
    }
    void update(T pos, const Info &val) {
        update(root, L, R, pos, val);
    }
    Info query(T pos) {
        return rangeQuery(pos, pos);
    }
    Info rangeQuery(T l, T r) {
        return rangeQuery(root, L, R, l, r);
    }
    void update(Node* &id, T l, T r, T pos, const Info &val) {
        if(id == nullptr) id = new Node();
        if(l == r) {
            id->info = val;
            return;
        }
        T mid = (l + r - 1) / 2;
        if(pos <= mid) {
            update(id->l, l, mid, pos, val);
        } else {
            update(id->r, mid + 1, r, pos, val);
        }
        pushup(id);
    }
    Info rangeQuery(Node* &id, T l, T r, T x, T y) {
        if(y < l || x > r || id == nullptr) return Info();
        if(x <= l && r <= y) {
            return id->info;
        }
        T mid = (l + r - 1) / 2;
        return rangeQuery(id->l, l, mid, x, y)
             + rangeQuery(id->r, mid + 1, r, x, y);
    }

    void merge(SegmentTree<Info, T> seg) {
        root = merge(root, seg.root, L, R);
    }
    Node* merge(Node* &xid, Node* &yid, T l, T r) {
        if(xid == nullptr) return yid;
        if(yid == nullptr) return xid;
        if(l == r) {
            xid->info = (xid->info ^ yid->info);
            return xid;
        }
        T mid = (l + r - 1) / 2;
        xid->l = merge(xid->l, yid->l, l, mid);
        xid->r = merge(xid->r, yid->r, mid + 1, r);
        pushup(xid);
        return xid;
    }

    SegmentTree<Info, T> split(T L, T R) { //分裂出[L, R]的部分
        SegmentTree<Info, T> seg = split(L - 1);
        SegmentTree<Info, T> rem = seg.split(R);
        merge(rem);
        return seg;
    }
    SegmentTree<Info, T> split(T k) { //分裂出(k, ∞]的部分
        SegmentTree<Info, T> seg(L, R);
        seg.root = split(root, L, R, k);
        return seg;
    }
    Node* split(Node* &id, T l, T r, T k) {
        if(id == nullptr || l == r || k >= r) return nullptr;
        Node* nid = new Node();
        if(k < l) {
            std::swap(nid, id);
            return nid;
        }
        T mid = (l + r - 1) / 2;
        if(k > mid) {
            nid->r = split(id->r, mid + 1, r, k);
        } else {
            nid->l = split(id->l, l, mid, k);
            std::swap(nid->r, id->r);
        }
        pushup(id);
        pushup(nid);
        return nid;
    }
    T queryk(T k) { //非通用函数
        return queryk(root, L, R, k);
    }
    T queryk(Node *id, T l, T r, T k) {
        if(id == nullptr) return -1;
        if(id->info.sum < k) return -1;
        if(l == r) return l;
        int mid = (l + r - 1) / 2;
        if(id->l != nullptr && id->l->info.sum >= k) {
            return queryk(id->l, l, mid, k);
        } else if(id->r != nullptr) {
            return queryk(id->r, mid + 1, r, k - (id->l == nullptr ? 0 : id->l->info.sum));
        }
        return -1;
    }
    T L, R;
    Node* root = nullptr;
};

struct Info {
    Info() = default;
    Info(i64 _val) {
        sum = _val;
    }
    i64 sum = 0;
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    return res;
}

Info operator^(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, idx = 1;
    std::cin >> n >> m;
    std::vector<SegmentTree<Info>> segs(n + 1, SegmentTree<Info>(MAXN + 1));
    for(int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        segs[idx].update(i, x);
    }
    for(int i = 0; i < m; ++i) {
        int opt;
        std::cin >> opt;
        if(opt == 0) {
            int p, x, y;
            std::cin >> p >> x >> y;
            segs[++idx] = segs[p].split(x, y);
        } else if(opt == 1) {
            int p, t;
            std::cin >> p >> t;
            segs[p].merge(segs[t]);
        } else if(opt == 2) {
            int p, x, q;
            std::cin >> p >> x >> q;
            segs[p].update(q, segs[p].query(q).sum + x);
        } else if(opt == 3) {
            int p, x, y;
            std::cin >> p >> x >> y;
            std::cout << segs[p].rangeQuery(x, y).sum << '\n';
        } else if(opt == 4) {
            int p, k;
            std::cin >> p >> k;
            std::cout << segs[p].queryk(k) << '\n';
        }
    }
    return 0;
}
