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
    vector<vector<PII>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    int st = 0;
    for(int u = 1; u <= n; u++) {
        if(adj[u].size() == 1) {
            st = u;
            break;
        }
    }
    vector<int> ans(n);
    int lo = 0, hi = n - 2;
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        int d = adj[u].size() - (fa != 0);
        for(auto [v, id] : adj[u]) {
            if(v == fa) continue;
            if(d == 1) {
                ans[id] = lo == 0 ? lo++ : hi--;
            } else {
                ans[id] = lo++;
            }
        }
        for(auto [v, _] : adj[u]) {
            if(v == fa) continue;
            self(v, u);
        }
    };
    dfs(st, 0);
    for(int i = 1; i < n; i++) {
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
