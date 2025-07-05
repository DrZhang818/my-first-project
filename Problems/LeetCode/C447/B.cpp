#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
    vector<int> fa;
    int find(int o) {
        return o == fa[o] ? fa[o] : fa[o] = find(fa[o]);
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return;
        fa[u] = v;
    }
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& a, int lim, vector<vector<int>>& Q) {
        fa.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
        for(int i = 1; i < n; i++) {
            if(a[i] - a[i - 1] <= lim) {
                merge(i + 1, i);
            }
        }
        int q = Q.size();
        vector<bool> ans(q);
        for(int i = 0; i < q; i++) {
            if(same(Q[i][0] + 1, Q[i][1] + 1)) {
                ans[i] = true;
            } else {
                ans[i] = false;
            }
        }
        return ans;
    }
};