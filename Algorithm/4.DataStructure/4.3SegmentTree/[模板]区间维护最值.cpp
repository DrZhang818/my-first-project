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
    vector<ll> mx, tag;
public:
    SegmentTree(int x) : n(x), mx(x << 2, -inf), tag(x << 2, -inf) {}
    void push_up(int o) {
        mx[o] = max(mx[ls(o)], mx[rs(o)]);
    }
    void addtag(int o, int l, int r, ll d) {
        tag[o] = max(tag[o], d);
        mx[o] = max(mx[o], d);
    }
    void push_down(int o, int l, int r) {
        if(tag[o] != -inf) {
            int mid = l + (r - l) / 2;
            addtag(ls(o), l, mid, tag[o]);
            addtag(rs(o), mid + 1, r, tag[o]);
            tag[o] = -inf;
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
    ll query_max(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mx[o];
        push_down(o, l, r);
        ll res = -inf;
        int mid = l + (r - l) / 2;
        if(L <= mid) res = max(res, query_max(L, R, ls(o), l, mid));
        if(R > mid) res = max(res, query_max(L, R, rs(o), mid + 1, r));
        return res;
    }
};

