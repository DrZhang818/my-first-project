#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    int mx = 0;
    vector<bool> vis(n + 1);
    for(int i = 1; i <= m; i++) {
        int c = 0;
        for(int j = 1; j <= n; j++) {
            string s;
            cin >> s;
            if(s == a[j]) c++, vis[j] = true;
        }
        mx = max(mx, c);
    }
    for(int i = 1; i <= n; i++) {
        if(vis[i] == 0) {
            cout << -1 << "\n";
            return;
        }
    }
    cout << mx + 3 * (n - mx) << "\n";
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
    
