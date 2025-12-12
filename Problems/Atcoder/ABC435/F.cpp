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
    vector<int> a(n + 1);
    vector<int> pos(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }    
    vector<int> pre(n + 1), suf(n + 1);
    stack<int> stk;
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[i] > a[stk.top()]) {
            pre[i] = stk.top();
            stk.pop();
        }
        stk.push(i);
    }
    while(!stk.empty()) stk.pop();
    for(int i = n; i >= 1; i--) {
        while(!stk.empty() && a[i] > a[stk.top()]) {
            suf[i] = stk.top();
            stk.pop();
        }
        stk.push(i);
    }
    vector<ll> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        int x = pos[i];
        if(pre[x]) {
            dp[i] = max(dp[i], dp[a[pre[x]]] + x - pre[x]);
        }
        if(suf[x]) {
            dp[i] = max(dp[i], dp[a[suf[x]]] + suf[x] - x);
        }
    }
    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
