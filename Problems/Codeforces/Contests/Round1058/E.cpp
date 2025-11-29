#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void chmin(int &x, int y) {
    if(x > y) {
        x = y;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    bool tag = false;
    if(n > m) {
        tag = true;
        swap(n, m);
    }
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= (tag ? m : n); i++) {
        string s;
        cin >> s;
        for(int j = 0; j < (tag ? n : m); j++) {
            if(tag) {
                a[j + 1][i] = s[j] - '0';
            } else {
                a[i][j + 1] = s[j] - '0';
            }
        }
    }

    // vector dp(m + 1, vector(n + 1, vector<int>(n + 1, inf)));

    vector<int> dp[m + 1][n + 1];
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j].resize(n + 1, inf);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            vector<int> p;
            for(int k = 1; k <= m; k++) {
                if(a[i][k] == 1 && a[j][k] == 1) {
                    p.push_back(k);
                }
            }
            if(p.size() < 2) {
                continue;
            }

            for(int k = 1; k < p.size(); k++) {
                int x = p[k - 1], y = p[k];
                int S = (j - i + 1) * (y - x + 1);
                for(int o = x; o <= y; o++) {
                    chmin(dp[o][i][j], S);
                }
            }

        }
    }


    vector<vector<int>> ans(n + 1, vector<int>(m + 1));

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(j > 1) {
                for(int k = j; k <= n; k++) {
                    chmin(dp[i][j][k], dp[i][j - 1][k]);
                }
            }
            int cur = inf;
            for(int k = j; k <= n; k++) {
                chmin(cur, dp[i][j][k]);
            }
            if(cur != inf) {
                ans[j][i] = cur;
            }
        }
    }

    if(tag) {
        for(int j = 1; j <= m; j++) {
            for(int i = 1; i <= n; i++) {
                cout << ans[i][j] << " \n"[i == n];
            }
        }
    } else {    
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                cout << ans[i][j] << " \n"[j == m];
            }
        }
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
