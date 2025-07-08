#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
inline int lowbit(int o) { return o & -o; }
class FenwickTree {
private:
    int n;
    vector<ll> tr;
public:
    FenwickTree(int x) : n(x), tr(x + 1) {}
    void add(int o, ll x) {
        for(; o <= n; o += lowbit(o)) {
            tr[o] += x;
        }
    }
    ll query(int o) {
        ll res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
    ll range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};


void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> d2(n + 3);
    FenwickTree tr1(n + 5), tr2(n + 5);
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            ll l, r, k, d;
            cin >> l >> r >> k >> d;
            ll len = r - l + 1;
            tr1.add(l, k * (n - l + 1));
            tr1.add(l + 1, (d-k) * (n - l));
            tr1.add(r + 1, (-k-len*d) * (n - r));
            tr1.add(r + 2, (k+(len-1)*d) * (n - r - 1));
            tr2.add(l, k);
            tr2.add(l + 1, d - k);
            tr2.add(r + 1, -k - len * d);
            tr2.add(r + 2, k + (len - 1) * d);
            d2[l] += k;
            d2[l + 1] += d - k;
            d2[r + 1] += -k - len * d;
            d2[r + 2] += k + (len - 1) * d;
        } else {
            int i;
            cin >> i;
            ll ans = tr1.query(i) - (n - i) * tr2.query(i);
            cout << ans << "\n";
        }   
    }
    for(int i = 1; i <= n; i++) {
        d2[i] += d2[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        d2[i] += d2[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        cout << d2[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
