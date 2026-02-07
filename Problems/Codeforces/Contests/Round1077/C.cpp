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
    vector<int> fa(n + 1);
    for(int i = 1; i < n; i++) {
        fa[i] = i + 1;
    }
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        fa[u] = max(fa[u], v);
    }

    vector<vector<int>> adj(n + 1);
    vector<int> dep(n + 1);
    for(int i = n - 1; i >= 1; i--) {
        dep[i] = dep[fa[i]] + 1;
        adj[fa[i]].push_back(i);
    }

    ll ans = 0;

    auto a = dep;
    sort(a.begin() + 1, a.end(), greater<int>());
    for(int l = 1, r = 1; l <= n; l = r) {
        while(r <= n && a[r] == a[l]) {
            r++;
        }
        ans += 1LL * (r - l) * (r - 2) * a[l]; 
    }
    
    int timer = 1;
    vector<int> in(n + 1), out(n + 1), ord(n + 1), sz(n + 1, 1);

    auto work = [&](this auto&& self, int u) -> void {
        for(auto& v : adj[u]) {
            self(v);
            sz[u] += sz[v];
            if(sz[v] > sz[adj[u][0]]) {
                swap(adj[u][0], v);
            } 
        }
    };

    work(n);

    vector<int> cnt(n + 1);

    auto dfs = [&](this auto&& self, int u) -> void {
        in[u] = timer++;
        ord[in[u]] = u;

        for(int i = 1; i < adj[u].size(); i++) {
            int v = adj[u][i];
            self(v);
            for(int x = in[v]; x < out[v]; x++) {
                cnt[dep[ord[x]]]--;
            }            
        }
        int sum = 0;
        
        if(!adj[u].empty()) {
            self(adj[u][0]);
            sum = sz[adj[u][0]];
        }

        ans -= 1LL * sum * dep[u];
        sum += 1;
        cnt[dep[u]]++;

        for(int i = 1; i < adj[u].size(); i++) {
            int v = adj[u][i];
            ans -= 1LL * sum * sz[v] * dep[u];
            sum += sz[v];
            for(int x = in[v]; x < out[v]; x++) {
                ans -= 1LL * cnt[dep[ord[x]]] * dep[u];
            }
            for(int x = in[v]; x < out[v]; x++) {
                cnt[dep[ord[x]]]++;
            } 
        }

        out[u] = timer;
    };

    dfs(n);

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
