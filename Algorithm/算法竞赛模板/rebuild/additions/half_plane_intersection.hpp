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
ld cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
ld dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}
struct Line {
    Point p, v;
    ld ang;
    Line(Point a, Point b) : p(a), v(b - a) {
        ld len = hypotl(v.x, v.y);
        assert(len > 0);
        v = v * (1 / len);
        ang = atan2l(v.y, v.x);
        if(ang < 0) {
            ang += 2 * acosl(-1);
        }
    }
    bool out(Point a) const {
        return cross(v, a - p) < -EPS;
    }
};
Point intersect(Line a, Line b) {
    return a.p + a.v * (cross(b.v, a.p - b.p) / cross(a.v, b.v));
}
// Intersection of closed LEFT half-planes; bounded positive-area case.
vector<Point> halfPlanes(vector<Line> a) {
    sort(a.begin(), a.end(), [](Line x, Line y) { return x.ang < y.ang; });
    vector<Line> b;
    for(Line l : a) {
        if(!b.empty() && fabsl(cross(b.back().v, l.v)) < EPS && dot(b.back().v, l.v) > 0) {
            if(cross(b.back().v, l.p - b.back().p) > 0) {
                b.back() = l;
            }
        } else {
            b.push_back(l);
        }
    }
    deque<Line> q;
    for(Line l : b) {
        while(q.size() > 1 && l.out(intersect(q[q.size() - 2], q.back()))) {
            q.pop_back();
        }
        while(q.size() > 1 && l.out(intersect(q[0], q[1]))) {
            q.pop_front();
        }
        if(!q.empty() && fabsl(cross(q.back().v, l.v)) < EPS) {
            return {};
        }
        q.push_back(l);
    }
    while(q.size() > 2 && q[0].out(intersect(q[q.size() - 2], q.back()))) {
        q.pop_back();
    }
    while(q.size() > 2 && q.back().out(intersect(q[0], q[1]))) {
        q.pop_front();
    }
    if(q.size() < 3 || fabsl(cross(q.front().v, q.back().v)) < EPS) {
        return {};
    }
    vector<Point> p;
    for(int i = 0; i < int(q.size()); i++) {
        p.push_back(intersect(q[i], q[(i + 1) % q.size()]));
    }
    return p;
}
