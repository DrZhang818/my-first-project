#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> c(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        int l = 0, r = 0, cnt = 0;
        for(int r = 0; r < m; r++) {
            while(l < m && a[i][l] == '#') l++;
            if(l >= m) break;
            if(a[i][r] == '.') {
                cnt++;
            } else {
                for(int j = l; j < r; j++) {
                    c[i][j] += cnt;
                }
                cnt = 0;
                l = r + 1;
            }
        }
        if(a[i][m - 1] == '.') {
            for(int j = l; j <= m - 1; j++) {
                c[i][j] += cnt;
            }
        }
    }    
    int ans = 0;
    for(int j = 0; j < m; j++) {
        int l = 0, r = 0, cnt = 0;
        for(int r = 0; r < n; r++) {
            while(l < n && a[l][j] == '#') l++;
            if(l >= n) break;
            if(a[r][j] == '.') {
                cnt++;
            } else {
                for(int i = l; i < r; i++) {
                    c[i][j] += cnt;
                }
                cnt = 0;
                l = r + 1;
            }
        }
        if(a[n - 1][j] == '.') {
            for(int i = l; i <= n - 1; i++) {
                c[i][j] += cnt;
            }
        }
    }    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ans = max(ans, c[i][j] - 1);
        }
    }
    cout << ans << "\n";

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

