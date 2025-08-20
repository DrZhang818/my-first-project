#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int m, n;
    cin >> m >> n;
    vector<int> c0(m + 1), c1(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> c0[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> c1[i];
    }
    vector x(m + 1, vector<int>(m + 1));
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= m; j++) {
            x[i][j] = (1LL * c0[j] * (c0[i] + c1[i]) % MOD + 1LL * c1[j] * c0[i] % MOD) % MOD;
        }
    }
    vector<int> dp(m + 1);
    dp[1] = 1;
    for(int t = 0; t < n; t++) {
        vector<int> ndp(m + 1);
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= m; j++) {
                add(ndp[j], 1LL * dp[i] * x[i][j] % MOD);
            }
        }
        swap(dp, ndp);
    }    
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        add(ans, dp[i]);
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
