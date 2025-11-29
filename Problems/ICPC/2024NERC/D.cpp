#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<map<int,int>> dp(n + 1), psum(n + 1);
    dp[0][-1] = 1, psum[0][-1] = 1;
    for(int i = 1; i <= n; i++) {
        int cur = a[i];
        int x = -1;
        for(int j = i - 1; j >= 0; j--) {
            auto it = psum[j].upper_bound(cur);
            if(it != psum[j].begin()) {
                it = prev(it);
                add(dp[i][cur], it->second);
            }
            if((a[j] | a[i]) == a[j]) {
                x = a[j];
                break;
            }
            a[j] |= a[i];
            cur = a[j];
        }
        if(x != -1) {
            for(auto &[y, c] : dp[i - 1]) {
                if(y >= x) {
                    add(dp[i][y], c);
                }
            }
        }
        int S = 0;
        for(auto &[y, c] : dp[i]) {
            add(S, c);
            psum[i][y] = S;
        }
    }
    int ans = psum[n].rbegin()->second;
    cout << ans << "\n";
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
