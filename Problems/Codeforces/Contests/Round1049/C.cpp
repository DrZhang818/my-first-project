#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    ll ans = -inf, tot = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(i & 1) {
            tot += a[i];
        } else {
            tot -= a[i];
        }
    }
    ll pos = -inf, neg = -inf;
    for(int i = 1; i <= n; i++) {
        if(i & 1) {
            pos = max(pos, -2LL * a[i] - i);
        } else {
            neg = max(neg, 2LL * a[i] + i);
        }
    }
    ans = max(ans, max(0LL, pos + neg) + tot);
    pos = -inf, neg = -inf;
    for(int i = 1; i <= n; i++) {
        if(i & 1) {
            pos = max(pos, -2LL * a[i] + i);
        } else {
            neg = max(neg, 2LL * a[i] - i);
        }
    }
    ans = max(ans, max(0LL, pos + neg) + tot);
    ans = max(ans, n - 1 - (n % 2 == 0) + tot);
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
