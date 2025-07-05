#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr ll inf = 1e18;
void solve() { 
    int n, m;
    ll L;
    cin >> n >> m >> L;
    vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, inf));
    for(int i = 1; i <= n; i++) dis[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = w;
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dis[i][k] == inf || dis[k][j] == inf) continue;
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 1000000000));
    for(int i = 1; i <= n; i++) {   
        for(int j = 1; j <= n; j++) {
            if(dis[i][j] <= L) {
                adj[i][j] = 1;
            }
        }
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        if(adj[u][v] == 1000000000) cout << -1 << "\n";
        else cout << adj[u][v] - 1 << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
    