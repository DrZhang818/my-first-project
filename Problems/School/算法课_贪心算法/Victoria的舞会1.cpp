#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for(int u = 1; u <= n; u++) {
        int v;
        while(cin >> v) {
            if(v == 0) break;
            adj[u].push_back(v);
            deg[u]++;
        }
    }    

    queue<int> q;
    vector<int> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        if(deg[i] < k) {
            q.push(i);
            vis[i] = true;
        }
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(vis[v]) continue;
            if(--deg[v] < k) {
                q.push(v);
                vis[v] = true;
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            ans++;
        }
    }

    cout << ans << "\n";
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