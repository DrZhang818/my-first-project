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
    int n;
    cin >> n;
    vector<int> x(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    auto dfs = [&](auto &&self, int u, int fa) -> ll {
        ll res = 0;
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            res += self(self, v, u);
            res += 1LL * abs(x[v]) * w;
            x[u] += x[v];
        }
        return res;
    };
    ll ans = dfs(dfs, 1, 0);
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
