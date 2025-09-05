#include <bits/stdc++.h>
using i64 = long long;

std::vector<int> kmp(const std::string &s) {
    std::vector<int> v(s.size());
    for(int i = 1, j = 0; i < s.size(); ++i) {
        while(j > 0 && s[i] != s[j]) {
            j = v[j - 1];
        }
        if(s[i] == s[j]) {
            ++j;
        }
        v[i] = j;
    }
    return v;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s, p;
    std::cin >> s >> p;
    auto v = kmp(p + "#" + s);
    for(int i = p.size() + 1; i < v.size(); ++i) {
        if(v[i] == p.size()) {
            std::cout << i - 2 * p.size() + 1 << '\n';
        }
    }
    for(int i = 0; i < p.size(); ++i) {
        std::cout << v[i] << " \n"[i + 1 == p.size()];
    }
    return 0;
}