#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n, q;
vector<ll> a, tr, tag;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o) {
    tr[o] = tr[ls(o)] + tr[rs(o)];
}
void build(int o, int l, int r) {
    if(l == r) {
        tr[o] = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
}
void addtag(int o, int l, int r, ll d) {
    tr[o] += d * (r - l + 1);
    tag[o] += d;
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
    int mid = l + r >> 1;
    if(L <= mid) add(L, R, ls(o), l, mid, d);
    if(R > mid) add(L, R, rs(o), mid + 1, r, d);
    push_up(o);
}
ll query(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tr[o];
    push_down(o, l, r);
    ll res = 0;
    int mid = l + r >> 1;
    if(L <= mid) res += query(L, R, ls(o), l, mid);
    if(R > mid) res += query(L, R, rs(o), mid + 1, r);
    return res;
}
void solve() { 
    cin >> n >> q;
    a.resize(n + 1);
    tr.assign(n << 2, 0);
    tag.assign(n << 2, 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int l, r;
            ll d;
            cin >> l >> r >> d;
            add(l, r, 1, 1, n, d);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(l, r, 1, 1, n) << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
