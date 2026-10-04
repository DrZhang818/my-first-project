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
