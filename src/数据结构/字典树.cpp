#include <bits/stdc++.h>

template<int N = 26>
struct Trie {
    Trie() = default;
    Trie(const std::string &rgx) : tree(1) {
        int k = 0;
        for(int i = 0, dx; i < rgx.size(); i += dx + 1) {
            dx = 2 * (i + 2 < rgx.size() && rgx[i + 1] == '-');
            for(int j = rgx[i]; j <= rgx[i + dx]; ++j) {
                dict[j] = k++;
            }
        }
    }
    void insert(const std::string &s) {
        int cur = 0;
        for(const auto &ch : s) {
            int &nxt = tree[cur][dict[ch]];
            if(nxt == 0) nxt = ++idx;
            cur = nxt;
            if(tree.size() <= cur) {
                tree.resize(cur + s.size());
                tot.resize(cur + s.size());
            }
            tot[cur]++;
        }
    }
    int find(const std::string &s) {
        int cur = 0;
        for(const auto &ch : s) {
            int &nxt = tree[cur][dict[ch]];
            if(nxt == 0) return 0;
            cur = nxt;
        }
        return tot[cur];
    }

    int idx = 0;
    std::vector<int> tot;
    std::array<int, 128> dict{};
    std::vector<std::array<int, N>> tree;
};

void solve() {
    int n, q;
    std::cin >> n >> q;
    Trie<62> t("0-9A-Za-z");
    for(int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        t.insert(s);
    }
    for(int i = 1; i <= q; ++i) {
        std::string s;
        std::cin >> s;
        std::cout << t.find(s) << '\n';
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