#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= 2;
    }
    
    vector<vector<int>> adj(n + 1);
    vector<int> s(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        s[u] ^= a[v];
        s[v] ^= a[u];
    }
    vector<int> ans;

    vector<int> vis(n + 1);
    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        if(a[u] == 0 && s[u] == 1) {
            ans.push_back(u);
            vis[u] = true;
        }        
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            if(a[u] == 0 && s[u] == 1 && vis[u] == false) {
                ans.push_back(u);
                vis[u] = true;
            }
        }
        if(!vis[u] && (s[u] ^ a[u])) {
            ans.push_back(u);
            for(int v : adj[u]) {
                s[v] ^= a[u];
            }
            vis[u] = true;
        }
    };

    dfs(1, 0);

    auto dfs2 = [&](this auto&& self, int u, int fa) -> void {
        if(!vis[u] && (s[u] ^ a[u])) {
            ans.push_back(u);
            vis[u] = true;
            for(int v : adj[u]) {
                s[v] ^= a[u];
            }
        }
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
        }
    };

    dfs2(1, 0);

    if(ans.size() < n) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for(int x : ans) {
        cout << x << " \n"[x == ans.back()];
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
