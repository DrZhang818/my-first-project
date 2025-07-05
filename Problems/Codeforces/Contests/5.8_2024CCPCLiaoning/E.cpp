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
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    int cnt = 1;
    if(n < 4 && m < 4 || n % 2 && m % 2) {
        cout << "NO\n";
    } else if(n % 4 == 0 || m % 4 == 0) {
        cout << "YES\n";
        if(n % 4 == 0) {
            for(int j = 1; j <= m; j++) {
                for(int i = 1; i <= n; i++) {
                    a[i][j] = cnt;
                    if(i % 4 == 0) cnt++;
                }
            }
        } else {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++) {
                    a[i][j] = cnt;
                    if(j % 4 == 0) cnt++;
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                cout << a[i][j] << " \n"[j == m];
            }
        }
    } else if(n % 2 == 0 && m % 2 == 0) {
        cout << "YES\n";
        if(m >= n) {
            for(int i = 1; i <= n; i++) {
                if(i & 1) {
                    a[i][1] = a[i][2] = a[i][3] = a[i + 1][1] = cnt++;
                    a[i][m] = a[i][m - 1] = a[i][m - 2] = a[i + 1][m] = cnt++;
                    for(int j = 4; j <= m - 3; j++) {
                        a[i][j] = cnt;
                        if(j % 4 == 3) cnt++;
                    }
                } else {
                    for(int j = 2; j <= m - 1; j++) {
                        a[i][j] = cnt;
                        if(j % 4 == 1) cnt++;
                    }
                }
            }
        } else {
            for(int j = 1; j <= m; j++) {
                if(j & 1) {
                    a[1][j] = a[2][j] = a[3][j] = a[1][j + 1] = cnt++;
                    a[n][j] = a[n - 1][j] = a[n - 2][j] = a[n][j + 1] = cnt++;
                    for(int i = 4; i <= n - 3; i++) {
                        a[i][j] = cnt;
                        if(i % 4 == 3) cnt++;
                    }
                } else {
                    for(int i = 2; i <= n - 1; i++) {
                        a[i][j] = cnt;
                        if(i % 4 == 1) cnt++;
                    }
                }
            }           
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                cout << a[i][j] << " \n"[j == m];
            }
        }
    } else {
        cout << "NO\n";
    }
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
