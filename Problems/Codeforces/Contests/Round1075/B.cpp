#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;

void solve() {  
    int n;
    ll x;
    cin >> n >> x;
    vector<ll> a(n + 1), b(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    ll cur = 0;
    for(int i = 1; i <= n; i++) {
        cur += (b[i] - 1) * a[i];
    }
    if(cur >= x) {
        cout << 0 << "\n";
        return;
    }
    bool ok = false;
    for(int i = 1; i <= n; i++) {
        if(a[i] * b[i] - c[i] > 0) {
            ok = true;
            break;
        }
    }
    if(!ok) {
        cout << -1 << "\n";
        return;
    }
    ll ans = numeric_limits<ll>::max();
    for(int i = 1; i <= n; i++) {
        ll len = a[i] * b[i] - c[i];
        if(len <= 0) continue;
        ll t = (x - cur + len - 1) / len;
        ans = min(ans, t);
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
