#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
vector<vector<int>> adj;
vector<int> fa, vis, ans;
vector<vector<PII>> Q;
int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); }
void tarjan(int u) {
    vis[u] = true;
    for(int v : adj[u]) if(!vis[v]) tarjan(v), fa[v] = u;
    for(auto [v, id] : Q[u]) if(vis[v]) ans[id] = find(v);  
}
void solve() { 
    int n, q, root;
    cin >> n >> q >> root;
    adj.resize(n + 1);
    vis.resize(n + 1);
    Q.resize(n + 1);
    fa.resize(n + 1);
    ans.resize(q + 1);
    iota(fa.begin(), fa.end(), 0);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1; i <= q; i++) {
        int u, v;
        cin >> u >> v;
        Q[u].push_back({v, i});
        Q[v].push_back({u, i});
    }
    tarjan(root);
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
