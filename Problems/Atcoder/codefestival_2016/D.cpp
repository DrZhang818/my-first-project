#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    auto calc = [&](int x, int y) {
        vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, numeric_limits<ll>::max()));
        for(int i = 1; i <= n + 1; i++) {
            dp[i][n + 1] = dp[n + 1][i] = 0;
        }

        vector<vector<int>> f(n + 1, vector<int>(n + 1));
        vector<vector<int>> g(n + 1, vector<int>(n + 1));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; i + j - 1 <= n; j++) {
                f[i][j] = f[i][j - 1] + (a[j][x] == a[i + j - 1][y]);
                g[i][j] = g[i][j - 1] + (a[j][y] == a[i + j - 1][x]);
            }
        }

        for(int i = n; i >= 1; i--) {
            for(int j = n; j >= 1; j--) {
                dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]);
                if(i >= j) {
                    dp[i][j] += f[i - j + 1][n - i + 1];
                } else {
                    dp[i][j] += g[j - i + 1][n - j + 1];
                }
            }
        }

        return dp[1][1];
    };

    ll ans = 0;

    for(int j = 2; j <= m; j++) {
        ans += calc(j - 1, j);
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
