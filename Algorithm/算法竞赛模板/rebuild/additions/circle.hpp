#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld EPS = 1e-12;
struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {
    }
    Point operator+(Point p) const {
        return {x + p.x, y + p.y};
    }
    Point operator-(Point p) const {
        return {x - p.x, y - p.y};
    }
    Point operator*(ld k) const {
        return {x * k, y * k};
    }
};
ld dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}
ld cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
ld dist(Point a, Point b) {
    return hypotl(a.x - b.x, a.y - b.y);
}
struct Circle {
    Point c;
    ld r;
};
bool circumcircle(Point a, Point b, Point c, Circle& ans) {
    Point u = b - a, v = c - a;
    ld d = 2 * cross(u, v);
    if(fabsl(d) < EPS) {
        return false;
    }
    Point o =
        a + Point(dot(u, u) * v.y - dot(v, v) * u.y, u.x * dot(v, v) - v.x * dot(u, u)) *
                (1 / d);
    ans = {o, dist(o, a)};
    return true;
}
// Return 0/1/2 intersections; -1 means coincident circles with positive radius.
int circleCross(Circle a, Circle b, vector<Point>& ans) {
    assert(a.r >= 0 && b.r >= 0);
    ans.clear();
    Point v = b.c - a.c;
    ld d = hypotl(v.x, v.y);
    if(d < EPS) {
        if(fabsl(a.r - b.r) >= EPS) {
            return 0;
        }
        if(a.r < EPS) {
            ans.push_back(a.c);
            return 1;
        }
        return -1;
    }
    if(d > a.r + b.r + EPS || d < fabsl(a.r - b.r) - EPS) {
        return 0;
    }
    ld x = (a.r * a.r - b.r * b.r + d * d) / (2 * d);
    ld h = sqrtl(max(ld(0), a.r * a.r - x * x));
    Point m = a.c + v * (x / d), u = Point(-v.y, v.x) * (h / d);
    ans.push_back(m + u);
    if(h > EPS) {
        ans.push_back(m - u);
    }
    return ans.size();
}
