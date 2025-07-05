#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

constexpr ll inf = 1e18;
vector<ll> tr, cnt, ma, se;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o) {
    tr[o] = tr[ls(o)] + tr[rs(o)];
    ma[o] = max(ma[ls(o)], ma[rs(o)]);
    if(ma[ls(o)] == ma[rs(o)]) {
        se[o] = max(se[ls(o)], se[rs(o)]);
        cnt[o] = cnt[ls(o)] + cnt[rs(o)];
    } else {
        se[o] = max(se[ls(o)], se[rs(o)]);
        se[o] = max(se[o], min(ma[ls(o)], ma[rs(o)]));
        cnt[o] = ma[ls(o)] > ma[rs(o)] ? cnt[ls(o)] : cnt[rs(o)];
    }
}
void build(int o, int l, int r) {
    if(l == r) {
        cin >> tr[o];
        ma[o] = tr[o];
        se[o] = -1;
        cnt[o] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
    push_up(o);
}
void addtag(int o, int x) {
    if(x >= ma[o]) return;
    tr[o] -= cnt[o] * (ma[o] - x);
    ma[o] = x;
}
void push_down(int o) {
    addtag(ls(o), ma[o]);
    addtag(rs(o), ma[o]);
}
void update(int L, int R, int o, int l, int r, ll x) {
    if(x >= ma[o]) return;
    if(L <= l && r <= R && se[o] < x) {
        addtag(o, x);
        return;
    }
    push_down(o);
    int mid = l + r >> 1;
    if(L <= mid) update(L, R, ls(o), l, mid, x);
    if(R > mid) update(L, R, rs(o), mid + 1, r, x);
    push_up(o);
}
ll query_max(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return ma[o];
    push_down(o);
    ll res = -inf;
    int mid = l + r >> 1;
    if(L <= mid) res = max(res, query_max(L, R, ls(o), l, mid));
    if(R > mid) res = max(res, query_max(L, R, rs(o), mid + 1, r));
    return res;
}
ll query_sum(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tr[o];
    push_down(o);
    ll res = 0;
    int mid = l + r >> 1;
    if(L <= mid) res += query_sum(L, R, ls(o), l, mid);
    if(R > mid) res += query_sum(L, R, rs(o), mid + 1, r);
    return res;
}
void solve() { 
    int n, m;
    cin >> n >> m;
    ma.assign(n << 2, 0);
    tr.assign(n << 2, 0);
    se.assign(n << 2, 0);
    cnt.assign(n << 2, 0);
    build(1, 1, n);
    for(int i = 1; i <= m; i++) {
        int flag;
        cin >> flag;
        int x, y;
        cin >> x >> y;
        if(flag == 0) {
            ll t;
            cin >> t;
            update(x, y, 1, 1, n, t); 
        } else if(flag == 1) {
            cout << query_max(x, y, 1, 1, n) << "\n";
        } else {
            cout << query_sum(x, y, 1, 1, n) << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
