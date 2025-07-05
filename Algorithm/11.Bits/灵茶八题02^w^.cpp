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
    vector<ll> dp(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if(i & 1) {
            dp[i] ^= a[i];
        }
    }
    for(int i = 1; i <= n; i++) {
        ans ^= dp[i];
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
