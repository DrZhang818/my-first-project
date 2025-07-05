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
    int mx = -inf, tot = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            mx = max(mx, a[i][j]);
        }
    }
    vector<int> c0(n + 1), c1(m + 1);
    for(int i = 1; i <= n; i++) {
        int c = 0;
        for(int j = 1; j <= m; j++) {
            c += a[i][j] == mx;
            if(a[i][j] == mx) tot += 1;
        }
        c0[i] = c;
    }
    for(int j = 1; j <= m; j++) {
        int c = 0;
        for(int i = 1; i <= n; i++) {
            c += a[i][j] == mx;
        }
        c1[j] = c;
    }
    int ans = mx;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int c = c0[i] + c1[j] - (a[i][j] == mx);
            if(c == tot) {
                ans = mx - 1;
            }
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
