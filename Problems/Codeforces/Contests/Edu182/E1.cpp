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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }  
   
    auto work = [&]() {
        vector<int> pre{0};
        for(int i = 1; i <= n; i++) {
            if(a[i] > pre.back()) {
                pre.push_back(a[i]);
            }
        }
        int m = pre.size() - 1;
        vector<int> f(n + 1);
        vector<int> dp(m + 1);
        dp[0] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = m; j >= 1; j--) {
                if(a[i] <= pre[j]) {
                    add(dp[j], dp[j]);
                }
                if(a[i] == pre[j]) {
                    if(j == 1) {
                        add(dp[j], 1);
                    } else {
                        add(dp[j], dp[j - 1]);
                    }
                    if(j == m) {
                        f[i] = dp[j - 1];
                    }
                }
            }
        }
        return f;
    };

    auto L = work();
    reverse(a.begin() + 1, a.end());
    auto R = work();
    reverse(a.begin() + 1, a.end());
    reverse(R.begin() + 1, R.end());

    int mx = ranges::max(a);
    int ans = 0, sum = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == mx) {
            add(ans, 1LL * L[i] * R[i] % MOD);
            add(ans, 1LL * sum * R[i] % MOD);
        }
        add(sum, sum);
        if(a[i] == mx) {
            add(sum, L[i]);
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
