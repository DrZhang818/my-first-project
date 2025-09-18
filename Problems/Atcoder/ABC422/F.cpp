#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void chmin(ll &x, ll y) {
    if(x > y) {
        x = y;
    }
}

void solve1() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<unordered_map<ll,ll>> dp(n + 1);
    dp[1][a[1]] = 0;
    using T = tuple<ll,ll,int>;
    priority_queue<T, vector<T>, greater<T>> q;
    q.emplace(0, a[1], 1);
    while(!q.empty()) {
        auto [val, w, u] = q.top(); q.pop();
        for(int v : adj[u]) {
            ll nval = val + w;
            ll nw = w + a[v];
            bool ok = find_if(dp[v].begin(), dp[v].end(), 
                [&](auto &p) {
                    return p.first <= nw && p.second <= nval;
                }) != dp[v].end();
            if(ok) {
                continue;
            }
            dp[v][nw] = nval;
            q.emplace(nval, nw, v);
        }
    }
    for(int i = 1; i <= n; i++) {
        ll mn = inf;
        for(auto [_, val] : dp[i]) {
            chmin(mn, val);
        }
        cout << mn << "\n";
    }
}

void solve2() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector dp(n + 1, vector<ll>(n, inf));
    for(int i = 0; i < n; i++) {
        dp[1][i] = 1LL * i * a[1];
    }
    for(int k = n - 1; k >= 1; k--) {
        for(int u = 1; u <= n; u++) {
            for(int v : adj[u]) {
                chmin(dp[v][k - 1], dp[u][k] + 1LL * a[v] * (k - 1));
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << dp[i][0] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve1();
    }
    return 0;
}
