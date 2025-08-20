#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, t;
    cin >> n >> t;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> d(n + 1, 1);
    int st;
    cin >> st;
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            d[u] = d[v] + 1;
        }
    };
    dfs(st, 0);
    for(int v : adj[st]) {
        if(d[v] & 1) {
            cout << "Ron\n";
            return;
        }
    }
    cout << "Hermione\n";
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
