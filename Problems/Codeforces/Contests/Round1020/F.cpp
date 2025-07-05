#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<vector<ll>> dp(n + 1, vector<ll>(2, 0));
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0') {
            dp[i][0] = dp[i - 1][0] + i - 1;
            dp[i][1] = dp[i - 1][1] + n - i;
        } else {
            dp[i][0] = dp[i - 1][1] + 1;
            dp[i][1] = 0;
        }
        ans = max({ans, dp[i][0], dp[i][1]});
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
