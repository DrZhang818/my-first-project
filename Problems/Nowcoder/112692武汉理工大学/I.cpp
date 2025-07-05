#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = LLONG_MAX;

//https://ac.nowcoder.com/acm/contest/112692/I
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    vector<db> dp(n + 1, inf);
    dp[n] = 0;
    for(int i = n - 1; i >= 0; i--) {
        ll tot = 0;
        for(int j = i + 1; j <= n; j++) {
            tot += dp[j];
            dp[i] = min(dp[i], ((db)(j - i + 1) * a[j] + tot) / (j - i));
        }
    }
    cout << fixed << setprecision(12) << dp[0] << "\n";
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
