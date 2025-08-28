#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    ll x, y;
    cin >> n >> x >> y;
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    int ans = n;
    ll s1 = 0, s2 = 0;
    sort(a.begin() + 1, a.end(), greater<ll>());
    for(int i = 1; i <= n; i++) {
        s1 += a[i];
        if(s1 > x) {
            ans = min(ans, i);
            break;
        }
    }
    sort(b.begin() + 1, b.end(), greater<ll>());
    for(int i = 1; i <= n; i++) {
        s2 += b[i];
        if(s2 > y) {
            ans = min(ans, i);
            break;
        }
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
