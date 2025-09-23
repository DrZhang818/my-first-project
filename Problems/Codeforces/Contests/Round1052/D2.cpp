#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int l, r;
    cin >> l >> r;
    int n = r - l + 1;
    vector<int> a(n + 1);
    iota(a.begin() + 1, a.end(), l);
    int L = 1, R = n + 1;
    for(int i = 29; i >= 0; i--) {
        int x = L;
        while(x < R && (~a[x] >> i & 1)) {
            x++;
        }
        if(x - L <= R - x) {
            int m = 2 * x - L;
            reverse(a.begin() + L, a.begin() + m);
            L = m;
        } else {
            int m = 2 * x - R;
            reverse(a.begin() + m, a.begin() + R);
            R = m;
        }
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += a[i] | (i + l - 1);
    }
    cout << ans << "\n";
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
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
