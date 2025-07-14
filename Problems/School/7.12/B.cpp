#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    int n;
    cin >> n;
    ll ans = -inf;
    ll v1 = -inf, v2 = -inf;
    for(int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        if(i != 1) {
            ans = max(ans, x + v2);
            ans = max(ans, v1 - x);
        }
        v1 = max(v1, x);
        v2 = max(v2, -x);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
