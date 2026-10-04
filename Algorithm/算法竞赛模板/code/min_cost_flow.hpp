#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct MCF {
    struct Edge {
        int to, rev;
        i64 cap, cost;
    };
    static constexpr i64 inf = numeric_limits<i64>::max() / 4;
    int n;
    vector<vector<Edge>> g;
    MCF(int n_ = 0) : n(n_), g(n_) {
    }
    void addEdge(int u, int v, i64 cap, i64 cost) {
        int uIndex = int(g[u].size());
        int vIndex = int(g[v].size()) + (u == v);
        g[u].push_back({v, vIndex, cap, cost});
        g[v].push_back({u, uIndex, 0, -cost});
    }
    pair<i64, i64> flow(int s, int t, i64 limit = inf) {
        assert(s != t);
        vector<i64> h = initPot(s);
        vector<i64> dis(n);
        vector<int> pv(n), pe(n);
        i64 flowSum = 0;
        i64 costSum = 0;
        while(flowSum < limit) {
            fill(dis.begin(), dis.end(), inf);
            priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> q;
            dis[s] = 0;
            q.push({0, s});
            while(!q.empty()) {
                auto [du, u] = q.top();
                q.pop();
                if(du != dis[u]) {
                    continue;
                }
                for(int i = 0; i < int(g[u].size()); i++) {
                    const Edge& edge = g[u][i];
                    if(!edge.cap) {
                        continue;
                    }
                    i64 nd = du + edge.cost + h[u] - h[edge.to];
                    if(nd < dis[edge.to]) {
                        dis[edge.to] = nd;
                        pv[edge.to] = u;
                        pe[edge.to] = i;
                        q.push({nd, edge.to});
                    }
                }
            }
            if(dis[t] == inf) {
                break;
            }
            for(int u = 0; u < n; u++) {
                if(dis[u] != inf) {
                    h[u] += dis[u];
                }
            }
            i64 pushed = limit - flowSum;
            for(int v = t; v != s; v = pv[v]) {
                const Edge& edge = g[pv[v]][pe[v]];
                pushed = min(pushed, edge.cap);
            }
            for(int v = t; v != s; v = pv[v]) {
                Edge& edge = g[pv[v]][pe[v]];
                costSum += pushed * edge.cost;
                edge.cap -= pushed;
                g[v][edge.rev].cap += pushed;
            }
            flowSum += pushed;
        }
        return {flowSum, costSum};
    }

  private:
    vector<i64> initPot(int s) const {
        vector<i64> dis(n, inf);
        dis[s] = 0;
        for(int round = 1; round < n; round++) {
            bool changed = false;
            for(int u = 0; u < n; u++) {
                if(dis[u] == inf) {
                    continue;
                }
                for(const Edge& edge : g[u]) {
                    if(edge.cap && dis[edge.to] > dis[u] + edge.cost) {
                        dis[edge.to] = dis[u] + edge.cost;
                        changed = true;
                    }
                }
            }
            if(!changed) {
                break;
            }
        }
        for(i64& value : dis) {
            if(value == inf) {
                value = 0;
            }
        }
        return dis;
    }
};
