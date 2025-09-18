#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll C[21][21];

void solve() {
    int n, m;
    ll Y;
    cin >> n >> m >> Y;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> dp(n + 1);
    for(int s = 0; s < 1 << n; s++) {
        int c = __builtin_popcount(s);
        ll LCM = 1;
        bool ok = true;
        for(int i = 0; i < n; i++) {
            if(s >> i & 1) {
                ll g = gcd(LCM, a[i]);
                if(LCM / g > Y / a[i]) {
                    ok = false;
                    break;
                }
                LCM = LCM / g * a[i];
            }
        }
        if(ok) {
            dp[c] += Y / LCM;
        }
    }
    ll ans = 0;
    for(int i = m, s = 1; i <= n; i++, s ^= 1) {
        ll cur = C[i][m] * dp[i];
        if(s == 1) {
            ans += cur;
        } else {
            ans -= cur;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= 20; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
