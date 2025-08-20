#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

struct info {
    int v, w;
};
void solve() {
    int n;
    cin >> n;
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<array<ll,2>> dp(n + 1);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        vector<ll> val;
        ll sum = 0;
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            sum += dp[v][0];
            if(w + dp[v][1] - dp[v][0] > 0) {
                val.push_back(w + dp[v][1] - dp[v][0]);
            }
        }
        sort(val.begin(), val.end(), greater<ll>());
        if(d[u] == 0) {
            dp[u][1] = -inf;
        } else {
            dp[u][1] = sum;
        }
        for(int i = 1; i <= d[u] && i <= val.size(); i++) {
            sum += val[i - 1];
            if(i < d[u]) {
                dp[u][1] = sum;
            }
        }
        dp[u][0] = sum;
    };
    dfs(dfs, 1, 0);
    cout << dp[1][0] << "\n";
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
