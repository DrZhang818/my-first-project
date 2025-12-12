#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[v].push_back(u);
    }
    vector<int> vis(n + 1);
    int q;
    cin >> q;
    while(q--) {
        int op, x;
        cin >> op >> x;
        if(op == 1) {
            if(vis[x]) continue;
            queue<int> q;
            q.push(x);
            while(!q.empty()) {
                int u = q.front(); q.pop();
                vis[u] = true;
                for(int v : adj[u]) {
                    if(!vis[v]) {
                        q.push(v);
                    }
                }
            }
        } else {
            if(vis[x]) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
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
