#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

bool ck(char c) {
    return c == '.' || c == '?';
}
void solve() {
    int n, m;
    cin >> n >> m;
    int dir[5] = {-1, 0, 1, 0, -1};
    vector<vector<char>> a(n + 2, vector<char>(m + 2, '*'));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    bool ok = true;
    for(int i = 1; i <= n && ok; i++) {
        for(int j = 1; j <= m && ok; j++) {
            char c = a[i][j];
            if(c == '.') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int i = 1; i <= n && ok; i++) {
        for(int j = 1; j <= m && ok; j++) {
            char c = a[i][j];
            if(c == '?') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int i = 1; i <= n && ok; i++) {
        for(int j = m; j >= 1 && ok; j--) {
            char c = a[i][j];
            if(c == '?') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int i = n; i >= 1 && ok; i--) {
        for(int j = 1; j <= m && ok; j++) {
            char c = a[i][j];
            if(c == '?') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int i = n; i >= 1 && ok; i--) {
        for(int j = m; j >= 1 && ok; j--) {
            char c = a[i][j];
            if(c == '?') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int j = 1; j <= m && ok; j++) {
        for(int i = 1; i <= n && ok; i++) {
            char c = a[i][j];
            if(c == '?') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int j = m; j >= 1 && ok; j--) {
        for(int i = 1; i <= n && ok; i++) {
            char c = a[i][j];
            if(c == '?') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int j = 1; j <= m && ok; j++) {
        for(int i = n; i >= 1 && ok; i--) {
            char c = a[i][j];
            if(c == '?') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int j = m; j >= 1 && ok; j--) {
        for(int i = n; i >= 1 && ok; i--) {
            char c = a[i][j];
            if(c == '?') {
                bool ok1 = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(ck(a[nx][ny])) ok1 = true;
                }
                if(!ok1) {
                    ok = false;
                    break;
                }
                if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = '<';
                    a[i][j+1] = '>';
                } else if(!ck(a[i-1][j]) && !ck(a[i][j-1]) && !ck(a[i][j+1])) {
                    a[i][j] = '^';
                    a[i+1][j] = 'v';
                } else if(!ck(a[i][j+1]) && !ck(a[i-1][j]) && !ck(a[i+1][j])) {
                    a[i][j] = '>';
                    a[i][j-1] = '<';
                } else if(!ck(a[i][j+1]) && !ck(a[i][j-1]) && !ck(a[i+1][j])) {
                    a[i][j] = 'v';
                    a[i-1][j] = '^';
                } else {
                    a[i][j] = '?';
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == '?') {
                ok = false;
            }
        }
    }
    if(!ok) {
        cout << "Not unique\n";
        return ;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << a[i][j];
        }
        cout << "\n";
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
