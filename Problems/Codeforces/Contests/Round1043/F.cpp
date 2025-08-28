#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int u, v;
};
vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return; 
    fa[v] = u;
}
void solve() {
    int n, m;
    cin >> n >> m;
    fa.assign(n + 1, 0);
    iota(fa.begin(), fa.end(), 0);
    vector<vector<int>> adj(n + 1);
    vector<info> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        e[i] = {u, v};
    }
    vector<int> p(n + 1), dep(n + 1);
    vector<bool> vis(n + 1);
    [&](this auto &&self, int u) -> void {
        vis[u] = true;
        for(int v : adj[u]) {
            if(vis[v]) {
                continue;
            }
            p[v] = u;
            dep[v] = dep[u] + 1;
            self(v);
        }
    } (1);
    for(int i = 1; i <= m; i++) {
        auto &[u, v] = e[i];
        if(p[u] != v) {
            swap(u, v);
        }
        if(p[u] != v) {
            int x = u, y = v;
            while(1) {
                x = find(x);
                y = find(y);
                if(x == y) {
                    break;
                }
                if(dep[x] > dep[y]) {
                    merge(p[x], x);
                } else {
                    merge(p[y], y);
                }
            }
        }
    }
    vector<bool> must(n + 1);
    for(int i = n; i > 1; i = p[i]) {
        if(find(i) == i) {
            must[i] = true;
        }
    }
    queue<info> q;
    for(int i = 1; i <= m; i++) {
        auto [u, v] = e[i];
        if(p[u] == v && must[u]) {
            q.emplace(u, i);
            q.emplace(v, i);
        }
    }
    vector<int> dp(n + 1, -1);
    while(!q.empty()) {
        auto [u, id] = q.front(); q.pop();
        if(dp[u] != -1) {
            continue;
        }
        dp[u] = id;
        for(int v : adj[u]) {
            q.emplace(v, id);
        }
    }
    int Q;
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        int c;
        cin >> c;
        cout << dp[c] << " \n"[i == Q];
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
