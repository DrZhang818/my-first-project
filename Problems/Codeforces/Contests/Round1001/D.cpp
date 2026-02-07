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
    vector<int> L(n + 1), R(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll ans = 0;

    vector<int> a(n + 1);

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        a[u] = L[u];
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            a[u] = max(a[u], min(R[u], a[v]));
        }
        for(int v : adj[u]) {
            if(v == fa) continue;
            ans += max(0, a[v] - a[u]);
        }
    };

    dfs(1, 0);
    ans += a[1];
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
