#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void solve() {
    int n, m, V;
    cin >> n >> m >> V;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dfn(n + 1), low(n + 1), bel(n + 1);
    int timer = 0, cnt = 0;
    stack<int> stk;
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        for(int v : adj[u]) {
            if(v == fa) {
                continue;
            }
            if(!dfn[v]) {
                self(v, u);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]) {
            ++cnt;
            int v;
            do {
                v = stk.top();
                stk.pop();
                bel[v] = cnt;
            } while(v != u);
        }
    };
    dfs(1, 0);
    
    vector<int> vis(n + 1, -1);
    int ans = 1;
    for(int i = 1; i <= n; i++) {
        if(vis[i] != -1) {
            continue;
        }
        queue<int> q;
        q.push(i);
        vis[i] = 0;
        bool bip = true;
        vector<int> val;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            val.push_back(a[u]);
            for(int v : adj[u]) {
                if(bel[v] != bel[u]) {
                    continue;
                }
                if(vis[v] == -1) {
                    vis[v] = vis[u] ^ 1;
                    q.push(v);
                } else if(vis[v] == vis[u]) {
                    bip = false;
                }
            }
        }
        int x = -1;
        for(int y : val) {
            if(y != -1) {
                if(x != -1 && x != y) {
                    cout << 0 << "\n";
                    return;
                }
                x = y;
            }
        }
        if(bip) {
            if(x == -1) {
                ans = 1LL * ans * V % MOD;
            }
        } else {
            if(x > 0) {
                cout << 0 << "\n";
                return;
            }
        }
    }
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
