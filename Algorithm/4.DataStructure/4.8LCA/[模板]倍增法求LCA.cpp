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
    const int N = log2(n);
    vector<int> dep(n + 1);
    vector<vector<int>> fa(n + 1, vector<int>(N + 1));
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto dfs = [&](auto &&dfs, int u, int fu) -> void {
        dep[u] = dep[fu] + 1;
        fa[u][0] = fu;
        for(int i = 1; i <= N; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for(int v : adj[u]) if(v != fu) dfs(dfs, v, u);
    };
    dfs(dfs, root, 0);
    auto LCA = [&](int u, int v) -> int {
        if(dep[u] < dep[v]) swap(u, v);
        for(int i = N; i >= 0; i--) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
        if(u == v) return v;
        for(int i = N; i >= 0; i--) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
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
    
