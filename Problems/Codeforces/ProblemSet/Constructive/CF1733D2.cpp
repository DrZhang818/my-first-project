#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1733/D2

void solve() {
    int n;
    ll x, y;
    cin >> n >> x >> y;
    string s, t;
    cin >> s >> t;
    s = "#" + s, t = "#" + t;
    vector<int> a{0};
    for(int i = 1; i <= n; i++) if(s[i] != t[i]) a.push_back(i);
    int m = a.size() - 1;
    if(m % 2) { cout << -1 << "\n"; return ; }
    if(x >= y) {
        if(m == 2 && a[1] + 1 == a[2]) {
            cout << min(x, 2 * y) << "\n";
        } else {
            cout << m / 2 * y << "\n";
        }
        return;
    }
    vector<ll> dp(m + 1);
    for(int i = 2; i <= m; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + y - x * (a[i] - a[i - 1]));
    }
    cout << m / 2 * y - dp[m] << "\n";
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
