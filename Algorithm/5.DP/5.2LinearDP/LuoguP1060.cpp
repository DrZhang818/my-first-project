#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> c(m + 1), w(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> c[i] >> w[i];
        w[i] *= c[i];
    }    
    vector<int> dp(n + 1);
    for(int i = 1; i <= m; i++) {
        for(int j = n; j >= c[i]; j--) {
            dp[j] = max(dp[j], dp[j - c[i]] + w[i]);
        }
    }
    cout << dp[n] << "\n";
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
