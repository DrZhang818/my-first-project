#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n;
vector<int> a, tree, tag;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o) {
    tree[o] = max(tree[ls(o)], tree[rs(o)]);
}
void addtag(int o, int d) {
    tag[o] = max(tag[o], d);
    tree[o] = max(tree[o], d);
}
void push_down(int o) {
    if(tag[o]) {
        addtag(ls(o), tag[o]);
        addtag(rs(o), tag[o]);
        tag[o] = 0;
    }
}
void update(int L, int R, int o, int l, int r, int d) {
    if(L <= l && r <= R) { 
        addtag(o, d);
        return;
    }
    push_down(o);
    int mid = l + (r - l) / 2;
    if(L <= mid) update(L, R, ls(o), l, mid, d);
    if(R > mid) update(L, R, rs(o), mid + 1, r, d);
    push_up(o);
}
int query(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tree[o];
    push_down(o);
    int mid = l + (r - l) / 2;
    int res = 0;
    if(L <= mid) res = max(res, query(L, R, ls(o), l, mid));
    if(R > mid) res = max(res, query(L, R, rs(o), mid + 1, r));
    return res;
}
struct info {
    int l, r, id;
};
void solve() { 
    cin >> n;
    a.resize(n + 1);
    tree.assign(n << 2, 0);
    tag.assign(n << 2, 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> fac(n + 1);
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        for(int j = 1; j <= sqrt(x); j++) {
            if(x % j == 0) {
                if(fac[j]) update(fac[j], i, 1, 1, n, j);
                if(fac[x / j]) update(fac[x / j], i, 1, 1, n, x / j);
                fac[j] = fac[x / j] = i;
            }
        }
    }
    int q;
    cin >> q;
    vector<info> Q(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> Q[i].l >> Q[i].r;
        Q[i].id = i;
    }
    sort(Q.begin() + 1, Q.end(), [&](auto x, auto y) -> bool{
        return x.r < y.r;
    });
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
    
