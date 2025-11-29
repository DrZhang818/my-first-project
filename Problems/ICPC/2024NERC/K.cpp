#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void chmin(ll &x, ll y) {
    if(x > y) {
        x = y;
    }
}

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> X{inf}, Y{inf};
    vector<int> p{0}, q{0};
    vector<ll> preX{0}, preY{0};
    for(int i = n; i >= 1; i--) {
        int g = gcd(i, a);
        preX.push_back(g);
        if(i == 1 || g < X.back()) {
            X.push_back(g);
            p.push_back(i);
        }
        g = gcd(i, b);
        preY.push_back(g);
        if(i == 1 || g < Y.back()) {
            Y.push_back(g);
            q.push_back(i);
        }
    }
    reverse(X.begin() + 1, X.end());
    reverse(Y.begin() + 1, Y.end());
    reverse(p.begin() + 1, p.end());
    reverse(q.begin() + 1, q.end());
    reverse(preX.begin() + 1, preX.end());
    reverse(preY.begin() + 1, preY.end());
    for(int i = 1; i <= n; i++) {
        preX[i] += preX[i - 1];
        preY[i] += preY[i - 1];
    }
    n = X.size() - 1;
    int m = Y.size() - 1;
    vector dp(n + 1, vector<ll>(m + 1, ll(1E18)));
    dp[0][1] = dp[1][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            chmin(dp[i][j], dp[i - 1][j] + preX[p[i]] - preX[p[i - 1]] + 1LL * Y[j] * (p[i] - p[i - 1]));
            chmin(dp[i][j], dp[i][j - 1] + preY[q[j]] - preY[q[j - 1]] + 1LL * X[i] * (q[j] - q[j - 1]));
        }
    }
    cout << dp[n][m] << "\n";    
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
