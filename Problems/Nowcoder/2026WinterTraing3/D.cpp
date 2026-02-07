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
    
    vector<vector<PII>> pos(3, vector<PII>(3));
    const auto range = {1, 2};

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
            int x = a[i][j];
            if(x) {
                for(int k : range) {
                    if(pos[x][k].first == 0) {
                        pos[x][k] = {i, j};
                        break;
                    }
                }
            }
        }
    }

    for(int i = 1; i <= n - 1; i++) {
        for(int j = 1; j <= m - 1; j++) {
            if(a[i][j] == 1 && a[i + 1][j + 1] == 1 && a[i][j + 1] == 2 && a[i + 1][j] == 2) {
                cout << "NO\n";
                return;
            }
            if(a[i][j] == 2 && a[i + 1][j + 1] == 2 && a[i][j + 1] == 1 && a[i + 1][j] == 1) {
                cout << "NO\n";
                return;
            }
        }
    }
    
    auto ck = [&](int i, int j) {
        return i == 1 || i == n || j == 1 || j == m;
    };

    int cnt = 0;
    for(int x : range) {
        for(int y : range) {
            cnt += ck(pos[x][y].first, pos[x][y].second);
        }
    }

    if(cnt <= 2) {
        cout << "YES\n";
        return;
    }

    vector<vector<int>> vis(n + 1, vector<int>(m + 1));

    if(cnt == 4) {
        auto [x1, y1] = pos[1][1];
        auto [x2, y2] = pos[1][2];

        while(x1 != x2 || y1 != y2) {
            vis[x1][y1] = true;
            if(y1 == 1 && x1 > 1) {
                x1--;
            } else if(x1 == 1 && y1 < m) {
                y1++;
            } else if(y1 == m && x1 < n) {
                x1++;
            } else if(x1 == n && y1 > 1) {
                y1--;
            }
        }

        int c = 0;
        for(auto [x, y] : pos[2]) {
            if(vis[x][y]) {
                c++;
            }
        }

        if(c == 1) {
            cout << "NO\n"; 
        } else {
            cout << "YES\n";
        }
    } else {
        if(a[1][1] && a[1][2] && a[1][1] != a[1][2] && a[1][2] == a[2][1]) {
            cout << "NO\n";
            return;
        } 
        if(a[1][m] && a[1][m - 1] && a[1][m] != a[1][m - 1] && a[1][m - 1] == a[2][m]) {
            cout << "NO\n";
            return;
        }
        if(a[n][1] && a[n - 1][1] && a[n][1] != a[n - 1][1] && a[n - 1][1] == a[n][2]) {
            cout << "NO\n";
            return;
        }
        if(a[n][m] && a[n][m - 1] && a[n][m] != a[n][m - 1] && a[n][m - 1] == a[n - 1][m]) {
            cout << "NO\n";
            return;
        }
        cout << "YES\n";
    }

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
