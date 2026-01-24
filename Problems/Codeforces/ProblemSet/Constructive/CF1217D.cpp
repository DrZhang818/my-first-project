#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<PII> edges(m + 1);
    vector<int> deg(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        edges[i] = {u, v};
        deg[v]++;
    }
    queue<int> q;
    int cnt = 0;
    for(int u = 1; u <= n; u++) {
        if(deg[u] == 0) {
            q.push(u);
            cnt++;
        }
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(--deg[v] == 0) {
                q.push(v);
                cnt++;
            }
        }
    }
    cout << (cnt == n ? 1 : 2) << "\n";
    vector<int> ans(m + 1, 1);
    if(cnt != n) {
        for(int i = 1; i <= m; i++) {
            auto [u, v] = edges[i];
            ans[i] = u < v ? 1 : 2;
        }
    }
    for(int i = 1; i <= m; i++) {
        cout << ans[i] << " \n"[i == m];
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
