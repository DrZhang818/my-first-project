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
    string T;
    cin >> T;
    vector<int> dp(1 << n);
    dp[0] = 1;
    for(int s = 1; s < 1 << n; s++) {
        char pre = '#';
        for(int i = 0; i < n; i++) {
            if(~s >> i & 1) {
                continue;
            }
            if(T[i] == pre) {
                continue;
            }
            pre = T[i];
            int t = s ^ (1 << i);
            add(dp[s], dp[t]);
        }
    }
    cout << dp[(1 << n) - 1] << "\n";
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
