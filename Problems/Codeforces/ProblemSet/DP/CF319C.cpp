#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

using i128 = __int128;

struct Point {
    ll x, y;
    Point& operator+=(const Point& p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point& operator-=(const Point& p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    friend Point operator+(Point a, const Point& b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point& b) {
        return a -= b;
    }
};

ll dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

i128 cross(const Point& a, const Point& b) {
    return i128(a.x) * b.y - i128(a.y) * b.x;
}

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<Point> q(n + 1);
    int l = 0, r = 0;
    q[r++] = Point(-b[1], 0);

    ll dp = 0;
    for(int i = 2; i <= n; i++) {
        Point p(-a[i], 1);
        while(r - l > 1 && dot(p, q[l]) >= dot(p, q[l + 1])) {
            l++;
        }

        dp = dot(p, q[l]);
        Point v(-b[i], dp);

        while(r - l > 1 && cross(q[r - 1] - q[r - 2], v - q[r - 1]) <= 0) {
            r--;
        }
        q[r++] = v;
    }

    cout << dp << "\n";
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
