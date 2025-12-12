#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, h;
    cin >> n >> h;
    vector<array<int,3>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    ll lo = h, hi = h;
    int t0 = 0;
    for(int i = 1; i <= n; i++) {
        auto [t, l, r] = a[i];
        int len = t - t0;
        t0 = t;
        lo -= len;
        hi += len;
        if(l > hi || r < lo) {
            cout << "No\n";
            return;
        }
        lo = max(lo, (ll)l);
        hi = min(hi, (ll)r);
    }
    cout << "Yes\n";
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
