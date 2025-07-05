#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


vector<int> fa;
vector<int> d;
int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); }
void merge(int u, int v) {
    int fu = find(u), fv = find(v);
    fa[fv] = fu;
}
bool add(int u, int v) { 
    int fu = find(u), fv = find(v);
    if(fu == fv) return false;
    merge(fu, fv);
    d[fu] = max({d[fu], d[fv], (d[fu] + 1) / 2 + (d[fv] + 1) / 2 + 1});
    return true;
}
void solve() { 
    int n, m, q;
    cin >> n >> m >> q;
    fa.assign(n + 1, 0);
    iota(fa.begin(), fa.end(), 0);
    d.assign(n + 1, 0);
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        merge(u, v);
    }
    vector<int> vis(n + 1, false);
    int ans = 0;
    auto dfs = [&](auto &&dfs, int u, int fa) -> int {
        vis[u] = true;
        int mx = 0, se = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            int cur = dfs(dfs, v, u);
            cur = max(cur, 0) + 1;
            if(cur >= mx) se = mx, mx = cur;
            else if(cur > se) se = cur; 
        }
        ans = max(ans, mx + se);
        return mx;
    };
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            ans = 0;
            dfs(dfs, i, 0);
            int fi = find(i);
            d[fi] = ans;
        } 
    }
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int x;
            cin >> x;
            int fx = find(x);
            cout << d[fx] << "\n";
        } else {
            int x, y;
            cin >> x >> y;
            add(x, y);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
