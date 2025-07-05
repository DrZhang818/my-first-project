#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class DSU {
private:
    vector<int> fa;
    vector<int> siz;
    int K;
public:
    DSU(){}
    DSU(int n) {
        fa.resize(n);
        siz.assign(n, 1);
        K = n;
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if(x != fa[x]) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) {
            return false;
        }
        siz[x] += siz[y];
        fa[y] = x;
        K -= 1;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return siz[find(x)];
    }
    int kinds() {
        return K;
    }
};
struct info {
    int u, v, w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
class Solution {
public:
    int maxStability(int n, vector<vector<int>>& e, int k) {
        int m = e.size();
        DSU g(n);
        int ans = inf;
        vector<info> ne;
        vector<int> a;
        int sz = 0;
        for(int i = 0; i < m; i++) {
            int u = e[i][0], v = e[i][1], s = e[i][2], t = e[i][3];
            if(t) {
                if(g.merge(u, v)) {
                    ans = min(ans, s);
                    sz++;
                } else {
                    return -1;
                }
            } 
        }
        for(int i = 0; i < m; i++) {
            int u = e[i][0], v = e[i][1], s = e[i][2], t = e[i][3];
            if(!t && !g.same(u, v)) {
                ne.emplace_back(u, v, s);
            }
        }
        sort(ne.begin(), ne.end());
        for(auto [u, v, w] : ne) {
            if(!g.same(u, v)) {
                g.merge(u, v);
                a.push_back(w);
                sz++;
            }
        }
        if(sz != n - 1) {
            return -1;
        }
        sort(a.begin(), a.end());
        for(int i = 0; i < a.size() && i < k; i++) {
            a[i] *= 2;
        }
        for(int i = 0; i < a.size(); i++) {
            ans = min(ans, a[i]);
        }
        return ans;
    }
};