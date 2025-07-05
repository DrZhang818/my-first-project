#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


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
    int st = -1;
    for(int i = 1; i <= n; i++) {
        if(adj[i].size() == 2) {
            st = i;
            break;
        }
    }
    if(st == -1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<PII> ans;
    auto dfs = [&](this auto &&self, int u, int fa, int tag) -> void {
        if(u == st) {
            int x = adj[u][0], y = adj[u][1];
            ans.emplace_back(x, u);
            ans.emplace_back(u, y);
            self(x, u, tag);
            self(y, u, tag ^ 1);
            return;
        }
        for(int v : adj[u]) {
            if(v != fa) {
                if(tag == 0) {
                    ans.emplace_back(u, v);
                } else {
                    ans.emplace_back(v, u);
                }
                self(v, u, tag ^ 1);
            }
        }

    };
    dfs(st, 0, 0);
    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
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
