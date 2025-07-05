#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n, q, N, timer = 0;
ll ans = 0, mx = 0;
vector<vector<PII>> adj, eg;
vector<int> D, a, dfn, fa, fu, vis, lca, dist;
vector<PII> Q;
vector<ll> dis;
void init() {
    N = log2(n);
    adj.resize(n + 1);
    D.resize(n + 1);
    a.resize(n + 1);
    dis.resize(n + 1);
    dfn.resize(n + 1);
    fa.resize(n + 1);
    fu.resize(n + 1);
    vis.resize(n + 1);
    eg.resize(n + 1);
    Q.resize(q + 1);
    lca.resize(q + 1);
    dist.resize(q + 1);
    iota(fa.begin(), fa.end(), 0);
}
int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); };
void tarjan(int u, int f) {
    dfn[++timer] = u, dis[u] = dis[f] + a[u], vis[u] = true;
    for(auto &[v, w] : adj[u]) if(!vis[v]) a[v] = w, tarjan(v, u), fa[v] = u, fu[v] = u; 
    for(auto &[v, id] : eg[u]) if(vis[v]) lca[id] = find(v);
}
bool check(int x) {
    int cnt = 0;
    for(int i = 0; i <= n; i++) D[i] = 0;
    for(int i = 1; i <= q; i++) {
        if(dist[i] > x) {
            cnt++;
            D[Q[i].first]++, D[Q[i].second]++, D[lca[i]] -= 2;
        }
    }
    for(int i = n; i >= 1; i--) D[fu[dfn[i]]] += D[dfn[i]];
    for(int i = 1; i <= n; i++) {
        if(D[i] == cnt && mx - a[i] <= x) {
            return true;
        }
    }
    return false;
}
void solve() { 
    cin >> n >> q;
    init();
    for(int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    for(int i = 1; i <= q; i++) {
        int u, v;
        cin >> u >> v;
        eg[u].push_back({v, i});
        eg[v].push_back({u, i});
        Q[i] = {u, v};
    }
    tarjan(1, 0);
    for(int i = 1; i <= q; i++) {
        dist[i] = dis[Q[i].first] + dis[Q[i].second] - 2 * dis[lca[i]];
        mx = max(mx, (ll)dist[i]);
    }
    ll l = -1, r = mx + 1;
    while(l + 1 < r) {
        ll mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid;
    }
    cout << r << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    