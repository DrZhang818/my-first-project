#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

//优化做法: 先枚举b再枚举a, 可以用单调队列维护最值



//自己的做法: 先枚举a再枚举b, 导致必须用线段树维护区间最值
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
class SegmentTree {
private:
    int n;
    vector<ll> mn;
    vector<ll> tag;
public:
    SegmentTree(int x) : n(x), mn(x << 2, inf), tag(x << 2, inf) {}
    void push_up(int o) {
        mn[o] = min(mn[ls(o)], mn[rs(o)]);
    }
    void addtag(int o, int l, int r, ll d) {
        tag[o] = min(tag[o], d);
        mn[o] = min(mn[o], d);
    }
    void push_down(int o, int l, int r) {
        if(tag[o] != inf) {
            int mid = l + (r - l) / 2;
            addtag(ls(o), l, mid, tag[o]);
            addtag(rs(o), mid + 1, r, tag[o]);
            tag[o] = inf;
        }
    }
    void update(int L, int R, int o, int l, int r, ll d) {
        if(L <= l && r <= R) {
            addtag(o, l, r, d);
            return;
        }
        push_down(o, l, r);
        int mid = l + (r - l) / 2;
        if(L <= mid) update(L, R, ls(o), l, mid, d);
        if(R > mid) update(L, R, rs(o), mid + 1, r, d);
        push_up(o);
    }
    ll query_min(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mn[o];
        push_down(o, l, r);
        ll res = inf;
        int mid = l + (r - l) / 2;
        if(L <= mid) res = min(res, query_min(L, R, ls(o), l, mid));
        if(R > mid) res = min(res, query_min(L, R, rs(o), mid + 1, r));
        return res;
    }
};

class Solution {
public:
    int minimumValueSum(vector<int>& a, vector<int>& b) {
        int n = a.size(), m = b.size();
        a.insert(a.begin(), 0), b.insert(b.begin(), 0);
        vector dp(n + 1, vector<int>(m + 1, inf));
        vector<SegmentTree> tr(m + 1, SegmentTree(n + 1));
        tr[0].update(1, 1, 1, 1, n + 1, 0);
        for(int i = 1; i <= n; i++) {
            int x = a[i];
            for(int j = i - 1; j >= 1 && (a[j] & a[i]) != a[j]; j--) {
                a[j] &= a[i];
            }
            for(int k = m; k >= 1; k--) {
                int l = lower_bound(a.begin() + 1, a.begin() + i + 1, b[k]) - a.begin();
                int r = upper_bound(a.begin() + 1, a.begin() + i + 1, b[k]) - a.begin() - 1;
                if(r < l) continue;
                dp[i][k] = tr[k - 1].query_min(l, r, 1, 1, n + 1) + x;
                tr[k].update(i + 1, i + 1, 1, 1, n + 1, dp[i][k]);
            }
        }
        return dp[n][m] >= inf ? -1 : dp[n][m];
    }
};