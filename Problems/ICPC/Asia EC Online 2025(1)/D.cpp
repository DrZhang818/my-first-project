#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://qoj.ac/contest/2513/problem/14304
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<array<ll,2>> f(n + 1);
    vector<ll> g(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        f[u][0] = -a[u];
        f[u][1] = a[u];
        ll sum = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            g[u] = max({g[u] + g[v], f[v][0] + f[u][1], f[v][1] + f[u][0]});
            f[u][0] = max({f[u][0] + g[v], sum + f[v][0], sum + g[v] - a[u]});
            f[u][1] = max({f[u][1] + g[v], sum + f[v][1], sum + g[v] + a[u]});
            sum += g[v];
        }
    };
    dfs(1, 0);
    cout << g[1] << "\n";
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
