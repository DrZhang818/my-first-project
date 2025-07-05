#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    stack<int> stk;
    vector<int> pre(n + 1, 0), suf(n + 1, n + 1);
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[stk.top()] >= a[i]) {
            suf[stk.top()] = i;
            stk.pop();
        }
        if(!stk.empty()) {
            pre[i] = stk.top();
        }
        stk.push(i);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, (suf[i] - pre[i] - 1) * a[i]);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
