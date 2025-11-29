#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa, sz;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
    sz[u] += sz[v];
}
bool same(int u, int v) {
    return find(u) == find(v);
}
void solve() {
    int n, m;
    cin >> n >> m;
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    sz.resize(n + 1, 1);
    vector<set<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        merge(u, v);
        adj[u].insert(v);
        adj[v].insert(u);
    }
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<PII> ans;
    int i = 1;
    vector<int> vis(n + 1);
    auto dfs = [&](this auto &&self, int u) -> bool {
        if(i == n) return true;
        if(!vis[u]) {
            vis[u] = true;
            sz[find(u)]--;
        }
        int v = a[i + 1];

        if(adj[u].contains(v)) {
            i++;
            adj[u].erase(v);
            adj[v].erase(u);
            if(!self(v)) {
                return self(u);
            }
        } else {
            vector<int> val(adj[u].begin(), adj[u].end());
            for(int p : val) {
                if(vis[p]) {
                    adj[u].erase(p);
                    adj[p].erase(u);
                }
            }
            if(!adj[u].empty()) {
                ans.push_back({u, v});
                merge(u, v);
                i++;
                if(!self(v)) {
                    return self(u);
                }
            } else {
                if(same(u, v)) {
                    return false;
                } else {
                    if(sz[find(u)] == 0) {
                        return true;
                    }
                    return false;
                }
            }
        }
        return false;
    };
    while(i < n) {
        dfs(a[i]);
        i++;
    }
    cout << ans.size() << "\n";
    for(auto [x, y] : ans) {
        cout << x << " " << y << "\n";
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
