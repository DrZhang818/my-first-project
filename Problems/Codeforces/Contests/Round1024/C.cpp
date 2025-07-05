#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


int dir[5] = {0, 1, 0, -1, 0};
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    int cur = 0, num = n * n - 1;
    int x = 1, y = 1;
    while(num >= 0) {
        a[x][y] = num--;
        int nx = x + dir[cur], ny = y + dir[cur + 1];
        if(nx < 1 || ny < 1 || nx > n || ny > n || a[nx][ny]) {
            cur = (cur + 1) % 4;
        }
        x = x + dir[cur], y = y + dir[cur + 1];
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << a[i][j] << " \n"[j == n];
        }
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
