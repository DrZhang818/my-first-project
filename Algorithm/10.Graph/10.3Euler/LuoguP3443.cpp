#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;

    vector<vector<PII>> adj(n + 1);
    vector<PII> e(m + 1);
    vector<int> in(n + 1), out(n + 1);

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v, i);
        e[i] = {u, v};
        out[u]++;
        in[v]++;
    }

    for(int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    auto get = [&](int u, int v) {
        auto it = lower_bound(adj[u].begin(), adj[u].end(), make_pair(v, 0));
        if(it == adj[u].end() || it->first != v) {
            return -1;
        }
        return it->second;
    };

    bool ok = true;

    vector<int> pre(m + 1), nxt(m + 1);

    int t;
    cin >> t;
    while(t--) {
        int k;
        cin >> k;
        vector<int> a(k + 1);
        for(int i = 1; i <= k; i++) {
            cin >> a[i];
        }

        int las = -1;
        for(int i = 1; i < k; i++) {
            int u = a[i], v = a[i + 1];
            int now = get(u, v);
            if(now == -1) {
                ok = false;
                break;
            }

            if(las != -1) {
                if(pre[now] && pre[now] != las || nxt[las] && nxt[las] != now) {
                    ok = false;
                    break;
                }
                pre[now] = las;
                nxt[las] = now;
            }

            las = now;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(in[i] != out[i]) {
            ok = false;
            break;
        }
    }

    if(!ok) {
        cout << "NIE\n";
        return;
    }

    vector<int> ans;
    vector<int> cur(n + 1);
    vector<bool> vis(m + 1);

    auto dfs = [&](this auto&& self, int u) -> void {
        while(cur[u] < adj[u].size()) {
            auto [v, id] = adj[u][cur[u]++];
            if(vis[id] || pre[id]) {
                continue;
            }

            vector<int> path;

            int x = u;
            while(id) {
                if(vis[id]) {
                    ok = false;
                    break;
                }
                vis[id] = true;
                x = e[id].second;
                if(nxt[id]) {
                    path.push_back(x);
                }
                id = nxt[id];
            }

            self(x);

            for(int i = path.size() - 1; i >= 0; i--) {
                ans.push_back(path[i]);
            }
        }
        ans.push_back(u);
    };

    dfs(1);

    if(!ok || ans.size() != m + 1) {
        cout << "NIE\n";
        return;
    }

    reverse(ans.begin(), ans.end());

    cout << "TAK\n";
    for(int i = 0; i <= m; i++) {
        cout << ans[i] << "\n";
    }
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
