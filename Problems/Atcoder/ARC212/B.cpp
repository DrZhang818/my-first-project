#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Edge {
    int v;
    ll w;
    friend bool operator<(const Edge& a, const Edge& b) {
        return a.w > b.w;
    }
};

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> adj(n + 1);
    int S = -1, T = -1, C = 0;
    for(int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
        if(i == 1) {
            S = v;
            T = u;
            C = c;
        }
    }

    vector<ll> dis(n + 1, numeric_limits<ll>::max() / 2);
    dis[S] = 0;

    priority_queue<Edge> q;
    q.push(Edge(S, 0));

    ll ans = -1;
    while(!q.empty()) {
        auto [u, w] = q.top(); q.pop();
        if(w != dis[u]) {
            continue;
        }

        if(u == T) {
            ans = w;
            break;
        }

        for(auto [v, c] : adj[u]) {
            if(w + c < dis[v]) {
                dis[v] = w + c;
                q.push({v, w + c});
            }
        }
    }

    if(ans == -1) {
        cout << -1 << "\n";
        return;
    }

    cout << ans + C << "\n";
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
