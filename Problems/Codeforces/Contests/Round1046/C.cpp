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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> pos(n + 1);
    vector<int> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        int x = a[i];
        pos[x].push_back(i);
        int sz = pos[x].size();
        if(sz < x) {
            continue;
        }
        int j = pos[x][sz - x];
        dp[i] = max(dp[i], dp[j - 1] + x);
    }
    cout << dp[n] << "\n";
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
