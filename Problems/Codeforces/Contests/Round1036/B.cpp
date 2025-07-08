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
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> mn(n + 1, inf);
    mn[1] = a[1];
    for(int i = 2; i <= n; i++) {
        mn[i] = min(a[i], mn[i - 1]);
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + mn[i];
    }
    ll ans = pre[n];
    for(int i = 1; i < n; i++) {
        ans = min(ans, pre[i - 1] + min(mn[i - 1], a[i] + a[i + 1]));
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
