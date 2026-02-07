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
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    vector<vector<int>> adj(n + 1);
    vector<PII> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        e[i] = {u, v};
    }

    vector<int> p(m + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(), 
        [&](auto x, auto y) {
            auto [u, v] = e[x];
            auto [z, w] = e[y];
            return max(d[u], d[v]) < max(d[z], d[w]);
        });

    vector<int> col(n + 1, -1);
    vector<int> ans(m + 1);
    for(int i = 1; i <= m; i++) {
        auto [u, v] = e[p[i]];
        if(d[u] < d[v]) {
            swap(u, v);
        }
        if(col[v] == -1 && col[u] == -1) {
            col[v] = 0;
            col[u] = 1;
        } else if(col[v] == -1) {
            col[v] = col[u] ^ 1;
        } else if(col[u] == -1) {
            col[u] = col[v] ^ 1;
        }
        ans[p[i]] = max(d[u], d[v]);
    }

    for(int u = 1; u <= n; u++) {
        bool ok = false;
        for(int v : adj[u]) {
            if(d[v] <= d[u] && col[u] != col[v]) {
                ok = true;
                break;
            }
        }
        if(!ok) {
            cout << -1 << "\n";
            return;
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << "BW"[col[i]];
    }
    cout << "\n";

    for(int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
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
