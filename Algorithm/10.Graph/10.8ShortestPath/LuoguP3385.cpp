#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if(w >= 0) {
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        } else {
            adj[u].emplace_back(v, w);
        }
    }
    queue<int> q;
    q.push(1);
    vector<int> dis(n + 1, inf), vis(n + 1), cnt(n + 1);
    dis[1] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(auto [v, w] : adj[u]) {
            if(dis[u] + w < dis[v]) {
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) {
                    cout << "YES\n";
                    return;
                }
                dis[v] = dis[u] + w;
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    cout << "NO\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
