#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
}

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<unordered_set<int>> adj(n + 1);

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    using T = tuple<int,int,int>;
    vector<T> ans {};

    for(int u = 1; u <= n; u++) {
        while(adj[u].size() >= 2) {
            int v = *adj[u].begin();
            adj[u].erase(v);
            adj[v].erase(u);
            int w = *adj[u].begin();
            adj[u].erase(w);
            adj[w].erase(u);

            if(adj[v].contains(w)) {
                adj[v].erase(w);
                adj[w].erase(v);
            } else {
                adj[v].insert(w);
                adj[w].insert(v);
            }

            ans.emplace_back(u, v, w);
        }
    }

    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);

    int x = -1, y = -1;
    for(int u = 1; u <= n; u++) {
        for(int v : adj[u]) {
            merge(u, v);
            x = u;
            y = v;
        }
    }

    if(x != -1) {
        int id = find(x);
        for(int i = 1; i <= n; i++) {
            find(i);
            if(fa[i] != i || fa[i] == id) continue;
            ans.emplace_back(x, y, i);
            y = i;
        }
    }

    cout << ans.size() << "\n";
    for(auto [u, v, w] : ans) {
        cout << u << " " << v << " " << w << "\n";
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
