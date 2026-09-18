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

vector<int> reach(const vector<vector<int>>& adj, int s) {
    vector<int> vis(adj.size()), q{s};
    vis[s] = 1;
    for(int i = 0; i < q.size(); i++) {
        for(int v : adj[q[i]]) {
            if(!vis[v]) {
                vis[v] = 1;
                q.push_back(v);
            }
        }
    }
    return vis;
}

void solve() {
    int n, m;
    cin >> n >> m;
    int s = 2 * n, t = s + 1;
    Dinic f(t + 1);
    for(int i = 0; i < n; i++) {
        f.addEdge(s, i, 1);
        f.addEdge(n + i, t, 1);
    }
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        f.addEdge(u, n + v, n + 1);
    }
    f.maxFlow(s, t);

    auto a = f.minCut(s);

    vector<vector<int>> rev(t + 1);
    for(int u = 0; u <= t; u++) {
        for(const auto& e : f.adj[u]) {
            if(e.cap > 0) {
                rev[e.to].push_back(u);
            }
        }
    }

    vector<int> b(t + 1), q{t};
    b[t] = 1;
    for(int i = 0; i < q.size(); i++) {
        for(int v : rev[q[i]]) {
            if(!b[v]) {
                b[v] = 1;
                q.push_back(v);
            }
        }
    }

    i64 x = 0, y = 0;
    for(int i = 0; i < n; i++) {
        x += a[i];
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