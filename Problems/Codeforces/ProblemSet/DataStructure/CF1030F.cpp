#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://codeforces.com/contest/1030/problem/F

ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}
inline int lowbit(int o) { return o & -o; }
class BIT {
    vector<ll> tr;
    int n;
public:
    BIT(int n) : tr(n + 1), n(n) {}
    void add(int o, ll d) {
        for(int i = o; i <= n; i += lowbit(i)) {
            tr[i] += d;
        }
    }
    void add_mod(int o, ll d) {
        for(int i = o; i <= n; i += lowbit(i)) {
            tr[i] = (tr[i] + d) % MOD;
        }
    }
    ll query(int o) {
        ll res = 0;
        for(int i = o; i > 0; i -= lowbit(i)) {
            res += tr[i];
        }
        return res;
    }
    ll range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
    ll query_mod(int o) {
        ll res = 0;
        for(int i = o; i > 0; i -= lowbit(i)) {
            res = (res + tr[i]) % MOD;
        }
        return res;
    }
    ll range_query_mod(int l, int r) {
        return mod(query_mod(r) - query_mod(l - 1));
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), w(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] -= i;
    }
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    BIT tr1(n + 1), tr2(n + 1);
    for(int i = 1; i <= n; i++) {
        tr1.add(i, w[i]);
        tr2.add_mod(i, 1LL * w[i] * a[i] % MOD);
    }
    auto ck = [&](int l, int r, int x) -> bool {
        return tr1.range_query(l, x) < tr1.range_query(x + 1, r);
    };
    while(q--) {
        int x, y;
        cin >> x >> y;
        if(x < 0) {
            int o = -x;
            tr1.add(o, -w[o]);
            tr2.add_mod(o, mod(1LL * -w[o] * a[o]));
            w[o] = y;
            tr1.add(o, w[o]);
            tr2.add_mod(o, mod(1LL * w[o] * a[o]));
        } else {
            int l = x - 1, r = y + 1;
            while(l + 1 < r) {
                int mid = l + r >> 1;
                if(ck(x, y, mid)) {
                    l = mid;
                } else {
                    r = mid;
                }   
            }
            ll ans = 0;
            l++;
            ans -= mod(tr2.range_query_mod(x, l));
            ans += mod(tr2.range_query_mod(l + 1, y));
            ans += mod(a[l] * mod(tr1.range_query(x, l)));
            ans -= mod(a[l] * mod(tr1.range_query(l + 1, y)));
            cout << mod(ans) << "\n";
        }
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
