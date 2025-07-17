#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E12 + 1;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    vector<ll> d(n);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    for(int i = 2; i <= n; i++) {
        d[i - 1] = a[i] - a[i - 1];
    }
    sort(d.begin() + 1, d.end());
    ll ans = 0;
    for(int i = 1; i <= n - m; i++) {
        ans += d[i];
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
