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

    vector<int> ok(n + 1);

    auto dfs = [&](this auto&& self, int u, int fa, int d) -> bool {
        if(adj[u].size() == 1) {
            return true;
        }
        int cnt = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            if(self(v, u, (d + 1) % k)) {
                cnt++;
            }
        }

        if(d == 0 && k > 1) {
            ok[u] = self(u, fa, 1);
        }

        if(d == 0) {
            return cnt >= 2 || (cnt >= 1 && ok[fa]);
        }
        return cnt >= 1;
    };
    bool ans = dfs(st, 0, 0);

    if(ans) {
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
