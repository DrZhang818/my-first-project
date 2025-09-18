#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, lim;
    cin >> n >> m >> lim;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }   
    vector<array<int,2>> dp(n + 1, {inf, inf});
    int k;
    cin >> k;
    queue<PII> q;
    for(int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        dp[x][0] = 0;
        q.push({x, 0});
    }
    while(!q.empty()) {
        auto [u, d] = q.front(); q.pop();
        if(d == lim) continue;
        for(int v : adj[u]) {
            if(dp[v][(d + 1) & 1] == inf) {
                dp[v][(d + 1) & 1] = d + 1;
                q.push({v, d + 1});
            }
        }
    }
    vector<array<int,2>> dis(n + 1, {inf, inf});
    dis[1][0] = 0;
    q.push({1, 0});
    vector<array<int,2>> pre(n + 1, {0, 0});
    while(!q.empty()) {
        auto [u, d] = q.front(); q.pop();
        for(int v : adj[u]) {
            if(dis[v][(d + 1) & 1] == inf) {
                if(d + 1 < dp[v][(d + 1) & 1]) {
                    dis[v][(d + 1) & 1] = d + 1;
                    pre[v][(d + 1) & 1] = u;
                    q.push({v, d + 1});
                }
            }
        }
    }
    int mn = min(dis[n][0], dis[n][1]);
    if(mn == inf) {
        cout << -1 << "\n";
        return;
    }
    cout << mn << "\n";
    vector<int> ans;
    for(int i = n, s = (mn & 1); i; i = pre[i][s], s ^= 1) {
        ans.push_back(i);
    }
    reverse(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
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
