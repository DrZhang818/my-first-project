#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 998244353;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> dp(m + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = m; j >= 1; j--) {
            dp[j] = dp[j] * j % MOD;
            dp[j] += dp[j - 1] * (m - j + 1) % MOD;
            dp[j] %= MOD;
        }
        dp[0] = 0;
    }
    cout << dp[m] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
