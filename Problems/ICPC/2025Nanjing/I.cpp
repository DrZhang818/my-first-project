#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr i64 inf = 1E18;

template <typename T>
void chmax(T& x, const T& y) {
    if(x < y) x = y;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), b(n + 1), c(n + 1), d(n + 1), e(n + 1), p(n + 1);

    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i] >> e[i] >> p[i];
    }

    vector<array<db, 4>> dp(m + 1);

    for(int i = n; i >= 1; i--) {
        vector<array<db, 4>> ndp(m + 1, {-inf, -inf, -inf, -inf});
        for(int j = 0; j <= m; j++) {
            if(j >= e[i] + d[i]) {
                chmax(ndp[j][3], dp[j - e[i] - d[i]][0] + c[i]);
            }
            if(j >= b[i]) {
                chmax(ndp[j][3], dp[j - b[i]][3] + a[i]);
            }
            if(j >= d[i]) {
                chmax(ndp[j][0], db(p[i]) / 100 * (dp[j - d[i]][1] + c[i]) + db(100 - p[i]) / 100 * (dp[j - d[i]][2] + c[i]));

                chmax(ndp[j][1], db(p[i]) / 100 * (dp[j - d[i]][1] + c[i]) + db(100 - p[i]) / 100 * (dp[j - d[i]][3] + c[i]));

                chmax(ndp[j][2], db(100 - p[i]) / 100 * (dp[j - d[i]][2] + c[i]) + db(p[i]) / 100 * (dp[j - d[i]][3] + c[i]));
            }
            if(j >= b[i]) {
                chmax(ndp[j][0], db(p[i]) / 100 * (dp[j - b[i]][1] + a[i]) + db(100 - p[i]) / 100 * (dp[j - b[i]][2] + a[i]));

                chmax(ndp[j][1], db(p[i]) / 100 * (dp[j - b[i]][1] + a[i]) + db(100 - p[i]) / 100 * (dp[j - b[i]][3] + a[i]));

                chmax(ndp[j][2], db(100 - p[i]) / 100 * (dp[j - b[i]][2] + a[i]) + db(p[i]) / 100 * (dp[j - b[i]][3] + a[i]));
            }
        }
        dp = move(ndp);
    }

    if(dp[m][0] < 0) {
        cout << -1 << "\n";
        return;
    }

    cout << fixed << setprecision(12) << dp[m][0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}