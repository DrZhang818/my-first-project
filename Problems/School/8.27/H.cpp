#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;

struct info {
    int v, w;
};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<info>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    k--;
    vector dp(1 << k, vector<ll>(n, inf));
    for(int i = 0; i < k; i++) {
        dp[1 << i][i] = 0;
    }

    vector<bool> vis(n);
    for(int s = 1; s < 1 << k; s++) {
        auto &ndp = dp[s];
        for(int sub = (s - 1) & s; sub > (s ^ sub); sub = (sub - 1) & s) {
            for(int i = 0; i < n; i++) {
                ndp[i] = min(ndp[i], dp[sub][i] + dp[s ^ sub][i]);
            }
        }

        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(ndp[i] < inf) {
                vis[i] = true;
                q.push(i);
            }
        }

        while(!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = false;
            for(auto [v, w] : adj[u]) {
                if(ndp[u] + w < ndp[v]) {
                    ndp[v] = ndp[u] + w;
                    if(!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }

    }

    auto &ans = dp[(1 << k) - 1];
    for(int i = k; i < n; i++) {
        cout << ans[i] << "\n";
    }
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
