#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Point {
    ll x, y;
    Point& operator-=(const Point& p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    friend Point operator-(Point a, const Point& b) {
        return a -= b;
    }
};

using i128 = __int128;

ll dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

i128 cross(const Point& a, const Point& b) {
    return i128(a.x) * b.y - i128(a.y) * b.x;
}

struct Info {
    ll x, y, w;
};

void solve() {  
    int n;
    cin >> n;
    vector<Info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].w;
    }
    sort(a.begin() + 1, a.end(), 
        [&](auto u, auto v) {
            return u.x < v.x;
        });

    vector<Point> q(n + 2);
    int l = 0, r = 0;
    q[r++] = Point(0, 0);

    ll ans = 0;
    ll dp = 0;
    for(int i = 1; i <= n; i++) {
        Point p(a[i].y, 1);
        while(r - l > 1 && dot(p, q[l]) <= dot(p, q[l + 1])) {
            l++;
        }

        dp = dot(p, q[l]) + a[i].x * a[i].y - a[i].w;
        ans = max(ans, dp);
        Point v(-a[i].x, dp);

        while(r - l > 1 && cross(q[r - 1] - q[r - 2], v - q[r - 1]) <= 0) {
            r--;
        }

        q[r++] = v;
    }
    cout << ans << "\n";
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
