#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct edge {
    int v, id;
};
struct info {
    int id, s;
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<edge>> adj(n + 1);
    vector<int> rid(2 * n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v, i << 1);
        adj[v].emplace_back(u, i << 1 | 1);
        rid[i << 1] = v;
        rid[i << 1 | 1] = u;
    }
    vector dp(2 * n, vector<int>(k + 1, -1));
    queue<info> q;
    for(auto [v, id] : adj[1]) {
        dp[id][1] = 1;
        q.push({id, 1});
    }
    vector vis(n + 1, vector<int>(k + 1));
    vector<int> ans(n + 1, inf);
    while(!q.empty()) {
        auto [id, s] = q.front(); q.pop();
        int u = rid[id], fa = rid[id ^ 1];
        if(s == k) ans[u] = min(ans[u], dp[id][s] / k);
        if(vis[u][s] == 2) continue;
        vis[u][s]++;
        for(auto [v, nid] : adj[u]) {
            if(s < k && v == fa) continue;
            int ns = s == k ? 1 : s + 1;
            if(dp[nid][ns] == -1) {
                dp[nid][ns] = dp[id][s] + 1;
                q.push({nid, ns});
            }
        }
    }
    for(int i = 2; i <= n; i++) {
        cout << (ans[i] == inf ? -1 : ans[i]) << " \n"[i == n];
    }
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
