#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() { 
    int n;
    cin >> n;
    vector<vector<PII>> adj(n);
    ll sum = 0;
    for(int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        sum += 2 * w;
    }
    ll ans = -inf;
    auto dfs = [&](auto &&dfs, int u, int fa) -> ll {
        ll d1 = -inf, d2 = -inf;
        for(auto &[v, w] : adj[u]) {
            if(v == fa) continue;
            ll temp = max(dfs(dfs, v, u), 0LL) + w;
            if(temp >= d1) {
                d2 = d1;
                d1 = temp;
            } else if(temp > d2) {
                d2 = temp;
            }
        }
        d2 = max(d2, 0LL);
        ans = max(ans, d1 + d2);
        return d1 == -inf ? 0 : d1;
    };
    dfs(dfs, 0, -1);
    cout << sum - ans << "\n";
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
