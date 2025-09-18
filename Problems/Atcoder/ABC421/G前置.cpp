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
    vector<ll> d(n + 1);
    for(int i = 1; i <= n; i++) {
        d[i] = a[i] - a[i - 1];
    }
    ll pos = 0, neg = 0;
    for(int i = 2; i <= n; i++) {
        if(d[i] > 0) {
            pos += d[i];
        } else if(d[i] < 0) {
            neg -= d[i];
        }
    }
    ll ans = max(pos, neg);
    ll cnt = 1 + max(pos, neg) - min(pos, neg);
    cout << ans << "\n" << cnt << "\n";
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
