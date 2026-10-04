#include <bits/stdc++.h>
using namespace std;
struct RangeGraph {
    using i64 = long long;
    static constexpr i64 INF = LLONG_MAX / 4;
    int n;
    vector<int> down, up;
    vector<vector<pair<int, i64>>> g;
    RangeGraph(int n_) : n(n_), down(4 * max(1, n_)), up(down.size()), g(n_ + 1) {
        assert(n > 0);
        build(1, 1, n);
    }
    int node() {
        g.emplace_back();
        return int(g.size()) - 1;
    }
    void edge(int u, int v, i64 w) {
        g[u].push_back({v, w});
    }
    void build(int p, int l, int r) {
        if(l == r) {
            down[p] = up[p] = l;
            return;
        }
        down[p] = node();
        up[p] = node();
        int m = (l + r) / 2;
        build(p * 2, l, m);
        build(p * 2 + 1, m + 1, r);
        for(int c : {p * 2, p * 2 + 1}) {
            edge(down[p], down[c], 0), edge(up[c], up[p], 0);
        }
    }
    void link(int p, int l, int r, int x, int y, int v, i64 w, bool fromPoint) {
        if(x <= l && r <= y) {
            if(fromPoint) {
                edge(v, down[p], w);
            } else {
                edge(up[p], v, w);
            }
            return;
        }
        int m = (l + r) / 2;
        if(x <= m) {
            link(p * 2, l, m, x, y, v, w, fromPoint);
        }
        if(y > m) {
            link(p * 2 + 1, m + 1, r, x, y, v, w, fromPoint);
        }
    }
    void pointToRange(int v, int l, int r, i64 w) {
        link(1, 1, n, l, r, v, w, true);
    }
    void rangeToPoint(int l, int r, int v, i64 w) {
        link(1, 1, n, l, r, v, w, false);
    }
    void rangeToRange(int l1, int r1, int l2, int r2, i64 w) {
        int v = node();
        rangeToPoint(l1, r1, v, 0);
        pointToRange(v, l2, r2, w);
    }
    vector<i64> distances(int s) const {
        vector<i64> d(g.size(), INF);
        priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> q;
        d[s] = 0;
        q.push({0, s});
        while(!q.empty()) {
            auto [du, u] = q.top();
            q.pop();
            if(du != d[u]) {
                continue;
            }
            for(auto [v, w] : g[u]) {
                if(d[v] > du + w) {
                    d[v] = du + w, q.push({d[v], v});
                }
            }
        }
        d.resize(n + 1);
        return d;
    }
};
