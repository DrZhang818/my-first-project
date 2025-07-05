#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    vector<vector<int>> a(6, vector<int>(6));
    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= 5; j++) {
            cin >> a[i][j];
        }
    }
    db ans = 0, extra = 0;
    ll tot = 0, bk = 0;
    for(int i = 1; i <= 5; i++) {
        ll cur = 0;
        for(int j = 1; j <= 5; j++) {
            cur += a[i][j];
        }
        if(i == 1 || i == 4) tot += cur;
        if(i == 2) tot += 2 * cur;
        if(i == 3) tot += 3 * cur;
        if(i == 5) tot += 5 * cur, bk = cur;
    }
    extra = 1.0 / bk;
    db pj = 100.0 / tot;
    for(int i = 1; i <= 4; i++) {
        db cur = 0;
        for(int j = 1; j <= 5; j++) {
            if(j == 1 || j == 2) cur += pj * a[i][j];
            if(j == 3) cur += pj * 0.8 * a[i][j];
            if(j == 4) cur += pj * 0.5 * a[i][j]; 
        }
        if(i == 1 || i == 4) ans += cur;
        if(i == 2) ans += 2 * cur;
        if(i == 3) ans += 3 * cur;
    }
    db cur = 0;
    for(int j = 1; j <= 5; j++) {
        if(j == 1) cur += a[5][j] * (pj * 5 + extra);
        if(j == 2) cur += a[5][j] * (pj * 5 + extra * 0.75);
        if(j == 3) cur += a[5][j] * (pj * 4 + extra * 0.4);
        if(j == 4) cur += a[5][j] * (pj * 5 * 0.5 + extra * 0.3); 
    }
    ans += cur;
    cout << fixed << setprecision(4) << ans << "%\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
