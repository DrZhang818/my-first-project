#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 998244353;
void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> dp(s + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = s; j >= 1 && j >= a[i]; j--) {
            dp[j] = (dp[j] + dp[j - a[i]]) % MOD;
        }
        if(a[i] <= s) dp[a[i]] = (dp[a[i]] + i) % MOD;
        ans = (ans + dp[s]) % MOD;
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
