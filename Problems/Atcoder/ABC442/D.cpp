#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct FenwickTree {
    inline int lowbit(int o) { return o & -o; }

    int n;
    vector<ll> tr;

    FenwickTree(int n) : n(n), tr(n) {}

    void add(int o, int d) {
        for(; o < n; o += lowbit(o)) {
            tr[o] += d;
        }
    }

    ll query(int o) {
        ll res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }

    ll rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void solve() {  
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    FenwickTree fen(n + 1);
    for(int i = 1; i <= n; i++) {
        fen.add(i, a[i]);
    }

    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x;
            cin >> x;
            fen.add(x, -a[x]);
            fen.add(x + 1, -a[x + 1]);
            swap(a[x], a[x + 1]);
            fen.add(x, a[x]);
            fen.add(x + 1, a[x + 1]);            
        } else {
            int l, r;
            cin >> l >> r;
            cout << fen.rangeQuery(l, r) << "\n";
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
