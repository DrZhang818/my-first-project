#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector dp(n + 1, vector<ll>(k + 1, inf));
    for(int j = 0; j <= k; j++) {
        dp[0][j] = 0;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            ll mn = inf;
            for(int v = 0; v <= j && i - 1 - v >= 0; v++) {
                mn = min(mn, a[i - v]);
                dp[i][j] = min(dp[i][j], dp[i - 1 - v][j - v] + (v + 1) * mn);
            }
        }
    }
    cout << dp[n][k] << "\n";
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
