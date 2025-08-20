#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, h, m;
    cin >> n >> h >> m;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<int> dp(h + 1, -1);
    dp[h] = m;
    for(int i = 1; i <= n; i++) {
        bool ok = false;
        for(int j = 0; j <= h; j++) {
            if(dp[j] == -1) continue;
            if(j >= a[i]) {
                dp[j - a[i]] = max(dp[j - a[i]], dp[j]);
                ok = true;
            }
            if(dp[j] >= b[i]) {
                dp[j] -= b[i];
                ok = true;
            } else {
                dp[j] = -1;
            }
        }
        if(!ok) {
            cout << i - 1 << "\n";
            return;
        }
    }
    cout << n << "\n";
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
