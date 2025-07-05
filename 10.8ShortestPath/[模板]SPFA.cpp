#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr ll inf = 1e18;
struct edge {
    int v, w;
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
    vector<ll> d(n + 1, inf), cnt(n + 1, 0);
    vector<bool> vis(n + 1);
    queue<int> q;
    d[s] = 0; vis[s] = 1; q.push(s);
    bool ne_circle = false;
    while(!q.empty()) {
        int u = q.front(); q.pop(); vis[u] = false;
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].v, w = adj[u][i].w;
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) {
                    ne_circle = true;
                    break;
                }
                if(!vis[v]) q.push(v), vis[v] = true;
            }
        }
        if(ne_circle) break;
    }
    if(ne_circle) {
        cout << -1 << "\n";
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
    
