#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;


void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    ll lo = inf, hi = -inf, tot = 0, cnt = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
        lo = min(lo, a[i]);
        hi = max(hi, a[i]);
    }
    for(int i = 1; i <= n; i++) if(a[i] == hi) cnt++;
    if(hi - 1 - lo > k || (hi - lo > k && cnt >= 2)) {
        cout << "Jerry\n";
    } else if(tot % 2 == 0) {
        cout << "Jerry\n";
    } else {
        cout << "Tom\n";
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
