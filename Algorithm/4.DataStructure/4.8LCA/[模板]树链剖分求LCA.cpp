#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, q, root;
    cin >> n >> q >> root;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> fa(n + 1), dep(n + 1), top(n + 1), sz(n + 1), son(n + 1);
    auto dfs1 = [&](auto &&self, int u, int f) -> void {
        fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1;
        for(int v : adj[u]) {
            if(v == f) continue;
            self(self, v, u);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]]) {
                son[u] = v;
            }
        }
    };  
    dfs1(dfs1, root, 0);
    auto dfs2 = [&](auto &&self, int u, int t) -> void {
        top[u] = t;
        if(!son[u]) return;
        self(self, son[u], t);
        for(int v : adj[u]) {
            if(v == fa[u] || v == son[u]) continue;
            self(self, v, v);
        }
    };
    dfs2(dfs2, root, root);
    auto LCA = [&](int u, int v) -> int {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    };
    while(q--) {
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
