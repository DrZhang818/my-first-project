#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll a, b, x, y, z;
    cin >> a >> b >> x >> y >> z;
    vector<ll> memo(1005, -1);
    auto dfs = [&](auto &&self, ll cur) -> ll {
        if(cur == b) {
            return 0;
        }
        ll &res = memo[cur];
        if(res != -1) return res;
        res = inf;
        if(cur * 2 <= 1004) res = min(res, self(self, cur * 2) + z);
        if(cur + 1 <= 1004) res = min(res, self(self, cur + 1) + x);
        if(cur - 1 >= 1) res = min(res, self(self, cur - 1) + y);
        return res; 
    };
    ll ans = dfs(dfs, a);
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
