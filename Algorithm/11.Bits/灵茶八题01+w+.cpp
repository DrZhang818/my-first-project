#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/U360300

void solve2() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        ans += i * (n - i + 1) * a[i];
    }
    cout << ans << "\n";
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<ll> dp(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + a[i] * i;
    }
    for(int i = 1; i <= n; i++) {
        ans += dp[i];
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
