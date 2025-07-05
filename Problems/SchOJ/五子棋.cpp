#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int n = 19;
void solve() { 
    vector<vector<int>> a(n + 2, vector<int>(n + 2, -1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        int c1 = 0, c2 = 0;
        for(int j = 1; j <= n; j++) {
            c1 = a[i][j] == 1 ? c1 + 1 : 0;
            c2 = a[i][j] == 2 ? c2 + 1 : 0;
            if((c1 == 4 || c2 == 4) && (a[i][j - 4] == 0 || a[i][j + 1] == 0)) {
                cout << (c1 == 4 ? 1 : 2) << ":" << i << "," << j - 3 << "\n";
                return;
            }
        }
    }
    for(int j = 1; j <= n; j++) {
        int c1 = 0, c2 = 0;
        for(int i = 1; i <= n; i++) {
            c1 = a[i][j] == 1 ? c1 + 1 : 0;
            c2 = a[i][j] == 2 ? c2 + 1 : 0;
            if((c1 == 4 || c2 == 4) && (a[i - 4][j] == 0 || a[i + 1][j] == 0)) {
                cout << (c1 == 4 ? 1 : 2) << ":" << i - 3 << "," << j << "\n";
                return;
            }
        }
    }

    for(int k = 1; k < 2 * n; k++) {
        int minJ = max(1, n - k + 1);
        int maxJ = min(n, 2 * n - k);
        int c1 = 0, c2 = 0;
        for(int j = minJ; j <= maxJ; j++) {
            int i = k + j - n;  
            c1 = a[i][j] == 1 ? c1 + 1 : 0;
            c2 = a[i][j] == 2 ? c2 + 1 : 0;
            if((c1 == 4 || c2 == 4) && (a[i - 4][j - 4] == 0 || a[i + 1][j + 1] == 0)) {
                cout << (c1 == 4 ? 1 : 2) << ":" << i - 3 << "," << j - 3 << "\n";
                return;
            }
        }
    }
    for(int k = 1; k < 2 * n; k++) {
        int minJ = max(1, k - n + 1);
        int maxJ = min(n, k);
        int c1 = 0, c2 = 0;
        for(int j = maxJ; j >= minJ; j--) {
            int i = k - j + 1;
            c1 = a[i][j] == 1 ? c1 + 1 : 0;
            c2 = a[i][j] == 2 ? c2 + 1 : 0;
            if((c1 == 4 || c2 == 4) && (a[i - 4][j + 4] == 0 || a[i + 1][j - 1] == 0)) {
                cout << (c1 == 4 ? 1 : 2) << ":" << i - 3 << "," << j + 3 << "\n";
                return;
            }
        }
    }
    cout << "No\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
