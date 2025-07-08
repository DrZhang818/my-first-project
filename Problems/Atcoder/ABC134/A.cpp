#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 1E9 + 7;
void add(ll &x, ll y) {
    x = (x + y) % MOD;
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector dp(n + 1, vector<vector<ll>>(n + 1, vector<ll>(k + 1)));
    dp[1][0][0] = 1, dp[1][1][2] = 1;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            for(int s = 0; s <= k - 2 * (j - 1); s++) {
                if(s + 2 * j <= k) add(dp[i + 1][j][s + 2 * j], dp[i][j][s]);
                if(j) {
                    if(s + 2 * j <= k) add(dp[i + 1][j][s + 2 * j], j * dp[i][j][s] * 2);
                    if(s + 2 * (j - 1) <= k) add(dp[i + 1][j - 1][s + 2 * (j - 1)], j * j * dp[i][j][s]);
                }
                if(s + 2 * (j + 1) <= k) add(dp[i + 1][j + 1][s + 2 * (j + 1)], dp[i][j][s]);
            }
        }
    }    
    cout << dp[n][0][k] << "\n";
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
