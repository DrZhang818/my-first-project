#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int inf = 1000000000;
int n, m, N;
struct edge {
    int u, v, w;
    friend bool operator < (const edge &a, const edge &b) { 
        return a.w > b.w; 
    }
};
vector<edge> e;
vector<vector<PII>> adj;
vector<int> fa, dep, vis;
vector<vector<int>> fu, mn;
int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); }
void kruskal() {
    sort(e.begin() + 1, e.end());
    for(int i = 1; i <= m; i++) {
        int x = find(e[i].u), y = find(e[i].v);
        if(x != y) {
            fa[x] = y;
            adj[e[i].u].push_back({e[i].v, e[i].w});
            adj[e[i].v].push_back({e[i].u, e[i].w});
        }
    }
}
void dfs(int u, int f) {
    dep[u] = dep[f] + 1, fu[u][0] = f, vis[u] = true;
    for(int i = 1; i <= N; i++) {
        fu[u][i] = fu[fu[u][i - 1]][i - 1];
        mn[u][i] = min(mn[u][i - 1], mn[fu[u][i - 1]][i - 1]);
    }
    for(auto [v, w] : adj[u]) {
        if(v != f) {
            mn[v][0] = w;
            dfs(v, u);
        }
    }
}
int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int res = inf;
    for(int i = N; i >= 0; i--) {
        if(dep[fu[u][i]] >= dep[v]) {
            res = min(res, mn[u][i]);
            u = fu[u][i];
        }
    }
    if(u == v) return res;
    for(int i = N; i >= 0; i--) {
        if(fu[u][i] != fu[v][i]) {
            res = min({res, mn[u][i], mn[v][i]});
            u = fu[u][i];
            v = fu[v][i];
        }
    }
    res = min({res, mn[u][0], mn[v][0]});
    return res;
}
void init() {
    N = log2(n);
    adj.resize(n + 1);
    e.resize(m + 1);
    fa.resize(n + 1);
    dep.resize(n + 1);
    vis.resize(n + 1);
    fu.resize(n + 1, vector<int>(N + 1));
    mn.resize(n + 1, vector<int>(N + 1, inf));
    iota(fa.begin(), fa.end(), 0);
}

void solve() { 
    cin >> n >> m;
    init();
    for(int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    kruskal();
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            dfs(i, 0);
        }
    }
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        if(find(u) != find(v)) cout << -1 << "\n";
        else cout << LCA(u, v) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
