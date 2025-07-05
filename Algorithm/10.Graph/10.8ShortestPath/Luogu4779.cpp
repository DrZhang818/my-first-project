#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

constexpr ll inf = 1e18;
struct edge {
    int v;
    ll w;
    friend bool operator < (const edge &a, const edge &b) {
        return a.w > b.w;
    }
};
void solve() { 
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<edge>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(edge(v, w));
    }
    vector<ll> d(n + 1, inf);
    vector<bool> vis(n + 1, false);
    priority_queue<edge> pq;
    pq.push(edge(s, 0));
    d[s] = 0;
    while(!pq.empty()) {
        edge e = pq.top(); pq.pop();
        int u = e.v;
        if(vis[u]) continue;
        vis[u] = true;
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].v;
            ll w = adj[u][i].w;
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pq.push(edge(v, d[v]));
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << d[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
