#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> d(n + 1);
    int depth = 0;
    {
        queue<int> q;
        q.push(1);
        int cur = 1;
        while(!q.empty()) {
            depth = cur;
            int sz = q.size();
            while(sz--) {
                int u = q.front(); q.pop();
                d[u] = cur;
                for(int v : adj[u]) {
                    if(d[v] == 0) {
                        q.push(v);
                    }
                }
            }
            cur++;
        }
    }

    vector<int> w(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, x;
        cin >> u >> x;
        if(depth - d[u] <= x) {
            w[u]++;
        }
    }

    vector<int> pre(n + 1), premx(n + 1), suf(n + 1);

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        pre[u] = pre[fa] + w[u];
        premx[d[u]] = max(premx[d[u]], pre[u]);
        suf[u] = w[u];
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            suf[u] = max(suf[u], suf[v] + w[u]);
        }
    };
    dfs(1, 0);

    int ans = 0;
    for(int u = 1; u <= n; u++) {
        ans = max(ans, premx[d[u] - 1] + suf[u]);
    }
    cout << ans << "\n";
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
