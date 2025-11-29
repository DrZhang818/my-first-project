#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    fa[v] = u;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if(u != v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<int> p(n + 1, -1);
    vector<bool> vis(n + 1, false);
    auto dfs = [&](auto &&self, int u, int f) -> void {
        p[u] = f;
        for(int v : adj[u]) {
            if(v == f && !vis[u]) {
                vis[u] = true;
                continue;
            }
            if(p[v] == -1) {
                self(self, v, u);
            } else {
                int x = find(u), y = find(v);
                while(x != y) {
                    int fx = find(p[x]);
                    merge(y, x);
                    x = fx;
                }
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        if(p[i] == -1) {
            dfs(dfs, i, 0);
        }
    }
    vector<vector<int>> dcc(n + 1);
    int cnt = 0;
    for(int u = 1; u <= n; u++) {
        int fu = find(u);
        if(u == fu) {
            cnt++;
        }
        dcc[fu].push_back(u);
    }
    cout << cnt << "\n";
    for(int i = 1; i <= n; i++) {
        if(!dcc[i].empty()) {
            cout << dcc[i].size() << " ";
            for(int x : dcc[i]) {
                cout << x << " \n"[x == dcc[i].back()];
            }
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
