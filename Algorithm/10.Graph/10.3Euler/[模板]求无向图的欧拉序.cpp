#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct Edge {
    int to, eid;
    friend bool operator < (const Edge &a, const Edge &b) {
        return a.to < b.to;
    }
};

void solve() {
    int n, m, idx = 0;
    cin >> n >> m;
    vector<vector<Edge>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, idx});
        adj[v].push_back({u, idx++});
    }
    int st = 0, oddDegCnt = 0;
    for(int i = n; i >= 1; i--) {
        int deg = adj[i].size();
        if(deg & 1) {
            st = i;
            oddDegCnt++;
        } else if(oddDegCnt == 0) {
            st = i;
        }
    }
    if(oddDegCnt > 2) {
        cout << "No\n";
        return ;
    }
    for(int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
    vector<int> path;
    path.reserve(m + 1);
    vector<bool> vis(m);
    auto dfs = [&](this auto &&self, int u) -> void {    
        auto &cur = adj[u];
        auto it = cur.begin();
        while(it != cur.end()) {
            Edge e = *it;
            it = cur.erase(it);
            int i = e.eid;
            if(vis[i]) continue;
            vis[i] = true;
            int v = e.to;
            self(v);
        }
        path.push_back(u);
    };
    dfs(st);
    reverse(path.begin(), path.end());
    cout << "Yes\n";
    for(int i = 0; i < m + 1; i++) {
        cout << path[i] << " \n"[i == m];
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
