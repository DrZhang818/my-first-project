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
    int mx = 0;
    vector<int> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        vis[x] = 1;
        mx = max(mx, x);
    }
    int u = bit_width((ull)mx);
    vector<int> dp(mx + 1, (1 << u) - 1);
    dp[0] = 0;
    for(int i = 0; i <= mx; i++) {
        if(vis[i]) {
            dp[i] = i;
        }
    }
    for(int i = 0; i < u; i++) {
        for(int s = 0; s <= mx; s++) {
            s |= 1 << i;
            if(s > mx) break;
            dp[s ^ (1 << i)] &= dp[s];
        }
    }
    int mex = 0;
    for(int i = 0; i <= mx; i++) {
        if(dp[i] == i) {
            mex++;
        } else {
            break;
        }
    }
    cout << mex << "\n";
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
