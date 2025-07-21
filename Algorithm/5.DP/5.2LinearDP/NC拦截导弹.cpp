#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/24213/1012
void solve() {
    vector<int> a{0};
    int x;
    while(cin >> x) {
        a.push_back(x);
    }
    int n = a.size() - 1;
    vector<int> dp(n + 1);
    auto get = [&](int x) -> int {
        int l = 0, r = n + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(dp[mid] >= x) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return l;
    };
    int len = 0;
    for(int i = 1; i <= n; i++) {
        int pos = get(a[i]);
        dp[pos + 1] = max(dp[pos + 1], a[i]);
    }
    for(int i = n; i >= 1; i--) {
        if(dp[i]) {
            cout << i << "\n";
            break;
        }
    }
    for(int i = 1; i <= n; i++) dp[i] = inf;
    for(int i = 1; i <= n; i++) {
        int pos = lower_bound(dp.begin() + 1, dp.end(), a[i]) - dp.begin();
        dp[pos] = min(dp[pos], a[i]);
    }
    for(int i = n; i >= 1; i--) {
        if(dp[i] != inf) {
            cout << i << "\n";
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
