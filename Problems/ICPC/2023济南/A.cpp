#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n + 1);
    for(int i = 0; i < n; i++) {
        a[i + 1] = s[i] == '(' || s[i] == ')';
    }

    vector<array<int, 2>> dp(n + 1);

    stack<int> stk;

    for(int i = 1; i <= n; i++) {
        int x = a[i];
        if(!stk.empty() && a[stk.top()] == x) {
            int j = stk.top(); stk.pop();
            dp[i][x] = 1;
            dp[i][x ^ 1] |= dp[j - 1][x ^ 1];
            if(dp[j - 1][x]) {
                cout << "No\n";
                return;
            }
        } else {
            stk.push(i);
        }
    }

    cout << "Yes\n";
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