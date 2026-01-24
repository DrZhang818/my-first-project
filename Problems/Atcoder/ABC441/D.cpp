#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    int v, w;
};

void solve() {  
    int n, m, l, s, t;
    cin >> n >> m >> l >> s >> t;
    vector adj(n + 1, vector<Info>{});
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    queue<Info> q;
    q.emplace(1, 0);
    for(int i = 1; i <= l; i++) {
        int sz = q.size();
        while(sz--) {
            auto [u, w] = q.front(); q.pop();
            for(auto [v, c] : adj[u]) {
                if(w + c <= t) { 
                    q.emplace(v, w + c);
                }
            }
        }
    }
    vector<int> canBe(n + 1);
    while(!q.empty()) {
        auto [u, w] = q.front(); q.pop();
        if(s <= w && w <= t) {
            canBe[u] = true;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(canBe[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
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
