#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(n & 1) {
        cout << -1 << "\n";
        return;
    }
    vector dp(n + 1, vector<ll>(n + 1, inf));
    for(int len = 2; len <= n; len += 2) {
        for(int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            for(int k = i + 1; k <= j; k += 2) {
                if(s[k] == s[i]) {
                    dp[i][j] = min(dp[i][j], (i + 1 > k - 1 ? 0 : dp[i + 1][k - 1]) + (k + 1 > j ? 0 : dp[k + 1][j]) + 1LL * a[i] * a[k]);
                }
            }
        }
    }
    if(dp[1][n] == inf) {
        cout << -1 << "\n";
        return;
    }
    cout << dp[1][n] << "\n";
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
