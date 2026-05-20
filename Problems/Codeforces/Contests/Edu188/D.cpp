#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(n + 1);
    vector<int> col(n + 1, -1);
    int ans = 0;

    auto bfs = [&](int x) {
        queue<int> q;
        q.push(x);
        col[x] = 0;
        bool ok = true;
        int c0 = 1, c1 = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = true;
            for(int v : adj[u]) {
                if(col[u] == col[v]) {
                    ok = false;
                }
                if(col[v] == -1) {
                    col[v] = col[u] ^ 1;
                    if(col[v] == 0) c0++;
                    else c1++;
                    q.push(v);
                }
            }
        }
        if(ok) {
            ans += max(c0, c1);
        }
    };

    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            bfs(i);
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
