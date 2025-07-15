#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll n;
    cin >> n;
    map<ll,ll> dp;
    auto dfs = [&](auto &&self, ll x) -> ll {
        if(x <= 2) return 0;
        if(x == 3) return 1;
        ll u, v;
        if(dp.contains(x / 2)) u = dp[x / 2];
        else u = self(self, x / 2);
        if(dp.contains((x + 1) / 2)) v = dp[(x + 1) / 2];
        else v = self(self, (x + 1) / 2); 
        return dp[x] = u + v + (x & 1);
    };
    cout << dfs(dfs, n) << "\n";
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
