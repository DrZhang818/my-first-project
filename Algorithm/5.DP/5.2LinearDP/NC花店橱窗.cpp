#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/24213/1005
void solve() {
    int k, n;
    cin >> k >> n;
    vector dp(n + 1, vector<int>(k + 1, -inf));
    vector w(k + 1, vector<int>(n + 1));
    for(int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + w[j][i]);
        }
    }
    cout << dp[n][k] << "\n";
    vector<int> pos(k + 1);
    int c = 0;
    for(int i = k, R = n; i >= 1; i--) {
        int id = 1, mx = -inf;
        for(int j = 1; j <= R; j++) {
            if(dp[j][i] > mx) {
                mx = dp[j][i];
                id = j;
            }
        }
        pos[++c] = id;
        R = id - 1;
    }
    for(int i = c; i >= 1; i--) {
        cout << pos[i] << " \n"[i == 1];
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
