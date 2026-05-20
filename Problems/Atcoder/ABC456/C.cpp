#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;

void solve() {
    string s;
    cin >> s;

    int ans = 0;
    int dp = 0;

    for(int i = 0; i < s.size(); i++) {
        if(i == 0 || s[i] == s[i - 1]) {
            dp = 1;
        } else {
            dp = (dp + 1) % MOD;
        }
        ans = (ans + dp) % MOD;
    }

    cout << ans << "\n";
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