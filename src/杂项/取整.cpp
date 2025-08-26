#include <bits/stdc++.h>
using i64 = long long;

template<typename T>
T floorDiv(T a, T b) {
    return a / b - (((a < 0) ^ (b < 0)) && a % b != 0);
}

template<typename T>
T ceilDiv(T a, T b) {
    return a / b + (!((a < 0) ^ (b < 0)) && a % b != 0);
}

template<typename T>
T roundDiv(T a, T b) {
    return a / b + (abs(a % b) * 2 >= abs(b) ? ((a < 0) ^ (b < 0) ? -1 : 1) : 0);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}