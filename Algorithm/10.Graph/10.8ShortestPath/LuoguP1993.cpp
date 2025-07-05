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
        int op;
        cin >> op;
        if(op == 1) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v, -w);
        } else if(op == 2) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[v].emplace_back(u, w);
        } else {
            int u, v;
            cin >> u >> v;
            adj[u].emplace_back(v, 0);
            adj[v].emplace_back(u, 0);
        }
    }
    queue<int> q;
    vector<int> d(n + 1, inf), cnt(n + 1);
    vector<bool> vis(n + 1);
    q.push(0); d[0] = 0, vis[0] = true;
    bool ok = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(auto [v, w] : adj[u]) {
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n + 1) {
                    ok = false;
                    break;
                }
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        if(!ok) {
            break;
        }
    }
    if(!ok) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
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
