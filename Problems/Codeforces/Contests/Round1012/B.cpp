#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> b(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++) {
        bool ok = true;
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '0') ok = false;
            b[i][j] |= ok;
        }
    }
    for(int j = 0; j < m; j++) {
        bool ok = true;
        for(int i = 0; i < n; i++) {
            if(a[i][j] == '0') ok = false;
            b[i][j] |= ok;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '1' && !b[i][j]) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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
    
