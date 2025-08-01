#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    if(n >= m) {
        cout << 0 << "\n";
        return;
    }
    sort(a.begin() + 1, a.end());
    vector<int> d(m);
    for(int i = 1; i < m; i++) {
        d[i] = a[i + 1] - a[i];
    }
    sort(d.begin() + 1, d.end());
    ll ans = 0;
    for(int i = 1; i <= m - n; i++) {
        ans += d[i];
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
