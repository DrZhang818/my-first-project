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
    vector<ll> d(n + 1);
    for(int i = 1; i <= n; i++) {
        d[i] = a[i] - a[i - 1];
    }
    ll ans = 0, t = 0;
    for(int i = 2; i <= n; i++) {
        if(d[i] > 0) {
            ans += d[i];
        } else {
            t += -d[i];
        }
    }
    ans += t;
    d[1] -= t;
    ans += abs(d[1]);
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
