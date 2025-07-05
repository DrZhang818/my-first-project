#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    //j = i + m - s
    for(int s = 1; s < n + m; s++) {
        int minJ = max(1, m - s + 1);
        int maxJ = min(m, m - s + n);
        for(int j = minJ; j <= maxJ; j++) {
            int i = j - m + s;
            cout << a[i][j] << " \n"[j == maxJ];
        }
    }
    //j  = s + 1 - i
    for(int s = 1; s < n + m; s++) {
        int minj = max(1, s + 1 - n);
        int maxj = min(m, s);
        for(int j = minj; j <= maxj; j++) {
            int i = s + 1 - j;
            cout << a[i][j] << " \n"[j == maxj];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
