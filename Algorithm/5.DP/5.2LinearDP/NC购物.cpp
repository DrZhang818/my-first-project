#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/24213/1015
void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
        sort(a[i].begin() + 1, a[i].end());
        for(int j = 1; j <= m; j++) {
            a[i][j] += a[i][j - 1];
        }
    }
    vector dp(n + 1, vector<int>(n + 5, inf));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            for(int k = max(0, 1 - j); k <= m && k <= n + 1 - j; k++) {
                dp[i][j + k - 1] = min(dp[i][j + k - 1], dp[i - 1][j] + a[i][k] + k * k);
            }
        }
    }
    cout << dp[n][0] << "\n";
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
