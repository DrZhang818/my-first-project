#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int MOD = 10007;
int n, q;
vector<ll> tr1, tr2, tr3, tag1, tag2, tag3;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o) {
    tr1[o] = tr1[ls(o)] + tr1[rs(o)];
    tr2[o] = tr2[ls(o)] + tr2[rs(o)];
    tr3[o] = tr3[ls(o)] + tr3[rs(o)];
    tr1[o] %= MOD;
    tr2[o] %= MOD;
    tr3[o] %= MOD;
}
void addtag(int o, int l, int r, ll x, ll y, ll z) {
    if(z) {
        tag1[o] = 0;
        tag2[o] = 1;
        tag3[o] = z;
        tr1[o] = z * (r - l + 1) % MOD;
        tr2[o] = z * z % MOD * (r - l + 1) % MOD;
        tr3[o] = z * z % MOD * z % MOD * (r - l + 1) % MOD;
    }
    if(y != 1) {
        tag1[o] = tag1[o] * y % MOD;
        tag2[o] = tag2[o] * y % MOD;
        tr1[o] = tr1[o] * y % MOD;
        tr2[o] = tr2[o] * y % MOD * y % MOD;
        tr3[o] = tr3[o] * y % MOD * y % MOD * y % MOD;
    }
    if(x) {
        tag1[o] = (tag1[o] + x) % MOD;
        tr3[o] = (tr3[o] + 3 * x * tr2[o] % MOD + 3 * x * x % MOD * tr1[o] % MOD + x * x % MOD * x % MOD * (r - l + 1) % MOD) % MOD;
        tr2[o] = (tr2[o] + 2 * x * tr1[o] % MOD + x * x % MOD * (r - l + 1) % MOD) % MOD;
        tr1[o] = (tr1[o] + x * (r - l + 1) % MOD) % MOD;
    }
}
void push_down(int o, int l, int r) {
    int mid = (l + r) >> 1;
    addtag(ls(o), l, mid, tag1[o], tag2[o], tag3[o]);
    addtag(rs(o), mid + 1, r, tag1[o], tag2[o], tag3[o]);
    tag1[o] = 0;
    tag2[o] = 1;
    tag3[o] = 0;
}
void update(int L, int R, int o, int l, int r, ll x, ll y, ll z) {
    if(L <= l && r <= R) {  
        addtag(o, l, r, x, y, z);
        return;
    }
    push_down(o, l, r);
    int mid = (l + r) >> 1;
    if(L <= mid) update(L, R, ls(o), l, mid, x, y, z);
    if(R > mid) update(L, R, rs(o), mid + 1, r, x, y, z);
    push_up(o);
}
ll query1(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tr1[o] % MOD;
    push_down(o, l, r);
    ll res = 0;
    int mid = (l + r) >> 1;
    if(L <= mid) res = (res + query1(L, R, ls(o), l, mid)) % MOD;
    if(R > mid) res = (res + query1(L, R, rs(o), mid + 1, r)) % MOD;
    return res % MOD;
}
ll query2(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tr2[o] % MOD;
    push_down(o, l, r);
    ll res = 0;
    int mid = (l + r) >> 1;
    if(L <= mid) res = (res + query2(L, R, ls(o), l, mid)) % MOD;
    if(R > mid) res = (res + query2(L, R, rs(o), mid + 1, r)) % MOD;
    return res % MOD;
}
ll query3(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tr3[o] % MOD;
    push_down(o, l, r);
    ll res = 0;
    int mid = (l + r) >> 1;
    if(L <= mid) res = (res + query3(L, R, ls(o), l, mid)) % MOD;
    if(R > mid) res = (res + query3(L, R, rs(o), mid + 1, r)) % MOD;
    return res % MOD;
}
void solve() { 
    tr1.assign(n << 2, 0);
    tr2.assign(n << 2, 0);
    tr3.assign(n << 2, 0);
    tag1.assign(n << 2, 0);
    tag2.assign(n << 2, 1);
    tag3.assign(n << 2, 0);
    while(q--) {
        ll flag, x, y, c;
        cin >> flag >> x >> y >> c;
        if(flag == 1) {
            update(x, y, 1, 1, n, c, 1, 0);
        } 
        else if(flag == 2) {
            update(x, y, 1, 1, n, 0, c, 0);
        } 
        else if(flag == 3) {
            update(x, y, 1, 1, n, 0, 1, c);
        }
        else {
            if(c == 1) cout << query1(x, y, 1, 1, n) << "\n";
            if(c == 2) cout << query2(x, y, 1, 1, n) << "\n";
            if(c == 3) cout << query3(x, y, 1, 1, n) << "\n";
        }
    } 

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n >> q) {
        if(!n && !q) break;
        solve();
    }
    return 0;
}
    
