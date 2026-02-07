#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

using i128 = __int128;

struct Point {
    i128 x, y;
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

i128 dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

i128 cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}
    
void print(i128 x) {
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

void solve() {  
    int n, L;
    cin >> n >> L;
    L++;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<i128> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }

    for(int i = 1; i <= n; i++) {
        pre[i] += i;
    }

    vector<i128> dp(n + 1, numeric_limits<i128>::max() / 2);
    dp[0] = 0;

    vector<Point> q(n + 5);
    int l = 0, r = 0;

    q[r++] = Point(0, 0);
    
    for(int i = 1; i <= n; i++) {
        auto s = pre[i];
        Point p(-2 * s, 1);
        while(r - l > 1 && dot(p, q[l]) >= dot(p, q[l + 1])) {
            l++;
        }

        dp[i] = dot(p, q[l]) + (s - L) * (s - L);
        Point v(s, s * s + s * L * 2 + dp[i]);

        while(r - l > 1 && cross(q[r - 1] - q[r - 2], v - q[r - 1]) <= 0) {
            r--;
        }

        q[r++] = v;
    }

    print(dp[n]);
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
