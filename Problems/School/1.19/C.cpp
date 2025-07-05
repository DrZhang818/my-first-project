#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u -= 1;
        v -= 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll ans = 0;
    vector<bool> vis(n, false);
    function<void(int, int)> dfs = [&](int fa, int cnt) -> void{
        if(cnt == n){
            ans++;
            return;
        }
        for(int i = 0; i < adj[fa].size(); i++){
            if(!vis[adj[fa][i]]){
                vis[adj[fa][i]] = true;
                dfs(adj[fa][i], cnt + 1);
                vis[adj[fa][i]] = false;
            }
        }
    };
    vis[0] = true;
    dfs(0, 1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}