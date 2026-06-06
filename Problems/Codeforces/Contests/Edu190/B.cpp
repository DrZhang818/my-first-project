#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    string s;
    cin >> s;
    array<int, 2> dp {};
    for(char c : s) {
        if(c == '4') {
            dp[0] += 1;
            dp[1] += 1;
        } else if(c == '2') {
            dp[1] += 1;
        } else {
            dp[1] = min(dp[0], dp[1]);
            dp[0] += 1;
        }
    }

    cout << min(dp[0], dp[1]) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}