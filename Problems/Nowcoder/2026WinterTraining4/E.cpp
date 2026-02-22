#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int pre[10][10][10][1 << 10][82];
PII ans[10][10][82];

void init(int m) {  
    int n = 9, k = n * m;

    const int N = m + 1;

    vector<vector<int>> dp(1 << N, vector<int>(k + 1, -inf));
    dp[0][0] = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            vector<vector<int>> ndp(1 << N, vector<int>(k + 1, -inf));
            for(int s = 0; s < 1 << N; s++) {
                for(int p = 0; p <= k; p++) {

                    if(dp[s][p] < 0) continue;
                    array<int,2> c {};

                    int t;
                    if(i > 0 && j + 1 < m) {
                        t = s >> (m - 2) & 1;
                        c[t]++;
                    }
                    if(i > 0) {
                        t = s >> (m - 1) & 1;
                        c[t]++;
                    }
                    if(i > 0 && j > 0) {
                        t = s >> m & 1;
                        c[t]++;
                    }
                    if(j > 0) {
                        t = s & 1;
                        c[t]++;
                    }

                    int ns = (s << 1) & ((1 << N) - 1);

                    if(dp[s][p] + c[1] > ndp[ns][p]) {
                        ndp[ns][p] = dp[s][p] + c[1];
                        pre[m][i][j][ns][p] = s;
                    }

                    if(p + 1 <= k) {
                        ns |= 1;

                        if(dp[s][p] + c[0] > ndp[ns][p + 1]) {
                            ndp[ns][p + 1] = dp[s][p] + c[0];
                            pre[m][i][j][ns][p + 1] = s;
                        }
                    }

                }
            }

            dp = move(ndp);

            if(j == m - 1) {
                for(int p = 0; p <= k; p++) {
                    int v = -1, s = 0;
                    for(int msk = 0; msk < 1 << N; msk++) {
                        if(dp[msk][p] > v) {
                            s = msk;
                            v = dp[msk][p];
                        } 
                    }  
                    ans[i][j][p] = {v, s};
                }
            }
        }
    }

};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    auto [v, s] = ans[n - 1][m - 1][k];

    cout << v << "\n";

    vector<vector<char>> a(n, vector<char>(m));
    for(int i = n - 1; i >= 0; i--) {
        for(int j = m - 1; j >= 0; j--) {
            a[i][j] = (s & 1) ? '*' : '.';
            int ns = pre[m][i][j][s][k];
            if(s & 1) {
                k--;
            }
            s = ns;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << a[i][j];
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= 9; i++) {
        init(i);
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
