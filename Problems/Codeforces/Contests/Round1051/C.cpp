#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, tag;
};
void solve() {
    int n;
    cin >> n;
    vector<int> ans(n + 1), deg(n + 1);
    queue<int> q;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        adj[u].emplace_back(v, x > y);
        adj[v].emplace_back(u, x < y);
        deg[u]++;
        deg[v]++;
    }
    vector<int> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 1) {
            q.push(i);
            vis[i] = true;
        }
    }
    int L = 1, R = n;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = true;
        if(L == R) {
            ans[u] = L;
            break;
        }
        for(auto &[v, tag] : adj[u]) {
            if(vis[v]) continue;
            if(tag) {
                ans[u] = R--;
            } else {
                ans[u] = L++;
            }
            if(--deg[v] == 1) {
                q.push(v);
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
