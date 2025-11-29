#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto st = max_element(a.begin() + 1, a.end());
    rotate(a.begin() + 1, st, a.end());
    a[0] = inf;
    a.push_back(inf);
    stack<int> stk;
    vector<int> pre(n + 1, 0), suf(n + 1, n + 1);
    ll ans = 0;
    for(int i = n; i >= 1; i--) {
        while(!stk.empty() && a[i] >= a[stk.top()]) {
            pre[stk.top()] = i;
            stk.pop();
        }
        if(!stk.empty()) {
            suf[i] = stk.top();
        }
        stk.push(i);
    }
    for(int i = 2; i <= n; i++) {
        ans += min(a[pre[i]], a[suf[i]]);
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
