#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://ac.nowcoder.com/acm/contest/24213/1016
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector dp(n + 1, vector<ll>(m + 1, -inf));
    for(int i = 0; i <= n; i++) dp[i][0] = 0;
    for(int i = 1; i <= n; i++) {
        if(i <= k) {
            dp[i][1] = max(dp[i - 1][1], (ll)a[i]);
            continue;
        }
        for(int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i - k][j - 1] + a[i]);
        }
    }
    cout << dp[n][m] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
