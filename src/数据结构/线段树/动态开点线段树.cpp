#include <bits/stdc++.h>
using i64 = long long;

//https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A
template<typename Info, typename T = i64>
struct SegmentTree {
    struct Node {
        Node* l = nullptr;
        Node* r = nullptr;
        Info info;
    };
    SegmentTree(T n) : n(n) {}
    void pushup(Node* id) {
        id->info = (id->l == nullptr ? Info() : id->l->info) 
                 + (id->r == nullptr ? Info() : id->r->info);
    }
    void update(T pos, const Info &val) {
        update(root, 1, n, pos, val);
    }
    Info query(T pos) {
        return rangeQuery(pos, pos);
    }
    Info rangeQuery(T l, T r) {
        return rangeQuery(root, 1, n, l, r);
    }
    void update(Node* &id, T l, T r, T pos, const Info &val) {
        if(id == nullptr) id = new Node();
        if(l == r) {
            id->info = val;
            return;
        }
        T mid = (l + r) / 2;
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
        T mid = (l + r) / 2;
        return rangeQuery(id->l, l, mid, x, y) 
             + rangeQuery(id->r, mid + 1, r, x, y);
    }
    const T n;
    Node* root = nullptr;
};

constexpr i64 INF = (1LL << 31) - 1;

struct Info {
    Info() = default;
    Info(i64 val) {
        min = val;
    }
    i64 min = INF;
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.min = std::min(x.min, y.min);
    return res;
}

void solve() {
    int n, q;
    std::cin >> n >> q;
    SegmentTree<Info> st(n);
    for(int i = 1; i <= n; ++i) {
        st.update(i, Info());
    }
    for(int i = 1; i <= q; ++i) {
        int opt;
        std::cin >> opt;
        if(opt == 0) {
            int pos, val;
            std::cin >> pos >> val;
            st.update(pos + 1, Info(val));
        } else if(opt == 1) {
            int l, r;
            std::cin >> l >> r;
            std::cout << st.rangeQuery(l + 1, r + 1).min << '\n';
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    // std::cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}
