#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

struct Edge {
    int v, w;
};

void solve() {  
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1);

    for(int i = 1; i <= m; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        adj[u].emplace_back(v, x);
        adj[v].emplace_back(u, x);
    }

    if(n & 1) {
        cout << -1 << "\n";
        return;
    }

    int _xor = 0;
    for(int i = 0; i <= n; i++) {
        _xor ^= i;
    }

    vector<int> w(n + 1);
    vector<int> vis(n + 1);

    auto dfs = [&](this auto&& self, int u) -> void {
        vis[u] = true;
        for(auto [v, c] : adj[u]) {
            if(!vis[v]) {
                w[v] = w[u] ^ c;
                vis[v] = true;
                self(v);
            }
        }
    };
    dfs(1);

    for(int i = 2; i <= n; i++) {
        _xor ^= w[i];
    }

    cout << _xor << "\n";
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
