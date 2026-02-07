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
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vector<vector<int>> d(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        d[i][m] = a[i][m - 1] == '0' ? 0 : 1;
        for(int j = m - 1; j >= 1; j--) {
            d[i][j] = (a[i][j] == '0' ? 1 : 0) ^ (a[i][j - 1] == '0' ? 0 : 1);
        }
    }

    int ans = 0;
    for(int j = 1; j <= m; j++) {
        int c0 = 0, c1 = 0;
        for(int i = 1; i <= n; i++) {
            c0 += d[i][j] == 0;
            c1 += d[i][j] == 1;
        }
        ans += min(c0, c1);
    }
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
