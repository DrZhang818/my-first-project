#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> g(k);
    vector vis(k, vector<bool>(k));
    vector<int> path;
    path.reserve(k * k);
    vis[k - 1][0] = true;
    auto dfs = [&](this auto &&self, int u) -> void {
        for(; g[u] < k; g[u]++) {
            int v = g[u];
            if(!vis[u][v]) {
                vis[u][v] = true;
                self(v);
            }
        }
        path.push_back(u);
    };
    dfs(0);
    int sz = path.size();
    for(int i = 0; i < n; i++) {
        cout << char('a' + path[i % sz]);
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
