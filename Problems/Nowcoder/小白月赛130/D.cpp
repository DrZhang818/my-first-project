#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        vis[x] = true;
    }
    
    int mex = 0;
    while(vis[mex]) {
        mex++;
    }

    vector<vector<int>> dp(k + 1, vector<int>(n + 1));
    dp[0][mex] = 1;

    for(int i = 1; i <= k; i++) {
        vector<int> d(n + 2);
        for(int j = 0; j <= n; j++) {
            add(dp[i][j], 1LL * dp[i - 1][j] * j % MOD);
            add(d[j + 1], dp[i - 1][j]);
        }
        for(int j = 1; j <= n; j++) {
            add(d[j], d[j - 1]);
            add(dp[i][j], d[j]);
        }
    }

    for(int x = 0; x <= n; x++) {
        int ans = 0;
        for(int t = 0; t <= k; t++) {
            add(ans, dp[t][x]);
        }
        cout << ans << " \n"[x == n];
    }
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
