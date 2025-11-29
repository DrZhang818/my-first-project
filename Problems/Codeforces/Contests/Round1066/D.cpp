#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int L = 1, R = n;
    ll ans = 0;
    
    while(L <= R) {
        if(L == R) {
            ans += max({l - a[L], a[R] - r, 0});
        } else {
            ans += max({a[R] - a[L], a[L] + a[R] - 2 * r, 2 * l - a[L] - a[R]});
        }
        L++;
        R--;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
