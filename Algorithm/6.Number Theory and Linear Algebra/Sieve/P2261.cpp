#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    ll ans = 1LL * n * k;
    for(int L = 1, R; L <= n && L <= k; L = R + 1) {
        R = k / (k / L);
        R = min(R, n);
        ll x = k / L, sum = 1LL * (L + R) * (R - L + 1) / 2;
        ans -= x * sum;
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
