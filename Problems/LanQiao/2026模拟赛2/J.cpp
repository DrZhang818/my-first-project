#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void dfs(const auto& adj, auto& bel, auto& dis, int u, int rt) {
    bel[u] = rt;
    for(auto [v, w] : adj[u]) {
        if(bel[v] != -1) continue;
        dis[v] = dis[u] + w;
        dfs(adj, bel, dis, v, rt);
    }
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<pair<int, i64>>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        i64 x;
        cin >> u >> v >> x;
        adj[u - 1].push_back({v, x});
        adj[v].push_back({u - 1, -x});
    }

    vector<int> bel(n + 1, -1);
    vector<i64> dis(n + 1, 0);

    for(int i = 0; i <= n; i++) {
        if(bel[i] == -1) {
            dfs(adj, bel, dis, i, i);
        }
    }

    while(q--) {
        int l, r;
        cin >> l >> r;
        if(bel[l - 1] != bel[r]) {
            cout << "UNKNOWN\n";
            continue;
        }
        cout << dis[r] - dis[l - 1] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}