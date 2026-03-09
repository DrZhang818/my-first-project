#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    i64 ans = 0, dp = 0;

    stack<int> stk;

    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[stk.top()] + 1 != a[i]) {
            stk.pop();
        }
        int j = stk.empty() ? 0 : stk.top();
        dp += i - j;
        ans += dp;
        stk.push(i);
    }

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
