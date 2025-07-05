#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
int sz, w;
void solve() { 
    vector<string> ss(sz + 1);
    int mx = 0;
    for(int i = 1; i <= sz; i++) {
        cin >> ss[i];
        mx = max(mx, (int)ss[i].size());
    }
    int m = (w + 2) / (mx + 2);
    int n = sz / m, rem = sz - n * m;
    vector<vector<string>> ans(n + 2, vector<string>(m + 1));
    sort(ss.begin() + 1, ss.end());
    int idx = 1;
    for(int j = 1; j <= m; j++) {
        for(int i = 1; i <= n + (j <= rem); i++) {
            ans[i][j] = ss[idx++];
        }
    }
    for(int i = 1; i <= n + (rem != 0); i++) {
        for(int j = 1; j <= m; j++) {
            cout << left << setw(mx) << ans[i][j];
            if(j != m) cout << "  ";
        }
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> sz >> w) {
        for(int i = 0; i < w; i++) {
            cout << "-";
        }
        cout << "\n";
        solve();
    }
    return 0;
}
    
