#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

int n;
vector<ll> sum, mx;
vector<ll> tag;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
void init() {
    sum.assign(n << 2, 0);
    mx.assign(n << 2, 0);
    tag.assign(n << 2, 0);
}
void push_up(int o) {
    sum[o] = sum[ls(o)] + sum[rs(o)];
    mx[o] = max(mx[ls(o)], mx[rs(o)]);
}
void addtag(int o, int l, int r, ll d) {
    tag[o] += d;
    sum[o] += d * (r - l + 1);
    mx[o] += d;
}
void push_down(int o, int l, int r) {
    if(tag[o]) {
        int mid = l + (r - l) / 2;
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
    int mid = l + (r - l) / 2;
    if(L <= mid) res += query_sum(L, R, ls(o), l, mid);
    if(R > mid) res += query_sum(L, R, rs(o), mid + 1, r);
    return res;
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

int main() {
    int q;
    cin >> n >> q;
    init();
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) add(i, i, 1, 1, n, a[i]);
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r, d;
            cin >> l >> r >> d;
            add(l, r, 1, 1, n, d); 
        } else {
            int l, r;
            cin >> l >> r;
            cerr << query_sum(l, r, 1, 1, n) << "\n";
            cerr << query_max(l, r, 1, 1, n) << "\n";
            cerr << "\n";
        }
    }
}