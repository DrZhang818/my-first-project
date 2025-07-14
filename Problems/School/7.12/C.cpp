#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E15;

//https://atcoder.jp/contests/abc102/tasks/arc100_b
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
    }
    ll ans = inf;
    for(int i = 1, j = 2, k = 3; j <= n - 2; j++) {
        while(i < j - 1 && abs(a[i]-(a[j]-a[i])) > abs(a[i+1]-(a[j] - a[i+1]))) i++;
        while(k < n - 1 && abs(a[k]-a[j]-(a[n]-a[k])) > abs(a[k+1]-a[j]-(a[n]-a[k+1]))) k++;
        ll mn = min({a[i], a[j] - a[i], a[k] - a[j], a[n] - a[k]});
        ll mx = max({a[i], a[j] - a[i], a[k] - a[j], a[n] - a[k]});
        ans = min(ans, mx - mn);
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
