#include <bits/stdc++.h>
using i64 = long long;
constexpr long double EPS = 1E-10;

using T = long double;
struct Point {
    T x = 0, y = 0;
    Point operator+(const Point &o) const {return {x + o.x, y + o.y};}
    Point operator-(const Point &o) const {return {x - o.x, y - o.y};}
    Point operator-() const {return {-x, -y};}
    Point operator*(T fac) const {return {x * fac, y * fac};}
    Point operator/(T fac) const {return {x / fac, y / fac};}
    bool operator<(const Point &o) const {
        return std::tie(x, y) < std::tie(o.x, o.y);
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream &operator<<(std::ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

struct Line {
    Point s, t;
    Line() = default;
    Line(Point _s, Point _t) : s(_s), t(_t) {}
};

int sgn(T a){ 
    if(fabs(a) < EPS) return 0;
    return a > 0 ? 1 : -1;
}

T dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
T cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
T cross(const Point &a, const Point &b, const Point &c) {
    return cross(b - a, c - a);
}
T len(const Point &a) {
    return sqrtl(a.x * a.x + a.y * a.y);
}
T angle(const Point &a, const Point &b) {
    return acosl(dot(a, b) / len(a) / len(b));
}
T dis2(const Point &a, const Point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
T dis(const Point &a, const Point &b) {
    return sqrtl(dis2(a, b));
}
Point rotate(const Point &a, const Point &b, T theta) {
    return {
        (b.x - a.x) * cosl(theta) - (b.y - a.y) * sinl(theta) + a.x,
        (b.x - a.x) * sinl(theta) + (b.y - a.y) * cosl(theta) + a.y
    };
}

bool intersect(const Line &a, const Line &b) {
    return cross(a.s, a.t, b.s) * cross(a.s, a.t, b.t) <= 0 
        && cross(b.s, b.t, a.s) * cross(a.s, b.t, a.t) <= 0;
}
bool intersectStrictly(const Line &a, const Line &b) {
    return cross(a.s, a.t, b.s) * cross(a.s, a.t, b.t) < 0 
        && cross(b.s, b.t, a.s) * cross(a.s, b.t, a.t) < 0;
}
Point getNode(const Line &a, const Line &b) {
    T dx = cross(b.s, b.t, a.s) / cross(b.s, b.t, a.t);
    return a.s + (a.t - a.s) * std::abs(dx); 
};

std::vector<Point> andrew(std::vector<Point> &v) {
    int n = v.size();
    std::sort(v.begin(), v.end());
    std::vector<Point> stk;
    for(int i = 0; i < n; ++i) {
        while(stk.size() > 1 && cross(stk[stk.size() - 2], stk.back(), v[i]) <= 0) {
            stk.pop_back();
        }
        stk.push_back(v[i]);
    }
    int t = stk.size();
    for(int i = n - 2; i >= 0; --i) {
        while(stk.size() > t && cross(stk[stk.size() - 2], stk.back(), v[i]) <= 0) {
            stk.pop_back();
        }
        stk.push_back(v[i]);
    }
    stk.pop_back();
    return stk;
};

T diameter(const std::vector<Point> &v) {
    int n = v.size();
    T res = 0;
    for(int i = 0, j = 1; i < n; ++i) {
        while(sgn(cross(v[i], v[(i + 1) % n], v[j]) - cross(v[i], v[(i + 1) % n], v[(j + 1) % n])) <= 0) {
            j = (j + 1) % n;
        }
        res = std::max({res, dis(v[i], v[j]), dis(v[(i + 1) % n], v[j])});
    }
    return res;
}

T diameter2(const std::vector<Point> &v) {
    int n = v.size();
    T res = 0;
    for(int i = 0, j = 1; i < n; ++i) {
        while(sgn(cross(v[i], v[(i + 1) % n], v[j]) - cross(v[i], v[(i + 1) % n], v[(j + 1) % n])) <= 0) {
            j = (j + 1) % n;
        }
        res = std::max({res, dis2(v[i], v[j]), dis2(v[(i + 1) % n], v[j])});
    }
    return res;
}

T grith(const std::vector<Point> &convex) {
    long double ans = 0;
    for(int i = 0; i < convex.size(); ++i) {
        ans += dis(convex[i], convex[(i + 1) % convex.size()]);
    }
    return ans;
}

void solve() {
    int n, m;
    std::cin >> n;
    std::vector<Point> A(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }
    std::cin >> m;
    std::vector<Point> B(m);
    for(int i = 0; i < m; ++i) {
        std::cin >> B[i];
    }
    long double ans = grith(A) + 2.0L * sqrtl(diameter2(B)) * acosl(-1.0L);   //A周长 + 2 * B直径 * PI
    std::cout << std::fixed << std::setprecision(15) << ans << '\n';
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    std::cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}