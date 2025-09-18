#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dir[5] = {-1, 0, 1, 0, -1};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 2, vector<char>(m + 2));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == '#') {
                int cnt = 0;
                for(int k = 0; k < 4; k++) {
                    cnt += a[i + dir[k]][j + dir[k + 1]] == '#';
                }
                if(cnt != 2 && cnt != 4) {
                    cout << "No\n";
                    return;
                }
            }
        }
    }
    cout << "Yes\n";
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
