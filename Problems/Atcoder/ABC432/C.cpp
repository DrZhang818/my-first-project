#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    ll x, y;
    cin >> n >> x >> y;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    ll rem = -1, mn = numeric_limits<ll>::max();
    for(int i = 1; i <= n; i++) {
        ll cur = a[i] * x % (y - x);
        if(rem != -1 && cur != rem) {
            cout << -1 << "\n";
            return;
        }
        rem = cur;
        if(mn < a[i] * x) {
            cout << -1 << "\n";
            return;
        }
        mn = min(mn, a[i] * y);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += (mn - a[i] * x) / (y - x);
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
