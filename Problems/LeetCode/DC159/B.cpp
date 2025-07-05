#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    struct info {
        int l = inf, r = -inf;
    };
    ll maxArea(vector<vector<int>>& a) {
        int n = a.size();
        int xl = inf, xr = -inf, yl = inf, yr = -inf;
        unordered_map<int,info> x,y;        
        for(int i = 0; i < n; i++) {
            int u = a[i][0], v = a[i][1];
            x[u].l = min(x[u].l, v);
            x[u].r = max(x[u].r, v);
            y[v].l = min(y[v].l, u);
            y[v].r = max(y[v].r, u);
            xl = min(xl, u), xr = max(xr, u);
            yl = min(yl, v), yr = max(yr, v);
        }
        ll ans = 0;
        for(auto [o, info] : x) {
            auto [l, r] = info;
            ans = max(ans, (ll)(r - l) * max(o - xl, xr - o));
        }
        for(auto [o, info] : y) {
            auto [l, r] = info;
            ans = max(ans, (ll)(r - l) * max(o - yl, yr - o));
        }
        return ans == 0 ? -1 : ans;
    }
};