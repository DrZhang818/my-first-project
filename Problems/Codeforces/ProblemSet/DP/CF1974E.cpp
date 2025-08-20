#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

struct info {
    int c, h;
};
void solve() {
    int m;
    ll x;
    cin >> m >> x;
    vector<info> a(m + 1);
    int tot = 0;
    for(int i = 1; i <= m; i++) {
        cin >> a[i].c >> a[i].h;
        tot += a[i].h;
    }  
    vector<ll> dp(tot + 1, inf);
    dp[0] = 0;
    for(int i = 1; i <= m; i++) {
        ll sum = (i - 1) * x;
        for(int j = tot - a[i].h; j >= 0; j--) {
            if(sum - dp[j] >= a[i].c) {
                dp[j + a[i].h] = min(dp[j + a[i].h], dp[j] + a[i].c);
            }
        }
    }
    for(int i = tot; i >= 0; i--) {
        if(dp[i] != inf) {
            cout << i << "\n";
            return;
        }
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
