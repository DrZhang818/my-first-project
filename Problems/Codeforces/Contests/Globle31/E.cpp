#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll l, r;
    cin >> l >> r;
    if(r - l + 1 & 1) {
        cout << 0 << "\n";
        return;
    }
    ll mxlen = (r - l + 1) / 2;
    ll ans = 1;
    for(int i = __lg(r); i >= 0; i--) {
        ll len = min(1LL << i, mxlen);
        if((r - l + 1) % len || (l >> i & 1) || (l + len - 1 >> i & 1) || (l + len >> i & 1) == 0 || (r >> i & 1) == 0) {
            continue;
        }
        ans *= 2;
    }
    cout << ans - 1 << "\n";
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
