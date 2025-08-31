#include <bits/stdc++.h>
using i64 = long long;

constexpr int MAXN = 2E5;
std::vector<int> prime;
std::vector<bool> nonPrime(MAXN + 1);
void findPrime(int n) {
    nonPrime[0] = nonPrime[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(nonPrime[i] == false) {
            prime.push_back(i);
        }
        for(int j = 0; i * prime[j] <= n; ++j) {
            nonPrime[i * prime[j]] = true;
            if(i % prime[j] == 0) break;
        }
    }
}

//区间筛, 筛区间[L, R]的质数
//https://www.luogu.com.cn/problem/UVA10140
int main() {
    i64 L, R;
    findPrime(MAXN);
    while(std::cin >> L >> R) {

        std::vector<i64> res;
        std::vector<bool> nonp(R - L + 1);
        for(auto x : prime) {
            if(x > R) break;
            for(int j = std::max((L + x - 1) / x, 2LL); 1LL * j * x <= R; ++j) {
                nonp[j * x - L] = 1;
            }
        }
        for(int i = 0; i <= R - L; ++i) {
            if(nonp[i] == 0 && i + L >= 2) {
                res.push_back(i + L);
            }
        }

        i64 mn = INT_MAX, mx = INT_MIN;
        int mnidx = -1, mxidx = -1;
        for(int i = 1; i < res.size(); ++i) {
            if(res[i] - res[i - 1] < mn) {
                mn = res[i] - res[i - 1];
                mnidx = i;
            }
            if(res[i] - res[i - 1] > mx) {
                mx = res[i] - res[i - 1];
                mxidx = i;
            }
        }
        if(res.size() <= 1) {
            std::cout << "There are no adjacent primes.\n";
        } else {
            std::cout << res[mnidx - 1] << ',' << res[mnidx] << " are closest, "
                      << res[mxidx - 1] << ',' << res[mxidx] << " are most distant.\n";
        }
    }
    return 0;
}