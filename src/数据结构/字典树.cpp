#include <bits/stdc++.h>

struct Trie {
    Trie() : v(1) {};
    void insert(const std::string &s) {
        int cur = 0;
        for(const auto &val : s) {
            if(v[cur][val - '0'] == 0) {
                v[cur][val - '0'] = ++idx;
            }
            cur = v[cur][val - '0'];
            if(v.size() <= cur) {
                v.resize(cur + 1);
                tot.resize(cur + 1);
            }
            tot[cur]++;
        }
    }
    int find(const std::string &s) {
        int cur = 0;
        for(const auto &val : s) {
            if(v.size() <= cur || v[cur][val - '0'] == 0) {
                return 0;
            }
            cur = v[cur][val - '0'];
        }
        return tot[cur];
    }
    constexpr static int N = 80;
    int idx = 0;
    std::vector<int> tot;
    std::vector<std::array<int, N>> v;
};

void solve() {
    int n, q;
    std::cin >> n >> q;
    Trie t;
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
    int T;
    std::cin >> T;
    while(T--) {
        solve();
    }

    return 0;
} 