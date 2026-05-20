#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    string s;
    cin >> s;

    int ans = 0;
    array<int, 3> dp {};

    for(int i = 0; i < s.size(); i++) {
        add(ans, 1);
        add(dp[s[i] - 'a'], 1);
        for(char c : {'a', 'b', 'c'}) {
            if(c == s[i]) continue;
            add(dp[s[i] - 'a'], dp[c - 'a']);
            add(ans, dp[c - 'a']);
        }
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