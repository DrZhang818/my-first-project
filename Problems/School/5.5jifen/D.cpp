#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//
const int mx = 12720 * 2;
bitset<mx + 1> dp[81][81];
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1)), b(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> b[i][j];
            a[i][j] = abs(a[i][j] - b[i][j]);
        }
    }
    dp[0][1][mx / 2] = 1;
    dp[1][0][mx / 2] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int k = a[i][j];
            dp[i][j] = dp[i - 1][j] << k | dp[i - 1][j] >> k | dp[i][j - 1] << k | dp[i][j - 1] >> k;
        }
    }   
    int ans = inf; 
    for(int i = dp[n][m]._Find_first(); i <= mx; i = dp[n][m]._Find_next(i)) {
        ans = min(ans, abs(i - mx / 2));
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;

    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
