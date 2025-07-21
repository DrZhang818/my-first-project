#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector dp(m + 1, vector<ll>(n));
    dp[0][0] = 1;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            dp[i + 1][(j - 1 + n) % n] += dp[i][j];
            dp[i + 1][(j + 1) % n] += dp[i][j];
        }
    }
    cout << dp[m][0] << "\n";
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
