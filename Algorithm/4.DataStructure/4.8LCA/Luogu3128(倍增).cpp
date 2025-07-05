#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    const int N = log2(n);
    vector<vector<int>> fa(n + 1, vector<int>(N + 1));
    vector<int> dep(n + 1);
    auto dfs = [&](auto && dfs, int u, int fu) -> void {
        dep[u] = dep[fu] + 1;
        fa[u][0] = fu;
        for(int i = 1; i <= N; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for(int v : adj[u]) if(v != fu) dfs(dfs, v, u);
    };
    dfs(dfs, 1, 0);
    auto LCA = [&](int u, int v) -> int {
        if(dep[u] < dep[v]) swap(u, v);
        for(int i = N; i >= 0; i--) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
        if(u == v) return v;
        for(int i = N; i >= 0; i--) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];                
    };
    vector<int> D(n + 1);
    for(int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        D[u]++, D[v]++, D[lca]--, D[fa[lca][0]]--;
    }
    int ans = 0;
    auto dfs2 = [&](auto &&dfs2, int u, int fu) -> void {
        for(int v : adj[u]) if(v != fu) dfs2(dfs2, v, u), D[u] += D[v];
        ans = max(ans, D[u]);
    };
    dfs2(dfs2, 1, 0);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
