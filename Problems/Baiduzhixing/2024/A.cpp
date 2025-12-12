#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector b(n, vector<ll>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }

    ll w[n][n][n];
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                w[i][j][k] = max({a[i], a[j], a[k], b[i][j], b[j][k], b[i][k], b[i][j] * b[i][k] * b[j][k]});
            }
        }
    }

    vector<ll> dp(1 << n);

    for(int i = 3; i <= n; i += 3) {
        for(int s = 0; s < 1 << n; s++) {
            if(__builtin_popcount(s) != i) continue;
            for(int i = 0; i < n; i++) {
                if(~s >> i & 1) continue;
                for(int j = i + 1; j < n; j++) {
                    if(~s >> j & 1) continue;
                    for(int k = j + 1; k < n; k++) {
                        if(~s >> k & 1) continue;
                        dp[s] = max(dp[s], dp[s & ~(1 << i) & ~(1 << j) & ~(1 << k)] + w[i][j][k]);
                    }
                }
            }
        }
    }
    cout << dp[(1 << n) - 1] << "\n";
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
