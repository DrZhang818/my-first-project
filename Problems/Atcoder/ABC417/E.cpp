#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vis(n + 1);
    vector<int> path;
    auto dfs = [&](auto &&self, int u) -> bool {
        vis[u] = true;
        path.push_back(u);
        sort(adj[u].begin(), adj[u].end());
        if(u == y) {
            for(int i : path) {
                cout << i << " ";
            }
            cout << "\n";
            return true;
        }
        for(int v : adj[u]) {
            if(vis[v]) continue;
            if(self(self, v)) return true;
        }
        path.pop_back();
        return false;
    };
    dfs(dfs, x);
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
