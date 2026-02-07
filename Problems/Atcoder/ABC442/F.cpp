#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<vector<char>> a(n + 1, vector<char>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> pre(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            pre[i][j] = pre[i][j - 1] + (a[i][j] == '#' ? 1 : 0);
        }
    }

    vector<int> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        auto f = dp;
        for(int j = n - 1; j >= 0; j--) {
            f[j] = min(f[j], f[j + 1]);
        }
        auto ndp = dp;
        for(int j = 0; j <= n; j++) {
            ndp[j] = f[j] + pre[i][j] + (n - j - pre[i][n] + pre[i][j]);
        }
        dp = move(ndp);
    }

    cout << *min_element(dp.begin(), dp.end()) << "\n";
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
