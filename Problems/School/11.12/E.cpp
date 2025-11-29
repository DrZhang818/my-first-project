#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    ll pre = 0, suf = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        suf += a[i];
    }
    ll ans = 1E18;
    for(int i = 1; i <= n; i++) {
        ans = min(ans, abs(suf - pre));
        pre += a[i];
        suf -= a[i];
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
