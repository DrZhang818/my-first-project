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
    vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, inf));
    vector<vector<ll>> path(n + 1, vector<ll>(n + 1, -1));
    for(int i = 1; i <= n; i++) adj[i][i] = dis[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        if(w < dis[u][v]) {
            dis[u][v] = dis[v][u] = adj[u][v] = adj[v][u] = w;
            path[u][v] = u, path[v][u] = v;
        }
    }
    ll mn = inf;
    auto find = [&](auto &&find, int u, int v, vector<int> &res) -> void {
        if(path[u][v] == u) return;
        find(find, u, path[u][v], res);
        res.push_back(path[u][v]);
    };
    vector<int> nodes;
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i < k; i++) {
            for(int j = i + 1; j < k; j++) {
                if(dis[i][j] + adj[j][k] + adj[k][i] < mn) {
                    mn = dis[i][j] + adj[j][k] + adj[k][i];
                    nodes.clear();
                    vector<int> temp;
                    find(find, i, j, temp);
                    for(int o : temp) {
                        nodes.push_back(o);
                    }
                    nodes.push_back(j);
                    nodes.push_back(k);
                    nodes.push_back(i);
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    if(mn == inf) {
        cout << "No solution." << "\n";
    } else {
        for (int i = 0; i < nodes.size(); ++i) {
            cout << nodes[i] << " \n"[i == nodes.size() - 1];
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
    
