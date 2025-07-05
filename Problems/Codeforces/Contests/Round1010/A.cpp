#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<string> inp(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> inp[i];
    }
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < m; j++) {
            a[i][j + 1] = inp[i][j] - '0';
        }
    }
    int ans = 0;
    int c1 = 0, c2 = 0;
    for(int i = 1; i <= n; i++) {
        int s = 0;
        for(int j = 1; j <= m; j++) {
            s ^= a[i][j];
        }
        if(s) c1++;
    }
    for(int j = 1; j <= m; j++) {
        int s = 0;
        for(int i = 1; i <= n; i++) {
            s ^= a[i][j];
        }
        if(s) c2++;
    }
    cout << max(c1, c2) << "\n";
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
    
