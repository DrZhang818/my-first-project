#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

/*
    00 0
    01 1
    02 2
    11 3
    12 4
    22 5
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    string s;
    cin >> s;
    s = "#" + s;
    using T = array<array<ll,6>,3>;
    T dp;
    for(int i = 0; i < 3; i++) {
        fill(dp[i].begin(), dp[i].end(), 0);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        T ndp = dp;
        if(s[i] == 'M') {
            ndp[0][a[i]]++;
        } else if(s[i] == 'E') {
            if(a[i] == 0) {
                ndp[1][0] += dp[0][0];
                ndp[1][1] += dp[0][1];
                ndp[1][2] += dp[0][2];
            } else if(a[i] == 1) {
                ndp[1][1] += dp[0][0];
                ndp[1][3] += dp[0][1];
                ndp[1][4] += dp[0][2];
            } else {
                ndp[1][2] += dp[0][0];
                ndp[1][4] += dp[0][1];
                ndp[1][5] += dp[0][2];
            }
        } else {
            if(a[i] == 0) {
                ans += dp[1][0] + dp[1][2] + dp[1][5];
                ans += 2 * (dp[1][1] + dp[1][3]);
                ans += 3 * dp[1][4];
            } else if(a[i] == 1) {
                ans += 2 * (dp[1][0] + dp[1][1]);
                ans += 3 * dp[1][2];
            } else {
                ans += dp[1][0] + dp[1][2];
                ans += 3 * dp[1][1];
            }
        }
        swap(dp, ndp);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
