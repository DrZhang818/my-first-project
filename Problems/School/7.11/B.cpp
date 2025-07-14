#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector adj(n + 1, vector<int>(n + 1, inf));
    for(int i = 1; i <= n; i++) {
        adj[i][i] = 0;
    }
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = adj[v][u] = w;
    }
    auto dis = adj;
    int ans = m;
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            if(dis[i][k] == inf) continue;
            for(int j = 1; j <= n; j++) {
                if(dis[k][j] == inf) continue;
                if(dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(adj[i][j] != inf && adj[i][j] == dis[i][j]) {
                ans--;
            }
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
