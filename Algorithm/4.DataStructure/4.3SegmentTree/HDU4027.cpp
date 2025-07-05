#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n, cnt = 1;
vector<ll> a, tr;
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
    int mid = l + (r - l) / 2;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
    push_up(o);
}
void update(int L, int R, int o, int l, int r) {
    if(l == r) {
        tr[o] = (ll)(sqrt(tr[o]));
        return;
    }
    if(tr[o] <= r - l + 1) return;
    int mid = l + (r - l) / 2;
    if(L <= mid) update(L, R, ls(o), l, mid);
    if(R > mid) update(L, R, rs(o), mid + 1, r);
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
void solve() { 
    a.resize(n + 1);
    tr.assign(n << 2, 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    cout << "Case #" << cnt << ":\n";
    int q;
    cin >> q;
    while(q--) {
        int flag, x, y;
        cin >> flag >> x >> y;
        if(x > y) swap(x, y);
        if(flag == 0) {
            update(x, y, 1, 1, n);
        } else {
            cout << query(x, y, 1, 1, n) << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n) {
        solve();
        cnt++;
        cout << "\n";
    }
    return 0;
}
    
