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
    vector<int> deg(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<vector<int>> nadj(n + 1);
    for(int i = 1; i <= n; i++) {
        nadj[deg[i]].push_back(i);
    }

    vector<int> kind;
    for(int i = 1; i <= n; i++) {
        kind.push_back(deg[i]);
    }
    sort(kind.begin(), kind.end());
    kind.erase(unique(kind.begin(), kind.end()), kind.end());

    int mx = *max_element(deg.begin() + 1, deg.end());

    vector<int> s;
    vector<int> ans(n + 1, inf);

    for(int i = kind.size() - 1; i >= 1; i--) {
        int d = kind[i];
        for(int u : nadj[d]) {
            s.push_back(u);
        }        

        queue<int> q;
        vector<int> vis(n + 1);
        for(int u : s) {
            q.push(u);
            vis[u] = true;
        }

        int dis = 0;
        while(!q.empty()) {
            int sz = q.size();
            dis++;
            while(sz--) {
                int u = q.front(); q.pop();
                for(int v : adj[u]) {
                    if(vis[v] || ans[v] <= dis) continue;
                    vis[v] = true;
                    q.push(v);
                    ans[v] = dis;
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(ans[i] == inf) {
            cout << -1 << " ";
        } else {
            cout << ans[i] << " ";
        }
    }
    cout << "\n";
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
