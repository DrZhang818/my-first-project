#pragma once
#include <bits/stdc++.h>
using namespace std;
struct Boruvka {
    using i64 = long long;
    struct Edge {
        int u, v;
        i64 w;
    };
    struct Result {
        i64 weight = 0;
        vector<int> edges;
        int comp = 0;
    };
    static Result run(int n, const vector<Edge>& e) {
        vector<int> p(n + 1), sz(n + 1, 1), best(n + 1);
        iota(p.begin(), p.end(), 0);
        auto find = [&](int u) {
            while(u != p[u]) {
                u = p[u] = p[p[u]];
            }
            return u;
        };
        Result ans;
        ans.comp = n;
        auto improve = [&](int r, int i) {
            if(best[r] < 0 || pair{e[i].w, i} < pair{e[best[r]].w, best[r]}) {
                best[r] = i;
            }
        };
        while(ans.comp > 1) {
            fill(best.begin(), best.end(), -1);
            // Component partition is frozen throughout candidate selection.
            for(int i = 0; i < (int)e.size(); i++) {
                int u = find(e[i].u), v = find(e[i].v);
                if(u != v) {
                    improve(u, i), improve(v, i);
                }
            }
            int merged = 0;
            for(int r = 1; r <= n; r++) {
                if(best[r] >= 0) {
                    int i = best[r], u = find(e[i].u), v = find(e[i].v);
                    if(u == v) {
                        continue;
                    }
                    if(sz[u] < sz[v]) {
                        swap(u, v);
                    }
                    p[v] = u;
                    sz[u] += sz[v];
                    ans.weight += e[i].w;
                    ans.edges.push_back(i + 1);
                    --ans.comp;
                    ++merged;
                }
            }
            if(!merged) {
                break;
            }
        }
        return ans;
    }
};
