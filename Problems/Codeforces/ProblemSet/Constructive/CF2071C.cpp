#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, st, end;
    cin >> n >> st >> end;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>> dis(n);
    vector<int> d(n + 1);
    auto dfs = [&](this auto &&dfs, int fa, int u) -> void {
        dis[d[u]].push_back(u);
        for(int v : adj[u]) {
            if(v == fa) continue;
            d[v] = d[u] + 1;
            dfs(u, v);
        }
    };
    dfs(0, end);
    for(int i = n - 1; i >= 0; i--) {
        for(int v : dis[i]) {
            cout << v << " ";
        }
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
