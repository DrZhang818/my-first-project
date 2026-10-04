#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Dinic {
    struct Edge {
        int to, rev;
        i64 cap;
    };
    int n;
    vector<vector<Edge>> g;
    vector<int> dep, it;
    Dinic(int n_ = 0) : n(n_), g(n_), dep(n_), it(n_) {
    }
    int addEdge(int u, int v, i64 cap) {
        int id = int(g[u].size());
        int rev = int(g[v].size()) + (u == v);
        g[u].push_back({v, rev, cap});
        g[v].push_back({u, id, 0});
        return id;
    }
    i64 maxFlow(int s, int t, i64 limit = numeric_limits<i64>::max() / 4) {
        assert(s != t);
        i64 flow = 0;
        while(flow < limit && bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
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
            for(const auto& edge : g[u]) {
                if(edge.cap && !visit[edge.to]) {
                    visit[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
        return visit;
    }

  private:
    bool bfs(int s, int t) {
        fill(dep.begin(), dep.end(), -1);
        queue<int> q;
        dep[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(const auto& edge : g[u]) {
                if(edge.cap && dep[edge.to] == -1) {
                    dep[edge.to] = dep[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return dep[t] != -1;
    }
    i64 dfs(int s, int t, i64 limit) {
        vector<int> st{s};
        vector<pair<int, int>> path;
        vector<i64> val{limit};
        while(!st.empty()) {
            int u = st.back();
            if(u == t) {
                i64 f = val.back();
                for(auto [v, id] : path) {
                    auto& e = g[v][id];
                    e.cap -= f;
                    g[e.to][e.rev].cap += f;
                }
                return f;
            }
            int& i = it[u];
            while(i < int(g[u].size()) && (!g[u][i].cap || dep[g[u][i].to] != dep[u] + 1)) {
                i++;
            }
            if(i == int(g[u].size())) {
                dep[u] = -1;
                st.pop_back();
                val.pop_back();
                if(!path.empty()) {
                    int p = path.back().first;
                    path.pop_back();
                    it[p]++;
                }
            } else {
                path.push_back({u, i});
                st.push_back(g[u][i].to);
                val.push_back(min(val.back(), g[u][i].cap));
            }
        }
        return 0;
    }
};
struct BoundFlow {
    struct Edge {
        int from, to;
        i64 lo, hi;
    };
    struct Result {
        i64 value;
        vector<i64> flow;
    };
    static constexpr i64 inf = numeric_limits<i64>::max() / 4;
    int n;
    vector<Edge> edges;
    BoundFlow(int n_ = 0) : n(n_) {
    }
    int addEdge(int from, int to, i64 lo, i64 hi) {
        assert(0 <= lo && lo <= hi);
        int id = int(edges.size());
        edges.push_back({from, to, lo, hi});
        return id;
    }
    bool circulation(vector<i64>& ans) const {
        auto net = build(false, -1, -1);
        if(net.dinic.maxFlow(net.S, net.T) != net.demand) {
            return false;
        }
        ans = recover(net);
        return true;
    }
    bool maxFlow(int s, int t, Result& ans) const {
        auto net = build(true, s, t);
        if(net.dinic.maxFlow(net.S, net.T) != net.demand) {
            return false;
        }
        auto& ex = net.dinic.g[t][net.extra];
        i64 base = inf - ex.cap;
        net.dinic.g[ex.to][ex.rev].cap = 0;
        ex.cap = 0;
        delSuper(net);
        i64 extra = net.dinic.maxFlow(s, t);
        ans = Result{base + extra, recover(net)};
        return true;
    }
    bool minFlow(int s, int t, Result& ans) const {
        assert(s != t);
        auto net = build(true, s, t);
        if(net.dinic.maxFlow(net.S, net.T) != net.demand) {
            return false;
        }
        auto& edge = net.dinic.g[t][net.extra];
        i64 base = inf - edge.cap;
        net.dinic.g[edge.to][edge.rev].cap = 0;
        edge.cap = 0;
        delSuper(net);
        i64 delta = net.dinic.maxFlow(t, s, base);
        ans = {base - delta, recover(net)};
        return true;
    }

  private:
    struct Net {
        Dinic dinic;
        int S, T;
        i64 demand = 0;
        vector<pair<int, int>> pos;
        int extra = -1;
    };
    Net build(bool addExtra, int s, int t) const {
        Net net;
        net.dinic = Dinic(n + 2);
        net.S = n;
        net.T = n + 1;
        vector<i64> balance(n);
        for(int i = 0; i < int(edges.size()); i++) {
            const Edge& edge = edges[i];
            int index = net.dinic.addEdge(edge.from, edge.to, edge.hi - edge.lo);
            net.pos.push_back({edge.from, index});
            balance[edge.from] -= edge.lo;
            balance[edge.to] += edge.lo;
        }
        if(addExtra) {
            net.extra = net.dinic.addEdge(t, s, inf);
        }
        for(int u = 0; u < n; u++) {
            if(balance[u] > 0) {
                net.dinic.addEdge(net.S, u, balance[u]);
                net.demand += balance[u];
            } else if(balance[u] < 0) {
                net.dinic.addEdge(u, net.T, -balance[u]);
            }
        }
        return net;
    }
    vector<i64> recover(const Net& net) const {
        vector<i64> result(edges.size());
        for(int i = 0; i < int(edges.size()); i++) {
            auto [u, index] = net.pos[i];
            const auto& edge = net.dinic.g[u][index];
            result[i] = edges[i].hi - edge.cap;
        }
        return result;
    }
    static void delSuper(Net& net) {
        for(int u = 0; u < net.dinic.n; u++) {
            for(auto& edge : net.dinic.g[u]) {
                if(u == net.S || u == net.T || edge.to == net.S || edge.to == net.T) {
                    edge.cap = 0;
                }
            }
        }
    }
};
