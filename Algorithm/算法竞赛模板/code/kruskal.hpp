#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Kruskal {
    struct Edge {
        int u, v;
        i64 w;
    };
    static pair<i64, vector<int>> run(int n, const vector<Edge>& edges) {
        vector<int> p(n + 1), sz(n + 1, 1), id(edges.size());
        iota(p.begin(), p.end(), 0);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](int i, int j) { return edges[i].w < edges[j].w; });
        auto find = [&](int x) {
            while(x != p[x]) {
                x = p[x] = p[p[x]];
            }
            return x;
        };
        i64 sum = 0;
        vector<int> chosen;
        for(int i : id) {
            int x = find(edges[i].u);
            int y = find(edges[i].v);
            if(x == y) {
                continue;
            }
            if(sz[x] < sz[y]) {
                swap(x, y);
            }
            p[y] = x;
            sz[x] += sz[y];
            sum += edges[i].w;
            chosen.push_back(i + 1);
        }
        return {sum, chosen};
    }
};
