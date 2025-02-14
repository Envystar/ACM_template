#include <bits/stdc++.h>

//马拉车(manacher)
//https://www.luogu.com.cn/problem/P3805

// 以第i个数为轴的最大回文 v[2 * i + 1]
// 以第i个数和i+1个数中间为轴的最大回文 v[2 * i + 2]
// 以[L, R] 区间中轴的最大回文为v[L + R + 1]
std::vector<int> manacher(const std::string& s) {
    int n = 2 * s.length() + 1;
    std::string t(n, '#');//处理字符串
    for(int i = 0; i < s.length(); ++i) {
        t[2 * i + 1] = s[i];
    }
    std::vector<int> v(n);//记录回文半径  [l, r] <=> [mid - v[mid], mid - v[mid]]
    for(int i = 0, mid = 0; i < n; ++i) { // mid为回文中心
        if(i <= mid + v[mid]) {
            v[i] = std::min(v[2 * mid - i], mid + v[mid] - i);// (t + i) / 2 = mid <=> t = 2 * mid - i;
        }
        while(t[i - v[i] - 1] == t[i + v[i] + 1] && 0 <= i - v[i] - 1 && i + v[i] + 1 < n) {
            ++v[i];
        }
        if(i + v[i] > mid + v[mid]) {
            mid = i;
        }
    }
    return v;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    std::vector<int> v = manacher(s);
    int ans = 0;
    for(int i = 0; i < v.size(); ++i) {
        ans = std::max(ans, v[i]);//求最长回文子串
        std::cout << v[i] << " \n"[i == v.size() - 1];
    }
    std::cout << ans << '\n';
    return 0;
}