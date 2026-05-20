#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        deg[v]++;
        adj[u].push_back(v);
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> ans;
    while(!q.empty()) {
        int u = q.top(); q.pop();
        ans.push_back(u);
        for(int v : adj[u]) {
            if(--deg[v] == 0) {
                q.push(v);
            }
        }
    }
    if(ans.size() < n) {
        cout << -1 << "\n";
        return;
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}