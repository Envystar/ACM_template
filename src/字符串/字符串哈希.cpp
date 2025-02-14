#include <bits/stdc++.h>
using i64 = long long;

const int NUM = 2, MAXLEN = 60000;//哈希次数，字符串最大长度
const std::vector<i64> base = {31, 37, 233};
const std::vector<i64> mod = {2013265921, 1004535809, 2147483647};
std::vector<std::array<i64, NUM>> fac(MAXLEN + 1);
struct Hash {
    Hash() {}
    Hash(const std::string &s) : n(s.size()), hs(s.size() + 1) {//0-index
        for(int j = 0; j < NUM; ++j) {
            for(int i = 1; i <= n; ++i) {
                hs[i][j] = (hs[i - 1][j] * base[j] + s[i - 1]) % mod[j];
            }
        }
    }
    std::array<i64, NUM> range(int l, int r) {//1-index
        std::array<i64, NUM> res;
        for(int i = 0; i < NUM; ++i) {
            res[i] = (hs[r][i] - hs[l - 1][i] * fac[r - l + 1][i] % mod[i] + mod[i]) % mod[i];
        }
        return res;
    }
    int n;
    std::vector<std::array<i64, NUM>> hs;
};

void HashInit() {
    for(int j = 0; j < NUM; ++j) {
        fac[0][j] = 1;
        for(int i = 1; i <= MAXLEN; ++i) {
            fac[i][j] = fac[i - 1][j] * base[j] % mod[j];
        }
    }
}

//字符串hash
//https://www.luogu.com.cn/problem/P3370
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    HashInit();//预处理
    int n;
    std::cin >> n;
    std::set<std::array<i64, NUM>> st;
    for(int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        Hash hs(s);
        st.insert(hs.range(1, s.size()));
    }
    std::cout << st.size() << '\n';
    return 0;
}