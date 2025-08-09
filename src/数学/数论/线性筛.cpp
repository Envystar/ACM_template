#include <bits/stdc++.h>
using i64 = long long;
constexpr int MAXN = 1E8;

std::vector<int> minp, prime;
std::vector<int> phi, mu;

void sieve(int n = MAXN) {
    minp = phi = mu = std::vector<int>(n + 1, 0);
    phi[1] = mu[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(minp[i] == 0) {
            minp[i] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            prime.push_back(i);
        }
        for(int j = 0; i * prime[j] <= n; ++j) {
            minp[i * prime[j]] = prime[j];
            if(minp[i] == prime[j]) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            mu[i * prime[j]] = -mu[i];
        }
    }
}

bool isPrime(int n) {
    return minp[n] == n;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    sieve(n);
    while(q--) {
        int idx;
        std::cin >> idx;
        std::cout << prime[idx - 1] << '\n';
    }
    return 0;
}