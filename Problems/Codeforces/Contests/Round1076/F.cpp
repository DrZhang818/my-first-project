#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

void solve() {  
    int n, sx, sy, tx, ty;
    cin >> n >> sx >> sy >> tx >> ty;
    map<int,int> lo, hi;
    vector<int> val {0};
    val.push_back(sx);
    val.push_back(tx);
    vector<int> X(n + 1), Y(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> X[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> Y[i];
    }
    for(int i = 1; i <= n; i++) {
        int x = X[i], y = Y[i];
        val.push_back(x);
        if(!lo.contains(x)) {
            lo[x] = y;
            hi[x] = y;
        } else {
            lo[x] = min(lo[x], y);
            hi[x] = max(hi[x], y);
        }
    }
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());
    lo[sx] = sy;
    hi[sx] = sy;
    lo[tx] = ty;
    hi[tx] = ty;
    int m = val.size() - 1;
    vector<array<ll,2>> dp(m + 1, {inf,inf});
    dp[1][0] = dp[1][1] = 0;
    int las = val[1];
    for(int i = 2; i <= m; i++) {
        int x = val[i];
        int loy = lo[x], hiy = hi[x];
        ll dis = hiy - loy;
        dp[i][0] = min(dp[i - 1][0] + abs(hiy - lo[las]), dp[i - 1][1] + abs(hiy - hi[las])) + (x - las) + dis;
        dp[i][1] = min(dp[i - 1][0] + abs(loy - lo[las]), dp[i - 1][1] + abs(loy - hi[las])) + (x - las) + dis;
        las = x;
    }
    cout << min(dp[m][0], dp[m][1]) << "\n";
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
