#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n, d;
    cin >> n >> d;
    vector<vector<int>> a(n, vector<int>(d));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < d; j++) {
            cin >> a[i][j];
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            db cur = 0;
            for(int k = 0; k < d; k++) {
                cur += (a[i][k] - a[j][k]) * (a[i][k] - a[j][k]);
            }
            cur = sqrt(cur);
            if(cur - (int)cur < 1e-5) ans++;
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

