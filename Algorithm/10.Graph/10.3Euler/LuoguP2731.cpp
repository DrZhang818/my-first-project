#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 500;

struct Info {
    int v, id;
    friend bool operator<(const Info& a, const Info& b) {
        return a.v < b.v;
    }
};

void solve() {  
    int m;
    cin >> m;
    vector<vector<Info>> adj(N + 1);
    vector<int> deg(N + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }

    int S = -1, T = -1;

    for(int i = 1; i <= N; i++) {
        if(deg[i] & 1) {
            if(S == -1) {
                S = i;
            } else if(T == -1) {
                T = i;
            }
        }     
    }

    if(S == -1) {
        for(int i = 1; i <= N; i++) {
            if(deg[i] > 0) {
                S = i;
                break;
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<int> ans;
    vector<int> cur(N + 1);
    vector<bool> vis(m + 1);

    auto dfs = [&](auto&& self, int u) -> void {
        while(cur[u] < adj[u].size()) {
            auto [v, id] = adj[u][cur[u]++];
            if(!vis[id]) {
                vis[id] = true;
                self(self, v);
            }
        }
        ans.push_back(u);
    };

    dfs(dfs, S);

    reverse(ans.begin(), ans.end());

    for(int i = 0; i <= m; i++) {
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
