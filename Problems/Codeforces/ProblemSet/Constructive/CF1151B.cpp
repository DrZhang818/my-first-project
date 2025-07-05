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
            cin >> a[i][j];
        }
    }
    for(int s = 0; s < 10; s++) {
        vector<int> ans(n + 1);
        int c1 = 0, c01 = 0;
        for(int i = 1; i <= n; i++) {
            int cnt = 0;
            for(int j = 1; j <= m; j++) {
                if(a[i][j] >> s & 1) {
                    cnt++;
                }
            }
            if(cnt == m) c1++, ans[i] = 1;
            else if(cnt != 0) c01++;
        }
        if(c01 || c1 % 2) {
            cout << "TAK\n";
            for(int i = 1; i <= n; i++) {
                if(ans[i]) continue;
                for(int j = 1; j <= m; j++) {
                    int o = a[i][j] >> s & 1;
                    if(c1 % 2 && o == 0) {
                        ans[i] = j;
                        break;
                    } else if(c1 % 2 == 0 && o == 1) {
                        ans[i] = j;
                        c1++;
                        break;
                    }
                }
                if(!ans[i]) ans[i] = 1;
            }
            for(int i = 1; i <= n; i++) {
                cout << ans[i] << " \n"[i == n];
            }
            return;
        }
    }
    cout << "NIE\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
