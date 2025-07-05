#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 1E9 + 7;
ll fast_pow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
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
    int cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(adj[i].size() == 1) {
            cnt++;
        }
    }
    if(cnt > 2) {
        cout << 0 << "\n";
        return;
    }
    if(cnt == 1) {
        cout << fast_pow(2, n) << "\n";
        return;
    }
    vector<int> sz(n + 1, 1);
    int c1 = 0, c2 = 0;
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        int c = adj[u].size() - (fa != 0);
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);     
            sz[u] += sz[v];
            if(c == 2) {
                if(c1 == 0) c1 = sz[v];
                else c2 = sz[v];
            } 
        }
    };
    dfs(1, 0);
    int rem = n - c1 - c2, mx = max(c1, c2);
    ll ans = fast_pow(2, rem) * (fast_pow(2, mx - min(c1, c2 + 1)) + fast_pow(2, mx - min(c2, c1 + 1))) % MOD;
    cout << ans << "\n";
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
