#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<pair<int,int>>> adj(n + 1);
    vector<pair<int,int>> edges(n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        edges[i] = {u, v};
    }

    vector<array<int, 2>> dp(n + 1, {-1, -1});

    auto dfs = [&](this auto&& self, int u, int id) -> int {
        int s = u == edges[id].first ? 0 : 1;
        if(dp[id][s] != -1) return dp[id][s];

        vector<int> vis(n + 1);
        auto work = [&](this auto&& work, int u, int id, int cnt, int _xor) -> void {
            if(cnt > k) return;
            for(auto [v, nid] : adj[u]) {
                if(nid == id) continue;
                _xor ^= self(v, nid);
            }

            vis[_xor] = true;
            for(auto [v, nid] : adj[u]) {
                if(nid == id) continue;
                work(v, nid, cnt + 1, _xor ^ self(v, nid));
            }
        };
        work(u, id, 1, 0);

        int mex = 0;
        while(mex <= n && vis[mex]) mex++;

        return dp[id][s] = mex;
    };

    for(int u = 1; u <= n; u++) {
        int _xor = 0;
        for(auto [v, id] : adj[u]) {
            _xor ^= dfs(v, id);
        }
        if(_xor == 0) {
            cout << 0;
        } else {
            cout << 1;
        }
    }

    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}