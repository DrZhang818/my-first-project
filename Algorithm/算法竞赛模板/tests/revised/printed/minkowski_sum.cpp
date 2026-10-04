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
template <class T>
vector<Point<T>> minkowskiSum(const vector<Point<T>>& a, const vector<Point<T>>& b) {
    int n = int(a.size());
    int m = int(b.size());
    if(n == 0 || m == 0) {
        return {};
    }
    if(n <= 2 || m <= 2) {
        vector<Point<T>> p;
        for(auto x : a) {
            for(auto y : b) {
                p.push_back(x + y);
            }
        }
        sort(p.begin(), p.end(),
             [](Point<T> x, Point<T> y) { return x.x < y.x || (x.x == y.x && x.y < y.y); });
        p.erase(unique(p.begin(), p.end()), p.end());
        if(p.size() <= 2) {
            return p;
        }
        vector<Point<T>> h;
        for(auto x : p) {
            while(h.size() >= 2 && cross(h.back() - h[h.size() - 2], x - h.back()) <= 0) {
                h.pop_back();
            }
            h.push_back(x);
        }
        int k = h.size();
        for(int i = int(p.size()) - 2; i >= 0; i--) {
            while(int(h.size()) > k &&
                  cross(h.back() - h[h.size() - 2], p[i] - h.back()) <= 0) {
                h.pop_back();
            }
            h.push_back(p[i]);
        }
        h.pop_back();
        return h;
    }
    auto lowest = [](const vector<Point<T>>& p) {
        int k = 0;
        for(int i = 1; i < int(p.size()); i++) {
            if(p[i].y < p[k].y || (p[i].y == p[k].y && p[i].x < p[k].x)) {
                k = i;
            }
        }
        return k;
    };
    auto edge = [](const vector<Point<T>>& p, int k) {
        return p[(k + 1) % int(p.size())] - p[k];
    };
    auto angleLess = [](const Point<T>& u, const Point<T>& v) {
        int su = sgn(u);
        int sv = sgn(v);
        if(su != sv) {
            return su > sv;
        }
        return cross(u, v) > 0;
    };
    int ia = lowest(a);
    int ib = lowest(b);
    vector<Point<T>> result;
    result.push_back(a[ia] + b[ib]);
    int i = 0, j = 0;
    while(i < n || j < m) {
        Point<T> ea = i < n ? edge(a, (ia + i) % n) : Point<T>(0, 0);
        Point<T> eb = j < m ? edge(b, (ib + j) % m) : Point<T>(0, 0);
        Point<T> take;
        if(i == n) {
            take = eb;
            j++;
        } else if(j == m) {
            take = ea;
            i++;
        } else if(angleLess(ea, eb)) {
            take = ea;
            i++;
        } else if(angleLess(eb, ea)) {
            take = eb;
            j++;
        } else {
            take = ea + eb;
            i++;
            j++;
        }
        Point<T> nxt = result.back() + take;
        while(int(result.size()) >= 2 &&
              cross(result.back() - result[int(result.size()) - 2], nxt - result.back()) <=
                  0) {
            result.pop_back();
        }
        result.push_back(nxt);
    }
    while(int(result.size()) >= 2 && cross(result.back() - result[int(result.size()) - 2],
                                           result[0] - result.back()) <= 0) {
        result.pop_back();
    }
    if(int(result.size()) >= 2 && result.front() == result.back()) {
        result.pop_back();
    }
    return result;
}
