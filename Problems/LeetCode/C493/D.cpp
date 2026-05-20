#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct DSU {
    int n;
    vector<int> fa; 
    vector<int> sz;
    DSU(int n) : n(n), fa(n), sz(n, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
    void merge(int u, int v) { 
        u = find(u);
        v = find(v);
        if(u == v) return;
        fa[v] = u;
        sz[u] += sz[v];
    }
    int getSize(int u) {
        return sz[find(u)];
    }
};

class Solution {
public:
    int maxActivated(vector<vector<int>>& points) {
        int n = points.size();
        
        DSU dsu(n);

        vector<int> p(n);
        iota(p.begin(), p.end(), 0);

        sort(p.begin(), p.end(), 
            [&](int i, int j) {
                return points[i][0] < points[j][0];
            });

        int las = -1;
        for(int i : p) {
            if(las != -1 && points[i][0] == points[las][0]) {
                dsu.merge(i, las);
            }
            las = i;
        }

        sort(p.begin(), p.end(), 
            [&](int i, int j) {
                return points[i][1] < points[j][1];
            });

        las = -1;
        for(int i : p) {
            if(las != -1 && points[i][1] == points[las][1]) {
                dsu.merge(i, las);
            }
            las = i;
        }

        int mx1 = 0, mx2 = 0;
        for(int i = 0; i < n; i++) {
            if(dsu.find(i) != i) continue;
            int sz = dsu.getSize(i);
            if(sz > mx1) {
                mx2 = mx1;
                mx1 = sz;
            } else if(sz > mx2) {
                mx2 = sz;
            }
        }

        return 1 + mx1 + mx2;
    }
};