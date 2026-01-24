#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {  
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = 0;
    auto dfs = [&](auto &&self, int u, int fa, int d) -> int {
        int sz = 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            int c = self(self, v, u, d + 1);
            sz += c;
            add(ans, 1LL * c * (n - c - d) % MOD);
        }
        add(ans, d - 1);
        return sz;
    };
    dfs(dfs, 1, 0, 1);
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
