#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;

    using pii = pair<int,int>;

    vector<vector<pii>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
    }

    vector<bool> ok(n + 1);

    vector<int> tag(n + 1);
    tag[1] = -1;

    auto dfs = [&](this auto&& self, int u, int col) -> void {
        ok[u] = true;
        vector<pii> vec {};
        for(int i = 0; i < adj[u].size(); ) {
            auto [v, c] = adj[u][i];
            if(c != col) {
                if(c != tag[v]) {
                    if(tag[v] > 0) {
                        vec.emplace_back(v, c);
                        tag[v] = -1;
                    } else if(tag[v] == 0) {
                        vec.emplace_back(v, c);
                        tag[v] = c;                        
                    }
                }
                swap(adj[u][i], adj[u].back());
                adj[u].pop_back();
            } else {
                i++;
            }
        }

        for(auto [v, c] : vec) {
            self(v, c);
        }
    };
    dfs(1, 0);

    for(int i = 1; i <= n; i++) {
        if(ok[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
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
