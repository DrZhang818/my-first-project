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
    string t;
    cin >> t;
    t = '#' + t;
    vector<int> dp(1 << n);
    dp[0] = 1;
    for(int s = 0; s < 1 << n; s++) {
        if(!dp[s]) continue;
        for(int i = 0; i < n; i++) {
            if(s >> i & 1) continue;
            if(t[s | 1 << i] == '1') continue;
            dp[s | 1 << i] = 1;
        }
    }
    if(dp[(1 << n) - 1]) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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
