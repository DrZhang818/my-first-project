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
struct node {
    int v;
    ll w1, w2;
    friend bool operator < (const node &a, const node &b) {
        return a.w1 > b.w1;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<ll> f(n + 1, inf);
    auto dijk = [&](int st) -> void {
        f[st] = 0;
        priority_queue<info> q;
        q.push({st, 0});
        vector<bool> vis(n + 1);
        while(!q.empty()) {
            auto [u, w] = q.top(); q.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(auto &[v, nw] : adj[u]) {
                if(f[u] + nw < f[v]) {
                    f[v] = f[u] + nw;
                    q.push({v, f[v]});
                }
            }
        }
    };
    dijk(n);
    auto Astar = [&](int st, int en, int k) -> ll {
        priority_queue<node> q;
        q.push({st, f[st], 0});
        while(!q.empty()) {
            auto [u, v, w] = q.top(); q.pop();
            if(u == en) {
                k--;
                if(k <= 0 && w != f[st]) {
                    return w;
                }
            }
            for(auto &[v, nw] : adj[u]) {
                q.push({v, w + nw + f[v], w + nw});
            }
        }
        return -1;
    };
    int ans = Astar(1, n, 2);
    cout << ans << "\n";
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
