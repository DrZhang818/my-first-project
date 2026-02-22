#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

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

    vector<i64> ans(n + 1);

    vector<i64> dp(n + 1), mx_dep(n + 1, 1), sum(n + 1);

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        sum[u] = a[u];
        int mx1 = 0, mx2 = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            mx_dep[u] = max(mx_dep[u], mx_dep[v] + 1);
            dp[u] += dp[v] + sum[v];
            sum[u] += sum[v];
            if(mx_dep[v] > mx1) {
                tie(mx1, mx2) = tuple(mx_dep[v], mx1);
            } else if(mx_dep[v] > mx2) {
                mx2 = mx_dep[v];
            }
        }

        ans[u] = dp[u];
        for(int v : adj[u]) {
            if(v == fa) continue;
            if(mx_dep[v] == mx1) {
                ans[u] = max(ans[u], dp[u] + sum[v] * mx2);
            } else {
                ans[u] = max(ans[u], dp[u] + sum[v] * mx1);
            }
            ans[u] = max(ans[u], dp[u] + ans[v] - dp[v]);
        }
    };
    dfs(1, 0);

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }

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
