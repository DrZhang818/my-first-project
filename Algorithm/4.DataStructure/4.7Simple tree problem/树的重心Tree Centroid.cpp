#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve(){ 
    int n;
    cin >> n;
    vector<int> adj[n];
    for(int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dp(n);
    auto dfs = [&](auto &&dfs, int u, int fa) -> int {
        int d = 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            int t = dfs(dfs, v, u);
            d += t;
            dp[u] = max(dp[u], t);
        }
        dp[u] = max(dp[u], n - d);
        return d;
    };
    dfs(dfs, 0, -1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
