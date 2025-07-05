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
    vector<vector<char>> a(n + 2, vector<char>(m + 2, '*'));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector<bool> vis;
    for(int p = 0; p < 3; p++) {
        vis.assign(m + 1, false);
        for(int i = 1; i <= n; i++) {
            int l = 1, r = 1, ok = 0;
            for(int j = 1; j <= m; j++) {
                if(vis[j]) {
                    if(!ok) l = j, ok = true;
                    r = j;
                } else {
                    if(ok) {
                        bool have = false;
                        for(int k = l; k <= r; k++) {
                            if(a[i][k] == '.') {
                                have = true;
                                break;
                            }
                        }
                        if(have) {
                            for(int k = l; k <= r; k++) {
                                a[i][k] = '.';
                            }
                        }
                    }
                    ok = false;
                }
            }
            if(ok) {
                bool have = false;
                for(int k = l; k <= r; k++) {
                    if(a[i][k] == '.') {
                        have = true;
                        break;
                    }
                }
                if(have) {
                    for(int k = l; k <= r; k++) {
                        a[i][k] = '.';
                    }
                }
            }
            for(int j = 1; j <= m; j++) vis[j] = a[i][j] == '.';
        } 
        vis.assign(m + 1, false);
        for(int i = n; i >= 1; i--) {
            int l = 1, r = 1, ok = 0;
            for(int j = 1; j <= m; j++) {
                if(vis[j]) {
                    if(!ok) l = j, ok = true;
                    r = j;
                } else {
                    if(ok) {
                        bool have = false;
                        for(int k = l; k <= r; k++) {
                            if(a[i][k] == '.') {
                                have = true;
                                break;
                            }
                        }
                        if(have) {
                            for(int k = l; k <= r; k++) {
                                a[i][k] = '.';
                            }
                        }
                    }
                    ok = false;
                }
            }
            if(ok) {
                bool have = false;
                for(int k = l; k <= r; k++) {
                    if(a[i][k] == '.') {
                        have = true;
                        break;
                    }
                }
                if(have) {
                    for(int k = l; k <= r; k++) {
                        a[i][k] = '.';
                    }
                }
            }
            for(int j = 1; j <= m; j++) vis[j] = a[i][j] == '.';
        }
        vis.assign(n + 1, false);
        for(int j = 1; j <= m; j++) {
            int l = 1, r = 1, ok = 0;
            for(int i = 1; i <= n; i++) {
                if(vis[i]) {
                    if(!ok) l = i, ok = true;
                    r = i;
                } else {
                    if(ok) {
                        bool have = false;
                        for(int k = l; k <= r; k++) {
                            if(a[k][j] == '.') {
                                have = true;
                                break;
                            }
                        }
                        if(have) {
                            for(int k = l; k <= r; k++) {
                                a[k][j] = '.';
                            }
                        }
                    }
                    ok = false;
                }
            }
            if(ok) {
                bool have = false;
                for(int k = l; k <= r; k++) {
                    if(a[k][j] == '.') {
                        have = true;
                        break;
                    }
                }
                if(have) {
                    for(int k = l; k <= r; k++) {
                        a[k][j] = '.';
                    }
                }
            }
            for(int i = 1; i <= n; i++) vis[i] = a[i][j] == '.';
        }
        vis.assign(n + 1, false);
        for(int j = m; j >= 1; j--) {
            int l = 1, r = 1, ok = 0;
            for(int i = 1; i <= n; i++) {
                if(vis[i]) {
                    if(!ok) l = i, ok = true;
                    r = i;
                } else {
                    if(ok) {
                        bool have = false;
                        for(int k = l; k <= r; k++) {
                            if(a[k][j] == '.') {
                                have = true;
                                break;
                            }
                        }
                        if(have) {
                            for(int k = l; k <= r; k++) {
                                a[k][j] = '.';
                            }
                        }
                    }
                    ok = false;
                }
            }
            if(ok) {
                bool have = false;
                for(int k = l; k <= r; k++) {
                    if(a[k][j] == '.') {
                        have = true;
                        break;
                    }
                }
                if(have) {
                    for(int k = l; k <= r; k++) {
                        a[k][j] = '.';
                    }
                }
            }        
            for(int i = 1; i <= n; i++) vis[i] = a[i][j] == '.';
        }
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
