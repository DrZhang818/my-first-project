#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<info>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    
    vector<int> point(k);
    for(int i = 0; i < k; i++) {
        cin >> point[i];
        point[i]--;
    }

    vector dp(1 << k, vector<int>(n, inf));
    for(int i = 0; i < k; i++) {
        dp[1 << i][point[i]] = 0;
    }

    vector<bool> inQ(n);
    for(int s = 1; s < 1 << k; s++) {
        auto &cur = dp[s];
        for(int sub = (s - 1) & s; sub > (s ^ sub); sub = (sub - 1) & s) {
            for(int i = 0; i < n; i++) {
                cur[i] = min(cur[i], dp[sub][i] + dp[s ^ sub][i]);
            }
        }
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(cur[i] < inf) {
                q.push(i);
                inQ[i] = true;
            }
        }
        while(!q.empty()) {
            int u = q.front(); q.pop();
            inQ[u] = false;
            for(auto [v, w] : adj[u]) {
                if(cur[u] + w < cur[v]) {
                    cur[v] = cur[u] + w;
                    if(!inQ[v]) {
                        inQ[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    int ans = *min_element(dp[(1 << k) - 1].begin(), dp[(1 << k) - 1].end());
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
