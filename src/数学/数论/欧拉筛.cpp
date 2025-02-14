#include <bits/stdc++.h>
using i64 = long long;
constexpr int MAXN = 1E8; 
std::vector<int> prime;
std::vector<bool> nonPrime(MAXN + 1);

void findPrime(int n) { //[0, n]之间素数 
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

// 线性莫比乌斯函数
// const int MAXN = 1E6;

// std::array<int, MAXN + 1> mu;
// std::array<bool, MAXN + 1> nonPrime;
// std::vector<int> prime;

// void init(int n = MAXN) {
//     mu[1] = 1;
//     nonPrime[0] = nonPrime[1] = true;
//     for(int i = 2; i < n; ++i) {
//          if(nonPrime[i] == false) {
//             prime.push_back(i);
//             mu[i] = 1;
//         }
//         for(int j = 0; i * prime[j] <= n; ++j) {
//             nonPrime[i * prime[j]] = true;
//             if(i % prime[j] == 0) break;
//             mu[i * prime[j]] = -mu[i];
//         }
//     }
// };

//线性筛
//https://www.luogu.com.cn/problem/P3383
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    findPrime(n);
    while(q--) {
        int idx;
        std::cin >> idx;
        std::cout << prime[idx - 1] << '\n';
    }
    return 0;
}