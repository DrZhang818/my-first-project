#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> col(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> col[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> in(n + 1), out(n + 1), ord(n + 1);
    vector<int> sz(n + 1, 1);
    int timer = 1;

    auto work = [&](auto&& self, int u, int fa) -> void {
        auto it = find(adj[u].begin(), adj[u].end(), fa);
        if(it != adj[u].end()) {
            swap(adj[u].back(), *it);
            adj[u].pop_back();
        }
        for(int& v : adj[u]) {
            self(self, v, u);
            sz[u] += sz[v];
            if(sz[v] > sz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    };

    work(work, 1, 0);

    vector<int> cnt(n + 1);
    vector<ll> ans(n + 1, 1LL * n * (n + 1) / 2);
    vector<ll> del(n + 1);

    auto add = [&](auto&& self, int u, int tar) -> int {
        if(cnt[col[u]] == 0) {
            del[col[u]] += sz[u];
        }
        cnt[col[u]]++;
        int res = cnt[tar] == 0 ? 1 : 0;
        for(auto v : adj[u]) {
            res += self(self, v, tar);
        }
        cnt[col[u]]--;
        return res;
    };  

    auto dfs = [&](auto &&self, int u) -> void {
        in[u] = timer++;
        ord[in[u]] = u;

        for(auto v : adj[u]) {
            if(v == adj[u][0]) continue;
            self(self, v);
            for(int x = in[v]; x < out[v]; x++) {
                del[col[ord[x]]] = 0;
            }
        }

        if(!adj[u].empty()) {
            self(self, adj[u][0]);
            int s = sz[adj[u][0]] - del[col[u]];
            ans[col[u]] -= 1LL * s * (s + 1) / 2;
        }

        for(auto v : adj[u]) {
            if(v == adj[u][0]) continue;
            ll res = add(add, v, col[u]);
            ans[col[u]] -= res * (res + 1) / 2;
        }

        del[col[u]] = sz[u];

        if(u == 1) {
            for(int i = 1; i <= n; i++) {
                if(i != col[u]) {
                    ll s = n - del[i];
                    ans[i] -= s * (s + 1) / 2;
                }
            }
        }

        out[u] = timer;
    };

    dfs(dfs, 1);

    for(int i = 1; i <= n; i++) {
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
