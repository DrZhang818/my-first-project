#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll r;
    cin >> r;
    ll ans = r % 10;
    r /= 10;
    ll x = 2;
    while(r > 0) {
        int rem = r % 10;
        r /= 10;
        ans += x * rem;
        x *= 2;
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
