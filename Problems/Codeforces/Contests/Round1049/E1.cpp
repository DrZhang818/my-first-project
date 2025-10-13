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
    if(m == 1) {
        cout << 1 << "\n";
        return;
    }
    int ans = 0;
    vector<int> dp;
    for(int i = 1; i <= n; i++) {
        int tag = (i % 2) == (n % 2);
        vector<int> ndp(1 << i);
        for(int s = 0; s < 1 << i; s++) {
            if(i == 1) {
                if(s == 0) {
                    ndp[s] = 1;
                } else {
                    ndp[s] = 2;
                }
            } else {
                int mn = inf, mx = -inf;
                for(int j : a) {
                    if(j >= i) {
                        break;
                    }
                    int ns = (s >> j + 1 << j) | (s & ((1 << j) - 1));
                    mn = min(mn, dp[ns]);
                    mx = max(mx, dp[ns]);
                }
                if(tag) {
                    ndp[s] = mx;
                } else {
                    ndp[s] = mn;
                }
            }
            if(i == n) {
                ans += ndp[s];
                if(ndp[s] == 2) {
                    cout << bitset<12>(s) << " " << ndp[s] << "\n";
                }
            }
        }
        swap(dp, ndp);
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
