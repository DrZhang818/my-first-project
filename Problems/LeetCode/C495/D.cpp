#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct DSU {
    vector<int> fa;
    vector<int> dis;

    DSU(int n) : fa(n), dis(n) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int o) {
        if(fa[o] != o) {
            int rt = find(fa[o]);
            dis[o] ^= dis[fa[o]];
            fa[o] = rt;
        }
        return fa[o];
    }

    bool merge(int u, int v, int w) {
        int x = find(u), y = find(v);
        if(x == y) {
            return (dis[u] ^ dis[v]) == w;
        }
        dis[x] = w ^ dis[u] ^ dis[v];
        fa[x] = y;
        return true;
    }
};

class Solution {
public:
    int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
        int ans = 0;
        DSU dsu(n);
        for(auto& e : edges) {
            if(dsu.merge(e[0], e[1], e[2])) {
                ans++;
            }
        }
        return ans;
    }
};