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
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<ll> dp(2 * n + 1);
    vector<int> pos(n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        int x = a[i];
        if(pos[x]) {
            dp[i] = max(dp[i - 1], dp[pos[x] - 1] + pre[i] - pre[pos[x] - 1]);
        } else {
            dp[i] = dp[i - 1];
        }
        pos[x] = i;
    }
    cout << dp[2 * n] << "\n";
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
