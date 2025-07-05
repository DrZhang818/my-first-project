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
    for(int i = 1; i <= n; i++) {
        adj[0].emplace_back(i, 0);
    }
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[v].emplace_back(u, w);
    }
    queue<int> q;
    vector<int> dis(n + 1, inf), cnt(n + 1);
    vector<bool> vis(n + 1);
    dis[0] = 0; vis[0] = true; q.push(0);
    bool ne_circle = false;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(auto [v, w] : adj[u]) {
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n + 1) {
                    ne_circle = true;
                    break;
                }
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        if(ne_circle) break;
    }
    if(ne_circle) {
        cout << "NO\n";
        return;
    }
    for(int i = 1; i <= n; i++) {
        cout << dis[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
