#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const db eps = 1e-9;

//https://atcoder.jp/contests/abc157/tasks/abc157_f
/*
    计算几何 || 二分
    题意:
        在二维平面上有N个点(x_i,y_i), 每个点有个权重系数c_i, 保证任意两点位置不同
        你需要选择一个中心点O(X,Y), 每个点的权重为c_i * d(<X,Y>, <x_i,y_i>)
        d表示欧几里得距离
        现在给定一个整数k, 请你最小化第K小的权重, 并输出答案
        范围: N∈[1,60], K∈[1,N], x_i,y_i∈[-1000,1000], c_i∈[1,100]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 最小化第K小这个问题显然具有单调性, 我们可以二分一个答案x
        验证能否有至少K个点的权重 <= x
        将权重计算移项得: d <= x / c, 这表示只要(x_i,y_i)处于以O为圆心,x/c为半径的园内即可
        问题就变为了: 是否存在一点被至少K个圆覆盖
        (1)考虑平凡情况, 当K = 1时, 答案显然是存在
        (2)当K >= 2时, 情况就有些复杂, 因为实数的不可枚举的, 这是计算几何问题的常见问题
            解决的方法是寻找特殊点, 对于本题来说, 只考虑两个圆的交点以及每个圆的圆心, 就足以覆盖
            所有情况
            证明: 我们考虑任意一个至少被K个圆覆盖的区域, 加入区域内存在某个圆的圆心, 那么这个圆心
                  就会探测出这个区域; 如果不存在圆心, 那么这个区域一定是这K个圆相交构成的, 那么
                  探测交点的时候就会探测出这个区域
        剩下的问题就是如何求解两个圆的交点了, 这是个经典的计算几何模板题
        我们可以用公共弦法求解这个问题
        首先求出两个圆心间的距离d, 判断包含/相离关系
        设点p0为连接两圆心的线段与公共弦的交点
        设l为圆心O1到p0的距离, h为p0到交点的距离, r1为圆O1的半径
        经过代数推导, l = (r1*r1 - r2*r2 + d*d) / (2*d)
        则由勾股定理, h = sqrt(r1*r1 - l*l)
        求解p0位置需要求出单位向量e
        e_x = (x2 - x1) / d, e_y = (y2 - y1) / d
        则p0 = (x1,y1) + l * e
        求解交点需要知道与e正交的单位向量rx(-e_y, e_x)和(e_y, -e_x), 这里取前者即可
        则交点为p0 +- h*rx
*/
struct Point {
    db x, y;
    Point() : x(0), y(0) {}
    Point(db a, db b) : x(a), y(b) {}
    friend db dist(const Point &a, const Point &b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};
struct Circle {
    Point O;
    db r;
    friend vector<Point> Intersect(const Circle &a, const Circle &b) {
        vector<Point> res;
        db d = dist(a.O, b.O);
        if(d > a.r + b.r + eps || d < abs(a.r - b.r) - eps) {
            return res;
        }
        db l = (a.r * a.r - b.r * b.r + d * d) / (2 * d);
        db h = sqrt(a.r * a.r - l * l);
        db e_x = (b.O.x - a.O.x) / d, e_y = (b.O.y - a.O.y) / d;
        Point p0(a.O.x + l * e_x, a.O.y + l * e_y);
        db rx = -h * e_y, ry = h * e_x;
        if(h < eps) {
            res.push_back(Point(p0.x + rx, p0.y + ry));
        } else {
            res.push_back(Point(p0.x + rx, p0.y + ry));
            res.push_back(Point(p0.x - rx, p0.y - ry));
        }
        return res;
    }
    friend bool inCircle(const Point &a, const Circle &b) {
        return b.r - dist(a, b.O) > -eps;
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<Circle> a(n + 1);
    vector<int> c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].O.x >> a[i].O.y >> c[i];
    }   
    auto ck = [&](db t) -> bool {
        vector<Point> P;
        for(int i = 1; i <= n; i++) {
            a[i].r = t / c[i];
            P.push_back(Point(a[i].O.x, a[i].O.y));
        }
        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                vector<Point> vec = Intersect(a[i], a[j]);
                for(int k = 0; k < vec.size(); k++) {
                    P.push_back(vec[k]);
                }
            }
        }
        for(int i = 0; i < P.size(); i++) {
            int cnt = 0;
            for(int j = 1; j <= n; j++) {
                if(inCircle(P[i], a[j])) {
                    cnt++;
                }
            }
            if(cnt >= k) {
                return true;
            }
        }
        return false;
    };
    db l = 0, r = 300000;
    for(int i = 1; i <= 60; i++) {
        db mid = (l + r) / 2;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << fixed << setprecision(9) << r << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
