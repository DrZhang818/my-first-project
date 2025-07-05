#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct node {
    int v, w;
};
void solve() { 
    int n;
    cin >> n;
    vector<vector<node>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int ans = 0;
    auto dfs = [&](auto &&dfs, int u, int fa) -> int {
        int mx = 0, se = 0;
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            int cur = dfs(dfs, v, u);
            cur = max(cur, 0) + w;
            if(cur >= mx) {
                se = mx;
                mx = cur;
            } else if(cur > se) {
                se = cur;
            }
        }
        ans = max(ans, mx + se);
        return mx;
    };
    dfs(dfs, 1, 0);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
