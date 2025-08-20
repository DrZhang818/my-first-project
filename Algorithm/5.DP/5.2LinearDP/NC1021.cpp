#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> dp(20005, -inf);
    dp[10000] = 0;        
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        for(int j = 0; j <= 20000; j++) {
            if(j - a[i] >= 0) {
                ndp[j - a[i]] = max(ndp[j - a[i]], dp[j] + a[i]);
            }
            if(j + a[i] <= 20000) {
                ndp[j + a[i]] = max(ndp[j + a[i]], dp[j] + a[i]);
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for(int i = 10000 - m; i <= 10000 + m; i++) {
        ans = max(ans, dp[i]);
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
