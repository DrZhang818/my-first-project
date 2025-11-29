#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, Q;
    cin >> n >> m >> Q;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[v].push_back(u);
        deg[u]++;
    }
    vector<int> f(n + 1, 1), g(n + 1, 1);
    while(Q--) {
        int op, u;
        cin >> op >> u;
        if(op == 1) {
            queue<PII> q;
            if(f[u]) {
                q.push({u, 1});
            }
            if(g[u]) {
                q.push({u, 2});
            }
            f[u] = g[u] = 0;
            while(!q.empty()) {
                auto [u, s] = q.front(); q.pop();
                for(int v : adj[u]) {
                    if(s == 1) {
                        if(g[v]) {
                            g[v] = 0;
                            q.push({v, 2});
                        }
                    } else {
                        if(f[v]) {
                            if(--deg[v] == 0) {
                                f[v] = 0;
                                q.push({v, 1});
                            }
                        }
                    }
                }
            }
        } else {
            if(f[u]) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
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
