#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 2333;

void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector dp(n + 2, vector<int>(m + 2));
    dp[n][1] = 1;
    for(int i = n; i >= 1; i--) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] || i == n && j == 1) continue;
            dp[i][j] = (dp[i + 1][j] + dp[i][j - 1]) % MOD;
        }
    }
    cout << dp[1][m] << "\n";
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
