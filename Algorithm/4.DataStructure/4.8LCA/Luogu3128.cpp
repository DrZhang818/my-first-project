#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n, k, res = 0;
vector<vector<int>> adj;
vector<vector<PII>> Q;
vector<int> ans, vis, fa, fu, D;
void init() {
    adj.resize(n + 1);
    D.resize(n + 1);
    Q.resize(n + 1);
    ans.resize(k + 1);
    vis.resize(n + 1);
    fa.resize(n + 1);
    fu.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
}
int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); }
void tarjan(int u) {
    vis[u] = true;
    for(auto v : adj[u]) if(!vis[v]) tarjan(v), fa[v] = u, fu[v] = u;
    for(auto [v, id] : Q[u]) if(vis[v]) ans[id] = find(v);
}
void dfs(int u, int f) {
    for(int v : adj[u]) {
        if(v == f) continue;
        dfs(v, u);
        D[u] += D[v];
    }
    res = max(res, D[u]);
}
void solve() { 
    cin >> n >> k;
    init();
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<PII> id(k + 1);
    for(int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        Q[u].push_back({v, i});
        Q[v].push_back({u, i});
        id[i] = {u, v};
    }
    tarjan(1);
    for(int i = 1; i <= k; i++) {
        int lca = ans[i];
        auto [u, v] = id[i];
        D[u]++, D[v]++, D[lca]--, D[fu[lca]]--;
    }
    dfs(1, 0);
    cout << res << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
