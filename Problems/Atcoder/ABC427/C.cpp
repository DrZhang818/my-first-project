#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector adj(n, vector<int>(n));
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u][v] = adj[v][u] = 1;
    }
    int ans = inf;
    for(int s = 0; s < 1 << n; s++) {
        int cur = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(adj[i][j] == 1) {
                    if((s >> i & 1) == (s >> j & 1)) {
                        cur++;
                    }
                }
            }
        }
        ans = min(ans, cur);
    }
    cout << ans << "\n";
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
