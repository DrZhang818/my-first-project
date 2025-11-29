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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1), suf(n + 2);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] + a[i];
    }
    vector<ll> f(n + 1);
    for(int i = 1; i <= n; i++) {
        f[i] = pre[i - 1] + i - 1LL * i * i;
    }
    for(int i = 1; i <= n; i++) {
        f[i] = max(f[i], f[i - 1]);
    }
    ll ans = pre[n];
    for(int i = 1; i <= n; i++) {
        ans = max(ans, suf[i + 1] + f[i] + 1LL * i * i + i);
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
