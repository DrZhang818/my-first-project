#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k, cnt = 0;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i], cnt += b[i] == -1;
    ll ans = 0;
    if(cnt != n) {
        bool ok = true;
        int tar = -1;
        for(int i = 1; i <= n; i++) {
            if(b[i] != -1 && tar == -1) tar = a[i] + b[i];
            else if(b[i] != -1 && a[i] + b[i] != tar) ok = false;
        }
        for(int i = 1; i <= n; i++) {
            if(b[i] == -1 && (tar - a[i] < 0 || tar - a[i] > k)) ok = false;
        }
        if(ok) cout << 1 << "\n";
        else cout << 0 << "\n";
    } else {
        int mn = inf, mx = -inf;
        for(int i = 1; i <= n; i++) mn = min(mn, a[i]), mx = max(mx, a[i]);
        ans = max(0, mn + k - mx + 1);
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
