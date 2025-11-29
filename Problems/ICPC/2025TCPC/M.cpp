#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector has(k + 1, vector<int>{});
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        has[x].push_back(i);
    }
    vector adj(n + 1, vector<int>{});
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dis(n + 1, inf);
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(dis[v] != inf) {
                continue;
            }
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }
    for(int i = 1; i <= k; i++) {
        int ans = 0;
        for(int o : has[i]) {
            ans = max(ans, dis[o]);
        }
        cout << ans << " \n"[i == k];
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
