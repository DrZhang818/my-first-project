#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> dp(n + 1);
    dp[0] = 1;

    for(int i = 1; i <= n; i++) {
        vector<int> lps(i + 1);
        lps[i] = 0;
        for(int j = i - 1; j >= 1; j--) {
            int x = lps[j + 1];
            while(x > 0 && a[j] != a[i - x]) {
                x = lps[i - x + 1];
            }
            lps[j] = x + (a[j] == a[i - x]);
        }
        for(int j = 1; j <= i; j++) {
            if(lps[j] == 0) {
                add(dp[i], dp[j - 1]);
            }
        }
    }

    cout << dp[n] << "\n";

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
