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
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    int umx = -inf, vmx = -inf, umn = inf, vmn = inf;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 'B') {
                umx = max(umx, i + j);
                umn = min(umn, i + j);
                vmx = max(vmx, i - j);
                vmn = min(vmn, i - j);
            }
        }
    }
    int mn = inf, x = -1, y = -1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int u = i + j, v = i - j;
            u = max(abs(u - umn), abs(u - umx));
            v = max(abs(v - vmn), abs(v - vmx));
            if(max(u, v) < mn) {
                mn = max(u, v);
                x = i, y = j;
            }
        }
    }
    cout << x << " " << y << "\n";
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
