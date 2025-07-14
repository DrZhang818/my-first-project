#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E15;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i] - i;
    }
    sort(b.begin() + 1, b.end());
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + b[i];
    }
    ll ans = inf;
    for(int i = 1; i <= n; i++) {
        ans = min(ans, -pre[i - 1] + pre[n] - pre[i - 1] + b[i] * (i - 1 - (n - i + 1)));
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
