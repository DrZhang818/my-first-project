#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;
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
    vector dp(n + 1, vector(n + 1, vector<int>(n + 1)));
    vector<int> ans(n + 1);
    ans[1] = n;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            dp[i][j][2] = 1;
        }
    }
    for(int len = 2; len < n; len++) {
        for(int i = 3; i <= n; i++) {
            for(int j = 2; j < i; j++) {
                for(int k = 1; k < j; k++) {
                    if(a[i] - a[j] == a[j] - a[k]) {
                        add(dp[j][i][len + 1], dp[k][j][len]);
                    }
                }
            }
        }
    }
    for(int len = 2; len <= n; len++) {
        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                add(ans[len], dp[i][j][len]);
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
