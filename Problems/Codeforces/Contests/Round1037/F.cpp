#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<int> fa(n + 1);
    vector<int> w(n + 1);
    auto dfs = [&](this auto &&self, int u) -> void {
        for(auto [v, ww] : adj[u]) {
            if(v == fa[u]) continue;
            fa[v] = u;
            w[v] = ww;
            self(v);
        }
    };
    dfs(1);
    ll ans = 0;
    vector<ll> sum(n + 1);
    vector<map<int,ll>> mp(n + 1);
    for(int i = 2; i <= n; i++) {
        if(a[i] != a[fa[i]]) {
            ans += w[i];
        }
        sum[fa[i]] += w[i];
        mp[fa[i]][a[i]] += w[i];
    }
    while(q--) {
        int u, x;
        cin >> u >> x;
        ans -= sum[u];
        if(mp[u].contains(a[u])) {
            ans += mp[u][a[u]];
        }
        if(u != 1) {
            if(a[u] != a[fa[u]]) {
                ans -= w[u];
            }
            if((mp[fa[u]][a[u]] -= w[u]) == 0) {
                mp[fa[u]].erase(a[u]);
            }
        }
        a[u] = x;
        if(u != 1) {
            if(a[u] != a[fa[u]]) {
                ans += w[u];
            }
            mp[fa[u]][a[u]] += w[u];
        }
        ans += sum[u];
        if(mp[u].contains(a[u])) {
            ans -= mp[u][a[u]];
        }
        cout << ans << "\n";
    }
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
