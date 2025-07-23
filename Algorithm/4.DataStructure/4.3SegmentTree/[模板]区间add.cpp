#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
class SegmentTree {
private:
    int n;
    vector<ll> sum, mx, mn;
    vector<ll> tag;
public:
    SegmentTree(int x) : sum(x << 2), mx(x << 2), mn(x << 2), tag(x << 2) {}
    void push_up(int o) {
        sum[o] = sum[ls(o)] + sum[rs(o)];
        mx[o] = max(mx[ls(o)], mx[rs(o)]);
        mn[o] = min(mn[ls(o)], mn[rs(o)]);
    }
    void addtag(int o, int l, int r, ll d) {
        tag[o] += d;
        sum[o] += d * (r - l + 1);
        mx[o] += d;
        mn[o] += d;
    }
    void push_down(int o, int l, int r) {
        if(tag[o]) {
            int mid = l + r >> 1;
            addtag(ls(o), l, mid, tag[o]);
            addtag(rs(o), mid + 1, r, tag[o]);
            tag[o] = 0;
        }
    }
    void add(int L, int R, int o, int l, int r, ll d) {
        if(L <= l && r <= R) {
            addtag(o, l, r, d);
            return;
        }
        push_down(o, l, r);
        int mid = l + (r - l) / 2;
        if(L <= mid) add(L, R, ls(o), l, mid, d);
        if(R > mid) add(L, R, rs(o), mid + 1, r, d);
        push_up(o);
    }
    ll query_sum(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return sum[o];
        push_down(o, l, r);
        ll res = 0;
        int mid = l + r >> 1;
        if(L <= mid) res += query_sum(L, R, ls(o), l, mid);
        if(R > mid) res += query_sum(L, R, rs(o), mid + 1, r);
        return res;
    }
    ll query_max(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mx[o];
        push_down(o, l, r);
        ll res = -inf;
        int mid = l + r >> 1;
        if(L <= mid) res = max(res, query_max(L, R, ls(o), l, mid));
        if(R > mid) res = max(res, query_max(L, R, rs(o), mid + 1, r));
        return res;
    }
    ll query_min(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mn[o];
        push_down(o, l, r);
        ll res = inf;
        int mid = l + r >> 1;
        if(L <= mid) res = min(res, query_min(L, R, ls(o), l, mid));
        if(R > mid) res = min(res, query_min(L, R, rs(o), mid + 1, r));
        return res;
    }
};

