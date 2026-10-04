#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using i64 = long long;
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
template <class T> auto dot(const Point<T>& a, const Point<T>& b) {
    using W = conditional_t<is_integral_v<T>, __int128_t, long double>;
    return W(a.x) * b.x + W(a.y) * b.y;
}
template <class T> auto cross(const Point<T>& a, const Point<T>& b) {
    using W = conditional_t<is_integral_v<T>, __int128_t, long double>;
    return W(a.x) * b.y - W(a.y) * b.x;
}
template <class T> auto square(const Point<T>& p) {
    return dot(p, p);
}
template <class T> db length(const Point<T>& p) {
    return sqrt(db(square(p)));
}
template <class T> db dis(const Point<T>& a, const Point<T>& b) {
    return length(a - b);
}
template <class T> Point<db> normalize(const Point<T>& p) {
    return Point<db>(db(p.x), db(p.y)) / length(p);
}
template <class T> Point<T> rotate(const Point<T>& a) {
    return Point<T>(-a.y, a.x);
}
template <class T> int sgn(const Point<T>& a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}
// 以 o 为极心的极角排序（同角按距离近优先），叉积用平移后的向量。
template <class T> void polarSort(vector<Point<T>>& p, const Point<T>& o = Point<T>()) {
    sort(p.begin(), p.end(), [&](const Point<T>& a, const Point<T>& b) {
        Point<T> ad = a - o;
        Point<T> bd = b - o;
        int sa = sgn(ad);
        int sb = sgn(bd);
        if(sa != sb) {
            return sa > sb;
        }
        auto c = cross(ad, bd);
        if(c != 0) {
            return c > 0;
        }
        return square(ad) < square(bd);
    });
}
template <class T>
vector<int> polarOrder(const vector<Point<T>>& pts, const Point<T>& o = Point<T>()) {
    int n = int(pts.size());
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) {
        Point<T> ad = pts[i] - o;
        Point<T> bd = pts[j] - o;
        int sa = sgn(ad);
        int sb = sgn(bd);
        if(sa != sb) {
            return sa > sb;
        }
        auto c = cross(ad, bd);
        if(c != 0) {
            return c > 0;
        }
        return square(ad) < square(bd);
    });
    return p;
}
template <class T> struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T>& a_ = Point<T>(), const Point<T>& b_ = Point<T>()) : a(a_), b(b_) {
    }
};
template <class T> db length(const Line<T>& l) {
    return length(l.a - l.b);
}
template <class T> bool parallel(const Line<T>& l1, const Line<T>& l2) {
    return cross(l1.b - l1.a, l2.b - l2.a) == 0;
}
template <class T> bool onLeft(const Point<T>& p, const Line<T>& l) {
    return cross(l.b - l.a, p - l.a) > 0;
}
template <class T> bool onLine(const Point<T>& p, const Line<T>& l) {
    return cross(p - l.a, l.b - l.a) == 0;
}
// 整型坐标返回 Point<db>，浮点坐标返回原类型。
template <class T> auto lineCross(const Line<T>& l1, const Line<T>& l2) {
    using RT = typename conditional<is_integral_v<T>, db, T>::type;
    RT num = RT(cross(l2.b - l2.a, l1.a - l2.a));
    RT den = RT(cross(l2.b - l2.a, l1.a - l1.b));
    RT t = num / den;
    return Point<RT>(RT(l1.a.x) + RT(l1.b.x - l1.a.x) * t,
                     RT(l1.a.y) + RT(l1.b.y - l1.a.y) * t);
}
template <class T> db distancePL(const Point<T>& p, const Line<T>& l) {
    if(l.a == l.b) {
        return length(p - l.a);
    }
    return db(fabsl((long double)cross(l.a - l.b, l.a - p))) / length(l);
}
