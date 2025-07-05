#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dep(n + 1), sz(n + 1);
    dep[0] = -1;
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        dep[u] = dep[fa] + 1, sz[u] = 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            sz[u] += sz[v];
        }
        dep[u] -= sz[u] - 1;
    };
    dfs(1, 0);
    sort(dep.begin() + 1, dep.end(), greater<int>());
    ll ans = 0;
    for(int i = 1; i <= k; i++) {
        ans += dep[i];
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
    
