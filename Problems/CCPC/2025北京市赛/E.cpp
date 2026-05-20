#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;

    vector<int> x(n + 1), y(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    int a, b, c;
    cin >> a >> b >> c;

    auto calc = [&](db X, db Y) -> db {
        db res = 0;
        for(int i = 1; i <= n; i++) {
            res = max(res, hypot(X - x[i], Y - y[i]));
        }
        return res;
    };

    db l = -inf, r = inf;
    db ans = 1E18;

    for(int t = 0; t < 100; t++) {
        db lo = l + (r - l) / 3;
        db hi = r - (r - l) / 3;

        db x = b == 0 ? db(-c) / a : lo;
        db y = b == 0 ? lo : db(1LL * a * x + c) / (-b);
        db dis1 = calc(x, y);

        x = b == 0 ? db(-c) / a : hi;
        y = b == 0 ? hi : db(1LL * a * x + c) / (-b);
        db dis2 = calc(x, y);

        if(dis1 < dis2) {
            r = hi;
            ans = min(ans, dis1);
        } else {
            l = lo;
            ans = min(ans, dis2);
        }
    }

    cout << fixed << setprecision(12) << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}