#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    array<int,3> a {};
    int n;
    for(int i = 0; i < 3; i++) {
        cin >> a[i];
    }
    cin >> n;
    vector<ll> dp(n + 1);
    dp[0] = 1;
    for(int i = 0; i < 3; i++) {
        for(int j = a[i]; j <= n; j++) {
            dp[j] += dp[j - a[i]];
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
