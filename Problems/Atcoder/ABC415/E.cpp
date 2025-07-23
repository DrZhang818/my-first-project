#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    int k = n + m - 1;
    vector<int> p(k + 1);
    for(int i = 1; i <= k; i++) {
        cin >> p[i];
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            a[i][j] -= p[i + j - 1];
        }
    }
    auto ck = [&](ll x) -> bool {
        if(x + a[1][1] < 0) return false;
        vector dp(n + 1, vector<ll>(m + 1, -1));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(i == 1 && j == 1) {
                    dp[i][j] = x + a[i][j];
                } else {
                    if(dp[i - 1][j] != -1) {
                        if(dp[i - 1][j] + a[i][j] >= 0) {
                            dp[i][j] = dp[i - 1][j] + a[i][j];
                        }
                    }
                    if(dp[i][j - 1] != -1) {
                        if(dp[i][j - 1] + a[i][j] >= 0) {
                            dp[i][j] = max(dp[i][j], dp[i][j - 1] + a[i][j]);
                        }
                    }
                }   
            }
        }
        return dp[n][m] != -1;
    };  
    ll l = -1, r = inf;
    while(l + 1 < r) {
        ll mid = l + (r - l) / 2;
        if(ck(mid)) {
            r = mid; 
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
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
