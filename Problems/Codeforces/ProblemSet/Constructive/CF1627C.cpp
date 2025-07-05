#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int to, id;
};
void solve() { 
    int n;
    cin >> n;
    vector<vector<info>> adj(n + 1);
    vector<int> deg(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    for(int i = 1; i <= n; i++) {
        if(deg[i] >= 3) {
            cout << -1 << "\n";
            return;
        }
    }
    vector<int> ans(n);
    auto dfs = [&](this auto&& dfs, int fa, int u, int flag) -> void {
        for(auto [v, id] : adj[u]) {
            if(v == fa) continue;
            flag ^= 1;
            ans[id] = flag == 0 ? 2 : 3;
            dfs(u, v, flag);
        }
    };
    dfs(0, 1, 0);
    for(int i = 1; i <= n - 1; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
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
    
