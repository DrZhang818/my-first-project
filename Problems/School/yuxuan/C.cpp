#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


const ll inf = 1e18;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n + 1, vector<ll>(n + 1, inf));
    for(int i = 1; i <= n; i++) adj[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u][v] = adj[v][u] = min(adj[u][v], w);
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
        int s;
        cin >> s;
        vector<int> en(5);
        for(int i = 1; i <= 4; i++) cin >> en[i];
        ll ans = inf;
        for(int i = 1; i <= 4; i++) {
            for(int j = 1; j <= 4; j++) {
                if(j == i) continue;
                for(int k = 1; k <= 4; k++) {
                    if(k == i || k == j) continue;
                    for(int m = 1; m <= 4; m++) {
                        if(m == i || m == j || m == k) continue;
                        ans = min(ans, adj[s][en[i]] + adj[en[i]][en[j]] + adj[en[j]][en[k]] + adj[en[k]][en[m]] + adj[en[m]][s]);
                    }
                }
            }
        }
        if(ans == inf) {
            cout << -1 << "\n";
        } else {
            cout << ans << "\n";

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
    
