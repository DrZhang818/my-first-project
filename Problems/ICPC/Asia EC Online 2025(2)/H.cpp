#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 3000;
const int MOD = 998244353;

int fac[N + 1];

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dep(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        dep[u] = dep[fa] + 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
        }
    };

    int ans = 1;
    for(int i = 1; i < n; i++) {
        dfs(i, 0);
        for(int j = i + 1; j <= n; j++) {
            int x = dep[j];
            int cur = mod(fac[x] - 2LL * fac[x - 1] % MOD + fac[x - 2]);
            add(ans, cur);
        }        
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * i * fac[i - 1] % MOD;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
