#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;


void solve() {
    int n;
    cin >> n;
    vector<vector<ll>> adj(n + 1, vector<ll>(n + 1));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> adj[i][j];
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    vector<vector<ll>> col(n + 1, vector<ll>(n + 1, inf)), row(n + 1, vector<ll>(n + 1, inf));
    for(int i = 1; i <= n; i++) {
        for(int j = 2; j <= n; j++) {
            col[i][j] = adj[i][j] - adj[i][j - 1];
        }
    }
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            row[i][j] = adj[i][j] - adj[i - 1][j];
        }
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(2, inf));
    dp[1][0] = 0, dp[1][1] = a[1];
    for(int i = 2; i <= n; i++) {
        bool fd0 = false, fdn1 = false;
        for(int j = 1; j <= n; j++) {
            if(row[i][j] == 0) fd0 = true;
            else if(row[i][j] == -1) fdn1 = true;
        }
        if(fd0) dp[i][0] = inf;
        else dp[i][0] = dp[i - 1][0];
        if(fdn1) dp[i][1] = inf;
        else dp[i][1] = dp[i - 1][0] + a[i];
        fd0 = fdn1 = false;
        for(int j = 1; j <= n; j++) {
            if(row[i][j] - 1 == 0) fd0 = true;
            else if(row[i][j] - 1 == -1) fdn1 = true;
        }
        if(!fd0) dp[i][0] = min(dp[i][0], dp[i - 1][1]);
        if(!fdn1) dp[i][1] = min(dp[i][1], dp[i - 1][1] + a[i]);
    }   
    ll ans = min(dp[n][0], dp[n][1]);
    if(ans >= inf) { cout << -1 << "\n"; return ; } 
    for(int i = 0; i <= n; i++) dp[i][0] = dp[i][1] = inf;
    dp[1][0] = 0, dp[1][1] = b[1];
    for(int i = 2; i <= n; i++) {
        bool fd0 = false, fdn1 = false;
        for(int j = 1; j <= n; j++) {
            if(col[j][i] == 0) fd0 = true;
            else if(col[j][i] == -1) fdn1 = true;
        }
        if(fd0) dp[i][0] = inf;
        else dp[i][0] = dp[i - 1][0];
        if(fdn1) dp[i][1] = inf;
        else dp[i][1] = dp[i - 1][0] + b[i];
        fd0 = fdn1 = false;
        for(int j = 1; j <= n; j++) {
            if(col[j][i] - 1 == 0) fd0 = true;
            else if(col[j][i] - 1 == -1) fdn1 = true;
        }
        if(!fd0) dp[i][0] = min(dp[i][0], dp[i - 1][1]);
        if(!fdn1) dp[i][1] = min(dp[i][1], dp[i - 1][1] + b[i]);
    }   
    if(min(dp[n][0], dp[n][1]) >= inf) { cout << -1 << "\n"; return ; }
    ans += min(dp[n][0], dp[n][1]);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
