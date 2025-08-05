#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
class SegmentTree {
private:
    int n;
    vector<int> sum, tag, a;
public:
    SegmentTree(int x) : n(x), sum(x << 2), tag(x << 2) {}
    SegmentTree(vector<int> &a) : a(a), n(a.size()), sum(n << 2), tag(n << 2) {}
    void push_up(int o) {
        sum[o] = ((ll)sum[ls(o)] + sum[rs(o)]) % MOD;
    }
    void build(int o, int l, int r) {
        if(l == r) {
            sum[o] = a[l];
            return ;
        }
        int mid = l + r >> 1;
        if(l <= mid) build(ls(o), l, mid);
        if(r > mid) build(rs(o), mid + 1, r);
        push_up(o);
    }
    void addtag(int o, int l, int r, int d) {
        tag[o] = d;
        sum[o] = 1LL * d * (r - l + 1) % MOD;
    }
    void push_down(int o, int l, int r) {
        if(tag[o]) {
            int mid = l + (r - l) / 2;
            addtag(ls(o), l, mid, tag[o]);
            addtag(rs(o), mid + 1, r, tag[o]);
            tag[o] = 0;
        }
    }
    void update(int L, int R, int o, int l, int r, int d) {
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
    int query_sum(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return sum[o];
        push_down(o, l, r);
        int res = 0;
        int mid = l + (r - l) / 2;
        if(L <= mid) add(res, query_sum(L, R, ls(o), l, mid));
        if(R > mid) add(res, query_sum(L, R, rs(o), mid + 1, r));
        return res;
    }
};


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    SegmentTree dp(a);
    dp.build(1, 1, n);
    for(int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        int sum = dp.query_sum(l, r, 1, 1, n);
        int len = r - l + 1;
        int inv_len = inv(len);
        dp.update(l, r, 1, 1, n, 1LL * sum * inv_len % MOD);
    }
    for(int i = 1; i <= n; i++) {
        cout << dp.query_sum(i, i, 1, 1, n) << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
