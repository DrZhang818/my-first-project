#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> d(n + 2, 1);
    d[0] = 0;
    ll ans = 0;
    while(q--) {
        int i, x;
        cin >> i >> x;
        ans -= x;
        d[i] += x;
        d[i + 1] = max(1LL, d[i + 1] - x);
    }
    for(int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
        ans += d[i];
    }
    cout << ans << "\n";
}  

void solve2() {
    int n, q;
    cin >> n >> q;
    vector<ll> add(n + 2), c(n + 1);
    while(q--) {
        int i, x;
        cin >> i >> x;
        add[i] += x;
        if(i < n) {
            c[i] = max(c[i], add[i] - add[i + 1]);
        }
    }
    ll x = 1, ans = 1;
    for(int i = 1; i < n; i++) {
        x += c[i] + 1;
        ans += x;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve2();
    }
    return 0;
}
