#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<pair<ll,ll>> t(n + 2);
    for(int i = 1; i <= n; i++) {
        ll d0 = (a[i] - b[i] + m) % m;
        ll d1 = (b[i] - a[i] + m) % m;
        t[i] = {d0, d1};
    }
    sort(t.begin() + 1, t.begin() + n + 1);
    ll ans = inf;
    for(int i = 0; i <= n; i++) {
        if(t[i].first == 0 && t[i + 1].first == 0) continue;
        ans = min(ans, t[i].first + t[i + 1].second);
    }
    if(ans == inf) {
        cout << 0 << "\n";
        return;
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
