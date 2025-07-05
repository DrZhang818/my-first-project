#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    ll x, d;
    cin >> n >> x >> d;
    vector<ll> a(n + 1);
    a[1] = x;
    ll tot = 0;
    for(int i = 2; i <= n; i++) {
        a[i] = a[i - 1] + d;
        tot += a[i];
    }
    ll lo = a[1] - tot, hi = -lo;
    cerr << lo << "\n";
    ll ans = (hi - lo) / (2 * d) + 1;
    ans += 2;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
