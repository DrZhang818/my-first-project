#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> p(n + 1);
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
        adj[p[i]].push_back(i);
    }

    vector<int> vis(n + 1);
    int u = 1;
    while(!vis[u]) {
        vis[u] = true;
        u = p[u];
    }

    vector<int> cycle;
    vector<bool> tag(n + 1);
    while(1) {
        cycle.push_back(u);
        u = p[u];
        tag[u] = true;
        if(u == cycle[0]) {
            break;
        }
    }

    if(cycle.size() % 2 == 0) {
        cout << "POSSIBLE\n";
        return;
    }

    vector<int> val(n + 1);
    vector<int> cnt(n + 1);

    auto dfs = [&](this auto&& self, int u) -> void {
        for(int v : adj[u]) {
            if(tag[v]) continue;
            self(v);
        }

        for(int v : adj[u]) {
            if(tag[v]) continue;
            if(val[v] <= n) {
                cnt[val[v]]++;
            }
        }

        int mex = 0;
        while(cnt[mex]) {
            mex++;
        }
        val[u] = mex;

        for(int v : adj[u]) {
            if(tag[v]) continue;
            cnt[val[v]] = 0;
        }
    };

    int mn = n + 1, mx = -1;

    for(int u : cycle) {
        dfs(u);
        mn = min(mn, val[u]);
        mx = max(mx, val[u]);
    }

    if(mn != mx) {
        cout << "POSSIBLE\n";
        return; 
    }

    cout << "IMPOSSIBLE\n";
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

