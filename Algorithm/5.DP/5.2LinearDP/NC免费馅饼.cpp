#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<ll>(1000 + m));
    m--;
    int t, x, v;
    ll w;
    int mx = 0; 
    while(cin >> t >> x >> v >> w) {
        if(m % v) continue;
        a[x][t + m / v] += w;
        mx = max(mx, t + m / v);
    }
    vector dp(mx + 1, vector<ll>(n + 1, -inf));
    dp[0][(n + 1) / 2] = a[(n + 1) / 2][0];
    for(int i = 1; i <= mx; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = max(1, j - 2); k <= min(n, j + 2); k++) {
                dp[i][j] = max(dp[i][j], dp[i - 1][k] + a[j][i]);
            }
        }
    }
    ll ans = 0;
    int id = 1;
    for(int i = 1; i <= n; i++) {
        if(dp[mx][i] > ans) {
            ans = dp[mx][i];
            id = i;
        }
    }
    cout << ans << "\n";
    vector<int> op(mx + 1);
    int c = 0;
    for(int i = mx, j = id; i >= 1; i--, j = id) {
        ll cmx = -1;
        for(int k = max(1, j - 2); k <= min(n, j + 2); k++) {
            if(dp[i - 1][k] > cmx) {
                cmx = dp[i - 1][k];
                id = k;
            }
        }
        op[++c] = j - id;
    }
    for(int i = c; i >= 1; i--) {
        cout << op[i] << "\n";
    }
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
