#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct Edge {
    int v, w;
    friend bool operator<(const Edge& a, const Edge& b) {
        return a.w > b.w;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> adj(n + 1), radj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        radj[v].emplace_back(u, w);
    }

    vector<i64> dis1(n + 1, inf), dis2(n + 1, inf);
    auto work = [&](auto& adj, auto& dis) {
        dis[1] = 0;
        priority_queue<Edge> q;
        q.emplace(1, 0);

        while(!q.empty()) {
            auto [u, w] = q.top(); q.pop();
            if(dis[u] != w) continue;
            for(auto [v, c] : adj[u]) {
                if(w + c < dis[v]) {
                    dis[v] = w + c;
                    q.emplace(v, dis[v]);
                }
            }
        }
    };

    work(adj, dis1);
    work(radj, dis2);

    i64 ans = 0;
    for(int i = 2; i <= n; i++) {
        ans += dis1[i] + dis2[i];
    }
    cout << ans << "\n";
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
