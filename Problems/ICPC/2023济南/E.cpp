#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

struct Dinic {
    struct Edge {
        int to, rev;
        i64 cap;
    };

    int n;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> level, cur;

    Dinic(int n) : n(n), adj(n), level(n), cur(n) {}

    // 返回正向边在 adj[u] 中的下标
    int addEdge(int u, int v, i64 cap) {
        int a = adj[u].size();
        int b = adj[v].size();

        adj[u].push_back({v, b + (u == v), cap});
        adj[v].push_back({u, a, 0});

        return a;
    }

    i64 maxFlow(int s, int t,
                i64 limit = std::numeric_limits<i64>::max()) {
        assert(s != t);

        i64 flow = 0;
        while (flow < limit && bfs(s, t)) {
            std::fill(cur.begin(), cur.end(), 0);

            while (flow < limit) {
                i64 f = dfs(s, t, limit - flow);
                if (f == 0) {
                    break;
                }
                flow += f;
            }
        }

        return flow;
    }

    std::vector<int> minCut(int s) const {
        std::vector<int> vis(n), q{s};
        vis[s] = 1;
        for(int i = 0; i < q.size(); i++) {
            int u = q[i];
            for(const auto& e : adj[u]) {
                if(e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = 1;
                    q.push_back(e.to);
                }
            }
        }
        return vis;
    }

private:
    bool bfs(int s, int t) {
        std::fill(level.begin(), level.end(), -1);
        std::vector<int> q{s};
        level[s] = 0;

        for (int i = 0; i < int(q.size()); i++) {
            int u = q[i];
            for (const auto &e : adj[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push_back(e.to);
                }
            }
        }

        return level[t] != -1;
    }

    i64 dfs(int u, int t, i64 f) {
        if (u == t) {
            return f;
        }

        for (int &i = cur[u]; i < int(adj[u].size()); i++) {
            auto &e = adj[u][i];

            if (e.cap == 0 || level[e.to] != level[u] + 1) {
                continue;
            }

            i64 pushed = dfs(e.to, t, std::min(f, e.cap));
            if (pushed == 0) {
                continue;
            }

            e.cap -= pushed;
            adj[e.to][e.rev].cap += pushed;
            return pushed;
        }

        return 0;
    }
};


void solve() {
    int n, m;
    cin >> n >> m;
    int s = 2 * n, t = s + 1;
    Dinic graph(t + 1);
    for(int i = 0; i < n; i++) {
        graph.addEdge(s, i, 1);
        graph.addEdge(n + i, t, 1);
    }
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph.addEdge(u, n + v, 1);
    }
    graph.maxFlow(s, t);

    i64 x = 0, y = 0;
    for(int i = 0; i < n; i++) {
        x += graph.level[i] != -1;
    }
    if(!x) {
        cout << 0 << "\n";
        return;
    }

    vector<int> b(t + 1), q;
    q.reserve(t + 1);
    q.push_back(t);
    b[t] = 1;
    for(int h = 0; h < q.size(); h++) {
        int u = q[h];
        for(const auto& [v, rev, _] : graph.adj[u]) {
            if(graph.adj[v][rev].cap > 0 && !b[v]) {
                q.push_back(v);
                b[v] = 1;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        y += b[n + i];
    }

    cout << x * y << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}