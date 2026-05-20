#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<pair<int, int>> edges(n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        edges[i] = {u, v};
    }

    vector<array<int, 2>> dp(n, {-2, -2});
    auto get = [&](this auto&& self, int u, int fa, int id) -> int {
        int o = u == edges[id].first ? 0 : 1;
        if(dp[id][o] != -2) {
            return dp[id][o];
        }

        int cnt = 0, d = -1;
        bool ok = true;

        for(auto [v, eid] : adj[u]) {
            if(v == fa) {
                continue;
            }
            int t = self(v, u, eid);
            if(t < 0) {
                return dp[id][o] = -1;
            }
            cnt++;
            if(cnt == 1) {
                d = t;
            } else if(cnt == 2 && t != d || cnt >= 3) {
                return dp[id][o] = -1;
            } 
        }

        int res = -1;
        if(ok && cnt == 0) {
            res = 0;
        }
        if(ok && cnt == 2) {
            res = d + 1;
        }

        return dp[id][o] = res;
    };

    for(int i = 1; i < n; i++) {
        auto [u, v] = edges[i];
        if(get(u, v, i) != -1 && get(v, u, i) != -1) {
            cout << i << "\n";
            return;
        }
    }

    auto full = [&](int s, int ban) -> bool {
        vector<int> nodes;

        auto collect = [&](this auto&& self, int u, int fa) -> void {
            nodes.push_back(u);
            for(auto [v, id] : adj[u]) {
                if(v == fa || id == ban) continue;
                self(v, u);
            }
        };
        collect(s, 0);

        int m = nodes.size();
        if(m == 1) return true;
        if((m + 1) & m) return false;

        int rt = 0;
        for(int u : nodes) {
            int deg = 0;
            for(auto [v, id] : adj[u]) {
                if(id == ban) continue;
                deg++;
            }
            if(deg == 2) {
                rt = u;
                break;
            }
        }

        if(!rt) return false;

        auto dfs = [&](this auto&& self, int u, int fa) -> int {
            int cnt = 0, d = -1;
            for(auto [v, id] : adj[u]) {
                if(v == fa || id == ban) continue;
                int t = self(v, u);
                if(t < 0) return -1;
                cnt++;
                if(cnt == 1) {
                    d = t;
                } else if(cnt == 2 && t != d || cnt >= 3) {
                    return -1;
                }
            }
            if(cnt == 0) {
                return 0;
            }
            if(cnt == 2) {
                return d + 1;
            }
            return -1;
        };

        return dfs(rt, 0) != -1;
    };

    vector<int> cand;
    for(int u = 1; u <= n; u++) {
        int d = adj[u].size();
        if(d == 2 || d == 4) {
            for(auto [y, id] : adj[u]) {
                cand.push_back(id);
            }
        }
    }

    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());

    for(auto id : cand) {
        auto [u, v] = edges[id];
        if(full(u, id) && full(v, id)) {
            cout << id << "\n";
            return;
        }
    }
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