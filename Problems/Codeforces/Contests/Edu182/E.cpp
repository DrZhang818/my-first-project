#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), L{0}, R{0};
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }  
    for(int i = 1; i <= n; i++) {
        if(a[i] > L.back()) {
            L.push_back(a[i]);
        }
    }
    for(int i = n; i >= 1; i--) {
        if(a[i] > R.back()) {
            R.push_back(a[i]);
        }
    }
    int sz1 = L.size() - 1, sz2 = R.size() - 1;
    int mx = *max_element(a.begin() + 1, a.end());
    vector pre(n + 1, vector<int>(sz1 + 1));
    vector suf(n + 2, vector<int>(sz2 + 1));
    vector dp(n + 1, vector<int>(sz1 + 1));
    dp[0][0] = 1;
    suf[n + 1][0] = 1;
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        for(int j = 0; j < sz1; j++) {
            if(a[i] <= L[j]) {
                add(dp[i][j], dp[i - 1][j]);
            } else if(a[i] == L[j + 1]) {
                add(dp[i][j + 1], dp[i - 1][j]);
                add(pre[i][j + 1], dp[i - 1][j]);
            }
        }
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1];
        for(int j = 0; j <= sz2; j++) {
            if(a[i] <= R[j]) {
                add(suf[i][j], suf[i + 1][j]);
            } else if(j < sz2 && a[i] == R[j + 1]) {
                add(suf[i][j + 1], suf[i + 1][j]);
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == mx) {
            add(ans, 1LL * pre[i][sz1] * (suf[i + 1][sz2 - 1] + suf[i + 1][sz2]) % MOD);
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
