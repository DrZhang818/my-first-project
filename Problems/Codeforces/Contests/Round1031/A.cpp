#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int k, a, b, x, y;
    cin >> k >> a >> b >> x >> y;
    if(x > y) swap(x, y), swap(a, b);
    ll ans = 0;
    if(k >= a) {
        ans += (k - a + x) / x;
        k -= ans * x;
    }
    if(k >= b) {
        ans += (k - b + y) / y;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
