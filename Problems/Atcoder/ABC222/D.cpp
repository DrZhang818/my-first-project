#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;
constexpr int N = 3000;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    for(int i = 1; i <= n; i++) {
        if(a[i] > b[i]) {
            cout << 0 << "\n";
            return;
        }
    }

    vector<int> dp(N + 1, 1);

    for(int i = 1; i <= n; i++) {
        vector<int> ndp(N + 1);

        for(int j = a[i]; j <= b[i]; j++) {
            ndp[j] = dp[j];
        }

        dp = move(ndp);
        for(int j = 1; j <= N; j++) {
            add(dp[j], dp[j - 1]);
        }        
    }

    cout << dp[N] << "\n";
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}