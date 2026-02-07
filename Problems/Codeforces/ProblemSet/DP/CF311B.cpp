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
    int n, m, p;
    cin >> n >> m >> p;
    vector<ll> d(n + 1);
    for(int i = 2; i <= n; i++) {
        cin >> d[i];
        d[i] += d[i - 1];
    }     

    vector<ll> t(m + 1);
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x >> t[i];
        t[i] -= d[x];
    }
    sort(t.begin() + 1, t.end());

    vector<ll> pre(m + 1);
    for(int i = 1; i <= m; i++) {
        pre[i] = pre[i - 1] + t[i];
    }

    vector<ll> dp(m + 1, numeric_limits<ll>::max() / 2);
    dp[0] = 0;

    vector<Point> q(m + 2);
    for(int k = 1; k <= p; k++) {
        int l = 0, r = 0;
        q[r++] = Point(0, 0);

        for(int i = 1; i <= m; i++) {
            Point u(-t[i], 1);
            while(r - l > 1 && dot(u, q[l]) >= dot(u, q[l + 1])) {
                l++;
            }

            Point v(i, pre[i] + dp[i]);
            dp[i] = dot(u, q[l]) + 1LL * i * t[i] - pre[i];
            
            while(r - l > 1 && cross(q[r - 1] - q[r - 2], v - q[r - 1]) <= 0) {
                r--;
            }
            q[r++] = v;
        }
    }

    cout << dp[m] << "\n";
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
