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
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int mx = *max_element(cnt.begin() + 1, cnt.end());
    vector<int> dp(mx + 1);
    dp[mx] = 1;
    for(int i = 1; i <= n; i++) {
        if(cnt[i] == 0) {
            continue;
        }
        for(int j = 0; j <= mx; j++) {
            add(dp[max(0, j - cnt[i])], 1LL * dp[j] * cnt[i] % MOD);
        }
    }
    cout << dp[0] << "\n";
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
