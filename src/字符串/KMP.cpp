#include <bits/stdc++.h>
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s, p;
    std::cin >> s >> p;
    int n = s.size(), m = p.size();
    s = '#' + s, p = '#' + p;
    std::vector<int> kmp(m + 1);
    for(int i = 2, j = 0; i <= m; ++i) { //求kmp数组
        while(j > 0 && p[i] != p[j + 1]) {
            j = kmp[j];
        }
        if(p[j + 1] == p[i]) {
            j++;
        }
        kmp[i] = j;
    }
    for(int i = 1, j = 0; i <= n; ++i) {
        while(j > 0 && s[i] != p[j + 1]) {
            j = kmp[j];
        }
        if(s[i] == p[j + 1]) {
            j++;
        }
        if(j == m) {
            std::cout << i - j + 1 << '\n';
            j = kmp[j];
        } 
    }
    for(int i = 1; i <= m; ++i) {
        std::cout << kmp[i] << " \n"[i == m];
    }
    return 0;
}