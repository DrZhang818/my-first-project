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
    vector<ll> a(n + 2);
    for(int i = 1; i <= n + 1; i++) {
        cin >> a[i];
    }
    vector<ll> b(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    ll ans = 0;
    for(int i = 1; i <= n + 1; i++) {
        if(b[i - 1]) {
            if(a[i] <= b[i - 1]) {
                ans += a[i];
                b[i - 1] -= a[i];
                a[i] = 0;
            } else {
                ans += b[i - 1];
                a[i] -= b[i - 1];
                b[i - 1] = 0;
            }
        }
        if(b[i]) {
            if(a[i] <= b[i]) {
                ans += a[i];
                b[i] -= a[i];
                a[i] = 0;
            } else {
                ans += b[i];
                a[i] -= b[i];
                b[i] = 0;
            }      
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
