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
    vector<vector<int>> a(n + 1);
    map<int,ll> dp;
    vector<int> mex(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        int m;
        cin >> m;
        a[i].resize(m + 1);
        auto& b = a[i];
        auto& lo = mex[i];
        for(int j = 1; j <= m; j++) {
            cin >> b[j];
        }
        sort(b.begin() + 1, b.end());
        int hi = 1;
        for(int j = 1; j <= m; j++) {
            int x = b[j];
            if(x == lo) {
                ++lo;
                ++hi;
            } else if(x == hi) {
                ++hi;
            } 
        }
        dp[lo] += hi - lo;
        sum += lo;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        auto& b = a[i];
        ans += 1LL * (sum - mex[i]) * (n - 1) * (b.size() - 1);
        for(int j = 1, k = 1; j < b.size(); j = k) {
            while(k < b.size() && b[k] == b[j]) {
                k++;
            }
            int cnt = k - j;
            if(dp.contains(b[j])) {
                ans += 1LL * dp[b[j]] * cnt;
            }
            if(cnt >= 2) {
                ans += 1LL * mex[i] * (n - 1) * cnt;
            } else {
                ans += 1LL * min(mex[i], b[j]) * (n - 1);
            }
        }
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
