#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct Edge {
    int v;
    char c;
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    vector<int> dis(n + 1, inf);
    dis[n] = 0;
    queue<int> q;
    q.push(n);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(auto [v, c] : adj[u]) {
            if(dis[v] == inf) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }

    vector<int> pre(n + 1);
    vector<bool> vis(n + 1);
    string ans;

    vector<int> cands;
    cands.push_back(1);
    while(cands[0] != n) {
        char min_c = 'z' + 1;
        for(int u : cands) {
            for(auto [v, c] : adj[u]) {
                if(dis[v] == dis[u] - 1) {
                    min_c = min(min_c, c);
                }
            }
        }

        ans += min_c;
        vector<int> nc;
        for(int u : cands) {
            for(auto [v, c] : adj[u]) {
                if(dis[v] == dis[u] - 1 && c == min_c) {
                    if(!vis[v]) {
                        vis[v] = true;
                        pre[v] = u;
                        nc.push_back(v);
                    }
                }
            }
        }

        cands = move(nc);
    }

    cout << dis[1] << "\n";
    vector<int> path;
    for(int u = n; u; u = pre[u]) {
        path.push_back(u);
    }
    reverse(path.begin(), path.end());
    for(int u : path) {
        cout << u << " \n"[u == path.back()];
    }
    cout << ans << "\n";
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
