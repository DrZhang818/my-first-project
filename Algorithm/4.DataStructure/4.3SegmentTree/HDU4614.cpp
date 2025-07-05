#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n;
vector<int> tr, tag;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o) {
    tr[o] = tr[ls(o)] + tr[rs(o)];
}
void build(int o, int l, int r) {
    if(l == r) {
        tr[o] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
    push_up(o);
}
void addtag(int o, int l, int r, int d) {
    tr[o] = d * (r - l + 1);
    tag[o] = d;
}
void push_down(int o, int l, int r) {
    if(tag[o] != -1) {
        int mid = l + r >> 1;
        addtag(ls(o), l, mid, tag[o]);
        addtag(rs(o), mid + 1, r, tag[o]);
        tag[o] = -1;
    }
}
void update(int L, int R, int o, int l, int r, int d) {
    if(L <= l && r <= R) {
        addtag(o, l, r, d);
        return;
    }
    push_down(o, l, r);
    int mid = l + r >> 1;
    if(L <= mid) update(L, R, ls(o), l, mid, d);
    if(R > mid) update(L, R, rs(o), mid + 1, r, d);
    push_up(o);
}
int query(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tr[o];
    int res = 0, mid = l + r >> 1;
    push_down(o, l, r);
    if(L <= mid) res += query(L, R, ls(o), l, mid);
    if(R > mid) res += query(L, R, rs(o), mid + 1, r);
    return res;
}
void solve() { 
    int q;
    cin >> n >> q;
    tr.assign(n << 2, 0);
    tag.assign(n << 2, -1);
    build(1, 1, n);
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int st, sz;
            cin >> st >> sz;
            st++;
            int l = st - 1, r = n + 1;
            while(l + 1 < r) {
                int mid = l + r >> 1;
                if(query(st, mid, 1, 1, n) != 0) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            if(r == n + 1) {
                cout << "Can not put any one.\n";
                continue;
            }
            st = r;
            l = st - 1, r = n + 1;
            ll mx = query(st, n, 1, 1, n);
            if(mx >= sz) mx = sz;
            while(l + 1 < r) {
                int mid = l + r >> 1;
                if(query(st, mid, 1, 1, n) >= mx) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            update(st, r, 1, 1, n, 0);
            cout << st - 1 << " " << r - 1 << "\n";
        } 
        else {
            int l, r;
            cin >> l >> r;
            l++, r++;
            cout << (r - l + 1) - query(l, r, 1, 1, n) << "\n";
            update(l, r, 1, 1, n, 1);
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
        cout << "\n";
    }
    return 0;
}
    
