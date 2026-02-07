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
    
    if(n == 1) {
        cout << (s == "1" ? 0 : -1) << "\n";
        return;
    }

    int sum = 0;
    for(char c : s) {
        sum += c == '0' ? -1 : 1;
    }
    if(sum >= 0) {
        cout << n << "\n";
        return;
    }
    if(sum == -n) {
        cout << -1 << "\n";
        return;
    }

    int ans = n + 3;

    auto cal = [&]() {
        if(s[0] == '1' || s[1] == '1' && sum == -1) {
            ans = n + 1;
            return;
        }
        if(s[1] == '1') {
            ans = min(ans, n + 2);
        }
        int cur = 0, dp = 0;
        for(char c : s) {
            int v = c == '0' ? -1 : 1;
            cur += v;
            dp = max(0, dp) + v;
            if(cur > 0) {
                ans = min(ans, n + 1);
            }
            if(dp >= 2) {
                ans = min(ans, n + 2);
            }
        }
    };

    cal();
    reverse(s.begin(), s.end());
    cal();

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
