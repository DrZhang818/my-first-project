#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

struct Edge {
    int u, v;
};

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<Edge> e(m);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v});
    }

    vector<int> dp(n + 1);
    dp[1] = 1;

    for(int t = 1; t <= k; t++) {
        vector<int> ndp(n + 1);
        for(int i = 1; i <= n; i++) {
            add(ndp[1], dp[i]);
        }
        for(int i = 2; i <= n; i++) {
            ndp[i] = ndp[i - 1];
        }
        for(int i = 1; i <= n; i++) {
            add(ndp[i], MOD - dp[i]);
        }
        for(auto [u, v] : e) {
            add(ndp[u], MOD - dp[v]);
            add(ndp[v], MOD - dp[u]);
        }
        dp = move(ndp);
    }

    cout << dp[1] << "\n";
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
