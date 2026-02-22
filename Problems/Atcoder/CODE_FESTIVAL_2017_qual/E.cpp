#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = s[i - 1] - '0';
    }

    vector<int> L(n + 1, n + 1), R(n + 1, 0);

    for(int i = 1; i <= n; i++) {
        if(a[i] == 1) {
            L[i] = min(L[i - 1], i);
        }
    }

    for(int i = n; i >= 1; i--) {
        if(a[i] == 1) {
            if(i == n) {
                R[i] = i;
            } else {
                R[i] = max(R[i + 1], i);
            }
        }
    }

    vector<int> dp(n + 1);

    for(int i = 2; i <= n; i++) {
        dp[i] = max(dp[i], dp[i - 1]);
        if(i < n && a[i - 1] == 1 && a[i] == 0 && a[i + 1] == 1) {
            dp[i] = max(dp[i], (L[i - 1] >= 2 ? dp[L[i - 1] - 2] : 0) + R[i - 1] - L[i - 1] + 1);
            dp[i] = max(dp[i], dp[L[i - 1] - 1] + R[i - 1] - L[i - 1]);
            for(int j = L[i + 1]; j <= R[i + 1]; j++) {
                dp[j] = max(dp[j], (a[i - 2] == 1 ? dp[i - 2] : i >= 3 ? dp[i - 3] : 0) + j - L[i + 1] + 1);
            }
        }
    }

    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
