#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <class T> struct Point {
    T x;
    T y;
    Point(const T& x_ = 0, const T& y_ = 0) : x(x_), y(y_) {
    }
    Point& operator+=(const Point& p) {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point& operator-=(const Point& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point& operator*=(const T& v) {
        x *= v;
        y *= v;
        return *this;
    }
    Point& operator/=(const T& v) {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, const Point& b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point& b) {
        return a -= b;
    }
    friend Point operator*(Point a, const T& b) {
        return a *= b;
    }
    friend Point operator*(const T& a, Point b) {
        return b *= a;
    }
    friend bool operator==(const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }
};
template <class T> auto cross(const Point<T>& a, const Point<T>& b) {
    using W = conditional_t<is_integral_v<T>, __int128_t, long double>;
    return W(a.x) * b.y - W(a.y) * b.x;
}
template <class T> auto dist2(const Point<T>& a, const Point<T>& b) {
    using W = conditional_t<is_integral_v<T>, __int128_t, long double>;
    W dx = W(a.x) - b.x, dy = W(a.y) - b.y;
    return dx * dx + dy * dy;
}
template <class T> auto diameter2(const vector<Point<T>>& hull) {
    int n = int(hull.size());
    using W = decltype(dist2(Point<T>(), Point<T>()));
    if(n < 2) {
        return W(0);
    }
    W best = 0;
    int j = 1;
    for(int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        while(cross(hull[ni] - hull[i], hull[(j + 1) % n] - hull[j]) > 0) {
            j = (j + 1) % n;
        }
        best = max(best, dist2(hull[i], hull[j]));
        best = max(best, dist2(hull[ni], hull[j]));
    }
    return best;
}
