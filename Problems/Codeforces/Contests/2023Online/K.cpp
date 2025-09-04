#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const db eps = 1e-8;

int dcmp(db x) { return x < -eps ? -1 : (x > eps ? 1 : 0); }
template<class T>
struct Point {
    T x;
    T y;
    Point(T a = 0, T b = 0) : x(a), y(b) {}

    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(Point p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(Point p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(T v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, Point b) {
        return a += b;
    }
    friend Point operator-(Point a, Point b) {
        return a -= b;
    }
    friend Point operator*(Point a, T b) {
        return a *= b;
    }
    friend Point operator*(T a, Point b) {
        return b *= a;
    }
    friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }
    friend istream &operator>>(istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend ostream &operator<<(ostream &os, Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
T square(Point<T> p) {
    return dot(p, p);
}

template<class T>
double length(Point<T> p) {
    return sqrt(double(square(p)));
}

long double length(Point<long double> p) {
    return sqrt(square(p));
}

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()) : a(a_), b(b_) {}
};

template<class T>
Point<T> rotate(Point<T> a) {
    return Point(-a.y, a.x);
}

template<class T>
int sgn(Point<T> a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

template<class T>
bool pointOnLineLeft(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

template<class T>
Point<T> lineInsection(Line<T> l1, Line<T> l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<class T>
bool pointOnSegment(Point<T> p, Line<T> l) {
    return cross(p - l.a, l.b - l.a) == 0 && min(l.a.x, l.b.x) <= p.x && p.x <= max(l.a.x, l.b.x)
        && min(l.a.y, l.b.y) <= p.y && p.y <= max(l.a.y, l.b.y);
}

template<class T>
bool pointInPolygon(Point<T> a, vector<Point<T>> p) {
    int n = p.size();
    for(int i = 0; i < n; i++) {
        if(pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    int t = 0;
    for(int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if(u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if(u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    return t == 1;
}

template<class T>
Point<T> FootPoint(Point<T> p, Point<T> a, Point<T> b) {
    Point<T> x = p - a, y = p - b, z = b - a;
    db len1 = dot(x, z) / length(z);
    return a + z * (len1 / length(z));
}

template<class T>
Point<T> dis_PL(Point<T> p, Point<T> a, Point<T> b) {
    if(a == b) return a;
    Point<T> x = p - a, y = p - b, z = b - a;
    if(dcmp(dot(x, z)) < 0) return a;
    if(dcmp(dot(y, z)) > 0) return b;
    return FootPoint(p, a, b);
}
Point<db> m;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<Point<db>> P(n);
    for(int i = 0; i < n; i++) {
        cin >> P[i];
    }
    while(q--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        m.x = (a + c) / 2.0;
        m.y = (b + d) / 2.0;
        db R_2 = ((a - c) * (a - c) + (b - d) * (b - d)) / 4.0;
        if(pointInPolygon(m, P)) {
            cout << fixed << setprecision(12) << R_2 / 2.0 << "\n";
            continue;
        }
        Point<db> ans = P[0];
        for(int i = 0; i < n; i++) {
            Point<db> cur = dis_PL(m, P[i], P[(i + 1) % n]);
            if(dcmp(length(m - cur) - length(m - ans)) < 0) ans = cur;
        }
        db r_2 = length(m - ans) * length(m - ans);
        cout << fixed << setprecision(12) << R_2 / 2.0 + r_2 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
