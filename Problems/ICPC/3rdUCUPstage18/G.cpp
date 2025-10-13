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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    
    auto val = a;
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());

    int m = val.size();
    vector<array<int,2>> dp(m + 1);
    int mx = 0, cmx = 0;
    for(int i = 1; i <= n; i++) {
        int x = lower_bound(val.begin() + 1, val.end(), a[i]) - val.begin();
        if(dp[x][0]) dp[x][1] = max(dp[x][0], dp[x][1]) + 1;
        dp[x][0] = mx + 1;
        mx = max(mx, dp[x][1]);
    }
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        ans = max(ans, dp[i][1]);
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
