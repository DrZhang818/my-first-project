#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;

struct info {
    int v, w;
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 2; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    ll mn = inf;
    vector<ll> ans(n + 1);
    auto dfs = [&](auto &&self, int u, int fa, ll rem) -> void {
        rem += a[u];
        for(auto [v, w] : adj[u]) {
            if(v == fa) {
                if(a[u] + a[v] > 2 * w) {
                    mn = min(mn, ans[u] + max(0LL, rem - w));
                }
                continue;
            }
            ans[v] = max(ans[u], ans[u] + w - rem);
            if(a[v] + a[u] > 2 * w) mn = min(mn, ans[v]);
            self(self, v, u, max(0LL, rem - w));
        }
    };
    dfs(dfs, 1, 0, 0);
    for(int i = 2; i <= n; i++) {
        cout << min(ans[i], mn) << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
