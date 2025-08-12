#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> w(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll ans = 0;
    auto dfs = [&](this auto &&self, int u, int fa) -> set<int> {
        set<int> st1;
        int cnt = 0, color = 0;
        set<int> vis;
        for(int v : adj[u]) {
            if(v == fa) continue;
            auto st2 = self(v, u);
            if(st1.size() < st2.size()) {
                swap(st1, st2);
            }
            for(int x : st2) {
                if(!vis.contains(x) && st1.contains(x)) {
                    cnt++;
                    vis.insert(x);
                    color = x;
                } 
                st1.insert(x);
            }
        }
        if(cnt >= 2) {
            ans += w[u];
        } else if(cnt == 1) {
            if(c[u] == 0) {
                c[u] = color;
            } else if(c[u] != color) {
                ans += w[u];
            }
        }
        if(c[u] == 0 && !st1.empty()) {
            c[u] = *st1.begin();
        }
        if(c[u] != 0) {
            st1.insert(c[u]);
        }
        return st1;
    };
    dfs(1, 0);
    if(c[1] == 0) c[1] = 1;
    auto color = [&](this auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            if(c[v] == 0) {
                c[v] = c[u];
            }
            self(v, u);
        }
    };
    color(1, 0);
    cout << ans << "\n";
    for(int i = 1; i <= n; i++) {
        cout << c[i] << " \n"[i == n];
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
