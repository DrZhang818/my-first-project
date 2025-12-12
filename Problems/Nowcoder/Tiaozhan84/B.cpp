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
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    ll ans = 0;
    for(int j = 1; j <= m; j++) {
        int c1 = 0, c2 = 0, c3 = 0;
        for(int i = 1; i <= n; i++) {
            if(a[i][j] == 0) {
                c1++;
            } else if(a[i][j] == 1) {
                c2++;
            } else {
                c3++;
            }
        }
        ans += n;
        if(c1 > c2 + c3) {
            ans += 2 * c1 * (c2 + c3);
        } else if(c2 > c1 + c3) {
            ans += 2 * c2 * (c1 + c3);
        } else {
            ans += 2 * (n / 2) * (n - n / 2);
        }
    }
    cout << ans << "\n";
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
