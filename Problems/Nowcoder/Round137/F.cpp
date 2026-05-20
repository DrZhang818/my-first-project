#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    
    int S = pre[n];
    int M = sqrt(S);
    vector<vector<int>> dp(S + 1, vector<int>(M + 1, inf));
    dp[0][0] = 0;

    for(int i = 1; i <= n; i++) {
        vector<vector<int>> ndp(S + 1, vector<int>(M + 1, inf));
        for(int j = 0; j <= S; j++) {
            int mn = inf;
            for(int k = 0; k <= M && j + k * k <= S; k++) {
                mn = min(mn, dp[j][k]);
                ndp[j + k * k][k] = min(ndp[j + k * k][k], mn + abs(j + k * k - pre[i]));
            }
        }
        dp = move(ndp);
    }

    int ans = *min_element(dp[S].begin(), dp[S].end());
    if(ans == inf) {
        ans = -1;
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
