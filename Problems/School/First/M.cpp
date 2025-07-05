#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> ans(n + 1);
    vector<vector<int>> a(n + 1, vector<int>(n));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n - 1; j++) {
            cin >> a[i][j];
        }
    }
    int p1 = -1, p2 = -1, c1 = 0, c2 = 0;
    for(int i = 1; i <= n; i++) {
        if(p1 == -1 || a[i][1] == p1) {
            p1 = a[i][1];
            c1++;
        } else if(a[i][1] != p1) {
            p2 = a[i][1];
            c2++;
        }
    }
    if(c1 > c2) {
        ans[1] = p1;
        ans[2] = p2;
    } else {
        ans[1] = p2;
        ans[2] = p1;
    }
    for(int j = 2; j <= n - 1; j++) {
        for(int i = 1; i <= n; i++) {
            if(a[i][j] != ans[j]) {
                ans[j + 1] = a[i][j];
                break;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
