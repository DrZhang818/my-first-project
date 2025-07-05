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
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    for(int i = 3; i <= n; i++) {
        for(int j = 2; j < i; j++) {
            int mn = max(a[i] - a[j] + 1, a[n] - a[i] - a[j] + 1);
            auto pos = lower_bound(a.begin() + 1, a.begin() + j, mn) - a.begin();
            ans += j - pos;
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
