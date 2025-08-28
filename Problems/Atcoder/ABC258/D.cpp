#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    int n, x;
    cin >> n >> x;
    ll ans = LLONG_MAX;
    vector<ll> a(n + 1), b(n + 1);
    vector<ll> mn(n + 1);
    mn[0] = inf;
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        mn[i] = min(mn[i - 1], b[i]);
    }
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i] + b[i];
        ll cnt = x - i;
        if(cnt < 0) {
            break;
        }
        ans = min(ans, sum + mn[i] * cnt);
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
