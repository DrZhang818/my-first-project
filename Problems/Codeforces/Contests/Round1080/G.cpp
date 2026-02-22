#include <bits/stdc++.h>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = 1E18;

constexpr int MX = 1000000007;

void solve() {  
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    adj[0].push_back(1);
    for(int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        if(u == 0 && v == 0) continue;
        adj[i].push_back(u);
        adj[i].push_back(v);
    }

    vector<ll> dp(n + 1);

    vector<int> in(n + 1);
    vector<int> rev(3 * n + 10);
    vector<int> fa(n + 1);
    int timer = 0;

    auto dfs = [&](this auto&& self, int u) -> void {
        if(u > 0) {
            in[u] = ++timer;
            rev[timer] = u;
        }
        for(int v : adj[u]) {
            fa[v] = u;
            self(v);
            if(dp[v] == inf) {
                dp[u] = inf;
            }
            dp[u] += dp[v] + 2;
            rev[++timer] = u;
            if(dp[u] >= MX) {
                dp[u] = inf;
            }
        }
    };
    dfs(0);

    vector<vector<ll>> st(n + 1, vector<ll>(30));
    vector<vector<ll>> p(n + 1, vector<ll>(30));

    for(int i = 1; i <= n; i++) {
        st[i][0] = dp[i];
        p[i][0] = fa[i];
    }

    for(int i = 1; i < 30; i++) {
        for(int j = 1; j <= n; j++) {
            p[j][i] = p[p[j][i - 1]][i - 1];
            st[j][i] = st[j][i - 1] + 1 + st[p[j][i - 1]][i - 1];
            if(st[j][i] >= MX) {
                st[j][i] = inf;
            }
        }
    }

    while(q--) {
        int u, k;
        cin >> u >> k;

        for(int i = 29; i >= 0; i--) {
            if(p[u][i] == 0 || st[u][i] + 1 >= k) continue;
            k -= st[u][i] + 1;
            u = p[u][i];
        }

        cout << rev[in[u] + k] << " ";
    }
    cout << "\n";

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
