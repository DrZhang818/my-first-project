#pragma once
#include <bits/stdc++.h>
using namespace std;
struct SecondMST {
    typedef long long ll;
    static const ll INF = LLONG_MAX / 4;
    struct Edge {
        int u, v;
        ll w;
    };
    struct Two {
        ll a, b;
        Two(ll x = -INF, ll y = -INF) : a(x), b(y) {
        }
    };
    static Two join(Two x, Two y) {
        ll v[4] = {x.a, x.b, y.a, y.b};
        Two z;
        for(int i = 0; i < 4; i++) {
            if(v[i] > z.a) {
                z.b = z.a, z.a = v[i];
            } else if(v[i] < z.a && v[i] > z.b) {
                z.b = v[i];
            }
        }
        return z;
    }
    // false: disconnected; second=INF: no strictly heavier spanning tree.
    static bool solve(int n, vector<Edge> e, ll& mst, ll& second) {
        vector<int> p(n + 1), id(e.size()), used(e.size());
        vector<vector<pair<int, ll>>> g(n + 1);
        iota(p.begin(), p.end(), 0);
        iota(id.begin(), id.end(), 0);
        function<int(int)> find = [&](int x) { return p[x] == x ? x : p[x] = find(p[x]); };
        sort(id.begin(), id.end(), [&](int x, int y) { return e[x].w < e[y].w; });
        mst = 0;
        second = INF;
        int cnt = 0;
        for(int k : id) {
            int x = find(e[k].u), y = find(e[k].v);
            if(x == y) {
                continue;
            }
            p[x] = y;
            used[k] = 1;
            mst += e[k].w;
            ++cnt;
            g[e[k].u].push_back(make_pair(e[k].v, e[k].w));
            g[e[k].v].push_back(make_pair(e[k].u, e[k].w));
        }
        if(cnt != n - 1) {
            return false;
        }
        int lg = 1;
        while((1LL << lg) <= n) {
            ++lg;
        }
        vector<int> dep(n + 1), ord(1, 1);
        vector<vector<int>> fa(lg, vector<int>(n + 1));
        vector<vector<Two>> mx(lg, vector<Two>(n + 1));
        for(size_t i = 0; i < ord.size(); i++) {
            int u = ord[i];
            for(size_t j = 0; j < g[u].size(); j++) {
                int v = g[u][j].first;
                if(v == fa[0][u]) {
                    continue;
                }
                fa[0][v] = u;
                dep[v] = dep[u] + 1;
                mx[0][v] = Two(g[u][j].second);
                ord.push_back(v);
            }
        }
        for(int j = 1; j < lg; j++) {
            for(int u = 1; u <= n; u++) {
                fa[j][u] = fa[j - 1][fa[j - 1][u]];
                mx[j][u] = join(mx[j - 1][u], mx[j - 1][fa[j - 1][u]]);
            }
        }
        for(size_t k = 0; k < e.size(); k++) {
            if(!used[k] && e[k].u != e[k].v) {
                int u = e[k].u, v = e[k].v;
                Two z;
                if(dep[u] < dep[v]) {
                    swap(u, v);
                }
                int d = dep[u] - dep[v];
                for(int j = 0; j < lg; j++) {
                    if(d >> j & 1) {
                        z = join(z, mx[j][u]), u = fa[j][u];
                    }
                }
                if(u != v) {
                    for(int j = lg - 1; j >= 0; j--) {
                        if(fa[j][u] != fa[j][v]) {
                            z = join(z, join(mx[j][u], mx[j][v]));
                            u = fa[j][u];
                            v = fa[j][v];
                        }
                    }
                    z = join(z, join(mx[0][u], mx[0][v]));
                }
                ll rem = e[k].w > z.a ? z.a : z.b;
                if(rem != -INF) {
                    second = min(second, mst + e[k].w - rem);
                }
            }
        }
        return true;
    }
};
