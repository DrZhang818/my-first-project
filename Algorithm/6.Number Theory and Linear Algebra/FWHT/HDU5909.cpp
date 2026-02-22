#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 1000000007;
constexpr int inv2 = (MOD + 1) / 2;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void fwht(vector<int>& a, auto merge) {
    int n = a.size();
    for(int i = 1; i < n; i <<= 1) {
        for(int j = 0; j < n; j += i << 1) {
            for(int k = 0; k < i; k++) {
                merge(a[j + k], a[j + i + k]);
            }
        }
    }
}

vector<int> work(vector<int> a, vector<int>&& b) {
    int n = a.size();
    auto f = [](auto& x, auto& y) { 
        auto u = x, v = y;
        y = MOD - y;
        add(x, v);
        add(y, u);
    };
    auto g = [](auto& x, auto& y) {
        auto u = x, v = y;
        x = 1LL * (u + v) * inv2 % MOD;
        y = 1LL * (u - v + MOD) * inv2 % MOD;
    };

    fwht(a, f);
    fwht(b, f);

    for(int i = 0; i < n; i++) {
        a[i] = 1LL * a[i] * b[i] % MOD;
    }

    fwht(a, g);
    return a;
}

void solve() {  
    int n, m;
    cin >> n >> m;

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

    vector<int> ans(m);
    vector<vector<int>> dp(n + 1, vector<int>(m));

    auto dfs = [&](auto&& self, int u, int fa) -> void {
        dp[u][a[u]] = 1;

        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            auto c = work(dp[u], move(dp[v]));
            for(int s = 0; s < m; s++) {
                add(dp[u][s], c[s]);
            }
        }

        for(int s = 0; s < m; s++) {
            add(ans[s], dp[u][s]);
        }
    };

    dfs(dfs, 1, 0); 
    
    for(int s = 0; s < m; s++) {
        cout << ans[s] << " \n"[s == m - 1];
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
