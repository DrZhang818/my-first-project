#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Dinic {
    struct Edge {
        int to, reverse;
        i64 capacity;
    };
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, iter;
    Dinic(int n_ = 0) : n(n_), adj(n_), level(n_), iter(n_) {
    }
    int addEdge(int u, int v, i64 capacity) {
        int id = int(adj[u].size());
        int reverse = int(adj[v].size()) + (u == v);
        adj[u].push_back({v, reverse, capacity});
        adj[v].push_back({u, id, 0});
        return id;
    }
    i64 maxFlow(int s, int t, i64 limit = numeric_limits<i64>::max() / 4) {
        assert(s != t);
        i64 flow = 0;
        while(flow < limit && bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            while(flow < limit) {
                i64 pushed = dfs(s, t, limit - flow);
                if(!pushed) {
                    break;
                }
                flow += pushed;
            }
        }
        return flow;
    }
    vector<bool> minCut(int s) const {
        vector<bool> visit(n);
        queue<int> q;
        visit[s] = true;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(const auto& edge : adj[u]) {
                if(edge.capacity && !visit[edge.to]) {
                    visit[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
        return visit;
    }

  private:
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(const auto& edge : adj[u]) {
                if(edge.capacity && level[edge.to] == -1) {
                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }
    i64 dfs(int u, int t, i64 limit) {
        if(u == t) {
            return limit;
        }
        for(int& i = iter[u]; i < int(adj[u].size()); i++) {
            Edge& edge = adj[u][i];
            if(!edge.capacity || level[edge.to] != level[u] + 1) {
                continue;
            }
            i64 pushed = dfs(edge.to, t, min(limit, edge.capacity));
            if(!pushed) {
                continue;
            }
            edge.capacity -= pushed;
            adj[edge.to][edge.reverse].capacity += pushed;
            return pushed;
        }
        return 0;
    }
};

pair<i64, vector<int>> maxClosure(const vector<i64>& w, const vector<pair<int, int>>& dep) {
    int n = int(w.size()) - 1, s = 0, t = n + 1;
    Dinic f(n + 2);
    i64 sum = 0;
    for(int u = 1; u <= n; u++) {
        if(w[u] > 0) {
            sum += w[u];
        }
    }
    assert(sum < LLONG_MAX / 4);
    for(int u = 1; u <= n; u++) {
        if(w[u] > 0) {
            f.addEdge(s, u, w[u]);
        }
        if(w[u] < 0) {
            f.addEdge(u, t, -w[u]);
        }
    }
    for(auto [u, v] : dep) {
        f.addEdge(u, v, sum + 1);
    }
    i64 ans = sum - f.maxFlow(s, t);
    auto vis = f.minCut(s);
    vector<int> chosen;
    for(int u = 1; u <= n; u++) {
        if(vis[u]) {
            chosen.push_back(u);
        }
    }
    return {ans, chosen};
}
