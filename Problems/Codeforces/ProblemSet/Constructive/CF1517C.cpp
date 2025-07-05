#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        int x = i, y = i, cnt = p[i];
        while(cnt) {
            if(x > n || a[x][y]) {
                cout << -1 << "\n";
                return;
            }
            a[x][y] = p[i];
            int nx = x, ny = y - 1;
            if(ny < 1 || a[nx][ny]) nx = x + 1, ny = y;
            x = nx, y = ny;
            cnt--;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            cout << a[i][j] << " \n"[j == i];
        }
    }
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

