#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> memo(n + 1, -1);
    auto dfs = [&](auto &&dfs, int u) -> int {
        int &res = memo[u];
        if(res != -1) {
            return res;
        }
        res = 0;
        for(int v : adj[u]) {
            res = max(res, dfs(dfs, v) + 1); 
        }
        return res;
    };
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, dfs(dfs, i));
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
    
