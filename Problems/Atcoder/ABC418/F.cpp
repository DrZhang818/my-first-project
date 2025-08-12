#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair<ll,ll> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;
const int N = 200000;

//https://atcoder.jp/contests/abc418/tasks/abc418_f
int fac[N + 1], inv_fac[N + 1], fib[N + 1];
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
int C(int n, int m) {
    if(n < m || m < 0) return 0;
    return 1LL * fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}
int F(int n, int m) {
    if(n < m || m < 0) return 0;
    return C(n - m + 1, m);
}
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
struct Matrix {
    int c[2][2];
    void init() {
        c[1][0] = c[0][1] = 0;
        c[0][0] = c[1][1] = 1;
    }
    Matrix () {
        init();
    }
    void set(int n, int m) {
        c[0][0] = F(n - 1, m);
        c[1][0] = n == 1 ? m == 0 : F(n - 2, m);
        c[0][1] = n == 1 ? m == 1 : F(n - 2, m - 1);
        c[1][1] = n == 2 ? m == 1 : F(n - 3, m - 1);
    }
    friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix res;
        res.c[0][0] = res.c[0][1] = res.c[1][0] = res.c[1][1] = 0;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 2; k++) {
                    add(res.c[i][j], 1LL * a.c[i][k] * b.c[k][j] % MOD);
                }
            }
        }
        return res;
    }
};
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
class SegmentTree {
public:
    vector<Matrix> mul;
    SegmentTree(int n) : mul(n << 2) {}
    void push_up(int o) {
        mul[o] = mul[ls(o)] * mul[rs(o)];
    }
    void update(int i, int o, int l, int r, Matrix &d) {
        if(l == r) {
            mul[o] = d;
            return;
        }
        int mid = l + r >> 1;
        if(i <= mid) update(i, ls(o), l, mid, d);
        else update(i, rs(o), mid + 1, r, d);
        push_up(o);
    }
};
struct info {
    int x, v;
    friend bool operator < (const info &a, const info &b) {
        return a.x < b.x;
    };
};
void solve() {
    int n, q;
    cin >> n >> q;
    SegmentTree tr(n);
    set<info> st;
    st.insert({0, 0});
    st.insert({n + 1, n});
    while(q--) {
        int x, v;
        cin >> x >> v;
        auto it = st.find({x, 0});
        if(it != st.end()) {
            auto pre = *prev(it);
            auto nxt = *next(it);
            st.erase(it);
            Matrix cur;
            tr.update(x, 1, 1, n, cur);
            if(nxt.x <= n) {
                cur.set(nxt.x - pre.x, nxt.v - pre.v);
                tr.update(nxt.x, 1, 1, n, cur);
            }
        }
        if(v != -1) {
            st.insert({x, v});
            it = st.find({x, 0});
            auto pre = *prev(it);
            auto nxt = *next(it);
            Matrix cur;
            cur.set(x - pre.x, v - pre.v);
            tr.update(x, 1, 1, n, cur);
            if(nxt.x <= n) {
                cur.set(nxt.x - x, nxt.v - v);
                tr.update(nxt.x, 1, 1, n, cur);
            }
        }
        auto res = tr.mul[1];
        int len = n - prev(prev(st.end()))->x;
        int ans = 0;
        add(ans, 1LL * res.c[0][0] * fib[len] % MOD);
        add(ans, 1LL * res.c[0][1] * fib[max(0, len - 1)] % MOD);
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    inv_fac[N] = inv(fac[N]);
    for(int i = N - 1; i >= 1; i--) {
        inv_fac[i] = 1LL * inv_fac[i + 1] * (i + 1) % MOD;
    }
    fib[0] = 1;
    fib[1] = 2;
    for(int i = 2; i <= N; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
