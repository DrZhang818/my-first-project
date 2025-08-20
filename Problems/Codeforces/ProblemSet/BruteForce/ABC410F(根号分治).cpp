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
    vector a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i][j] = c == '#' ? 1 : -1;
        }
    }
    ll ans = 0;
    if(n < m) {
        vector<int> val(m + 1);
        for(int i = 1; i <= n; i++) {
            vector<int> b(m + 1);
            for(int j = i; j >= 1; j--) {
                int pre = 0;
                val[0] = 0;
                for(int k = 1; k <= m; k++) {
                    pre += a[j][k];
                    b[k] += pre;
                    val[k] = b[k];
                }                
                sort(val.begin(), val.end());
                for(int x = 0, y = 0; x <= m; x = y + 1, y = x) {
                    while(y < m && val[y + 1] == val[y]) {
                        y++;
                    }
                    ll cnt = y - x + 1;
                    ans += cnt * (cnt - 1) / 2;
                }
            }
        }
    } else {
        vector<int> val(n + 1);
        for(int i = 1; i <= m; i++) {
            vector<int> b(n + 1);
            for(int j = i; j >= 1; j--) {
                int pre = 0;
                val[0] = 0;
                for(int k = 1; k <= n; k++) {
                    pre += a[k][j];
                    b[k] += pre;
                    val[k] = b[k];
                }
                sort(val.begin(), val.end());
                for(int x = 0, y = 0; x <= n; x = y + 1, y = x) {
                    while(y < n && val[y + 1] == val[y]) {
                        y++;
                    }
                    ll cnt = y - x + 1;
                    ans += cnt * (cnt - 1) / 2;
                }
            }
        }
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
