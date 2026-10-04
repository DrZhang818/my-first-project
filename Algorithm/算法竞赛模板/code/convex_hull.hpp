#pragma once
#include <bits/stdc++.h>
using namespace std;
using db = long double;
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
    friend Point operator/(Point a, const T& b) {
        return a /= b;
    }
    friend Point operator*(const T& a, Point b) {
        return b *= a;
    }
    friend bool operator==(const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator<(const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};
template <class T> auto cross(const Point<T>& a, const Point<T>& b) {
    using W = conditional_t<is_integral_v<T>, __int128_t, long double>;
    return W(a.x) * b.y - W(a.y) * b.x;
}
template <class T> vector<Point<T>> convexHull(vector<Point<T>> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = int(p.size());
    if(n <= 2) {
        return p;
    }
    sort(p.begin(), p.end());
    vector<Point<T>> h;
    for(int i = 0; i < n; i++) {
        while(int(h.size()) >= 2 &&
              cross(h.back() - h[int(h.size()) - 2], p[i] - h.back()) <= 0) {
            h.pop_back();
        }
        h.push_back(p[i]);
    }
    int k = int(h.size());
    for(int i = n - 2; i >= 0; i--) {
        while(int(h.size()) > k &&
              cross(h.back() - h[int(h.size()) - 2], p[i] - h.back()) <= 0) {
            h.pop_back();
        }
        h.push_back(p[i]);
    }
    h.pop_back();
    return h;
}
// 多边形面积（鞋带公式，逆时针为正）。
template <class T> db polygonArea(const vector<Point<T>>& p) {
    db area = 0;
    int n = int(p.size());
    for(int i = 0; i < n; i++) {
        area += db(cross(p[i], p[(i + 1) % n]));
    }
    return area / 2.0;
}
