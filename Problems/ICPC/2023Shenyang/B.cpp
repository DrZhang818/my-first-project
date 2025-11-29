#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll k;
void add(ll &x, ll y) {
    x = min(x + y, k + 1);  
}

void solve() {
    int n;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<bool> used(n + 1);
    
    auto cal = [&](int m) -> ll {
        vector dp(n + 1, vector<array<ll,2>>(n + 1));
        dp[1][1][0] = dp[1][1][1] = 1;
        int fixed = 0;
        for(int j = 1; j <= m; j++) {
            fixed += a[j] == 1;
        }
        for(int i = 1; i < n; i++) {
            int rk = -1;
            for(int j = 1; j <= m; j++) {
                if(a[j] == i + 1) {
                    rk = 1;
                    fixed++;
                    for(int k = 1; k < j; k++) {
                        if(a[k] < i + 1) {
                            rk++;
                        }
                    }
                    break;
                }
            }
            for(int j = 1; j <= i; j++) {
                for(int k = 1; k <= j; k++) {
                    if(rk == -1 && k > fixed || rk == k) {
                        add(dp[i + 1][k][1], dp[i][j][0]);
                    }
                }
                for(int k = j + 1; k <= i + 1; k++) {
                    if(rk == -1 && k > fixed || rk == k) {
                        add(dp[i + 1][k][0], dp[i][j][1]);
                    }
                }
            }
        }
        ll ans = 0;
        for(int j = 1; j <= n; j++) {
            add(ans, dp[n][j][0]);
            add(ans, dp[n][j][1]);
        }
        return ans;
    };

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!used[j]) {
                a[i] = j;
                ll cur = cal(i);
                if(cur < k) {
                    k -= cur;
                } else {
                    used[j] = true;
                    break;
                }
            }
        }
        if(!used[a[i]]) {
            cout << -1 << "\n";
            return;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
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
