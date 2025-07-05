#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m, h;
    cin >> n >> m >> h;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    int mx = 0, x = -1, y = -1, ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] != 0) continue;
            int cnt = 0;
            for(int k = j; k >= 1; k--) {
                if(a[i][k] >= h) break;
                if(a[i][k] < 0) cnt++;
            }
            for(int k = j; k <= m; k++) {
                if(a[i][k] >= h) break;
                if(a[i][k] < 0) cnt++;
            }
            for(int k = i; k >= 1; k--) {
                if(a[k][j] >= h) break;
                if(a[k][j] < 0) cnt++;
            }
            for(int k = i; k <= n; k++) {
                if(a[k][j] >= h) break;
                if(a[k][j] < 0) cnt++;
            }
            if(cnt > mx) { mx = cnt, x = i, y = j; }
            if(cnt >= 3) { ans++; }
        }
    }
    cout << ans << "\n";
    cout << x - 1 << " " << y - 1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
