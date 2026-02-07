#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, p, q;
    cin >> n >> p >> q;
    vector<int> a(n + 1);

    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
    }    
    
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> mx(n + 1), sum(n + 1);

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        sum[u] = a[u];
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            sum[u] += sum[v];
            mx[u] = max(mx[u], sum[v]);
        }
        mx[u] = max(mx[u], tot - sum[u]);
    };
    dfs(1, 0);

    int root = 1;
    for(int i = 2; i <= n; i++) {
        if(mx[i] <= mx[root]) {
            root = i;
        }
    }

    fill(sum.begin(), sum.end(), 0);
    [&](this auto&& self, int u, int fa) -> void {
        auto it = find(adj[u].begin(), adj[u].end(), fa);
        if(it != adj[u].end()) {
            swap(adj[u].back(), *it);
            adj[u].pop_back();
        }
        sum[u] = a[u];
        for(int v : adj[u]) {
            self(v, u);
            sum[u] += sum[v];
        }
    }(root, 0);
 
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] > 0) {
            ans += q;
        }
    }

    map<ll,int> mp;

    auto work = [&](this auto&& self, int u) -> void {
        int d = 0;
        for(int v : adj[u]) {
            if(sum[v] > 0) {
                d++;
            }
        }
        if(u == root) {
            if(a[u] == 0 && d <= 2) {
                mp[0] += 1;
            }
        } else {
            if(a[u] == 0 && d <= 1) {
                mp[0] += 1;
            } else {
                mp[sum[u]] += 1;
            }
        }
        for(int v : adj[u]) {
            self(v);
        }
    };

    work(root);

    int rem = n;
    for(auto [v, c] : mp) {
        rem -= c;
        rem = max(rem, 1);
        ans = min(ans, 1LL * v * p + 1LL * rem * q);
    }
    cout << ans << "\n";
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
