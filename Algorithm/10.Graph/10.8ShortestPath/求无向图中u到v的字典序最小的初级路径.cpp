#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info { 
    int v, w;
    friend bool operator < (const info &a, const info &b) {
        return a.w < b.w;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<int> dfn(n + 1), low(n + 1);
    int timer = 0;
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        dfn[u] = low[u] = ++timer;
        for(auto &[v, _] : adj[u]) {
            if(!dfn[v]) {
                self(v, u);
                low[u] = min(low[u], low[v]);
            } else if(v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    int st, en;
    cin >> st >> en;
    dfs(en, 0);
    if(!dfn[st]) {
        cout << -1 << "\n";
        return;
    }
    vector<int> vis(n + 1);
    int u = st, mn = inf;
    while(u != en) {
        mn = min(mn, dfn[u]);
        vis[u] = true;
        sort(adj[u].begin(), adj[u].end());
        for(auto &[v, w] : adj[u]) {
            if(vis[v]) continue;
            if((dfn[v] < mn || dfn[v] > dfn[u]) && low[v] < mn) {
                u = v;
                cout << w << " ";
                break;
            } else if(dfn[v] < dfn[u]){
                for(auto &[vv, _] : adj[v]) {
                    if(vv != u && low[vv] < mn && !vis[vv]) {
                        u = v;
                        cout << w << " ";
                        break;
                    }
                }
                if(u == v) break;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
