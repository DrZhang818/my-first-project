#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<ll> tr;
    FenwickTree(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        tr.assign(n, {});
    }
    void add(int o, ll x) {
        for(; o < n; o += lowbit(o)) {
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
    ll rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
    int select(ll k) {
        int x = 0;
        ll cur = 0;
        for(int i = 1 << __lg(n); i; i >>= 1) {
            if(x + i < n && cur + tr[x + i] < k) {
                x += i;
                cur += tr[x];
            }
        }
        return x + 1;
    }
};

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;
    FenwickTree fen(2 * n + 2);
    ll ans = 0;
    fen.add(n + 1, 1);
    int f = 0;
    for(char c : s) {
        if(c == 'A') {
            f++;
        } else if(c == 'B') {
            f--;
        }
        ans += fen.query(f + n);
        fen.add(f + n + 1, 1);
    }
    cout << ans << "\n";
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
