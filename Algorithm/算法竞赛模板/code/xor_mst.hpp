#pragma once
#include <bits/stdc++.h>
using namespace std;
// Complete graph on values a[0..n-1], edge weight a[u] XOR a[v].
struct XorMST {
    struct Node {
        int ch[2]{-1, -1};
        int a = -1, b = -1;
    };
    static pair<long long, vector<pair<int, int>>> run(const vector<uint32_t>& a) {
        int n = a.size();
        vector<int> p(n), sz(n, 1), color(n);
        iota(p.begin(), p.end(), 0);
        auto find = [&](int u) {
            while(u != p[u]) {
                u = p[u] = p[p[u]];
            }
            return u;
        };
        long long ans = 0;
        int groups = n;
        vector<pair<int, int>> chosen;
        while(groups > 1) {
            for(int u = 0; u < n; u++) {
                color[u] = find(u);
            }
            vector<Node> t(1);
            auto mark = [&](int k, int u) {
                if(t[k].a < 0) {
                    t[k].a = u;
                } else if(color[t[k].a] != color[u]) {
                    t[k].b = u;
                }
            };
            for(int u = 0; u < n; u++) {
                int k = 0;
                mark(k, u);
                for(int b = 31; b >= 0; b--) {
                    int c = a[u] >> b & 1;
                    if(t[k].ch[c] < 0) {
                        int v = t.size();
                        t.emplace_back();
                        t[k].ch[c] = v;
                    }
                    k = t[k].ch[c];
                    mark(k, u);
                }
            }
            auto good = [&](int k, int u) {
                return k >= 0 && ((t[k].a >= 0 && color[t[k].a] != color[u]) ||
                                  (t[k].b >= 0 && color[t[k].b] != color[u]));
            };
            vector<pair<int, int>> best(n, {-1, -1});
            for(int u = 0; u < n; u++) {
                int k = 0;
                for(int b = 31; b >= 0; b--) {
                    int c = a[u] >> b & 1;
                    k = t[k].ch[good(t[k].ch[c], u) ? c : c ^ 1];
                }
                int v = color[t[k].a] != color[u] ? t[k].a : t[k].b;
                auto& e = best[color[u]];
                if(e.first < 0 || (a[u] ^ a[v]) < (a[e.first] ^ a[e.second])) {
                    e = {u, v};
                }
            }
            for(auto [u, v] : best) {
                if(u >= 0) {
                    int x = find(u), y = find(v);
                    if(x == y) {
                        continue;
                    }
                    if(sz[x] < sz[y]) {
                        swap(x, y);
                    }
                    p[y] = x;
                    sz[x] += sz[y];
                    --groups;
                    ans += (a[u] ^ a[v]);
                    chosen.push_back({u, v});
                }
            }
        }
        return {ans, chosen};
    }
};
