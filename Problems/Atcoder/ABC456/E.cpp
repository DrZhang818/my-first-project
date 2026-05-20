#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for(int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    int w;
    cin >> w;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    vector<vector<int>> adj(w * n + 1);

    auto get = [&](int i, int day) {
        return i + day * n;
    };

    for(int i = 1; i <= n; i++) {
        const auto& cur = s[i];
        for(int j = 1; j < w; j++) {
            if(cur[j - 1] == 'o' && cur[j] == 'o') {
                adj[get(i, j - 1)].push_back(get(i, j));
            }
        }
        if(cur[w - 1] == 'o' && cur[0] == 'o') {
            adj[get(i, w - 1)].push_back(i);
        }
    }

    for(auto [u, v] : edges) {
        for(int i = 0; i < w; i++) {
            if(s[u][i] == 'o' && s[v][(i + 1) % w] == 'o') {
                adj[get(u, i)].push_back(get(v, (i + 1) % w));
            }
            if(s[v][i] == 'o' && s[u][(i + 1) % w] == 'o') {
                adj[get(v, i)].push_back(get(u, (i + 1) % w));
            }
        }
    }

    vector<int> vis(w * n + 1);

    auto dfs = [&](this auto&& self, int u) -> bool {
        vis[u] = 1;
        for(int v : adj[u]) {
            if(vis[v] == 0) {
                if(self(v)) {
                    return true;
                }
            } else if(vis[v] == 1) {
                return true;
            }
        }
        vis[u] = 2;
        return false;
    };

    for(int i = 1; i <= n; i++) {
        if(vis[i] == 0 && dfs(i)) {
            cout << "Yes\n";
            return;
        }
    }

    cout << "No\n";
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