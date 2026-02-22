#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

struct Point {
    i64 x, y;
    Point& operator+=(const Point& a) & {
        x += a.x;
        y += a.y;
        return *this;
    }
    Point& operator-=(const Point& a) & {
        x -= a.x;
        y -= a.y;
        return *this;
    }
    friend Point operator+(Point a, const Point& b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point& b) {
        return a -= b;
    }
};

i64 dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

i128 cross(const Point& a, const Point& b) {
    return i128(a.x) * b.y - i128(a.y) * b.x;
}

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> x(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    vector<int> a(n), b(n);
    for(int i = 1; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i < n; i++) {
        cin >> b[i];
    }

    vector<i64> dp(n + 1, inf);
    dp[0] = 0;

    vector<Point> q(n + 5);

    for(int s = 0; s <= k; s++) {
        int front = 0, tail = 0;

        for(int i = 1; i <= n; i++) {
            Point u(-2 * x[i], 1);

            while(front + 1 < tail && dot(u, q[front]) >= dot(u, q[front + 1])) {
                front++;
            }

            Point v = q[front];

            Point cur(x[i], 1LL * x[i] * x[i] + dp[i] + b[i]);

            dp[i] = min(dp[i], dot(u, v) + 1LL * x[i] * x[i]);
            dp[i] = min(dp[i], dp[i - 1] + a[i - 1]);

            while(front + 1 < tail && cross(q[tail - 1] - q[tail - 2], cur - q[tail - 1]) <= 0) {
                tail--;
            }

            q[tail++] = cur;
        }
    }

    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
