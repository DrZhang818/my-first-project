#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;

    int m = 1;
    vector<pair<int, int>> e(n + 1);

    auto get = [&](auto& mp, i64 x) {
        if(mp.find(x) == mp.end()) mp[x] = m++;
        return mp[x];
    };

    map<int, int> L, R;
    for(int i = 1; i <= n; i++) {
        i64 x;
        cin >> x;
        e[i] = {get(L, x - i), get(R, x + i)};
    }

    vector<vector<pair<int,int>>> adj(m + 1);
    vector<int> pos(n + 1), odd(m + 1), vis(m + 1);
    for(int i = 1; i <= n; i++) {
        auto [u, v] = e[i];
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        pos[i] = u;
        odd[u] ^= 1;
    }

    auto dfs = [&](auto&& self, int u) -> void {
        vis[u] = true;
        for(auto [v, id] : adj[u]) {
            if(vis[v]) continue;
            self(self, v);
            if(odd[v]) {
                pos[id] = pos[id] == u ? v : u;
                odd[u] ^= 1;
                odd[v] ^= 1;
            }
        }
    };

    for(int u = 1; u <= m; u++) {
        if(vis[u]) continue;
        dfs(dfs, u);
        if(odd[u]) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";

    vector<vector<int>> vec(m + 1);
    for(int i = 1; i <= n; i++) {
        vec[pos[i]].push_back(i);
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < vec[i].size(); j += 2) {
            cout << vec[i][j] << " " << vec[i][j + 1] << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}