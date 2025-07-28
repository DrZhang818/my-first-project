#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    ll x;
    cin >> n >> x;
    vector<ll> dp(n), dp1(n);
    dp[0] = 1;
    dp1[0] = 1;
    for(int i = 1; i < n; i++) {
        dp[i] = 2 * dp[i - 1] + 3;
        dp1[i] = 2 * dp1[i - 1] + 1;
    }
    auto dfs = [&](auto &&self, int k, ll cnt) -> ll {
        if(k == 0) return 1;
        ll sz = dp[k - 1];
        ll ans = 0;
        cnt--;
        if(cnt == 0) return ans;
        if(cnt > sz) {
            ans += dp1[k - 1];
            cnt -= sz;
        } else {
            ans += self(self, k - 1, cnt);
            return ans;
        }
        cnt--;
        ans++;
        if(cnt == 0) return ans;
        if(cnt > sz) {
            ans += dp1[k - 1];
            cnt -= sz;
        } else {
            ans += self(self, k - 1, cnt);
        }
        return ans;
    };
    cout << dfs(dfs, n, x) << "\n";
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
