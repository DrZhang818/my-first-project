#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/114593/E
void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vis(1 << 21);
    vector<int> fa(n + 1);
    auto dfs = [&](auto &&self, int u) -> void {
        for(int v : adj[u]) {
            if(v == fa[u]) continue;
            fa[v] = u;
            self(self, v);
        }
        int tp = 0, S = 0, T = 0;
        while(u && tp <= 20) {
            int x = s[u - 1] - '0';
            S |= x << tp;
            T = T << 1 | x;
            tp++;
            vis[S] = vis[T] = true;
            u = fa[u];
        }
    };
    dfs(dfs, 1);
    while(q--) {
        int x;
        cin >> x;
        if(vis[x]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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
