#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct CHT {
    using i128 = __int128;
    struct Point {
        i64 x, y;
        Point operator-(const Point& p) const {
            return {x - p.x, y - p.y};
        }
    };
    vector<Point> hull;
    static i128 cross(Point a, Point b) {
        return i128(a.x) * b.y - i128(a.y) * b.x;
    }
    static i128 dot(Point a, Point b) {
        return i128(a.x) * b.x + i128(a.y) * b.y;
    }
    void addPoint(Point p) {
        if(!hull.empty() && hull.back().x == p.x) {
            if(hull.back().y <= p.y) {
                return;
            }
            hull.pop_back();
        }
        while(hull.size() >= 2 &&
              cross(hull.back() - hull[hull.size() - 2], p - hull.back()) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    i128 query(Point q) const {
        int l = 0, r = int(hull.size()) - 1;
        while(l < r) {
            int m = (l + r) >> 1;
            if(dot(hull[m], q) <= dot(hull[m + 1], q)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return dot(hull[l], q);
    }
};
