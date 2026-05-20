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
    vector<int> h(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    vector<vector<int>> adj(n + 1);
    for(int v = 2; v <= n; v++) {
        int u;
        cin >> u;
        adj[u].push_back(v);
    }

    vector<int> w(n + 1);
    for(int i = 2; i <= n; i++) {
        cin >> w[i];
    }

    vector<i64> dp(n + 1);

    auto dfs = [&](auto&& self, int u, int fa, i64 sum) -> void {
        sort(adj[u].begin(), adj[u].end(),
            [&](int x, int y) {
                return w[x] < w[y];
            });
        int las = 0;
        for(int v : adj[u]) {
            sum += w[v] - las;

            self(self, v, u, sum);
            sum = dp[v];

            las = w[v];
        }
        sum += h[u] - las;
        dp[u] = sum;
    };  
    dfs(dfs, 1, 0, 0);

    for(int i = 1; i <= n; i++) {
        cout << dp[i] << " \n"[i == n];
    }
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