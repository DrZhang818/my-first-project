#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int a, b;
    cin >> a >> b;

    vector dp(a + 1, vector(b + 1, array<db, 2> {}));

    for(int i = 0; i <= a; i++) {
        for(int j = 0; j <= b; j++) {
            if(i == 0 && j == 0) continue;
            dp[i][j][0] = db(i) / (i + j) + (j == 0 ? 0 : db(j) / (i + j) * dp[i][j - 1][1]);
            if(i >= 1 && j >= 1) {
                dp[i][j][1] += db(i * j) / ((i + j) * (i + j - 1)) * dp[i - 1][j - 1][0];
            }
            if(j >= 2) {
                dp[i][j][1] += db(j * (j - 1)) / ((i + j) * (i + j - 1)) * dp[i][j - 2][0];
            }
        }
    }

    cout << fixed << setprecision(12) << dp[a][b][0] << "\n";
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
