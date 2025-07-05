#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int v, id;
};
void solve() { 
    int n;
    cin >> n;
    vector<int> deg(n + 1);
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }
    int mx = *max_element(deg.begin() + 1, deg.end());
    if(mx <= 2) {
        for(int i = 0; i < n - 1; i++) {
            cout << i << "\n";
        }
        return ;
    } 
    vector<int> ans(n, -1);
    int idx = 0;
    for(int i = 1; i <= n; i++) {
        if(deg[i] >= 3) {
            for(auto [v, id] : adj[i]) {
                if(idx >= 3) break;
                ans[id] = idx++;
            }
        }
    }
    for(int i = 1; i < n; i++) {
        if(ans[i] == -1) {
            ans[i] = idx++;
        }
    }
    for(int i = 1; i < n; i++) {
        cout << ans[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
