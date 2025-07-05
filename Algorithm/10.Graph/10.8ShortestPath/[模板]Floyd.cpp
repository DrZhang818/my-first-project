#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
constexpr ll inf = 1000000000;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, inf));
    vector<vector<int>> nxt(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) dis[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        if(w < dis[u][v]) {
            dis[u][v] = w;
            nxt[u][v] = v;
        }
    }
    for(int k = 1; k <= n; k++) { 
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) { 
                if(dis[i][k] == inf || dis[k][j] == inf) continue;
                if(dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        if(dis[i][i] < 0) {
            cout << -1 << "\n";
            return;
        }   
    }
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        if(dis[u][v] == inf) {
            cout << -1 << "\n";
        } else {
            cout << dis[u][v] << "\n";
            int k = u;
            while(k != v) {
                cout << k << " ";
                k = nxt[k][v];
            }
            cout << v << "\n";
        }
    }
    //输出路径测试
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
