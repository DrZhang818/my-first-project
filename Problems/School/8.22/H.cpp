#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int a, b, c, x, y;
    cin >> a >> b >> c >> x >> y;
    ll ans = 0;
    if(2 * c >= (a + b)) {
        ans += a * x + b * y;
    } else {
        int t = min(x, y);
        ans += t * 2 * c;
        x -= t;
        y -= t;
        if(x) {
            if(2 * c >= a) {
                ans += a * x;
            } else {
                ans += 2 * c * x;
            }
        } else if(y) {
            if(2 * c >= b) {
                ans += b * y;
            } else {
                ans += 2 * c * y;
            }
        }
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
