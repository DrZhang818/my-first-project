#include <bits/stdc++.h>
using namespace std;
struct OfflineConn {
    int n, q;
    vector<int> fa, sz;
    vector<array<int, 3>> stk;
    vector<vector<pair<int, int>>> seg;
    OfflineConn(int n_, int q_)
        : n(n_), q(q_), fa(n_ + 1), sz(n_ + 1, 1), seg(4 * max(1, q_)) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        while(x != fa[x]) {
            x = fa[x];
        }
        return x;
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) {
            return;
        }
        if(sz[u] < sz[v]) {
            swap(u, v);
        }
        stk.push_back({{u, v, sz[u]}});
        fa[v] = u;
        sz[u] += sz[v];
    }
    void undo(int s) {
        while((int)stk.size() > s) {
            array<int, 3> a = stk.back();
            stk.pop_back();
            fa[a[1]] = a[1];
            sz[a[0]] = a[2];
        }
    }
    void put(int p, int l, int r, int x, int y, pair<int, int> e) {
        if(x <= l && r <= y) {
            seg[p].push_back(e);
            return;
        }
        int m = (l + r) / 2;
        if(x <= m) {
            put(p * 2, l, m, x, y, e);
        }
        if(y > m) {
            put(p * 2 + 1, m + 1, r, x, y, e);
        }
    }
    void add(int l, int r, int u, int v) {
        if(l <= r) {
            put(1, 1, q, l, r, make_pair(u, v));
        }
    }
    void dfs(int p, int l, int r, const vector<pair<int, int>>& ask, vector<int>& ans) {
        int s = stk.size();
        for(size_t i = 0; i < seg[p].size(); i++) {
            merge(seg[p][i].first, seg[p][i].second);
        }
        if(l == r) {
            ans[l] = (find(ask[l].first) == find(ask[l].second));
        } else {
            int m = (l + r) / 2;
            dfs(p * 2, l, m, ask, ans);
            dfs(p * 2 + 1, m + 1, r, ask, ans);
        }
        undo(s);
    }
    vector<int> solve(const vector<pair<int, int>>& ask) {
        vector<int> ans(q + 1);
        if(q) {
            dfs(1, 1, q, ask, ans);
        }
        return ans;
    }
};
