#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];
    ll ans = inf;
    vector<int> suf(n + 2);
    for(int i = n, j = m, cur = 0; i >= 1; i--) {
        if(j >= 1 && a[i] >= b[j]) j--, cur++;
        suf[i] = cur;
    }
    for(int i = 1, j = 1; i <= n + 1; i++) {
        if(suf[i] == m - j + 1) ans = 0;
        if(suf[i] == m - j) ans = min(ans, b[j]);
        if(i <= n && j <= m && a[i] >= b[j]) j++;
    }
    if(ans == inf) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }
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
