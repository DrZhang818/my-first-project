#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//解决有向无环图(DAG)
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> res;
    vector<int> vis(n + 1, 0);
    auto dfs = [&](auto &&dfs, int u) -> void {
        vis[u] = 1; // 正在访问
        for(int v : adj[u]) {
            if(vis[v] == 1) {
                cout << -1 << "\n";  //有环
            }
            if(vis[v] == 0) {
                dfs(dfs, v);
            }
        }
        vis[u] = 2; // 已完成
        res.push_back(u);
    };
    for(int i = 1; i <= n; i++) {
        if(vis[i] == 0) {
            dfs(dfs, i);
        }
    }
    reverse(res.begin(), res.end());
    for(int x : res) {
        cout << x << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

