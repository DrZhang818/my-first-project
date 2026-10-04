#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct APSP {
    static constexpr i64 INF = numeric_limits<i64>::max() / 4;
    int n;
    vector<vector<i64>> dis;
    APSP(int n_) : n(n_), dis(n_ + 1, vector<i64>(n_ + 1, INF)) {
        for(int i = 1; i <= n; i++) {
            dis[i][i] = 0;
        }
    }
    void addEdge(int u, int v, i64 w) {
        relax(u, v, w);
        relax(v, u, w);
    }
    void addDirected(int u, int v, i64 w) {
        relax(u, v, w);
    }
    void relax(int u, int v, i64 w) {
        for(int i = 1; i <= n; i++) {
            if(dis[i][u] == INF) {
                continue;
            }
            for(int j = 1; j <= n; j++) {
                if(dis[v][j] == INF) {
                    continue;
                }
                if(dis[i][j] > dis[i][u] + w + dis[v][j]) {
                    dis[i][j] = dis[i][u] + w + dis[v][j];
                }
            }
        }
    }
};
