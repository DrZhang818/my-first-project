#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m, sz;
    cin >> n >> m >> sz;
    vector<vector<int>> adj(n + 1);
    ll tot = 0, mnodd = inf, mneven = 0;
    for(int i = 1; i <= sz; i++) {
        ll x;
        cin >> x;
        tot += x;
        if(x % 2 == 1) {
            mnodd = min(mnodd, x);
        }
    }
    ll mxodd = -inf, mxeven = 0;
    if(tot % 2 == 0) {
        mxeven = tot;
        if(mnodd != inf) {
            mxodd = tot - mnodd;
        }
    } else {
        mxodd = tot;
        mxeven = tot - mnodd;
    }
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> ans(n + 1);
    vector<array<ll,2>> vis(n + 1, {-1, -1});
    queue<pair<int,long long>> q;
    q.push({1, 0});
    while(!q.empty()) {
        auto [u, len] = q.front();
        q.pop();
        if(vis[u][len % 2] != -1) continue;
        vis[u][len % 2] = len;
        for(int v : adj[u]) {
            if(vis[v][(len + 1) % 2] == -1) {
                q.push({v, len + 1});
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        int len = inf;
        if(vis[i][0] != -1) {
            len = vis[i][0];
            if(len <= mxeven) {
                ans[i] |= 1;
            }
        }
        if(vis[i][1] != -1) {
            len = vis[i][1];
            if(len <= mxodd) {
                ans[i] |= 1;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i];
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
