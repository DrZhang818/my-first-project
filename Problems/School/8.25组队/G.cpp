#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

struct info {
    int v;
    ll w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<int> vis(n + 1);
    vector<ll> dis(n + 1, inf);
    dis[1] = a[1];
    priority_queue<info> q;
    q.push({1, a[1]});
    while(!q.empty()) {
        auto [u, w] = q.top(); q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto [v, nw] : adj[u]) {
            if(w + nw + a[v] < dis[v]) {
                dis[v] = w + nw + a[v];
                q.push({v, dis[v]});
            }
        }
    }
    for(int i = 2; i <= n; i++) {
        cout << dis[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
