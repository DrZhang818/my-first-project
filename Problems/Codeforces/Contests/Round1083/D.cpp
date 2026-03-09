#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 1000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> pre(n + 2), suf(n + 2);

    {
        stack<int> stk;
        int cur = 0;
        for(int i = n; i >= 1; i--) {
            while(!stk.empty() && a[stk.top()] < a[i]) {
                stk.pop();
                cur++;
            }
            suf[i] = cur;
            stk.push(i);
        }
    }

    {
        stack<int> stk;
        int cur = 0;
        for(int i = 1; i <= n; i++) {
            while(!stk.empty() && a[stk.top()] < a[i]) {
                stk.pop();
                cur++;
            }
            pre[i] = cur;
            stk.push(i);
        }
    }

    int ans = inf;
    for(int i = 1; i <= n; i++) {
        ans = min(ans, pre[i - 1] + suf[i]);
    }
    ans = min(ans, pre[n]);

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
