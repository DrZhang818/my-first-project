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

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](auto&& self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            if(u != 1 && a[v] == 0) {
                a[v] ^= 1;
                a[u] ^= 1;
                a[fa] ^= 1;
            }
        }
    };
    dfs(dfs, 1, 0);

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += a[i];
    }

    if(a[1] == 0) {
        for(int v : adj[1]) {
            if(a[v] == 1 || adj[v].size() == 1) continue;
            ans++;
            break;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}