#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

struct info {
    int v;
    ll w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
void solve() {
    int n, m, b;
    cin >> n >> m >> b;
    vector<int> val(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    auto ck = [&](int x) -> bool {
        priority_queue<info> q;
        vector<ll> d(n + 1, inf);
        vector<bool> vis(n + 1);
        d[1] = 0;
        q.push({1, 0});
        while(!q.empty()) {
            auto [u, _] = q.top(); q.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(auto [v, w] : adj[u]) {
                if(val[v] > x) continue;
                if(d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    q.push({v, d[v]});
                }
            }
        }
        return d[n] <= b;
    };
    int l = max(val[1], val[n]) - 1, r = 1E9 + 7;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if(r >= 1E9 + 1) {
        cout << "AFK\n";
        return;
    }
    cout << r << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
