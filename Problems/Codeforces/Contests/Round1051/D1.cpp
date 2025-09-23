#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://codeforces.com/contest/2143/problem/D1

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;    
}
    
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector dp(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        add(ndp[a[i]][0], 1);
        for(int j = 1; j <= a[i]; j++) {
            for(int k = 0; k < j; k++) {
                add(ndp[a[i]][k], dp[j][k]);
            }
        }
        for(int j = a[i] + 1; j <= n; j++) {
            for(int k = 0; k <= a[i]; k++) {
                add(ndp[j][a[i]], dp[j][k]);
            }
        }
        swap(dp, ndp);
    }
    int ans = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            add(ans, dp[i][j]);
        }
    }
    cout << ans << "\n";
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
