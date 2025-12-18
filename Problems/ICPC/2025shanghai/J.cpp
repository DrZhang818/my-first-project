#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;
    vector<array<vector<int>,9>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u][w].push_back(v);
        adj[n][w].push_back(v);
    }

    vector<int> a{n};

    auto dfs = [&](this auto &&self, int len) -> bool {
        if(len) {
            int t = k;
            for(int i = 0; i < t && i < a.size(); i++) {
                cout << len << "\n";
                k--;
            }
        }
        if(k == 0) return true;
        auto t = a;
        for(int i = 1; i <= 8; i++) {
            vector<int> na;
            for(int u : t) {
                if(na.size() > k) break;
                for(int v : adj[u][i]) {
                    na.push_back(v);
                }
            }
            if(na.empty()) continue;
            swap(a, na);
            if(self(len + 1)) return true;
        }
        return false;
    };

    dfs(0);

    while(k > 0) {
        cout << -1 << "\n";
        k--;
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
