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
struct node {
    int u;
    ll t;
    friend bool operator < (const node &a, const node &b) {
        return a.t > b.t;
    }
};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    priority_queue<node> q;
    vector<int> a(n + 1);
    vector<vector<info>> adj(n + k + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] == 0) {
            q.push({i, 0});
        }
    }
    for(int i = 1; i <= k; i++) {
        int t, c;
        cin >> t >> c;
        q.push({n + i, t});
        for(int j = 1; j <= c; j++) {
            int o;
            cin >> o;
            adj[n + i].emplace_back(o, -1);
        }
    }    
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    vector<ll> ans(n + 1, -1);
    while(!q.empty()) {
        auto [u, t] = q.top(); q.pop();
        if(u <= n) {
            if(ans[u] != -1) {
                continue;
            }
            if(--a[u] <= 0) {
                ans[u] = t;
                for(auto [v, w] : adj[u]) {
                    if(ans[v] != -1) continue;
                    q.push({v, t + w});
                }
            } 
        } else {
            for(auto [v, _] : adj[u]) {
                if(ans[v] != -1) continue;
                a[v] = 0;
                q.push({v, t});                
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
    while(t--) {
        solve();
    }
    return 0;
}
