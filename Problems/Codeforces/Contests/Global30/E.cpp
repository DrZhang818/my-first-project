#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

struct info {
    int u, v, w;
};

vector<int> fa, bad, w;

int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
}
vector<vector<int>> adj;
void add(int u, int v, int c) {
    u = find(u);
    v = find(v);
    if(u == v) {
        w[u] = min(w[u], c);
        return;
    }
    fa.push_back({});
    bad.push_back({});
    w.push_back(inf);
    adj.push_back({});
    int f = fa.size() - 1;
    fa[f] = f;
    merge(f, u);
    merge(f, v);
    adj[f].push_back(u);
    adj[f].push_back(v);
    w[f] = c;
}

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<info> e;
    vector<int> deg(n + 1);
    ll ans = 0;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        deg[u]++;
        deg[v]++;
        e.emplace_back(u, v, w);
        ans += w;
    }
    fa.assign(n + 1, {});
    iota(fa.begin(), fa.end(), 0);
    bad.assign(n + 1, {});
    w.assign(n + 1, inf);
    adj.assign(n + 1, {});
    for(int i = 1; i <= n; i++) {
        if(deg[i] & 1) {
            bad[i] = 1;
        }
    }
    for(auto [u, v, w] : e) {
        add(u, v, w);
    }
    int f = fa.size() - 1;
    auto dfs = [&](this auto &&self, int u) -> void {
        for(int v : adj[u]) {
            w[v] = min(w[v], w[u]);
            self(v);
            bad[u] += bad[v];
        }
        ans += w[u] * (bad[u] / 2);
        bad[u] %= 2;
    };
    dfs(f);
    cout << ans << "\n";
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