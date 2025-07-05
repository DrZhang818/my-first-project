#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n;
vector<ll> tr;
vector<ll> a;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
void push_up(int o) {
    tr[o] = tr[ls(o)] + tr[rs(o)];
}
//build可以省略
void build(int o, int l, int r) {
    if(l == r) {
        tr[o] = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
    push_up(o);
}   
void update(int pos, int o, int l, int r, ll d) {
    if(l == r) {
        tr[o] = d;
        return;
    }
    int mid = l + (r - l) / 2;
    if(pos <= mid) update(pos, ls(o), l, mid, d);
    if(pos > mid) update(pos, rs(o), mid + 1, r, d);
    push_up(o);
}
ll query(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tr[o];
    ll res = 0;
    int mid = l + (r - l) / 2;
    if(L <= mid) res += query(L, R, ls(o), l, mid);
    if(R > mid) res += query(L, R, rs(o), mid + 1, r);
    return res;
}
