#include <bits/stdc++.h>
using i64 = long long;

constexpr int BASE = 1900;
constexpr int DAY[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
constexpr int PRE[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

bool isLeapYear(int y) {
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int dayId(int y, int m, int d) { // (y, m, d) 离 (BASE, 1, 1) 的天数，从0开始
    int res = (y - BASE) * 365 + PRE[m - 1] + d - 1;
    int y1 = BASE - 1, y2 = y - 1;
    res += (y2 / 4 - y2 / 100 + y2 / 400);
    res -= (y1 / 4 - y1 / 100 + y1 / 400);
    return res + (m > 2 && isLeapYear(y));
}

int wday(int y, int m, int d) { //求周几
    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 + 1;
}

std::array<int, 3> idToDate(i64 id) { // 通过 dayId 反向获取日期
    int y = BASE + (id * 10000) / 3652425;
    while (dayId(y, 1, 1) > id) y--;
    while (dayId(y + 1, 1, 1) <= id) y++;
    int m = (id - dayId(y, 1, 1)) * 1000 / 30419 + 1;
    while (dayId(y, m, 1) > id) m--;
    while (dayId(y, m + 1, 1) <= id) m++;
    int d = id - dayId(y, m, 1) + 1;
    return {y, m, d};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    return 0;
}