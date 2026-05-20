#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, k, st;
    cin >> n >> k >> st;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](this auto&& self, int u, int fa) -> int {
        if(adj[u].size() == 1) {
            return 0;
        }
        int d1 = inf, d2 = inf;
        for(int v : adj[u]) {
            if(v == fa) continue;
            int d = self(v, u) + 1;
            if(d < d1) {
                d2 = d1;
                d1 = d;
            } else if(d < d2) {
                d2 = d;
            }
        }
        if(d1 + d2 <= k + 1) {
            return 0;
        }
        return d1;
    };

    if(dfs(st, 0) == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
