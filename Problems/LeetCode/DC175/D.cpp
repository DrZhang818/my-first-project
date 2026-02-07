#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

template<class T>
struct Point {
    T x;
    T y;
    Point(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_) {}
    
    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(const Point &p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(const Point &p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(const T &v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point &operator/=(const T &v) & {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, const Point &b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point &b) {
        return a -= b;
    }
    friend Point operator*(Point a, const T &b) {
        return a *= b;
    }
    friend Point operator/(Point a, const T &b) {
        return a /= b;
    }
    friend Point operator*(const T &a, Point b) {
        return b *= a;
    }
    friend bool operator==(const Point &a, const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T> &a_ = Point<T>(), const Point<T> &b_ = Point<T>()) : a(a_), b(b_) {}
};

template<class T>
T dot(const Point<T> &a, const Point<T> &b) {
    return a.x * b.x + a.y * b.y;
}

using i128 = __int128;

template<class T>
i128 cross(const Point<T> &a, const Point<T> &b) {
    return static_cast<i128>(a.x) * b.y - static_cast<i128>(a.y) * b.x;
}

class Solution {
public:
    ll minPartitionScore(vector<int>& a, int k) {
        int n = a.size();
        vector<ll> pre(n + 1);
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + a[i - 1];
        }

        vector<ll> dp(n + 1, inf);

        dp[0] = 0;
        vector<Point<ll>> q(n + 1);

        for(int j = 1; j <= k; j++) {
            int l = 0, r = 0;

            ll s = pre[j - 1];
            q[r++] = Point<ll>(s, s * s - s + dp[j - 1]);

            for(int i = j; i + (k - j) <= n; i++) {
                s = pre[i];
                Point<ll> p(-2 * s, 1);

                while(r - l > 1 && dot(p, q[l]) >= dot(p, q[l + 1])) {
                    l++;
                }

                Point<ll> v(s, s * s - s + dp[i]);
                dp[i] = dot(p, q[l]) + s * s + s;

                while(r - l > 1 && cross(q[r - 1] - q[r - 2], v - q[r - 1]) <= 0) {
                    r--;
                }

                q[r++] = v;
            }
        }

        return dp[n] / 2;
    }
};