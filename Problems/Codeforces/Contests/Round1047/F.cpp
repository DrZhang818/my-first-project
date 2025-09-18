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
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> stk;
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[stk.back()] < a[i]) {
            stk.pop_back();
        }
        if(!stk.empty()) {
            int l = -1, r = stk.size();
            while(l + 1 < r) {
                int mid = l + r >> 1;
                if(a[stk[mid]] >= b[i]) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            if(l != -1) {
                pre[i] = stk[l];
            }
        }
        stk.push_back(i);
    }
    ll ans = 0;
    vector<ll> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if(a[i] == b[i]) {
            dp[i] += i;
        } else {
            dp[i] += pre[i];
        }
        ans += dp[i];
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
