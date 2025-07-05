#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const db eps = 1e-8;

//https://www.luogu.com.cn/problem/UVA10263
/*
    计算几何
    题意:
        给定一个点M和由N+1个点依次连接构成的类曲线图(N条线段)
        你需要求出曲线上离M最近的P点坐标(P可以在任意一条线段上)
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 我们有个很朴素的暴力方法: 求出点M到每条线段的最短距离,
        取其中最小的一个就是P点所在线段, 再进一步求出P点在哪
        因此核心问题就是如何求解点到线段的最短距离
        我们可以把这个问题转化成点到点的距离
        设线段两个端点为a,b, 我们要求点p到线段a,b的最短距离d(p,a,b)
        (1)若a = b, 那么转化成点到点的距离d(p,a)
        (2)若a != b
            设x = p - a, y = p - b, z = b - a
            <1>若dot(x,z) < 0, 说明p的垂线与线段无交点, 且p离a更近
                转化为d(p,a)
            <2>若dot(y,z) > 0, 说明p的垂线与线段无交点, 且p离b更近
                转化为d(p,b)
            <3>p的垂线与线段有交点, 此时要求出垂足o
                转化为d(p,o)
        垂足的求法:
            设x = p - a, y = p - b, z = b - a
            我们要利用p在向量ab上的投影来算出比例系数, 通过偏移找到垂足
            len = dot(x,z) / length(z)  这是|ao|
            tot = length(z)             这是|bo|
            o = a + z * (len1 / length(z))
        两点间距离的求法
            求解d(x,y)
            令z = y - x, 转化为length(z)
*/
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
        if(u.x < a.x && v.x >= a.x && pointOnLineLeft(a, line(v, u))) {
            t ^= 1;
        }
        if(u.x >= a.x && v.x < a.x && pointOnLineLeft(a, line(u, v))) {
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
    int n;
    cin >> n;
    vector<Point<db>> a(n + 2);
    for(int i = 1; i <= n + 1; i++) {
        cin >> a[i];
    }
    Point<db> ans = a[1];
    for(int i = 1; i <= n; i++) {
        Point<db> cur = dis_PL(m, a[i], a[i + 1]);
        if(dcmp(length(m - cur) - length(m - ans)) < 0) ans = cur;
    }
    cout << fixed << setprecision(4) << ans.x << "\n" << ans.y << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> m) {
        solve();
    }
    return 0;
}
