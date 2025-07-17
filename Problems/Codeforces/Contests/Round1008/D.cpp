#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

//https://codeforces.com/contest/2078/problem/D
struct info {
    char op1, op2;
    int x, y;
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].op1 >> a[i].x >> a[i].op2 >> a[i].y;
    }
    vector<ll> dp1(2), dp2(2);
    dp1[0] = dp1[1] = dp2[0] = dp2[1] = 1;
    for(int i = n; i >= 1; i--) {
        auto ndp1 = dp1;
        auto ndp2 = dp2;
        auto [op1, op2, x, y] = a[i];
        ll mx = 0;
        if(op1 == 'x') {
            x--;
        } 
        mx = x * max(dp2[0], dp2[1]);
        ndp1[0] += mx;
        if(op1 == 'x') ndp2[0] += mx;

        mx = 0;
        if(op2 == 'x') {
            y--;
        } 
        mx = y * max(dp2[0], dp2[1]);
        ndp1[1] += mx;
        if(op2 == 'x') ndp2[1] += mx;
        mx = 0;

        dp1 = ndp1;
        dp2 = ndp2;
    }
    ll ans = dp1[0] + dp1[1];
    cout << ans << "\n";
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
    
