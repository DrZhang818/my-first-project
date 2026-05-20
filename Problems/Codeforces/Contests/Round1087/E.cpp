#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    s = "#" + s;

    vector<int> lps(n + 1);
    vector<i64> dp(n + 1);
    auto calc = [&](int l, int r) {
        lps[l] = l - 1;

        for(int i = l + 1; i <= r; i++) {
            int j = lps[i - 1];
            while(j >= l && s[i] != s[j + 1]) {
                j = lps[j];
            }
            lps[i] = s[i] == s[j + 1] ? j + 1 : l - 1;
        }

        i64 res = 0;

        for(int i = l; i <= r; i++) {
            if(lps[i] == l - 1) {
                dp[i] = 1;
            } else {
                dp[i] = dp[i - lps[i] + l - 1] + dp[lps[i]];
            }
            res += dp[i];
        }

        return res;
    };


    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << calc(l, r) << "\n";
    }
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
