#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int cnt, id;
    friend bool operator < (const info &a, const info &b) {
        if(a.cnt != b.cnt) return a.cnt < b.cnt;
        return a.id < b.id;
    }
};
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
    int p = 1;
    vector<int> sz(n + 1, 1), w(n + 1);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            w[u] = max(w[u], sz[v]);
        }
        if(max(w[u], n - sz[u]) <= n / 2) {
            p = u; 
        }
    };
    dfs(dfs, 1, 0);
    vector<int> a;
    auto dfs2 = [&](auto &&self, int u, int fa) -> void {
        a.push_back(u);
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
        }
    };
    for(int v : adj[p]) {
        dfs2(dfs2, v, p);
    }
    if(n % 2 == 0) {
        a.push_back(p);
    }
    for(int i = 0; i < n / 2; i++) {
        cout << a[i] << " " << a[i + n / 2] << "\n";
    }
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
