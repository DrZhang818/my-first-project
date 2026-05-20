#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;

    vector<vector<pair<int,int>>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    i64 lo = 1, hi = inf;
    auto dfs = [&](this auto&& self, int u, int fa, i64 S, int tag) -> void {
        if(tag == 0) {
            lo = max(lo, 1 - S);
        } else {
            hi = min(hi, S - 1);
        }
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            self(v, u, w - S, tag ^ 1);
        }
    };
    dfs(1, 0, 0, 0);

    if(lo > hi) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    vector<int> ans(n + 1);
    ans[1] = lo;
    [&](this auto&& self, int u, int fa) -> void {
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            ans[v] = w - ans[u];
            self(v, u);
        }
    }(1, 0);

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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