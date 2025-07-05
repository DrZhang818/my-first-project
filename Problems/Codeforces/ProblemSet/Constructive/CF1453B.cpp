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
    vector<int> d(n + 1);
    ll tot = 0;
    for(int i = n - 1; i >= 1; i--) { 
        d[n - i] = a[i] - a[i + 1];
        tot += abs(d[n - i]);
    }
    ll ans = tot;
    for(int i = 0; i <= n - 1; i++) {
        if(i == 0 || i == n - 1) {
            ans = min(ans, tot - abs(d[i]) - abs(d[i + 1]));
        } else {
            ans = min(ans, tot - abs(d[i]) - abs(d[i + 1]) + abs(d[i] + d[i + 1]));
        }
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
