#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = 1;
    vector<int> vis(n + 1);
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int sz = q.size();
        int k = ans, used = 0;
        while(sz--) {
            int u = q.front(); q.pop();
            vis[u] = true;
            int d = 0;
            for(int v : adj[u]) {
                if(!vis[v]) {
                    q.push(v);
                    d++;
                }
            }
            if(d == 0) continue;
            int can = k - (used == 0);
            ans += max(0, d - can);
            k -= min(d, can);
            used = 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
