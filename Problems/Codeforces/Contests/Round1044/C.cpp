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
    vector<vector<int>> dp(n + 1);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        cout << "? " << i << " " << n;
        for(int j = 1; j <= n; j++) {
            cout << " " << j;
        }
        cout << endl;
        int x;
        cin >> x;
        dp[x].push_back(i);
        mx = max(mx, x);
    }
    vector<int> ans;
    for(int i = mx - 1, cur = dp[mx][0]; i >= 0; i--) {
        ans.push_back(cur);
        for(int v : dp[i]) {
            cout << "? " << cur << " " << 2 << " " << cur << " " << v << endl;
            int x;
            cin >> x;
            if(x != 1) {
                cur = v;
                break;
            }
        }
    }
    cout << "! " << mx;
    for(int x : ans) {
        cout << " " << x;
    }
    cout << endl;
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
