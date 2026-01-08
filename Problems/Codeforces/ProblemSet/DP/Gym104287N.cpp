#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    int v, w;
};

void solve() {  
    int n;
    cin >> n;
    vector adj(n + 1, vector<Info> {});
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<ll> f(n + 1), g(n + 1);
    vector<ll> dp(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            if(f[v] + w > f[u]) {
                g[u] = f[u];
                f[u] = f[v] + w;
            } else if(f[v] + w > g[u]) {
                g[u] = f[v] + w;
            }
            dp[u] = max(dp[u], dp[v]);
        }
        dp[u] = max(dp[u], f[u] + g[u]);
    };
    dfs(1, 0);
    ll ans = 0;
    auto work = [&](this auto &&self, int u, int fa, ll up) -> void {
        array<ll,3> val {};
        val[0] = up;
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;  
            ll x = f[v] + w;
            for(int j = 0; j < 3; j++) {
                if(x > val[j]) {
                    for(int k = 2; k > j; k--) {
                        val[k] = val[k - 1];
                    }
                    val[j] = x;
                    break;
                }
            }
        }
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            ll x = f[v] + w;
            if(x == val[0]) {
                ans = max(ans, min(dp[v], val[1] + val[2]));
                self(v, u, val[1] + w);                
            } else if(x == val[1]) {
                ans = max(ans, min(dp[v], val[0] + val[2]));
                self(v, u, val[0] + w);
            } else {
                ans = max(ans, min(dp[v], val[0] + val[1]));
                self(v, u, val[0] + w);
            }
        }
    };
    work(1, 0, 0);
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
