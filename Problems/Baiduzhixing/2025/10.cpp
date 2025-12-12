#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

struct info {
    int v, w;
};

struct node {
    int v;
    ll w;
    int s;
    friend bool operator < (const node &a, const node &b) {
        return a.w > b.w;
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<info>> adj(n + 1);
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<ll>> mat(n + 1, vector<ll>(n + 1, inf));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= k; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        mat[u][v] = mat[v][u] = w;
    }
    vector<ll> suma(1 << n);
    suma[0] = inf;
    for(int s = 1; s < 1 << n; s++) {
        vector<ll> mn(m, inf);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < bn; j++) {
                if(s >> j & 1) {
                    mn[i] = min(mn[i], (ll)a[j][i]);
                }
            }
            suma[s] += mn[i];
        }
    }
    vector<vector<ll>> dis(1 << n, vector<ll>(n + 1, inf));
    vector<vector<bool>> vis(1 << n, vector<bool>(n + 1));
    priority_queue<node> q;
    q.push({n, 0, 0});
    while(!q.empty()) {
        auto [u, w, s] = q.top(); q.pop();
        if(vis[s][u]) continue;
        for(auto [v, nw] : adj[u]) {
            int ns = s;
            if(v != n) {
                ns |= 1 << v;
            }
            if(w + nw < dis[ns][v]) {
                dis[ns][v] = w + nw;
                q.push({v, w + nw, ns});
            }
        }
    }
    ll ans = inf;
    for(int s = 0; s < 1 << n; s++) {
        for(int u = 0; u <= n; u++) {
            if(u == n) {
                ans = min(ans, dis[s][u] + suma[s]);
            } else {
                ans = min(ans, dis[s][u] + mat[u][n] + suma[s]);
            }
        }
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