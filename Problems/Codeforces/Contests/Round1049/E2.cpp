#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;
    vector<int> a(k);
    for(int i = 0; i < k; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> dp;
    for(int i = 1; i <= n; i++) {
        vector<int> ndp(1 << i);
        int tag = (i % 2) == (n % 2);
        for(int s = 0; s < 1 << i; s++) {
            if(i == 1) {
                if(s == 0) {
                    ndp[s] = 0;
                } else {
                    ndp[s] = 1;
                }   
            } else {        
                ndp[s] = tag ^ 1;
                for(int j : a) {
                    if(j >= i) {
                        break;
                    }        
                    int ns = (s >> j + 1 << j) | (s & ((1 << j) - 1));
                    if(tag) {
                        ndp[s] |= dp[ns];
                    } else {
                        ndp[s] &= dp[ns];
                    }       
                }
            }       
        }   
        swap(dp, ndp);
    }   

    vector<int> cnt(n + 1);
    for(int s = 0; s < 1 << n; s++) {
        if(dp[s]) {
            cnt[__builtin_popcount(s)] += 1;
        }
    }   

    int ans = 0;

    for(int i = 1; i <= m; i++) {
        vector<int> pw1(n + 1, 1), pw2(n + 1, 1);
        for(int j = 1; j <= n; j++) {
            pw1[j] = 1LL * pw1[j - 1] * (i - 1) % MOD;
            pw2[j] = 1LL * pw2[j - 1] * (m - i + 1) % MOD;
        }
        for(int j = 1; j <= n; j++) {
            add(ans, 1LL * pw1[n - j] * pw2[j] % MOD * cnt[j] % MOD);
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
