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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1), radj(n + 1);
    vector<PII> e(m);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
        e[i] = {u, v};
    }
    vector<int> vis1(n + 1), vis2(n + 1);
    auto dfs = [&](this auto &&self, int u, vector<vector<int>> &adj ,vector<int> &vis) -> void {
        vis[u] = true;
        for(int v : adj[u]) {
            if(vis[v]) continue;
            self(v, adj, vis);
        }
    };
    dfs(1, adj, vis1);
    dfs(n, radj, vis2);
    vector<vector<info>> g(n + 1);
    for(auto [u, v] : e) {
        if(vis1[u] && vis2[v]) {
            g[u].emplace_back(v, 2);
            g[v].emplace_back(u, -1);
        }
    }
    vector<int> d(n + 1, inf), cnt(n + 1);
    vector<bool> vis(n + 1);
    queue<int> q;
    q.push(1);
    d[1] = 0;
    vis[1] = true;
    bool ne_circle = false;
    while(!q.empty()) {
        int u = q.front(); q.pop(); vis[u] = false;
        for(auto [v, w] : g[u]) {
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) {
                    ne_circle = true;
                    break;
                }
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        if(ne_circle) {
            break;
        }
    }
    if(ne_circle) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    for(auto [u, v] : e) {
        if(vis1[u] && vis2[v]) {
            cout << d[v] - d[u] << "\n";
        } else {
            cout << 1 << "\n";
        }
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
