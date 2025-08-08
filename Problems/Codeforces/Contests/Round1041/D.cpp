#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 200000;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int fac[N + 1];
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vis(n + 1);
    int rt = 1;
    for(int i = 1; i <= n; i++) {
        if(adj[i].size() > adj[rt].size()) {
            rt = i;
        }
    }
    vis[rt] = true;
    auto dfs = [&](this auto &&self, int u, int fa, bool tag) -> int {
        int cnt = 0, sz = 0;
        vector<int> son;
        for(int v : adj[u]) {
            if(v == fa) continue;
            if(vis[v]) return 0;
            vis[v] = true;
            if(adj[v].size() >= 2) {
                cnt++;
                son.push_back(v);
            } else   {
                sz++;
            }
        }
        if(cnt > 1 + tag) return 0;
        int res = fac[sz];
        if(cnt == 0) {
            if(fa == 0) {
                return res * 2LL % MOD;
            } else {
                return res;
            }
        } else if(cnt == 1) {
            res = 1LL * res * self(son[0], u, 0) % MOD;
            if(fa == 0 && adj[u].size() > 1) res = 2LL * res % MOD; 
            if(fa == 0) {
                return 2LL * res % MOD;
            } else {
                return res;
            }
        } else {
            int x = 0, y = 0;
            x = self(son[0], u, 0);
            y = self(son[1], u, 0);
            res = 2LL * res * x % MOD * y % MOD;
            return 2LL * res % MOD;
        }
    };
    int ans = dfs(rt, 0, 1);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
