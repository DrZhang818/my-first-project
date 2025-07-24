#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    k--;
    vector<int> a;
    for(int s = 0; s < 1 << m - 1; s++) {
        if(s & s << 1) continue;
        a.push_back(s);
    }
    vector<int> dp(m + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        vector<int> ndp(m + 1);
        for(int s : a) {
            for(int j = 0; j <= m - 1; j++) {
                if(s >> j & 1) {
                    add(ndp[j], dp[j + 1]);
                    add(ndp[j + 1], dp[j]);
                    j++;
                } else {
                    add(ndp[j], dp[j]);
                }
            }
        }
        swap(dp, ndp);
    }
    cout << dp[k] << "\n";
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
