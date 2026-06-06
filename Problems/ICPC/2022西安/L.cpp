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
    
    vector<vector<int>> adj(n + 1);
    for(int u = 2; u <= n; u++) {
        int v;
        cin >> v;
        adj[v].push_back(u);
    }

    vector<int> h(n + 1), cnt(n + 1);
    auto dfs = [&](this auto&& self, int u) -> void {
        h[u] = 0;
        for(int v : adj[u]) {
            self(v);
            h[u] = max(h[u], h[v] + 1);
        }
        cnt[h[u]]++;
    };
    dfs(1);

    int ans = inf;
    for(int i = 0; i <= n; i++) {
        ans = min(ans, i + cnt[i]);
    }

    cout << ans << "\n";
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