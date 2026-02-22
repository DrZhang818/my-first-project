#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));

    int tot = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            tot += (a[i][j] == 1);
        }
    }

    vector<vector<int>> suf_row(n + 2, vector<int>(m + 2));
    vector<vector<int>> suf_col(n + 2, vector<int>(m + 2));

    for(int i = 1; i <= n; i++) {
        suf_row[i][m] = (a[i][m] == 1);
        for(int j = m - 1; j >= 1; j--) {
            suf_row[i][j] = suf_row[i][j + 1] + (a[i][j] == 1);
        }
    }

    for(int j = 1; j <= m; j++) {
        suf_col[n][j] = (a[n][j] == 1);
        for(int i = n - 1; i >= 1; i--) {
            suf_col[i][j] = suf_col[i + 1][j] + (a[i][j] == 1);
        }
    }

    int tar = tot / 2;

    int x = 0, y = 0;
    int up = 0, down = 0;

    string ans;

    while(x != n || y != m) {
        if(y < m && down + suf_col[x + 1][y + 1] <= tar) {
            ans += "R";
            down += suf_col[x + 1][y + 1];
            y++;
        } else {
            ans += "D";
            up += suf_row[x + 1][y + 1];
            x++;
        }
    }

    cout << 1LL * up * down << "\n";
    cout << ans << "\n";
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
