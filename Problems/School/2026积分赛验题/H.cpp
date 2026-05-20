#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

template <typename T>
void chmin(T& x, const T& y) {
    if(x > y) {
        x = y;
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    vector<array<i64, 200>> dp(m);
    for(int i = 0; i < m; i++) {
        fill(dp[i].begin(), dp[i].end(), inf);
        dp[i][0] = 1LL * i * k + a[0][i];
    }

    for(int i = 0; i < n; i++) {
        vector<i64> mn(m, inf);
        for(int j = 0; j < m; j++) {
            for(int p = 0; p < m - 1; p++) {
                chmin(dp[j][p + 1], dp[j][p] + a[i][(j + p + 1) % m]);
            }
            for(int p = 0; p < m; p++) {
                chmin(mn[p], dp[j][p]);
            }
        }
        if(i + 1 < n) {
            vector<array<i64, 200>> ndp(m);
            for(int j = 0; j < m; j++) {
                fill(ndp[j].begin(), ndp[j].end(), inf);
                for(int p = 0; p < m; p++) {
                    chmin(ndp[j][p], mn[p] + 1LL * j * k + a[i + 1][(j + p) % m]);
                }
            }
            dp = move(ndp);
        }
    }

    i64 ans = inf;
    for(int i = 0; i < m; i++) {
        chmin(ans, dp[i][m - 1]);
    }

    cout << ans << "\n";
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
