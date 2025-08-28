#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    vector a(n + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    string s;
    cin >> s;
    for(char c : s) {
        int nx = x, ny = y;
        if(c == 'L') {
            ny--;
        } else if(c == 'R') {
            ny++;
        } else if(c == 'U') {
            nx--;
        } else {
            nx++;
        }
        if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == '#') {
            continue;
        }
        x = nx;
        y = ny;
    }
    cout << x << " " << y << "\n";
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
