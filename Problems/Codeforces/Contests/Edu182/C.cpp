#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<array<int,2>> dp(n + 1);
    dp[1][0] = dp[1][1] = 1;
    for(int i = 2; i <= n; i++) {
        if(a[i] >= a[i - 1] && b[i] >= b[i - 1]) {
            add(dp[i][0], dp[i - 1][0]);
        }
        if(b[i] >= a[i - 1] && a[i] >= b[i - 1]) {
            add(dp[i][1], dp[i - 1][0]);
        }
        if(a[i] >= b[i - 1] && b[i] >= a[i - 1]) {
            add(dp[i][0], dp[i - 1][1]);
        }
        if(b[i] >= b[i - 1] && a[i] >= a[i - 1]) {
            add(dp[i][1], dp[i - 1][1]);
        }
    }
    int ans = (dp[n][0] + dp[n][1]) % MOD;
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
