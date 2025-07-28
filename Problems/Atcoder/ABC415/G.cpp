#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 90005;

void solve() {
    ll n;
    int m;
    cin >> n >> m;
    vector<int> w(301);
    for(int i = 1; i <= m; i++) {
        int A, B;
        cin >> A >> B;
        w[A] = max(w[A], B);
    }
    int a = 1, b = 0;
    for(int i = 1; i <= 300; i++) {
        int x = i, y = w[i];
        if(y * a > x * b) {
            a = x;
            b = y;
        }
    }
    ll ans = n;
    if(n > N + a) {
        ll t = (n - N - a) / (a - b) + 1;
        ans += t * b;
        n -= t * (a - b);
    }
    vector<ll> dp(n + 1);
    for(int i = 1; i <= 300; i++) {
        for(int j = i; j <= n; j++) {
            dp[j] = max(dp[j], dp[j - i + w[i]] + w[i]);
        }
    }
    cout << ans + dp[n] << "\n";
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
